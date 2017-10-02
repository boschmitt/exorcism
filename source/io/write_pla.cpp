/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#include <cstdio>
#include <vector>

#include "two_level.h"

namespace exorcism {

void
write_pla(const two_lvl32 &pla, const char *fname)
{
	assert(pla.m_n_inputs < 32);
	assert(pla.m_fnct.size() == 1);
	FILE *fp = fopen(fname, "w+");

	fprintf(fp, ".i %u\n", pla.m_n_inputs);
	fprintf(fp, ".o 1\n");
	fprintf(fp, ".p %lu\n", pla.m_fnct[0].size());
	for (auto cube : pla.m_fnct[0])
		fprintf(fp, "%s 1\n", cube.str(pla.m_n_inputs).c_str());
	fprintf(fp, ".e\n");
	fclose(fp);
}

}
