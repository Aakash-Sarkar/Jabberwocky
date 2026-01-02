/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "util.h"
#include "color.h"





#define																					\
rotate( class )								concat3			(	rotate, _, class	)

#define																					\
HOWTO_ROT( class, to, from, ... )			void										\
											rotate			(	class	)				\
															(	class*		to,			\
																class*		from,		\
																		__VA_ARGS__		\
															)

#define																					\
_ROT( class, to, from, angle )				do											\
											{											\
												assert		(	to		);				\
												assert		(	from	);				\
																						\
												rotate		(	class	)				\
															(	to,						\
																from,					\
																angle					\
															);							\
											}	while		(	0	)


#define																					\
ROT( class, to, from, angle )				do											\
											{											\
												if			(	!to		)				\
													DEF		(	class,					\
																to						\
															);							\
																						\
												_ROT		(	class,					\
																to,						\
																from,					\
																angle					\
															);							\
											}	while		(	0	)




#define																					\
project( class1, class2 )					project_##class2##_to_##class1

#define																					\
HOWTO_PROJ( class1, class2, to, from, ... )	void										\
											project			(	class1,		class2	)	\
															(	class1		*to,		\
																class2		*from,		\
																__VA_ARGS__				\
															)

#define																					\
_PROJ( class1, class2, to, from, ... )		do											\
											{											\
												assert		(	to		);				\
												assert		(	from	);				\
																						\
												project		(	class1, class2	)		\
															(	to,		from,			\
																__VA_ARGS__				\
															);							\
											}	while		(	0	)


#define																					\
PROJ( class1, class2, to, from, ... )		do											\
											{											\
												if			(	!to		)				\
													DEF		(	class1,					\
																to						\
															);							\
																						\
												_PROJ		(	class1,					\
																class2,					\
																to,						\
																from,					\
																__VA_ARGS__				\
															);							\
											}	while		(	0	)

#define																					\
draw(class)										concat3		(	draw, _, class	)

#define																					\
HOWTO_DRAW( class, self, ... )					void									\
												draw		(	class	)				\
															(	class*		self,		\
																__VA_ARGS__				\
															)

#define																					\
DRAW( class, self, ... )						do										\
												{										\
													assert	(	self	);				\
													draw	(	class	)				\
															(	self,					\
																__VA_ARGS__				\
															);							\
												}	while	(	0	)

