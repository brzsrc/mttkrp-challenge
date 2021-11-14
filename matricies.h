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

#ifndef PASTA_MATRICES_H
#define PASTA_MATRICES_H

/* Dense matrix */
static inline sptNnzIndex sptGetMatrixLength(const sptMatrix *mtx) {
	return mtx->nrows * mtx->stride;
}
int sptNewMatrix(sptMatrix *mtx, sptIndex const nrows, sptIndex const ncols);
int sptRandomizeMatrix(sptMatrix *mtx, bool random);

int sptConstantMatrix(sptMatrix * const mtx, sptValue const val);

void sptFreeMatrix(sptMatrix *mtx);
int sptDumpMatrix(sptMatrix *mtx, FILE *fp);

int sptMatrixSolveNormals(
		sptIndex const mode,
		sptIndex const nmodes,
		sptMatrix ** aTa,
		sptMatrix * rhs);
int sptSparseTensorToMatrix(sptMatrix *dest, const sptSparseTensor *src);

/* Dense Rank matrix, ncols = small rank (<= 256) */
int sptNewRankMatrix(sptRankMatrix *mtx, sptIndex const nrows, sptElementIndex const ncols);
int sptRandomizeRankMatrix(sptRankMatrix *mtx, sptIndex const nrows, sptElementIndex const ncols);
int sptConstantRankMatrix(sptRankMatrix *mtx, sptValue const val);
void sptRankMatrixInverseShuffleIndices(sptRankMatrix *mtx, sptIndex * mode_map_inds);
void sptFreeRankMatrix(sptRankMatrix *mtx);

/* Dense rank matrix operations */
int sptRankMatrixDotMulSeqTriangle(sptIndex const mode, sptIndex const nmodes, sptRankMatrix ** mats);
int sptRankMatrix2Norm(sptRankMatrix * const A, sptValue * const lambda);
int sptRankMatrixMaxNorm(sptRankMatrix * const A, sptValue * const lambda);
void GetRankFinalLambda(
		sptElementIndex const rank,
		sptIndex const nmodes,
		sptRankMatrix ** mats,
		sptValue * const lambda);
int sptRankMatrixSolveNormals(
		sptIndex const mode,
		sptIndex const nmodes,
		sptRankMatrix ** aTa,
		sptRankMatrix * rhs);

/* Sparse matrix, COO format */
int sptNewSparseMatrix(sptSparseMatrix *mtx, sptIndex const nrows, sptIndex const ncols);
int sptCopySparseMatrix(sptSparseMatrix *dest, const sptSparseMatrix *src);
void sptFreeSparseMatrix(sptSparseMatrix *mtx);

#endif