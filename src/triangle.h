/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "color.h"
#include "point.h"




typedef							struct Face			{	int idx1;
														int idx2;
														int idx3;		}	Face_t;


typedef							struct Triangle3d	{	Point3d_t p1;
														Point3d_t p2;
														Point3d_t p3;	}	Triangle3d_t;


typedef							struct Triangle2d	{	Point2d_t p1;
														Point2d_t p2;
														Point2d_t p3;	}	Triangle2d_t;




typedef							DECL_ARRAY			(	Face_t,
														int*	idx1;
														int*	idx2;
														int*	idx3;	);

typedef							DECL_ARRAY			(	Triangle2d_t,
														ARRAY ( Point2d_t )		p1;
														ARRAY ( Point2d_t )		p2;
														ARRAY ( Point2d_t )		p3;	);

typedef							DECL_ARRAY			(	Triangle3d_t,
														ARRAY ( Point3d_t )		p1;
														ARRAY ( Point3d_t )		p2;
														ARRAY ( Point3d_t )		p3;	);



HOWTO_ARRAY_INIT				(	Face_t,			array	);

HOWTO_ARRAY_INIT				(	Triangle2d_t,	array	);

HOWTO_ARRAY_INIT				(	Triangle3d_t,	array	);




HOWTO_ARRAY_RESET				(	Face_t,			array	);

HOWTO_ARRAY_RESET				(	Triangle2d_t,	array	);

HOWTO_ARRAY_RESET				(	Triangle3d_t,	array	);




HOWTO_LOAD						(	Face_t,			ptr,	array,	idx		);

HOWTO_LOAD						(	Triangle2d_t,	ptr,	array,	idx		);

HOWTO_LOAD						(	Triangle3d_t,	ptr,	array,	idx		);


HOWTO_STORE						(	Face_t,			ptr,	array	);

HOWTO_STORE						(	Triangle2d_t,	ptr,	array	);

HOWTO_STORE						(	Triangle3d_t,	ptr,	array	);




HOWTO_COPY						(	Face_t,			to,	from	);

HOWTO_COPY						(	Triangle2d_t,	to,	from	);

HOWTO_COPY						(	Triangle3d_t,	to,	from	);




HOWTO_ROTATE					(	Triangle3d_t,	to,	from,	vec3_t* angle	);

HOWTO_ROTATE					(	Triangle2d_t,	to,	from,	vec2_t* angle	);




HOWTO_DRAW						(	Triangle2d_t,
									triangle,
									Point2d_t*			origin,
									Color_t*			color,
									Color_buffer_t*		colorbuf	);

HOWTO_DRAW						(	Triangle3d_t,
									triangle,
									Point2d_t*			origin,
									Color_t*			color,
									Color_buffer_t*		colorbuf	);




HOWTO_PROJECT					(	Triangle2d_t,		Triangle3d_t,
									to,					from,
									Projection_type_t	type	);





