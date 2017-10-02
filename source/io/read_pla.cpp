/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "cube32.h"
#include "io.h"
#include "parse.h"
#include "two_level.h"

namespace exorcism {

/*------------------------------------------------------------------------------
| Reads file into memory buffer.
| Returns NULL in case of error.
*-----------------------------------------------------------------------------*/
static inline char *
file_read(const char *fname)
{
	FILE *file = fopen(fname, "rb");
	size_t fsize;
	char *buffer;

	if (file == NULL) {
		fprintf(stderr, "Couldn't open file: %s\n", fname);
		return NULL;
	}
	fseek(file, 0, SEEK_END);
	fsize = (size_t)ftell(file);
	rewind(file);
	/* Alloc a memory buffer bigger than fsize to append '\0' at the end of
	 * buffer. This way, while parsing we are garanteed to know when EOF */
	buffer = (char *) malloc(sizeof *buffer * (fsize + 3));
	fread(buffer, fsize, 1, file);
	buffer[fsize] = '\n';
	buffer[fsize + 1] = '\0';
	return buffer;
}

/*------------------------------------------------------------------------------
| Read and parse PLA file.
*-----------------------------------------------------------------------------*/
two_lvl32
read_pla(const char *fname, const bool verbose = false)
{
	two_lvl32 pla;
	char *buffer;

	buffer = file_read(fname);
	if (buffer == NULL)
		return pla;
	/* Parsing Header */
	char *tk = buffer;
	std::uint32_t n_inputs = 0;
	std::uint32_t n_outputs = 0;
	std::uint32_t n_terms;
	/* Handle directives */
	while (1) {
		parse_skip_spaces(&tk);
		if (*tk == '.') {
			++tk;
			if (*tk == 'i') {
				++tk;
				n_inputs = parse_read_ui32(&tk);
			}
			if (*tk == 'o') {
				++tk;
				n_outputs = parse_read_ui32(&tk);
			}
			if (*tk == 'p') {
				++tk;
				n_terms = parse_read_ui32(&tk);
			}
			parse_skip_line(&tk);
			continue;
		}
		/* Ignore comments */
		if (*tk == '#') {
			parse_skip_line(&tk);
			continue;
		}
		break;
	}
	if (n_inputs > 32 || n_outputs > 1) {
		fprintf(stdout, "[e] Limitations: 32 inputs, 1 output.\n");
		assert(0);
	}
	if (verbose) {
		fprintf(stdout, "[i] inputs: %d\n", n_inputs);
		fprintf(stdout, "[i] outputs: %d\n", n_outputs);
		fprintf(stdout, "[i] reading PLA as an ESOP.\n");
	}

	pla.m_type = two_lvl_type::ESOP;
	pla.m_n_inputs = n_inputs;
	pla.m_fnct.push_back({});
	while (1) {
		if (*tk == EOF)
			break;
		parse_skip_spaces(&tk);
		/* Look for file end directive (.e) */
		if (strncmp(tk, ".e", 2) == 0)
			break;
		assert(*tk == '0' || *tk == '1' || *tk == '-');
		char *tk_end = tk + n_inputs;
		if (!isspace(*tk_end)) {
			fprintf(stderr, "Cube input data is inconsistent with the declared attributes");
			break;
		}
		cube32 c;
		for (std::uint32_t i = 0; i < n_inputs; ++i, ++tk) {
			switch (*tk) {
			case '-': break;
			case '1': c.insert(i, 1); break;
			case '0': c.insert(i, 0); break;
			}
		}
		pla.m_fnct[0].push_back(c);
		parse_skip_spaces(&tk);
		tk_end = tk + n_outputs;
		if (!isspace(*tk_end)) {
			fprintf(stderr, "Cube output data is inconsistent with the declared attributes");
			break;
		}
		parse_skip_line(&tk);
	}
	return pla;
}

}
