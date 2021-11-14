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

#ifndef PASTA_VECTORS_H
#define PASTA_VECTORS_H

#include <bits/types/FILE.h>
#include "types.h"
#include "structs.h"

void sptQuickSortNnzIndexArray(sptNnzIndex * array, sptNnzIndex l, sptNnzIndex r);

/* Dense vector, with sptValueVector type */
int sptNewValueVector(sptValueVector *vec, sptNnzIndex len, sptNnzIndex cap);
int sptConstantValueVector(sptValueVector * const vec, sptValue const val);

int sptAppendValueVector(sptValueVector *vec, sptValue const value);

int sptResizeValueVector(sptValueVector *vec, sptNnzIndex const size);
void sptFreeValueVector(sptValueVector *vec);

/* Dense vector, with sptIndexVector type */
int sptNewIndexVector(sptIndexVector *vec, sptNnzIndex len, sptNnzIndex cap);

int sptAppendIndexVector(sptIndexVector *vec, sptIndex const value);

int sptResizeIndexVector(sptIndexVector *vec, sptNnzIndex const size);
void sptFreeIndexVector(sptIndexVector *vec);


#endif