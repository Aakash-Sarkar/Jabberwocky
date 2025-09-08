/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "color.h"
#include "point.h"

typedef						struct Face			{	int idx[3];		}	Face_t;

typedef						struct Triangle3d	{	Point3d_t p1;
													Point3d_t p2;
													Point3d_t p3;	}	Triangle_t;



HOWTO_COPY					(	Face_t,		to,	from	);

HOWTO_COPY					(	Triangle_t,	to,	from	);

HOWTO_ROTATE				(	Triangle_t,	to,	from,	vec3_t angle	);


HOWTO_DRAW					(	Triangle_t,
								triangle,
								Point2d_t*			origin,
								Color_t*			color,
								Color_buffer_t*		colorbuf	);







