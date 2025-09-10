/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "color.h"
#include "point.h"

typedef							struct Face			{	int idx[3];		}	Face_t;


typedef							struct Triangle3d	{	Point3d_t p1;
														Point3d_t p2;
														Point3d_t p3;	}	Triangle3d_t;


typedef							struct Triangle2d	{	Point2d_t p1;
														Point2d_t p2;
														Point2d_t p3;	}	Triangle2d_t;


HOWTO_COPY					(	Face_t,		to,	from	);

HOWTO_COPY					(	Triangle3d_t,	to,	from	);


HOWTO_ROTATE				(	Triangle3d_t,	to,	from,	vec3_t angle	);

HOWTO_ROTATE				(	Triangle2d_t,	to,	from,	vec3_t angle	);


HOWTO_DRAW					(	Triangle2d_t,
								triangle,
								Point2d_t*			origin,
								Color_t*			color,
								Color_buffer_t*		colorbuf	);

HOWTO_DRAW					(	Triangle3d_t,
								triangle,
								Point2d_t*			origin,
								Color_t*			color,
								Color_buffer_t*		colorbuf	);


HOWTO_PROJECT				(	Triangle2d_t,		Triangle3d_t,
								to,					from,
								Projection_type_t	type	);




