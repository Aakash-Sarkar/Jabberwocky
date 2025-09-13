/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "object.h"
#include "geometry.h"

/**
 * VECTORS:
 *
 */

typedef					struct				Vec2	{	float x;
														float y;	}	vec2_t;

typedef					struct				Vec3	{	float x;
														float y;
														float z;	}	vec3_t;

typedef					struct				Vec4	{	float x;
														float y;
														float z;
														float w;	}	vec4_t;



/** PROJECTION:
 *
 * Projection is the method by which a 3D object is
 * represented on a 2D plane. The methods of projection
 * is used to determine how a 3D object will look when
 * viewed from a certain angle.
 */

typedef					enum		Projection_type	{	ORTHOGRAPHIC	= 0,
														ISOMETRIC,
														PERSPECTIVE			}
														Projection_type_t;





HOWTO_COPY							(	vec2_t,	to,	from	);

HOWTO_COPY							(	vec3_t,	to,	from	);




HOWTO_ROTATE						(	vec3_t,	to,	from,	vec3_t* angle	);




HOWTO_PROJECT						(	vec2_t,		vec3_t,
										to,			from,
										Projection_type_t			type	);



