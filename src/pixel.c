/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "pixel.h"




struct Pixel				{	uint32_t	color;
								int			posX;
								int			posY;
							};


struct Image				{	ARRAY ( Pixel_t )	pixels;
								Rect_t				rect;
								Format_type_t		format_type;
								int					size;
							};


struct Patch				{	ARRAY ( Pixel_t )	pixels;	};