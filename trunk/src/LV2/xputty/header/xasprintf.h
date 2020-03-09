
#ifndef _GNU_SOURCE

/*  Multiplatform implementation of asprintf() from:
    https://stackoverflow.com/questions/40159892/using-asprintf-on-windows
    define _GNU_SOURCE to use the GNU asprintf extension instead this one.
*/

#pragma once

#ifndef XASPRINTF_H_
#define XASPRINTF_H_

#ifdef __cplusplus
extern "C" {
#endif


int _vscprintf_so(const char * format, va_list pargs);

int vasprintf(char **strp, const char *fmt, va_list ap);

int asprintf(char *strp[], const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif //XASPRINTF_H_

#endif // !_GNU_SOURCE
