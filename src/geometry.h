/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#pragma once

#include "util.h"




#define rotator(class)								concat3(rotate, _, class)

#define	HOWTO_ROTATE(class, self, ...)				class*												\
													rotator( class )	(	class*	self,				\
																			__VA_ARGS__		)

#define	ROTATE( class, self, ... )					rotator( class )	( self,	__VA_ARGS__ )




#define projector( class1, class2 )					concat7(project, _, class2, _, to, _, class1)

#define																									\
HOWTO_PROJECT( class1, class2, to, from, ... )		void												\
													projector( class1, class2 )	(	class1*	to,			\
																					class2*	from,		\
																					__VA_ARGS__			\
																				)

#define																									\
PROJECT( class1, class2, to, from, ... )			projector( class1, class2 ) (	to,					\
																					from,				\
																					__VA_ARGS__			\
																				)




#define painter( class )							concat3( draw, _, class )

#define																									\
HOWTO_DRAW( class, self, ... )						class*												\
													painter( class )	(	class* self,				\
																			__VA_ARGS__					\
																		)

#define	DRAW(class, obj, ...)						painter( class )	(	self,						\
																				__VA_ARGS__				\
																		)

