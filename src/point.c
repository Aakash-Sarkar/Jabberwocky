/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "point.h"
#include "rect.h"




HOWTO_ARRAY_INIT				(	Point2d_t,	array		)
{
	ARRAY_INIT					(	vec2_t,		&array->v	);
	array->count				=	0;
}

HOWTO_ARRAY_INIT				(	Point3d_t,	array		)
{
	ARRAY_INIT					(	vec3_t,		&array->v	);
	array->count				=	0;
}


HOWTO_ARRAY_RESET				(	Point2d_t,	array		)
{
	ARRAY_RESET					(	vec2_t,		&array->v	);
	array->count				=	0;
}

HOWTO_ARRAY_RESET				(	Point3d_t,	array		)
{
	ARRAY_RESET					(	vec3_t,		&array->v	);
	array->count				=	0;
}


HOWTO_LOAD						(	Point2d_t,
									ptr,		array,		idx	)
{
	LOAD						(	vec2_t,
									&ptr->v,	&array->v,	idx	);
}

HOWTO_LOAD						(	Point3d_t,
									ptr,		array,		idx	)
{
	LOAD						(	vec3_t,
									&ptr->v,	&array->v,	idx	);
}

HOWTO_STORE						(	Point2d_t,	ptr,		array	)
{
	STORE						(	vec2_t,
									&ptr->v,	&array->v	);

	array->count++;
}

HOWTO_STORE						(	Point3d_t,	ptr,		array	)
{
	STORE						(	vec3_t,
									&ptr->v,	&array->v	);

	array->count++;
}


HOWTO_COPY						(	Point2d_t,	to,			from	)
{
	COPY						(	vec2_t,
									&to->v,		&from->v	);
}

HOWTO_COPY						(	Point3d_t,	to,			from	)
{
	COPY						(	vec3_t,
									&to->v,		&from->v	);
}




HOWTO_ROTATE					(	Point2d_t,	to,	from,	vec2_t*	angle	)
{
}

HOWTO_ROTATE					(	Point3d_t,	to,	from,	vec3_t*	angle	)
{
	ROTATE						(	vec3_t,	
									&to->v,		&from->v,	angle	);
}




HOWTO_DRAW						(	Point2d_t,
									point,
									Point2d_t*			origin,
									Color_t*			color,
									Color_buffer_t*		colorbuf	)
{

	int								posX = 0,
									posY = 0;


	MEM							(	Rect_t,		rect,	1	);

	posX						=	( int )	(	point->v.x  +  origin->v.x	);
	posY						=	( int )	(	point->v.y  +  origin->v.y	);


	rect->posX					=	posX;
	rect->posY					=	posY;
	rect->width					=	4;
	rect->height				=	4;


	DRAW						(	Rect_t,
									rect,		color,		colorbuf	);
}

HOWTO_DRAW						(	Point3d_t,
									point,
									Point2d_t*			origin,
									Color_t*			color,
									Color_buffer_t*		colorbuf	)
{

	MEM							(	Point2d_t,		proj,	1	);

	PROJECT						(	Point2d_t,		Point3d_t,
									proj,			point,		PERSPECTIVE	);

	DRAW						(	Point2d_t,		proj,
									origin,			color,		colorbuf	);
}




HOWTO_PROJECT					(	Point2d_t,			Point3d_t,
									to,					from,
									Projection_type_t	type		)
{

	PROJECT						(	vec2_t,			vec3_t,
									&to->v,			&from->v,	type	);
}

