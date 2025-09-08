/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "color.h"

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

typedef						struct		Rect	{	int		posX;
													int		posY;
													int		width;
													int		height;	}	Rect_t;

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
bool						pixel_at_border		(	Rect_t*	rect,
													int		posX,
													int		posY,
													int		border_len	);

/**
 * @brief: paint a rectangle into color buffer
 * 
 * @param rect:							rectangle to paint 
 * @param interior_color:				color of pixels falling inside border
 * @param border_color:					color of pixels falling at the border
 * @param colorbuf:						buffer to write the color values
 * @param border_len:					thickness of border in pixels
 *
 * @return: SUCCESS if operation succeeds, FAIL otherwise
 */
bool						paint_rect			(	Rect_t*			rect,
													Color_t*		interior_color,
													Color_t*		border_color,
													Color_buffer_t*	colorbuf,
													int				border_len	);

/**
 * @brief: draw a rectangle into the color buffer
 *
 * @param colorbuf:						buffer to draw the rectangle
 * @param rect:							rectangle to draw
 *
 * @return: SUCCESS if operation succeeds, FAIL otherwise
 */
bool						draw_rectangle		(	Color_buffer_t*		colorbuf,
													Rect_t*				rect	);

bool						draw_grid			(	Color_buffer_t* colorbuf	);



/**
 * Helper macro to iterate over all rectangles in a color buffer
 */
#define																			\
for_each_rect_in_buffer(n, rect, buf)	for (									\
												(	(n) = 0,					\
													(rect)->posX = 0,			\
													(rect)->posY = 0			\
												);								\
												(	(rect)->posX < (buf)->width	\
													&&							\
													(rect)->posY < (buf)->height\
												);								\
												(	(n) += (rect)->width,		\
													(rect)->posX =	(			\
														(n) % (					\
															((buf)->width		\
															/					\
															(rect)->width)		\
															* (rect)->width		\
														)						\
													),							\
													(rect)->posY = (			\
														((n) / ((buf)->width))	\
														* ((rect)->height)		\
													)							\
												)								\
											)



#define																			\
for_each_posY_in_rect(rect, posY)		for (									\
												posY =  (rect)->posY;			\
												posY <  (rect)->posY +			\
														(rect)->height;			\
												posY++							\
											)


#define																			\
for_each_posX_in_rect(rect, posX)		for (									\
												posX =  (rect)->posX;			\
												posX <  (rect)->posX +			\
														(rect)->width;			\
												posX++							\
											)




