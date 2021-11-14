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
#include "structs.h"
#include "vector.h"
#include "error.h"
#include "sptensors.h"
#include "helper_funcs.h"
#include <stdlib.h>
#include <string.h>

/**
 * Create a new sparse tensor
 * @param tsr    a pointer to an uninitialized sparse tensor
 * @param nmodes number of modes the tensor will have
 * @param ndims  the dimension of each mode the tensor will have
 */
int sptNewSparseTensor(sptSparseTensor *tsr, sptIndex nmodes, const sptIndex ndims[]) {
	sptIndex i;
	int result;
	tsr->nmodes = nmodes;
	tsr->sortorder = malloc(nmodes * sizeof tsr->sortorder[0]);
	for(i = 0; i < nmodes; ++i) {
		tsr->sortorder[i] = i;
	}
	tsr->ndims = malloc(nmodes * sizeof *tsr->ndims);
//	spt_CheckOSError(!tsr->ndims, "SpTns New");
	memcpy(tsr->ndims, ndims, nmodes * sizeof *tsr->ndims);
	tsr->nnz = 0;
	tsr->inds = malloc(nmodes * sizeof *tsr->inds);
//	spt_CheckOSError(!tsr->inds, "SpTns New");
	for(i = 0; i < nmodes; ++i) {
		result = sptNewIndexVector(&tsr->inds[i], 0, 0);
		spt_CheckError(result, "SpTns New", NULL);
	}
	result = sptNewValueVector(&tsr->values, 0, 0);
	spt_CheckError(result, "SpTns New", NULL);
	return 0;
}


/**
 * Release any memory the sparse tensor is holding
 * @param tsr the tensor to release
 */
void sptFreeSparseTensor(sptSparseTensor *tsr) {
	sptIndex i;
	for(i = 0; i < tsr->nmodes; ++i) {
		sptFreeIndexVector(&tsr->inds[i]);
	}
	free(tsr->sortorder);
	free(tsr->ndims);
	free(tsr->inds);
	sptFreeValueVector(&tsr->values);
	tsr->nmodes = 0;
}


