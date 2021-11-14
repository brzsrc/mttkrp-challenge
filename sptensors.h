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

#ifndef PASTA_SPTENSORS_H
#define PASTA_SPTENSORS_H

#include <bits/types/FILE.h>

/* Sparse tensor */
int sptNewSparseTensor(sptSparseTensor *tsr, sptIndex nmodes, const sptIndex ndims[]);

void sptFreeSparseTensor(sptSparseTensor *tsr);

int sptLoadSparseTensor(sptSparseTensor *tsr, sptIndex start_index, char const * const fname);
// int sptLoadSparseTensor(sptSparseTensor *tsr, sptIndex start_index, FILE *fp);
int sptDumpSparseTensor(const sptSparseTensor *tsr, sptIndex start_index, FILE *fp);
int sptMatricize(sptSparseTensor const * const X,
								 sptIndex const m,
								 sptSparseMatrix * const A,
								 int const transpose);

void sptSparseTensorCalcIndexBounds(sptIndex inds_low[], sptIndex inds_high[], const sptSparseTensor *tsr);
int spt_ComputeSliceSizes(
		sptNnzIndex * slice_nnzs,
		sptSparseTensor * const tsr,
		sptIndex const mode);
void sptSparseTensorStatus(sptSparseTensor *tsr, FILE *fp);
double sptSparseTensorDensity(sptSparseTensor const * const tsr);
int sptSparseTensorSetFibers(
		sptNnzIndexVector *fiberidx,
		sptIndex mode,
		sptSparseTensor *ref
);
int sptSparseTensorSetIndices(
		sptSparseTensor *dest,
		sptNnzIndexVector *fiberidx,
		sptIndex mode,
		sptSparseTensor *ref
);


int sptDumpSparseTensorHiCOO(sptSparseTensorHiCOO * const hitsr, FILE *fp);
int sptSparseTensorSetIndicesHiCOO(
		sptSparseTensorHiCOO *dest,
		sptNnzIndexVector *fiberidx,
		sptSparseTensorHiCOOGeneral *ref);
int sptSparseTensorSetFibersHiCOO(
		sptNnzIndexVector *bptr,
		sptNnzIndexVector *fiberidx,
		sptSparseTensorHiCOOGeneral *ref);

int sptDumpSparseTensorHiCOOGeneral(sptSparseTensorHiCOOGeneral * const hitsr, FILE *fp);

void sptSparseTensorStatusHiCOOGeneral(sptSparseTensorHiCOOGeneral *hitsr, FILE *fp);
void sptLoadShuffleFile(sptSparseTensor *tsr, FILE *fs, sptIndex ** map_inds);
void sptSparseTensorStatusHiCOO(sptSparseTensorHiCOO *hitsr, FILE *fp);


/* Sparse tensor unary operations */
int sptSparseTensorAddScalar(sptSparseTensor *Z, sptSparseTensor *X, sptValue a);
int sptOmpSparseTensorAddScalar(sptSparseTensor *Z, sptSparseTensor *X, sptValue a);
int sptCudaSparseTensorAddScalar(sptSparseTensor *Z, sptSparseTensor *X, sptValue a);
int sptSparseTensorMulScalar(sptSparseTensor *Z, sptSparseTensor *X, sptValue a);
int sptOmpSparseTensorMulScalar(sptSparseTensor *Z, sptSparseTensor *X, sptValue a);
int sptCudaSparseTensorMulScalar(sptSparseTensor *Z, sptSparseTensor *X, sptValue a);

int sptSparseTensorAddScalarHiCOO(sptSparseTensorHiCOO *Z, sptSparseTensorHiCOO *X, sptValue a);
int sptOmpSparseTensorAddScalarHiCOO(sptSparseTensorHiCOO *Z, sptSparseTensorHiCOO *X, sptValue a);
int sptCudaSparseTensorAddScalarHiCOO(sptSparseTensorHiCOO *Z, sptSparseTensorHiCOO *X, sptValue a);
int sptSparseTensorMulScalarHiCOO(sptSparseTensorHiCOO *Z, sptSparseTensorHiCOO *X, sptValue a);
int sptOmpSparseTensorMulScalarHiCOO(sptSparseTensorHiCOO *Z, sptSparseTensorHiCOO *X, sptValue a);
int sptCudaSparseTensorMulScalarHiCOO(sptSparseTensorHiCOO *Z, sptSparseTensorHiCOO *X, sptValue a);

/* Sparse tensor binary operations */
int sptSparseTensorDotAdd(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptOmpSparseTensorDotAdd(sptSparseTensor *Z, sptSparseTensor *X, sptSparseTensor *Y, int collectZero, int nthreads);
int sptSparseTensorDotAddEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptOmpSparseTensorDotAddEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptCudaSparseTensorDotAddEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptSparseTensorDotAddEqHiCOO(sptSparseTensorHiCOO *hiZ, const sptSparseTensorHiCOO *hiX, const sptSparseTensorHiCOO *hiY, int collectZero);
int sptOmpSparseTensorDotAddEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);
int sptCudaSparseTensorDotAddEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);

int sptSparseTensorDotSub(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptOmpSparseTensorDotSub(sptSparseTensor *Z, sptSparseTensor *X, sptSparseTensor *Y, int collectZero, int nthreads);
int sptSparseTensorDotSubEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptOmpSparseTensorDotSubEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptCudaSparseTensorDotSubEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptSparseTensorDotSubEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);
int sptOmpSparseTensorDotSubEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);
int sptCudaSparseTensorDotSubEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);

int sptSparseTensorDotMul(sptSparseTensor *Z, const sptSparseTensor * X, const sptSparseTensor *Y, int collectZero);
int sptOmpSparseTensorDotMul(sptSparseTensor *Z, sptSparseTensor *X, sptSparseTensor *Y, int collectZero, int nthreads);
int sptSparseTensorDotMulEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptOmpSparseTensorDotMulEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptCudaSparseTensorDotMulEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptSparseTensorDotMulEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);
int sptOmpSparseTensorDotMulEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);
int sptCudaSparseTensorDotMulEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);

int sptSparseTensorDotDivEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptOmpSparseTensorDotDivEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptCudaSparseTensorDotDivEq(sptSparseTensor *Z, const sptSparseTensor *X, const sptSparseTensor *Y, int collectZero);
int sptSparseTensorDotDivEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);
int sptOmpSparseTensorDotDivEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);
int sptCudaSparseTensorDotDivEqHiCOO(sptSparseTensorHiCOO *Z, const sptSparseTensorHiCOO *X, const sptSparseTensorHiCOO *Y, int collectZero);

int sptSparseTensorMulMatrix(sptSemiSparseTensor *Y, sptSparseTensor *X, const sptMatrix *U, sptIndex const mode);
int sptOmpSparseTensorMulMatrix(sptSemiSparseTensor *Y, sptSparseTensor *X, const sptMatrix *U, sptIndex const mode);
int sptCudaSparseTensorMulMatrix(
		sptSemiSparseTensor *Y,
		sptSparseTensor *X,
		const sptMatrix *U,
		sptIndex const mode,
		sptIndex const impl_num,
		sptNnzIndex const smen_size);
int sptSparseTensorMulMatrixHiCOO(sptSemiSparseTensorHiCOO *Y, sptSparseTensorHiCOOGeneral *X, const sptMatrix *U, sptIndex const mode);
int sptOmpSparseTensorMulMatrixHiCOO(sptSemiSparseTensorHiCOO *Y, sptSparseTensorHiCOOGeneral *X, const sptMatrix *U, sptIndex const mode);
int sptCudaSparseTensorMulMatrixHiCOO(
		sptSemiSparseTensorHiCOO *Y,
		sptSparseTensorHiCOOGeneral *X,
		const sptMatrix *U,
		sptIndex const mode,
		sptIndex const impl_num,
		sptNnzIndex const smen_size);

int sptSparseTensorMulVector(sptSparseTensor *Y, sptSparseTensor *X, const sptValueVector *V, sptIndex mode);
int sptOmpSparseTensorMulVector(sptSparseTensor *Y, sptSparseTensor *X, const sptValueVector *V, sptIndex mode);
int sptCudaSparseTensorMulVector(
		sptSparseTensor *Y,
		sptSparseTensor *X,
		const sptValueVector *V,
		sptIndex const mode,
		sptIndex const impl_num,
		sptNnzIndex const smen_size);
int sptSparseTensorMulVectorHiCOO(sptSparseTensorHiCOO *Y, sptSparseTensorHiCOOGeneral *X, const sptValueVector *V, sptIndex mode);
int sptOmpSparseTensorMulVectorHiCOO(sptSparseTensorHiCOO *Y, sptSparseTensorHiCOOGeneral *X, const sptValueVector *V, sptIndex mode);
int sptCudaSparseTensorMulVectorHiCOO(
		sptSparseTensorHiCOO *Y,
		sptSparseTensorHiCOOGeneral *X,
		const sptValueVector *V,
		sptIndex const mode,
		sptIndex const impl_num,
		sptNnzIndex const smen_size);


/**
 * Kronecker product
 */
int sptSparseTensorKroneckerMul(sptSparseTensor *Y, const sptSparseTensor *A, const sptSparseTensor *B);

/**
 * Khatri-Rao product
 */
int sptSparseTensorKhatriRaoMul(sptSparseTensor *Y, const sptSparseTensor *A, const sptSparseTensor *B);


/**
 * Matricized tensor times Khatri-Rao product.
 */
int sptMTTKRP(
		sptSparseTensor const * const X,
		sptMatrix * mats[],     // mats[nmodes] as temporary space.
		sptIndex const mats_order[],    // Correspond to the mode order of X.
		sptIndex const mode);
int sptOmpMTTKRP(
		sptSparseTensor const * const X,
		sptMatrix * mats[],     // mats[nmodes] as temporary space.
		sptIndex const mats_order[],    // Correspond to the mode order of X.
		sptIndex const mode,
		const int tk);
int sptCudaMTTKRP(
		sptSparseTensor const * const X,
		sptMatrix ** const mats,     // mats[nmodes] as temporary space.
		sptIndex * const mats_order,    // Correspond to the mode order of X.
		sptIndex const mode,
		sptIndex const impl_num);


/**
 * Matricized tensor times Khatri-Rao product for HiCOO tensors
 */
int sptMTTKRPHiCOO(
		sptSparseTensorHiCOO const * const hitsr,
		sptMatrix * mats[],     // mats[nmodes] as temporary space.
		sptIndex const mats_order[],    // Correspond to the mode order of X.
		sptIndex const mode);
int sptOmpMTTKRPHiCOO(
		sptSparseTensorHiCOO const * const hitsr,
		sptMatrix * mats[],     // mats[nmodes] as temporary space.
		sptIndex const mats_order[],    // Correspond to the mode order of X.
		sptIndex const mode,
		const int nthreads);
int sptCudaMTTKRPHiCOO(
		sptSparseTensorHiCOO const * const hitsr,
		sptMatrix ** const mats,     // mats[nmodes] as temporary space.
		sptIndex * const mats_order,    // Correspond to the mode order of X.
		sptIndex const mode,
		sptNnzIndex const max_nnzb,
		int const impl_num);


#endif