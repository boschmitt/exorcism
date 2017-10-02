/*------------------------------------------------------------------------------
| This file is distributed under the BSD 2-Clause License.
| See LICENSE for details.
*-----------------------------------------------------------------------------*/
#ifndef IO__IO_H
#define IO__IO_H

#include "two_level.h"

namespace exorcism {

two_lvl32 read_pla(const char *, const bool);
void write_pla(const two_lvl32 &, const char *);

}
#endif
