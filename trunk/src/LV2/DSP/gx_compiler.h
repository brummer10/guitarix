#ifndef SRC_HEADERS_GX_COMPILER_H_
#define SRC_HEADERS_GX_COMPILER_H_

#ifdef __APPLE__
#define __rt_func __attribute__((section("TEXT,rt_text")))
#define __rt_data __attribute__((section("DATA,rt_data")))
#else
#define __rt_func __attribute__((section("rt_text")))
#define __rt_data __attribute__((section("rt_data")))
#endif

#endif  // SRC_HEADERS_GX_COMPILER_H_
