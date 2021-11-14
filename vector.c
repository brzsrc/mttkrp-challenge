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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "vector.h"
#include "error.h"
#include "helper_funcs.h"

/**
 * Initialize a new value vector
 *
 * @param vec a valid pointer to an uninitialized sptValueVector variable,
 * @param len number of values to create
 * @param cap total number of values to reserve
 *
 * Vector is a type of one-dimentional array with dynamic length
 */
int sptNewValueVector(sptValueVector *vec, sptNnzIndex len, sptNnzIndex cap) {
	if(cap < len) {
		cap = len;
	}
	if(cap < 2) {
		cap = 2;
	}
	vec->len = len;
	vec->cap = cap;
	vec->data = malloc(cap * sizeof *vec->data);
	spt_CheckOSError(!vec->data, "ValVec New");
	memset(vec->data, 0, cap * sizeof *vec->data);
	return 0;
}


/**
 * Fill an existed dense value vector with a specified constant
 *
 * @param vec   a valid pointer to an existed sptVector variable,
 * @param val   a given value constant
 *
 * Vector is a type of one-dimentional array with dynamic length
 */
int sptConstantValueVector(sptValueVector * const vec, sptValue const val) {
	for(sptNnzIndex i=0; i<vec->len; ++i)
		vec->data[i] = val;
	return 0;
}

/**
 * Add a value to the end of a value vector
 *
 * @param vec   a pointer to a valid value vector
 * @param value the value to be appended
 *
 * The length of the value vector will be changed to contain the new value.
 */
int sptAppendValueVector(sptValueVector *vec, sptValue const value) {
	if(vec->cap <= vec->len) {
#ifndef MEMCHECK_MODE
		sptNnzIndex newcap = vec->cap + vec->cap/2;
#else
		sptNnzIndex newcap = vec->len+1;
#endif
		sptValue *newdata = realloc(vec->data, newcap * sizeof *vec->data);
		spt_CheckOSError(!newdata, "ValVec Append");
		vec->cap = newcap;
		vec->data = newdata;
	}
	vec->data[vec->len] = value;
	++vec->len;
	return 0;
}

/**
 * Resize a value vector
 *
 * @param vec  the value vector to resize
 * @param size the new size of the value vector
 *
 * If the new size is larger than the current size, new values will be appended
 * but the values of them are undefined. If the new size if smaller than the
 * current size, values at the end will be truncated.
 */
int sptResizeValueVector(sptValueVector *vec, sptNnzIndex const size) {
	sptNnzIndex newcap = size < 2 ? 2 : size;
	if(newcap != vec->cap) {
		sptValue *newdata = realloc(vec->data, newcap * sizeof *vec->data);
		spt_CheckOSError(!newdata, "ValVec Resize");
		vec->len = size;
		vec->cap = newcap;
		vec->data = newdata;
	} else {
		vec->len = size;
	}
	return 0;
}

/**
 * Release the memory buffer a value vector is holding
 *
 * @param vec a pointer to a valid value vector
 *
 */
void sptFreeValueVector(sptValueVector *vec) {
	vec->len = 0;
	vec->cap = 0;
	free(vec->data);
}


/*
 * Initialize a new sptIndex vector
 *
 * @param vec a valid pointer to an uninitialized sptIndex variable,
 * @param len number of values to create
 * @param cap total number of values to reserve
 *
 * Vector is a type of one-dimentional array with dynamic length
 */

int sptNewIndexVector(sptIndexVector *vec, sptNnzIndex len, sptNnzIndex cap) {
	if(cap < len) {
		cap = len;
	}
	if(cap < 2) {
		cap = 2;
	}
	vec->len = len;
	vec->cap = cap;
	vec->data = malloc(cap * sizeof *vec->data);
	spt_CheckOSError(!vec->data, "IdxVec New");
	memset(vec->data, 0, cap * sizeof *vec->data);
	return 0;
}


/**
 * Add a value to the end of a sptIndexVector
 *
 * @param vec   a pointer to a valid index vector
 * @param value the value to be appended
 *
 * The length of the size vector will be changed to contain the new value.
 */
int sptAppendIndexVector(sptIndexVector *vec, sptIndex const value) {
	if(vec->cap <= vec->len) {
#ifndef MEMCHECK_MODE
		sptNnzIndex newcap = vec->cap + vec->cap/2;
#else
		sptNnzIndex newcap = vec->len+1;
#endif
		sptIndex *newdata = realloc(vec->data, newcap * sizeof *vec->data);
		spt_CheckOSError(!newdata, "IdxVec Append");
		vec->cap = newcap;
		vec->data = newdata;
	}
	vec->data[vec->len] = value;
	++vec->len;
	return 0;
}

/**
 * Resize an index vector
 *
 * @param vec  the index vector to resize
 * @param size the new size of the index vector
 *
 * If the new size is larger than the current size, new values will be appended
 * but the values of them are undefined. If the new size if smaller than the
 * current size, values at the end will be truncated.
 */
int sptResizeIndexVector(sptIndexVector *vec, sptNnzIndex const size) {
	sptNnzIndex newcap = size < 2 ? 2 : size;
	if(newcap != vec->cap) {
		sptIndex *newdata = realloc(vec->data, newcap * sizeof *vec->data);
		spt_CheckOSError(!newdata, "IdxVec Resize");
		vec->len = size;
		vec->cap = newcap;
		vec->data = newdata;
	} else {
		vec->len = size;
	}
	return 0;
}

/**
 * Release the memory buffer a sptIndexVector is holding
 *
 * @param vec a pointer to a valid size vector
 *
 */
void sptFreeIndexVector(sptIndexVector *vec) {
	free(vec->data);
	vec->len = 0;
	vec->cap = 0;
}


