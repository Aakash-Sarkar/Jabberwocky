/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>

#include "color.h"
#include "geometry.h"
#include "util.h"
#include "renderer.h"



typedef						struct		Rect	{	int					posX;
													int					posY;
													int					width;
													int					height;		}	Rect_t;


typedef						struct		Grid	{	int					width;
													int					height;
													int					border_len;	}	Grid_t;


/* Here beginneth the declarations of functions */


bool						pixel_at_border		(	Rect_t*			rect,
													int				posX,
													int				posY,
													int				border_len
												);



HOWTO_DRAW										(	Rect_t,
													self,
													Color_t*		color,
													Renderer_t*		renderer
												);


HOWTO_DRAW										(	Grid_t,
													self,
													Color_t*		color,
													Renderer_t*		renderer
												);



/**
 * Helper macro to iterate over all rectangles in a color buffer
 */
#define																				\
for_each_rect_in_buffer(n, rect, buf)	for (										\
												(	(n) = 0,						\
													(rect)->posX = 0,				\
													(rect)->posY = 0				\
												);									\
												(	(rect)->posX < (buf)->width		\
													&&								\
													(rect)->posY < (buf)->height	\
												);									\
												(	(n) += (rect)->width,			\
													(rect)->posX =	(				\
														(n) % (						\
															((buf)->width /			\
															(rect)->width) *		\
															(rect)->width			\
														)							\
													),								\
													(rect)->posY = (				\
														((n) / ((buf)->width))		\
														* ((rect)->height)			\
													)								\
												)									\
											)



#define																				\
for_each_posY_in_rect(rect, posY)		for (										\
												posY =  (rect)->posY;				\
												posY <  (rect)->posY +				\
														(rect)->height;				\
												posY++								\
											)


#define																				\
for_each_posX_in_rect(rect, posX)		for (										\
												posX =  (rect)->posX;				\
												posX <  (rect)->posX +				\
														(rect)->width;				\
												posX++								\
											)




