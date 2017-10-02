/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#include <array>
#include <cassert>
#include <cstdio>
#include <cstdint>
#include <functional>
#include <string>

#include "cube32.h"

namespace exorcism {

cube32::cube32()
	: m_value(INVALID)
{ }

cube32::cube32(const std::uint64_t value)
	: m_value(value)
{ }

cube32::cube32(const std::uint32_t m, const std::uint32_t p)
	: m_mask(m), m_polarity(p)
{ }

bool
cube32::operator==(const cube32 that) const { return m_value == that.m_value; }

bool
cube32::operator!=(const cube32 that) const { return m_value != that.m_value; }

bool
cube32::operator< (const cube32 that) const { return m_value <  that.m_value; }

bool
cube32::operator==(const std::uint64_t value) const { return m_value == value; }

bool
cube32::operator!=(const std::uint64_t value) const { return m_value != value; }

cube32
cube32::operator&(const cube32 that) const
{
	const auto int_mask = m_mask & that.m_mask;
	if ((m_polarity ^ that.m_polarity) & int_mask)
		return ZERO;
	return cube32(m_value | that.m_value);
}

void
cube32::insert(const std::uint32_t var, const std::uint32_t p)
{
	assert(var < 32 && p <= 1);
	m_mask |= (1 << var);
	m_polarity |= (p << var);
}

void
cube32::remove(const std::uint32_t var)
{
	assert(var < 32);
	m_mask &= ~(1 << var);
	m_polarity &= ~(1 << var);
}

void
cube32::rotate(const std::uint32_t var)
{
	assert(var < 32);
	auto tmp = m_mask ^ (~m_polarity & (1 << var));
	m_polarity ^= ~(m_polarity ^ m_mask) & (1 << var);
	m_mask = tmp;
}

void
cube32::invert() { m_polarity ^= m_mask; }

std::uint32_t
cube32::n_lits() const { return __builtin_popcount(m_mask); }

std::string
cube32::str() const
{
	std::string s;
	for (auto i = 0; i < 32; ++i) {
		if (((m_mask >> i) & 1) == 0) {
			if (((m_polarity >> i) & 1))
				break;
			s.push_back('-');
		} else if (m_polarity & (1 << i))
			s.push_back('1');
		else
			s.push_back('0');
	}
	return s;
}

void
cube32::print() const
{
	for (auto i = 0; i < 32; i++) {
		if (((m_mask >> i) & 1) == 0) {
			if (((m_polarity >> i) & 1))
				break;
			fprintf(stdout, "-");
		} else if (m_polarity & (1 << i))
			fprintf(stdout, "1");
		else
			fprintf(stdout, "0");
	}
	fprintf(stdout, "\n");
}

std::uint32_t
difference(const cube32 lhs, const cube32 rhs)
{ return (lhs.m_polarity ^ rhs.m_polarity) | (lhs.m_mask ^ rhs.m_mask); }

std::uint32_t
distance(const cube32 lhs, const cube32 rhs)
{ return __builtin_popcount(difference(lhs, rhs)); }

cube32
merge(const cube32 lhs, const cube32 rhs)
{
	const auto diff = difference(lhs, rhs);
	return cube32(lhs.m_mask ^ (rhs.m_mask & diff),
	              lhs.m_polarity ^ (~rhs.m_polarity & diff));
}

std::array<cube32, 4>
exorlink(cube32 c0, cube32 c1, std::uint32_t dist, std::uint32_t *group)
{
	assert(dist <= 4);
	std::uint32_t diff = difference(c0, c1);
	std::array<cube32, 4> ret;
	if (c0.m_value > c1.m_value)
		std::swap(c0.m_value, c1.m_value);
	auto c_polarity = ~(c0.m_polarity) & ~(c1.m_polarity);
	auto c_mask = c0.m_mask ^ c1.m_mask;
	for (auto i = 0; i < dist; ++i) {
		auto tmp_polarity = c0.m_polarity;
		auto tmp_mask = c0.m_mask;
		auto tmp_pos  = diff;
		for (auto j = 0; j < dist; ++j) {
			/* compute next position */
			std::uint64_t p = tmp_pos & -(tmp_pos);
			tmp_pos &= tmp_pos - 1;
			switch (*group++) {
			case 0:
				/* take from c0 */
				break;
			case 1:
				/* take from c1 */
				tmp_polarity ^= ((c1.m_polarity & p) ^ tmp_polarity) & p;
				tmp_mask ^= ((c1.m_mask & p) ^ tmp_mask) & p;
				break;
			case 2:
				/* take other */
				tmp_polarity ^= ((c_polarity & p) ^ tmp_polarity) & p;
				tmp_mask ^= ((c_mask & p) ^ tmp_mask) & p;
				break;
			}
		}
		ret[i].m_polarity = tmp_polarity;
		ret[i].m_mask = tmp_mask;
	}
	return ret;
}

}
