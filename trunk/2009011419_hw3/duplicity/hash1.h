/*
 *  Copyright (C) 2011 Tianyang Li
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author Tianyang Li
 * E-Mail tmy1018 gmail com
 */

#ifndef HASH1_H
#define HASH1_H

#include <stdint.h>
#include <cstddef>

// FNV hash http://isthe.com/chongo/tech/comp/fnv/
inline uint32_t Hash1(char *str) {
	static uint32_t const kOffsetBasis = 2166136261u;
	static uint32_t const kFNVPrime = 16777619u;
	// these 2 constants taken from http://isthe.com/chongo/tech/comp/fnv/
	uint32_t hash = kOffsetBasis;
	while (*str != '\0') {
		// hash += (hash << 1) + (hash << 4) + (hash << 7) + (hash << 8) + (hash << 24);
		// see hash_32.c at http://isthe.com/chongo/tech/comp/fnv/
		hash *= kFNVPrime;
		hash ^= (uint32_t)(*str);
	}
	return hash;
}

#endif
