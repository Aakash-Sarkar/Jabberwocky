/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#pragma once

#include "util.h"




#define rotator(class)								concat3			(rotate, _, class)

#define	HOWTO_ROT(class, self, ...)					class*												\
													rotator			( class ) (	class* self,			\
																				__VA_ARGS__		)

#define	_ROT( class, self, ... )					rotator			( class ) ( self,	__VA_ARGS__ )

#define	ROT( class, self, ... )						do	{												\
															assert	(	self	);						\
															_ROT	(	class,							\
																		self,							\
																	__VA_ARGS__							\
																	);									\
													}	while		(	0	)




#define																									\
projector( class1, class2 )							concat7 ( project, _, class2, _, to, _, class1 )

#define																									\
HOWTO_PROJ( class1, class2, to, from, ... )			void												\
													projector ( class1, class2 )	(	class1*	to,		\
																						class2*	from,	\
																						__VA_ARGS__		\
																					)

#define																									\
_PROJ( class1, class2, to, from, ... )				projector	( class1, class2 )	(	to,				\
																						from,			\
																						__VA_ARGS__		\
																				)

#define																									\
PROJ( class1, class2, to, from, ... )				do													\
													{													\
														assert			(	from	);					\
														if				(	!to		)					\
														{												\
															DEF			(	class1,	to	);				\
														}												\
																										\
														assert			(	to 	);						\
																										\
														_PROJ			(	class1,		class2,			\
																			to,			from,			\
																			__VA_ARGS__					\
																		);								\
													}	while			(	0	)




#define painter( class )							concat3( draw, _, class )

#define																									\
HOWTO_DRAW( class, self, ... )						class*												\
													painter( class )	(	class* self,				\
																			__VA_ARGS__					\
																		)

#define	_DRAW( class, self, ... )					painter( class )	(	self,						\
																				__VA_ARGS__				\
																		)



#define																									\
DRAW( class, self, ... )							do													\
													{													\
																										\
														assert			(	self 	);					\
																										\
														_DRAW			(	class,						\
																			self,						\
																			__VA_ARGS__					\
																		);								\
													}	while			(	0	)
