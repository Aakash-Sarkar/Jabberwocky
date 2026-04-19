/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "util.h"
#include "color.h"





#define																					\
rotate( class )								concat3			(	rotate, _, class	)

#define																					\
HOWTO_ROT( class, self, ... )				void										\
											rotate			(	class	)				\
															(	class*		self,		\
																		__VA_ARGS__		\
															)

#define																					\
__ROT( class, self, angle )					rotate			(	class	)				\
															(	self,					\
																angle					\
															)

#define																					\
_ROT( class, self, angle )				do												\
											{											\
												assert		(	self	);				\
												assert		(	angle	);				\
																						\
												__ROT		(	class,					\
																self,					\
																angle					\
															);							\
																						\
											}	while		(	0	)


#define																					\
ROT( class, self, angle )				do												\
											{											\
												_ROT		(	class,					\
																self,					\
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
draw( class )									concat3		(	draw, _, class	)

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

#define																					\
_FILL(	x_start,	x_end,																\
		y_start,	y_end,																\
		x_inc,		x_inc2,																\
		y_inc,		y_inc2,																\
		origin_x,	origin_y,															\
		color,		colorbuf	)				do										\
												{										\
													int			posX	=	0,			\
																posY	=	0;			\
																						\
																						\
													x_start	=	x_start	+	origin_x;	\
													x_end	=	x_end	+	origin_x;	\
																						\
													y_start	=	y_start	+	origin_y;	\
													y_end	=	y_end	+	origin_y;	\
																						\
																						\
													for		(	posY	=	y_start;	\
																posY	<=	y_end;		\
																posY	+=	y_inc		\
															)							\
													{									\
														for (	posX	=	x_start;	\
																posX	<=	x_end;		\
																posX	+=	x_inc		\
															)							\
														{								\
															paint_color	(	color,		\
																			colorbuf,	\
																			PIXELFORMAT_ARGB8888,	\
																			posX,		\
																			posY,		\
																			0			\
																		);				\
														}								\
																						\
													}									\
												}	while	(	0	)


#define																					\
FILL( class, self, ... )						do										\
												{										\
													assert	(	self	);				\
																						\
													fill	(	class	)				\
															(	self,					\
																__VA_ARGS__				\
															);							\
												}	while	(	0	)

