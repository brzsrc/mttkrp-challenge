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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

/**
 * Global variables to store last error code and information
 */
static __thread struct {
		const char *module;
		int errcode;
		const char *file;
		unsigned line;
		char *reason;
} g_last_error = { NULL, 0, NULL, 0, NULL };

/**
 * Set last error information as specified and print the error message.
 * Should not be called directly, use the macro `spt_CheckError`.
 */
void spt_ComplainError(const char *module, int errcode, const char *file, unsigned line, const char *reason) {
	g_last_error.errcode = errcode;
	g_last_error.module = module;
	g_last_error.file = file;
	g_last_error.line = line;
	if(reason) {
		free(g_last_error.reason);
		g_last_error.reason = strdup(reason);
		if(!g_last_error.reason) {
			abort();
		}
	}
	if(g_last_error.reason && g_last_error.reason[0] != '\0') {
		fprintf(stderr, "[%s] error 0x%08x at %s:%u, %s\n",
						g_last_error.module,
						g_last_error.errcode,
						g_last_error.file,
						g_last_error.line,
						g_last_error.reason
		);
	} else {
		fprintf(stderr, "[%s] error 0x%08x at %s:%u\n",
						g_last_error.module,
						g_last_error.errcode,
						g_last_error.file,
						g_last_error.line
		);
	}
}


