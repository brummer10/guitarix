#ifndef SRC_HEADERS_GX_COMPILER_H_
#define SRC_HEADERS_GX_COMPILER_H_


#ifdef __APPLE__
/* This not work kill ardour or reaper when try load plugin to daw
#define __rt_func __attribute__((section("TEXT,rt_text")))
#define __rt_data __attribute__((section("DATA,rt_data")))
*/
//This Work
#define __rt_func __attribute__((section("__TEXT,__rt.text,regular,pure_instructions")))
#define __rt_data __attribute__((section("__DATA,__rt.data")))
#else
#define __rt_func __attribute__((section("rt_text")))
#define __rt_data __attribute__((section("rt_data")))
#endif

#endif  // SRC_HEADERS_GX_COMPILER_H_
