'' FreeBASIC binding for gsl-1.16
''
'' based on the C header files:
''   permutation/gsl_permute_ulong.h
''
''   Copyright (C) 1996, 1997, 1998, 1999, 2000, 2007 Brian Gough
''
''   This program is free software; you can redistribute it and/or modify
''   it under the terms of the GNU General Public License as published by
''   the Free Software Foundation; either version 3 of the License, or (at
''   your option) any later version.
''
''   This program is distributed in the hope that it will be useful, but
''   WITHOUT ANY WARRANTY; without even the implied warranty of
''   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
''   General Public License for more details.
''
''   You should have received a copy of the GNU General Public License
''   along with this program; if not, write to the Free Software
''   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
''
'' translated to FreeBASIC by:
''   FreeBASIC development team

#pragma once

#include once "crt/long.bi"
#include once "crt/stdlib.bi"
#include once "gsl/gsl_errno.bi"
#include once "gsl/gsl_permutation.bi"

extern "C"

#define __GSL_PERMUTE_ULONG_H__
declare function gsl_permute_ulong(byval p as const uinteger ptr, byval data as culong ptr, byval stride as const uinteger, byval n as const uinteger) as long
declare function gsl_permute_ulong_inverse(byval p as const uinteger ptr, byval data as culong ptr, byval stride as const uinteger, byval n as const uinteger) as long

end extern
