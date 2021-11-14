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

//#include <pasta.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "error.h"
#include "helper_funcs.h"

/**
 * Initialize a new dense matrix
 *
 * @param mtx   a valid pointer to an uninitialized sptMatrix variable
 * @param nrows the number of rows
 * @param ncols the number of columns
 *
 * The memory layout of this dense matrix is a flat 2D array, with `ncols`
 * rounded up to multiples of 8
 */
int sptNewMatrix(sptMatrix *mtx, sptIndex const nrows, sptIndex const ncols) {
	mtx->nrows = nrows;
	mtx->ncols = ncols;
	mtx->cap = nrows != 0 ? nrows : 1;
	mtx->stride = ((ncols-1)/8+1)*8;
#ifdef _ISOC11_SOURCE
	mtx->values = aligned_alloc(8 * sizeof (sptValue), mtx->cap * mtx->stride * sizeof (sptValue));
#elif _POSIX_C_SOURCE >= 200112L
	{
		int result = posix_memalign((void **) &mtx->values, 8 * sizeof (sptValue), mtx->cap * mtx->stride * sizeof (sptValue));
		if(result != 0) {
			mtx->values = NULL;
		}
	}
#else
	mtx->values = malloc(mtx->cap * mtx->stride * sizeof (sptValue));
#endif
	spt_CheckOSError(!mtx->values, "Mtx New");
	memset(mtx->values, 0, mtx->cap * mtx->stride * sizeof (sptValue));
	return 0;
}

/**
 * Build a matrix with random number
 *
 * @param mtx   a pointer to an initialized matrix
 * @param nrows fill the specified number of rows
 * @param ncols fill the specified number of columns
 *
 * The matrix is filled with uniform distributed pseudorandom number in [0, 1]
 * The random number will have a precision of 31 bits out of 51 bits
 */
int sptRandomizeMatrix(sptMatrix *mtx, bool random) {
	for(sptIndex i=0; i<mtx->nrows; ++i)
		for(sptIndex j=0; j<mtx->ncols; ++j) {
			if (random) {
				srand(time(NULL) + (rand()%100) + i + j);
			} else {
				srand(1234 + i + j);
			}
			mtx->values[i * mtx->stride + j] = sptRandomValue();
		}
	return 0;
}


/**
 * Fill an existed dense matrix with a specified constant
 *
 * @param mtx   a pointer to a valid matrix
 * @param val   a given value constant
 *
 */
int sptConstantMatrix(sptMatrix *mtx, sptValue const val) {
	for(sptIndex i=0; i<mtx->nrows; ++i)
		for(sptIndex j=0; j<mtx->ncols; ++j)
			mtx->values[i * mtx->stride + j] = val;
	return 0;
}


/**
 * Release the memory buffer a dense matrix is holding
 *
 * @param mtx a pointer to a valid matrix
 *
 * By using `sptFreeMatrix`, a valid matrix would become uninitialized and
 * should not be used anymore prior to another initialization
 */
void sptFreeMatrix(sptMatrix *mtx) {
	free(mtx->values);
	mtx->nrows = 0;
	mtx->ncols = 0;
	mtx->cap = 0;
	mtx->stride = 0;
}


