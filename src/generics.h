/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "util.h"



#define                                                                             \
itr( class )								concat3 ( class, _, itr )

#define                                                                             \
arr( class )								concat3 ( class, _, arr )

#define                                                                             \
lst( class )								concat3 ( class, _, lst )

#define                                                                             \
cont( class )								concat3 ( class, _, cont )



#define																				\
init( class )								concat3 ( init,	_, class )

#define																				\
fini( class )								concat3 ( fini, _, class )

#define																				\
def( class )								concat3 ( def, _, class )

#define																				\
copy( class )								concat3 ( copy,	_, class )

#define																				\
ctor( class )								concat3 ( create, _, class )

#define																				\
dtor( class )								concat3 ( destroy, _, class )



#define																				\
cmp( class )								concat3 ( cmp,	_, class )

#define																				\
add( class )								concat3 ( add,	_, class )

#define																				\
sub( class )								concat3 ( sub,	_, class )

#define																				\
inc( class )								concat3 ( inc,	_,	class )

#define																				\
dec( class )								concat3 ( dec,	_,	class )

#define																				\
mul( class )								concat3 ( mul,	_, class )

#define																				\
div( class )								concat3 ( div,	_, class )

#define																				\
dotp( class )								concat3 ( dotp,	_, class )

#define																				\
crosp( class )								concat3 ( crosp,_, class )



#define																				\
iterate( class )							concat3(	itr,	_,	class	)