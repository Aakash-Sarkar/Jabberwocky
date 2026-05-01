/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "generics.h"



#define																					\
HOWTO_ROT( class, self, ... )				void										\
											rotate			(	class	)				\
															(	class*		self,		\
																		__VA_ARGS__		\
															)

#define																					\
_ROT( class, self, angle )					rotate			(	class	)				\
															(	self,					\
																angle					\
															)

#define																					\
ROT( class, self, angle )					do											\
											{											\
												assert		(	self	);				\
												assert		(	angle	);				\
																						\
												_ROT		(	class,					\
																self,					\
																angle					\
															);							\
																						\
											}	while		(	0	)



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
																						\
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


#define																					\
fill( class )									concat3		(	fill, _, class	)

#define																					\
HOWTO_FILL( class, self, ... )					void									\
												fill		(	class	)				\
															(	class		*self,		\
																__VA_ARGS__				\
															)

//////////////////////////////////////////////////////////////////////////////////
//							FILL SCANLINE:
//////////////////////////////////////////////////////////////////////////////////
//
//
//		A scanline here represents a horizontal line segment on the 2D grid of
//		pixels on the screen that will be filled with a specific color in the
//		color buffer.
//
//							x_start				x_end
// 
//							^					^
//							|					|
//				+ - + - + - + - + - + - + - + - + - + - + - +	
//				:	:	:	:	:	:	:	:	:	:	:	:
//				+ - + - + - + - + - + - + - + - + - + - + - +
//				:	:	:	:	:	:	:	:	:	:	:	:
//				+ - + - + - + - + - + - + - + - + - + - + - +
//				:	:	:	:	:	:	:	:	:	:	:	:
//				+ - + - + - +---+---+---+---+---+ - + - + - +
//				:	:	:	|||||||||||||||||||||	:	:	:	->	posY
//				+ - + - + - +---+---+---+---+---+ - + - + - +
//				:	:	:	:	scanline		:	:	:	:
//				+ - + - + - + - + - + - + - + - + - + - + - +
//				:	:	:	:	:	:	:	:	:	:	:	:
//				+ - + - + - + - + - + - + - + - + - + - + - +
//				:	:	:	:	:	:	:	:	:	:	:	:
//				+ - + - + - + - + - + - + - + - + - + - + - +
//
//
//		A scanline is defined with the following parameters:
//
//		posY:		The y-coordinate of the scanline
//		x_start:	The starting x-coordinate of the scanline
//		x_end:		The ending x-coordinate of the scanline
//
//
//////////////////////////////////////////////////////////////////////////////////

#define																					\
FILL_SCANLINE( _x_start, _x_end, _posY,													\
				_origin, _clr, _clrbuf )		do										\
												{										\
													Point2d_t		*_p1	=	NULL,	\
																	*_p2	=	NULL;	\
																						\
													Line_t			*_scanline	=	NULL;	\
																						\
													NEW			(	Point2d_t,			\
																	_p1,				\
																	_x_start,			\
																	_posY				\
																);						\
																						\
													NEW			(	Point2d_t,			\
																	_p2,				\
																	_x_end,				\
																	_posY				\
																);						\
																						\
													NEW			(	Line_t,				\
																	_scanline,			\
																	_p1,				\
																	_p2					\
																);						\
																						\
													DRAW		(	Line_t,				\
																	_scanline,			\
																	_origin,			\
																	_clr,				\
																	_clrbuf				\
																);						\
																						\
													DEL			(	Line_t,				\
																	_scanline			\
																);						\
																						\
													DEL			(	Point2d_t,			\
																	_p1					\
																);						\
																						\
													DEL			(	Point2d_t,			\
																	_p2					\
																);						\
																						\
												}	while	(	0	)


#define																					\
FILL( class, _self, ... )						do										\
												{										\
													assert	(	_self	);				\
																						\
													fill	(	class	)				\
															(	_self,					\
																__VA_ARGS__				\
															);							\
												}	while	(	0	)

