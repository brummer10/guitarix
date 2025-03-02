/*
 * ParallelThread.h
 *
 * SPDX-License-Identifier:  BSD-3-Clause
 *
 * Copyright (C) 2024 brummer <brummer@web.de>
 */

/****************************************************************
 ** ParallelThread - class to run a processes in a parallel thread
 *                   requires minimum c++17
 *                   works best with c++20 (std::atomic::wait)
 *
 *  ParallelThread aims to be suitable in real-time processes
 *  to provide a parallel processor.
 *
 *  But ParallelThread could be used in trivial environments,
 *  as worker thread, as well.
 *
 *  usage:
 *      //Create a instance for ParallelThread
 *      ParallelThread proc;
 *      // start the thread
 *      proc.start();
 *      // optional set a name for the thread, default name is "anonymous"
 *         that may be helpful for diagnostics.
 *      proc.setThreadName("YourName");
 *      // optional set the scheduling class and the priority (as int32_t)
 *      proc.setPriority(priority, scheduling_class)
 *      // optional set the timeout value for the waiting functions
 *         in microseconds. Default is 400 micro seconds.
 *         This is a safety guard to avoid dead looks.
 *         When overrun this time, the process will break and data may be lost.
 *         A reasonable value for usage in real-time could be calculated by
 *      proc.setTimeOut(std::max(100,static_cast<int>((bufferSize/(sampleRate*0.000001))*0.1)));
 *      // set the function to run in the parallel thread
 *         function should be defined in YourClass as void YourFunction();
 *      proc.set<YourClass, &YourClass::YourFunction>(*this);
 *      // now anything is setup to run the thread,
 *         so try to get the processing pointer by getProcess()
 *         getProcess() check if the thread is in waiting state, if not,
 *         it waits as max two times the time set by setTimeOut()
 *         so be prepared to run the function in the main process
 *         in case the parallel process is not ready to run.
 *         That is the worst case, and shouldn't happen under normal
 *         circumstances.
 *         if getProcess() return true, runProcess(), otherwise
 *         run the function in the main thread. 
 *      if (proc.getProcess()) proc.runProcess() else functionToRun();
 *      // optional at the point were processed data needs to be merged, 
 *         wait for the data. In case there is no data processed,
 *         or the data is already ready, processWait() returns directly
 *      proc.processWait();
 *         processWait() waits maximal 5 times the timeout. If the
 *         process isn't ready in that time, the data is lost and 
 *         processWait() break to avoid Xruns or dead looks. 
 *         That is the worst case and shouldn't happen 
 *         under normal circumstances.
 *      // Finally stop the thread before exit.
 *      proc.stop(); 
 */

#if defined(_WIN32)
#define MINGW_STDTHREAD_REDUNDANCY_WARNING
#endif

#include <atomic>
#include <cstdint>
#include <unistd.h>
#include <mutex>
#include <thread>
#include <cstring>
#include <ctime>
#include <condition_variable>

#include <pthread.h>

#pragma once

#ifndef PARALLEL_THREAD_H_
#define PARALLEL_THREAD_H_

class ProcessPtr
{ 
public:
    ProcessPtr() {
      set<0, ProcessPtr, &ProcessPtr::dummyFunc>(this);
      set<1, ProcessPtr, &ProcessPtr::dummyFunc>(this);
      i = 0;
      }
 
    template <class C, void (C::*Function)()>
    void set(C* instance) {
        instPtr[i] = instance;
        memberFunc[i] = &wrap<C, Function>;
    }
 
    template <uint32_t s, class C, void (C::*Function)()>
    void set(C* instance) {
        instPtr[s] = instance;
        memberFunc[s] = &wrap<C, Function>;
    }

    void setProcessor(uint32_t i_) {
        i = i_;
    }

    void process() const {
        return memberFunc[i](instPtr[i]);
    }

    void dummyFunc() {}
 
private:
    typedef void* InstancePtr;
    typedef void (*MemberFunc)(InstancePtr);
 
    template <class C, void (C::*Function)()>
    static inline void wrap(InstancePtr instance) {
        return (static_cast<C*>(instance)->*Function)();
    }


    InstancePtr instPtr[2];
    MemberFunc memberFunc[2];
    uint32_t i;
};

class ParallelThread: public ProcessPtr
{
public:
    //Constructor
    ParallelThread()
        : pRun(false)
         ,pWait(false)
         ,isWaiting(false)
         #if __cplusplus > 201703L
         ,pWorkCond(false)
         #endif
    {
        timeoutPeriod = 400;
        threadName = "anonymous";
        init();
    }

    //Destructor
    ~ParallelThread() {
        if( pRun.load(std::memory_order_acquire) ) {
            stop();
        };
    }

    // start the new thread
    void start() noexcept {
        if (!isRunning()) run();
    }

    // helper function: check if thread is running
    inline bool isRunning() const noexcept {
        return (pRun.load(std::memory_order_acquire) && 
                 pThd.joinable());
    }

    // set a name for the thread (may help on diagnostics)
    void setThreadName(std::string name) noexcept {
        threadName = name;
    }

    // set thread policy and priority class, this may fail silent
    void setPriority(int32_t rt_prio, int32_t rt_policy) noexcept {
        if (isRunning())
            setThreadPolicy(rt_prio, rt_policy);
    }

    // set the time out for the thread waiting functions in milliseconds 
    void setTimeOut(uint32_t timeout) noexcept {
        timeoutPeriod = timeout;
    }

    // try to get the process pointer, return false when thread is busy 
    inline bool getProcess() noexcept {
        if (isRunning() && !getState()) {
            int maxDuration = 0;
            while (!getState()) {
                pthread_mutex_lock(&pWaitProc);
                if (pthread_cond_timedwait(&pProcCond, &pWaitProc, getTimeOut()) == ETIMEDOUT) {
                    pthread_mutex_unlock(&pWaitProc);
                    maxDuration +=1;
                    //fprintf(stderr, "%s wait for process %i\n", threadName.c_str(), maxDuration);
                    if (maxDuration > 2) {
                        //fprintf(stderr, "%s break waitForProcess\n", threadName.c_str());
                        break;
                    }
                } else {
                    pthread_mutex_unlock(&pWaitProc);;
                }
            }
        }
        if (getState()) pWait.store(true, std::memory_order_release);
        return getState();
    }

    // notify the thread that work is to be done
    inline void runProcess() noexcept {
        #if __cplusplus > 201703L
        pWorkCond.store(true);
        #endif
        pWorkCond.notify_one();
    }

    // wait for the processed data from the thread, 
    // in worst case this may fail silent
    // when to much time expires (5 * timeOut time)
    // to avoid Xruns or dead looks.
    inline void processWait() noexcept {
        if (isRunning()) {
            int maxDuration = 0;
            while (pWait.load(std::memory_order_acquire)) {
                pthread_mutex_lock(&pWaitProc);
                if (pthread_cond_timedwait(&pProcCond, &pWaitProc, getTimeOut()) == ETIMEDOUT) {
                    pthread_mutex_unlock(&pWaitProc);
                    maxDuration +=1;
                    //fprintf(stderr, "%s wait for data %i\n", threadName.c_str(), maxDuration);
                    if (maxDuration > 5) {
                        pWait.store(false, std::memory_order_release);
                        //fprintf(stderr, "%s break processWait\n", threadName.c_str());
                    }
                } else {
                    pthread_mutex_unlock(&pWaitProc);;
                }
            }
            //fprintf(stderr, "%s processed data %i\n", threadName.c_str(), maxDuration);
        }
    }

    // stop the thread (at least on Destruction)
    void stop() noexcept {
        if (isRunning()) {
            pRun.store(false, std::memory_order_release);
            if (pThd.joinable()) {
                set<ProcessPtr, &ProcessPtr::dummyFunc>(this);
                #if __cplusplus > 201703L
                pWorkCond.store(true);
                #endif
                pWorkCond.notify_one();
                pThd.join();
            }
        }
    }


private:
    std::atomic<bool> pRun;
    std::atomic<bool> pWait;
    std::atomic<bool> isWaiting;

    #if __cplusplus > 201703L
    std::atomic<bool> pWorkCond;
    #else
    std::mutex pWaitWork;
    std::condition_variable pWorkCond;
    #endif

    std::thread pThd;
    std::string threadName;
    uint32_t timeoutPeriod;

    pthread_mutex_t pWaitProc;
    pthread_cond_t pProcCond;
    struct timespec timeOut;

    // init pthread_cond_t and pthread_mutex_t
    inline void init() noexcept {
        pthread_condattr_t cond_attr;
        pthread_condattr_init(&cond_attr);
        pthread_condattr_setclock(&cond_attr, CLOCK_MONOTONIC);
        pthread_cond_init(&pProcCond, &cond_attr);
        pthread_condattr_destroy(&cond_attr);
        pWaitProc = PTHREAD_MUTEX_INITIALIZER;
    }

    // run the thread, wait for signal and process the given function
    inline void run() noexcept {
        if( pRun.load(std::memory_order_acquire) ) {
            stop();
        };
        pRun.store(true, std::memory_order_release);
        pThd = std::thread([this]() {
            #if __cplusplus <= 201703L
            std::unique_lock<std::mutex> lk(pWaitWork);
            #endif
            while (pRun.load(std::memory_order_acquire)) {
                isWaiting.store(true, std::memory_order_release);
                pthread_cond_broadcast(&pProcCond);
                // wait for signal from parent thread that work is to do
                #if __cplusplus > 201703L
                pWorkCond.wait(false);
                pWorkCond.store(false);
                #else
                pWorkCond.wait(lk);
                #endif
                isWaiting.store(false, std::memory_order_release);
                pWait.store(true, std::memory_order_release);
                process();
                pWait.store(false, std::memory_order_release);
            }
            // when done
        });    
    }

    // check if thread is busy, return true when not
    inline bool getState() const noexcept {
        return isWaiting.load(std::memory_order_acquire);
    }

    // set thread scheduling class and priority level 
    inline void setThreadPolicy(int32_t rt_prio, int32_t rt_policy) noexcept {
        #if defined(__linux__) || defined(_UNIX) || defined(__APPLE__) || defined(_OS_UNIX_)
        sched_param sch_params;
        if (rt_prio == 0) {
            rt_prio = sched_get_priority_max(rt_policy);
        }
        if ((rt_prio/5) > 0) rt_prio = rt_prio/5;
        sch_params.sched_priority = rt_prio;
        if (pthread_setschedparam(pThd.native_handle(), rt_policy, &sch_params)) {
            fprintf(stderr, "ParallelThread:%s fail to set priority\n", threadName.c_str());
        }
        #elif defined(_WIN32)
        // REALTIME_PRIORITY_CLASS, THREAD_PRIORITY_NORMAL
        if (SetThreadPriority(pThd.native_handle(), 24)) {
            fprintf(stderr, "ParallelThread:%s fail to set priority\n", threadName.c_str());
        }
        #else
        //system does not supports thread priority!
        #endif
    }

    // calculate the timeout for the thread wait functions
    inline struct timespec *getTimeOut() noexcept {
        clock_gettime (CLOCK_MONOTONIC, &timeOut);
        long int at = (timeoutPeriod * 1000);
        if (timeOut.tv_nsec + at > 1000000000) {
            timeOut.tv_sec +=1;
            at -= 1000000000;
        }
        timeOut.tv_nsec += at;
        return &timeOut;
    }

    // simple implement clock_gettime for windows (8)
    #if defined(_WIN32)
    int clock_gettime(int, struct timespec *spec) {
        int64_t wTime;
        GetSystemTimePreciseAsFileTime((FILETIME*)&wTime);
        wTime      -=116444736000000000LL;  //1jan1601 to 1jan1970
        spec->tv_sec  =wTime / 10000000LL;           //seconds
        spec->tv_nsec =wTime % 10000000LL *100;      //nano-seconds
        return 0;
    }
    #endif

};

#endif
