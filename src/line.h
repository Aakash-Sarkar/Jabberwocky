/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "point.h"
#include "color.h"
#include "geometry.h"




typedef			struct Line		{	Point2d_t				*p1;
									Point2d_t				*p2;
									Point2d_t				*slope;
									Point2d_t				*inv_slope;
								}	Line_t;



HOWTO_INIT						(	Line_t,
									self,
									Point2d_t	*p1,
									Point2d_t	*p2
								);


HOWTO_FINI						(	Line_t,		self	);

HOWTO_CPY						(	Line_t,		to,		frm	);

HOWTO_DRAW						(	Line_t,
									line,
									Point2d_t			*origin,
									Color_t				*color, 
									Color_buffer_t		*colorbuf
								);



