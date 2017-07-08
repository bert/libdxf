/*!
 * \file dbg.h
 *
 * \author Zed A. Shaw <help@learncodethehardway.org>
 *
 * \brief Zed's Awesome Debug Macros.
 *
 * Exerpt from "Learn C the hard way",
 * <a href="https://learncodethehardway.org/c/">
 * Exercise 20: Zed's Awesome Debug Macros</a> 
 * by Zed A. Shaw <help@learncodethehardway.org>.
 *
 * Adaptation for libdxf: Copyright (C) 2016, 2017 by
 * Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.\n\n
 * This program is distributed in the hope that it will be useful, but
 * <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
 * <b>MERCHANTABILITY</b> or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.\n
 * See the GNU General Public License for more details.\n\n
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to:\n
 * Free Software Foundation, Inc.,\n
 * 59 Temple Place,\n
 * Suite 330,\n
 * Boston,\n
 * MA 02111 USA.\n
 * <hr>
 */


#ifndef LIBDXF_SRC_DBG_H
#define LIBDXF_SRC_DBG_H


#include <stdio.h>
#include <errno.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif


#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif


/*!
 * The \c clean_errno macro that's used in the others to get a safe
 * readable version of \c errno.
 */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))


/*!
 * The \c log_err macro for logging messages meant for the end user.\n
 * Works like \c debug but can't be compiled out.
 */
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

/*!
 * The \c log_warn macro for logging messages meant for the end user.\n
 * Works like \c debug but can't be compiled out.
 */
#define log_warn(M, ...) fprintf(stderr, "[WARNING] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

/*!
 * The \c log_info macro for logging messages meant for the end user.\n
 * Works like \c debug but can't be compiled out.
 */
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)


/*!
 * The \c check macro will make sure the condition A is true, and if not
 * logs the error \c M (with variable arguments for \c log_err),
 * then jumps to the function's \c error: label for cleanup.
 */
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

/*!
 * The macro \c sentinel is placed in any part of a function that
 * shouldn't run, and if it does prints an error message then jumps to
 * the \c error: label.\n
 * You put this in if-statements and switch-statements to catch
 * conditions that shouldn't happen, like the \c default: .
 */
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }


/*!
 * A short-hand macro \c check_mem that makes sure a pointer is valid,
 * and if it isn't reports it as an error with "Out of memory".
 */
#define check_mem(A) check((A), "Out of memory.")


/*!
 * An alternative macro \c check_debug that still checks and handles an
 * error, but if the error is common then you don't want to bother
 * reporting it.\n
 * In this one it will use \c debug instead of \c log_err to report the
 * message, so when you define \c NDEBUG the check still happens, the
 * error jump goes off, but the message isn't printed.
 */
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_DBG_H */


/* EOF */
