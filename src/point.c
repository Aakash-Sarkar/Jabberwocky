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
	LOAD						(	vec2_t,		&ptr->v,	&array->v,	idx	);
}

HOWTO_LOAD						(	Point3d_t,
									ptr,		array,		idx	)
{
	LOAD						(	vec3_t,		&ptr->v,	&array->v,	idx	);
}

HOWTO_STORE						(	Point2d_t,	ptr,		array	)
{
	STORE						(	vec2_t,		&ptr->v,	&array->v	);

	array->count++;
}

HOWTO_STORE						(	Point3d_t,	ptr,		array	)
{
	STORE						(	vec3_t,		&ptr->v,	&array->v	);

	array->count++;
}


HOWTO_COPY						(	Point2d_t,	to,			from	)
{
	COPY						(	vec2_t,		&to->v,		&from->v	);
}

HOWTO_COPY						(	Point3d_t,	to,			from	)
{
	COPY						(	vec3_t,		&to->v,		&from->v	);
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

	MEM							(	Rect_t,		rect,		1	);
	MEM							(	Point2d_t,	o_point,	1	);

	// By default all our points will be in the range (-1 * fov_scale) up to
	// (+1 * fov_scale). This shifts the points to the center of the screen.

	ADD							(	Point2d_t,	o_point,	point,	origin	);


	rect->posX					=	( int )	o_point->v.x;
	rect->posY					=	( int )	o_point->v.y;
	rect->width					=	4;
	rect->height				=	4;


	DRAW						(	Rect_t,		rect,		color,	colorbuf	);
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




//////////////////////////////////////////////////////////////////////////////////
//				Arithmetic Operations Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ADD					(	Point2d_t,	dst,	op1,	op2	)
{
	ADD						(	vec2_t,	&dst->v,	&op1->v,	&op2->v	);
}

HOWTO_ADD					(	Point3d_t,	dst,	op1,	op2	)
{
	ADD						(	vec3_t,	&dst->v,	&op1->v,	&op2->v	);
}


HOWTO_SUB					(	Point2d_t,	dst,	op1,	op2	)
{
	SUB						(	vec2_t,	&dst->v,	&op1->v,	&op2->v	);
}

HOWTO_SUB					(	Point3d_t,	dst,	op1,	op2	)
{
	SUB						(	vec3_t,	&dst->v,	&op1->v,	&op2->v	);
}


HOWTO_MUL					(	Point2d_t,	dst,	src,	factor	)
{
	MUL						(	vec2_t,	&dst->v,	&src->v,	factor	);

}

HOWTO_MUL					(	Point3d_t,	dst,	src,	factor	)
{
	MUL						(	vec3_t,	&dst->v,	&src->v,	factor	);
}


HOWTO_DOTP					(	Point2d_t,	dst,	src1,	src2	)
{
	DOTP					(	vec2_t,		dst,	&src1->v,	&src2->v	);
}

HOWTO_DOTP					(	Point3d_t,	dst,	src1,	src2	)
{
	DOTP					(	vec3_t,		dst,	&src1->v,	&src2->v	);
}


HOWTO_CROSSP				(	Point3d_t,	dst,	src1,	src2	)
{
	CROSSP					(	vec3_t,		&dst->v,	&src1->v,	&src2->v	);
}