/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "point.h"
#include "color.h"
#include "geometry.h"

typedef							struct Line {	Point2d_t	*p1;
												Point2d_t	*p2;	}	Line_t;




HOWTO_CONSTRUCT					(	Line_t,
									self,
									Point2d_t	*p1,
									Point2d_t	*p2		);

HOWTO_DESTRUCT					(	Line_t,	self	);

HOWTO_CPY						(	Line_t,	to,	from	);


HOWTO_DRAW						(	Line_t,
									self,
									Point2d_t*			origin,
									Color_t*			color, 
									Color_buffer_t*		colorbuf	);


