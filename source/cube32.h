/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#ifndef CUBE32_H
#define CUBE32_H

#include <array>
#include <cstdio>
#include <cstdint>
#include <functional>
#include <string>

namespace exorcism {

class cube32 {
public:
	/* Constants */
	static const std::uint64_t ZERO = 0x00000000FFFFFFFFULL;
	static const std::uint64_t ONE  = 0x0000000000000000ULL;
	static const std::uint64_t INVALID = 0xFFFFFFFF00000000ULL;

	union {
		struct {
			std::uint32_t m_mask;
			std::uint32_t m_polarity;
		};
		std::uint64_t m_value;
	};

	/* Constructors */
	cube32();
	cube32(const std::uint64_t);
	cube32(const std::uint32_t, const std::uint32_t);

	/* Comparing to cube32 */
	bool operator==(const cube32) const;
	bool operator!=(const cube32) const;
	bool operator< (const cube32) const;

	/* Comparing against std::uint64_t */
	bool operator==(const std::uint64_t) const;
	bool operator!=(const std::uint64_t) const;

	cube32 operator&(const cube32) const;
	cube32 operator^(const cube32) const;
	cube32 operator=(const std::uint64_t) const;

	void insert(const std::uint32_t, const std::uint32_t);
	void remove(const std::uint32_t);
	void rotate(const std::uint32_t);
	void invert();

	std::uint32_t n_lits() const;
	std::string str() const;
	void print() const;
	void print_as_vec() const;
};

struct cube32_hash {
	std::size_t
	operator()(const cube32 &c) const {
		return std::hash<std::uint64_t>()(c.m_value);
	}
};

/*------------------------------------------------------------------------------
| Returns a bitmap indicating the variables for which the corresponding
| literals have different values.
*-----------------------------------------------------------------------------*/
std::uint32_t difference(const cube32, const cube32);

/*------------------------------------------------------------------------------
| The distance of two cubes is the number of variables for which the 
| corresponding literals have different values.
*-----------------------------------------------------------------------------*/
std::uint32_t distance(const cube32, const cube32);


std::array<cube32, 4> exorlink(cube32, cube32, std::uint32_t, std::uint32_t *);
cube32 merge(const cube32, const cube32);

}

#endif
