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

#include "kmp.h"

// Thomas H. Cormen; Charles E. Leiserson, Ronald L. Rivest, Clifford Stein (2001).
// "Section 32.4: The Knuth-Morris-Pratt algorithm". Introduction to Algorithms (Second ed.).
// MIT Press and McGraw-Hill. pp. 923–931. ISBN 978-0-262-03293-3.

// KMP compute prefix function
// char *pattern - pattern to be processed
// int len - length of pattern
// int *pf - pointer to storage for prefix function
void KMPPrefixFunction(char *pattern, int len, int *pf) {
	pf[0] = 0;
	int k = 0;
	for (int q = 1; q != len; ++q) {
		while ((k != 0) && (pattern[k + 1] != pattern[q])) {
			k = pf[k];
		}
		if (pattern[k + 1] == pattern[q]) {
			++k;
		}
		pf[q] = k;
	}
}

