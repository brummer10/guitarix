#ifndef SRC_HEADERS_GX_COMPILER_H_
#define SRC_HEADERS_GX_COMPILER_H_

#ifdef __APPLE__
#define __rt_func __attribute__((section("TEXT,.rt.text")))
#define __rt_data __attribute__((section("DATA,.rt.data")))
#else
#define __rt_func __attribute__((section(".rt.text")))
#define __rt_data __attribute__((section(".rt.data")))
#endif

#endif  // SRC_HEADERS_GX_COMPILER_H_
