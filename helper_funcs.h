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

#ifndef PASTA_HELPER_FUNCS_H
#define PASTA_HELPER_FUNCS_H

#include <omp.h>
#include <stdlib.h>
#include "error.h"
#include "types.h"

/**
 * The assert function that always execute even when `NDEBUG` is set
 *
 * Quick & dirty error checking. Useful when writing small programs.
 */
#define sptAssert(expr) ((expr) ? (void) 0 : exit(-1))

/* Timer functions, using either CPU or GPU timer */
int sptNewTimer(sptTimer *timer, int use_cuda);
int sptStartTimer(sptTimer timer);
int sptStopTimer(sptTimer timer);
double sptElapsedTime(const sptTimer timer);
double sptPrintElapsedTime(const sptTimer timer, const char *name);
double sptPrintAverageElapsedTime(const sptTimer timer, const int niters, const char *name);
int sptFreeTimer(sptTimer timer);

/* Base functions */
char * sptBytesString(uint64_t const bytes);
sptValue sptRandomValue(void);




#endif