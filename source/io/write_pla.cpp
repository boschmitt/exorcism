/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#include <cstdio>
#include <vector>

#include "two_level.h"

namespace losys {

void
write_pla(two_lvl32 &rep, char *fname)
{
	FILE *fp = fopen(fname, "w+");
	fprintf(fp, ".i %d\n.o 1\n.p %d\n", esop.n_inputs, esop.esops[0].size());
	for (auto e : esop.esops[0])
		fprintf(fp, "%s 1\n", e.str(esop.n_inputs).c_str());
	fprintf(fp, ".e\n");
	fclose(fp);
}

}
