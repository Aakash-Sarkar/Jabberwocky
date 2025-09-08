/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>

#include "color.h"
#include "geometry.h"
#include "util.h"

/**
 * @brief Rect: A Rectangle
 * 
 * Defines a rectangle using four parameters:
 * 
 * posX:								X coordinate of the rectangle on screen.
 * posY:								Y coodrinate of the rectangle  on screen
 * width:								width of the rectangle
 * height:								height of the rectangle
 *
 */

typedef						struct		Rect	{	int					posX;
													int					posY;
													int					width;
													int					height;		}	Rect_t;


typedef						struct		Grid	{	int					width;
													int					height;
													int					border_len;	}	Grid_t;


/* Here beginneth the declarations of functions */


/**
 * @brief: Check if the pixel is at the border of rectangle
 * 
 * @param rect:							Rectangle to check
 * @param posX:							X co-ordinate of the pixel
 * @param posY:							Y co-ordinate of the pixel
 * @param border_len:					border thickness in pixels
 * 
 * @return: true if the pixel is at the border, false otherwise
 */
bool						pixel_at_border		(	Rect_t*				rect,
													int					posX,
													int					posY,
													int					border_len	);


/**
 * @brief: draw a rectangle into the color buffer
 *
 * @return: SUCCESS if operation succeeds, FAIL otherwise
 */
HOWTO_DRAW										(	Rect_t,
													rect,
													Color_t*			color,
													Color_buffer_t*		colorbuf	);


HOWTO_DRAW										(	Grid_t,
													grid,
													Color_t*			color,
													Color_buffer_t*		colorbuf	);



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




