/*
 *                           0BSD 
 * 
 *                    BSD Zero Clause License
 * 
 *  Copyright (c) 2019 Hermann Meyer
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 */


/* define _GNU_SOURCE to remove dependency of xasprintf.h */

/*
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
*/

#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdarg.h> 
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <libgen.h>

#pragma once

#ifndef XFILEPICKER_H_
#define XFILEPICKER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* comment out xdgmine.h will disable the file filter, you may implement your own.*/
#ifndef _WIN32 //xdgmime n.a.
#include "xdgmime.h"
#endif
/* comment out xasprintf and define _GNU_SOURCE on top of this file will remove this dependency.*/
#include "xasprintf.h"

#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR "/" 
#endif

typedef struct {
    int use_filter;
    bool show_hidden;
    unsigned int file_counter;
    unsigned int dir_counter;
    char *filter;
    char *path;
    char *selected_file;
    char **file_names;
    char **dir_names;
} FilePicker;


/**
 * @brief fp_get_files             - fill file_names and dir_names with the
 * results from readdir path
 * @param *filepicker              - pointer to the struct holding the list pointers
 * @param *path                    - the path to read from
 * @param get_dirs                 - 0 = only read files 1 = refill the directory buffer as well
 * @return int                     - return the position of the given path in the directory list 
 */

int fp_get_files(FilePicker *filepicker, char *path, int get_dirs);

/**
 * @brief fp_free                  - release all memory used by the filepicker
 * @param *filepicker              - pointer to the struct to be released
 * @return void
 */

void fp_free(FilePicker *filepicker);

/**
 * @brief fp_init                  - set default values used by the filepicker
 * @param *filepicker              - pointer to the struct to allocate
 * @param *path                    - the path to read from
 * @return void
 */

void fp_init(FilePicker *filepicker, const char *path);

#ifdef __cplusplus
}
#endif

#endif //XFILEPICKER_H_
