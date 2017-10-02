/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#ifndef EXORCISM_H
#define EXORCISM_H

#include <array>
#include <chrono>
#include <unordered_set>
#include <vector>

#include "cube32.h"
#include "two_level.h"

namespace exorcism {

/*------------------------------------------------------------------------------
| Exorcism manager
*-----------------------------------------------------------------------------*/
class exorcism_mngr {
public:
	exorcism_mngr(const std::vector<cube32> &, std::uint32_t, bool);
	std::vector<cube32> run();

private:
	int add_cube(const cube32 &, bool);
	int find_pairs(const cube32 &, std::uint32_t);
	unsigned exorlink2();

	void pairs_bookmark();
	void pairs_rollback();

private:
	bool m_verbose;
	typedef std::unordered_set<cube32, cube32_hash> hash_bucket;
	std::vector<hash_bucket> m_cubes;
	std::uint32_t m_n_vars;
	std::uint32_t m_n_cubes;

	std::vector<std::vector<std::pair<cube32, cube32>>> m_pairs;
	std::vector<std::vector<std::pair<cube32, cube32>>> m_pairs_tmp;

	/* Stats */
	std::array<uint32_t, 4> m_n_dist = {0, 0, 0, 0};

	/* Bookkeeping */
	std::array<std::uint32_t, 4> m_pairs_bookmark = {0, 0, 0, 0};

	/* Algorithm Control */
	std::uint32_t m_max_dist = 2;

	unsigned cube_groups2[8] = {2, 0, 1, 2,
                                    0, 2, 2, 1};
};

static two_lvl32 exorcise(const two_lvl32 &original, bool verbose = false)
{
	exorcism_mngr exor(original.m_fnct[0], original.m_n_inputs, verbose);
	auto ret = exor.run();
	return {two_lvl_type::ESOP, original.m_n_inputs, {ret}};
}

}

#endif
