/*
    This file is part of ParTI!.

    ParTI! is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    ParTI! is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with ParTI!.
    If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PASTA_ERROR_H_INCLUDED
#define PASTA_ERROR_H_INCLUDED

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif


/**
 * An opaque data type to store a specific time point, using either CPU or GPU clock.
 */
typedef struct sptTagTimer *sptTimer;

typedef enum {
		SPTERR_NO_ERROR       = 0,
		SPTERR_UNKNOWN        = 1,
		SPTERR_SHAPE_MISMATCH = 2,
		SPTERR_VALUE_ERROR    = 3,
		SPTERR_ZERO_DIVISION  = 4,
		SPTERR_NO_MORE        = 99,
		SPTERR_OS_ERROR       = 0x10000,
		SPTERR_CUDA_ERROR     = 0x20000,
} SptError;


/**
 * Check if a value is not zero, print error message and return.
 * @param errcode the value to be checked
 * @param module  the module name of current procedure
 * @param reason  human readable error explanation
 */
#ifndef NDEBUG
#define spt_CheckError(errcode, module, reason) \
    if(unlikely((errcode) != 0)) { \
        spt_ComplainError(module, (errcode), __FILE__, __LINE__, (reason)); \
        return (errcode); \
    }
#else
#define spt_CheckError(errcode, module, reason) \
    if(unlikely((errcode) != 0)) { \
        return (errcode); \
    }
#endif
//#include <pasta.h>

#ifndef NDEBUG
#define spt_CheckOmpError(errcode, module, reason) \
    if(unlikely((errcode) != 0)) { \
        spt_ComplainError(module, (errcode), __FILE__, __LINE__, (reason)); \
        exit(errcode); \
    }
#else
#define spt_CheckOmpError(errcode, module, reason) \
    if(unlikely((errcode) != 0)) { \
        exit(errcode); \
    }
#endif

/**
 * Check if a condition is true, set the error information as the system error, print error message and return.
 * @param cond   the condition to be checked
 * @param module the module name of current procedure
 */
#define spt_CheckOSError(cond, module) \
    if(unlikely((cond))) { \
        spt_CheckError(errno + SPTERR_OS_ERROR, (module), strerror(errno)); \
    }


void spt_ComplainError(const char *module, int errcode, const char *file, unsigned line, const char *reason);

#ifdef __cplusplus
}
#endif

#endif
