/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#ifndef LOSYS__TWO_LEVEL_H
#define LOSYS__TWO_LEVEL_H
#include <cassert>
#include <cstdint>
#include <vector>

#include "cube32.h"

namespace exorcism {

enum class two_lvl_type : uint8_t {
	SOP,
	ESOP,
	INVALID
};

struct two_lvl32 {
	two_lvl_type  m_type;
	std::uint32_t m_n_inputs;
	std::vector<std::vector<cube32>> m_fnct;
};

inline void print_stats(struct two_lvl32 &fnt, bool print_cubes = false)
{
	switch (fnt.m_type) {
	case two_lvl_type::SOP:
		fprintf(stdout, "[SOP] ");
		break;
	case two_lvl_type::ESOP:
		fprintf(stdout, "[ESOP] ");
		break;
	default:
		assert(0);
	}
	uint32_t n_cubes = 0;
	uint32_t n_lits = 0;
	for (auto f : fnt.m_fnct) {
		n_cubes += f.size();
		for (auto c : f) {
			n_lits += c.n_lits();
			if (print_cubes)
				c.print();
		}
		fprintf(stdout, "Cubes = %5lu\n", f.size());
	}
}

}
#endif

