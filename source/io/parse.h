/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#ifndef IO__PARSE_H
#define IO__PARSE_H

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

namespace exorcism {

static inline void
parse_skip_spaces(char **pos)
{
	assert(pos != NULL);
	for (; (**pos == ' ') || (**pos == '\t'); (*pos)++);
}

static inline void
parse_skip_word(char **pos)
{
	assert(pos != NULL);
	for (; !isspace(**pos); (*pos)++);
}

static inline void
parse_skip_line(char **pos)
{
	assert(pos != NULL);
	for(; **pos != '\n' && **pos != '\r' && **pos != EOF; (*pos)++);
	if (**pos != EOF)
		(*pos)++;
	return;
}

static inline uint32_t
parse_read_ui32(char **token)
{
	uint32_t value = 0;

	parse_skip_spaces(token);
	if (!isdigit(**token)) {
		fprintf(stderr, "Parsing error. Unexpected char: %c.\n", **token);
		exit(1);
	}
	while (isdigit(**token)) {
		value = (value * 10) + (uint32_t)(**token - '0');
		(*token)++;
	}
	return value;
}

}

#endif
