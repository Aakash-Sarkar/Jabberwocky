/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "point.h"
#include "rect.h"



HOWTO_DEF						(	Point2d_t,	self	)
{
	DEF							(	Vec2_t,
									self->v
								);
}

HOWTO_CONSTRUCT					(	Point2d_t,
									self,
									float		x,
									float		y
								)
{
	NEW							(	Vec2_t,
									self->v,
									x,	y
								);
}

HOWTO_DESTRUCT					(	Point2d_t,	self	)
{
	DEL							(	Vec2_t,
									self->v
								);
}

HOWTO_DEF						(	Point3d_t,	self	)
{
	DEF							(	Vec3_t,
									self->v
								);
}

HOWTO_CONSTRUCT					(	Point3d_t,
									self,
									float		x,
									float		y,
									float		z
								)
{
	NEW							(	Vec3_t,
									self->v,
									x,	y,	z
								);
}

HOWTO_DESTRUCT					(	Point3d_t,	self	)
{
	DEL							(	Vec3_t,
									self->v
								);
}

HOWTO_DEF						(	ARRAY	(	Point2d_t	),	self	)
{
	DEF							(	ARRAY	(	Vec2_t	),
									self->v
								);

	self->count					=	0;
}

HOWTO_DEF						(	ARRAY	(	Point3d_t	),	self	)
{
	DEF							(	ARRAY	(	Vec3_t	),
									self->v
								);

	self->count					=	0;
}


HOWTO_DESTRUCT					(	ARRAY	(	Point2d_t	),	self	)
{
	DEL							(	ARRAY	(	Vec2_t	),
									self->v
								);

	self->count				=	0;
}

HOWTO_DESTRUCT					(	ARRAY	(	Point3d_t	),	self	)
{
	DEL							(	ARRAY	(	Vec3_t	),
									self->v
								);

	self->count				=	0;
}


HOWTO_LD						(	Point2d_t,
									ptr,
									arr,
									idx
								)
{
	LD							(	Vec2_t,
									ptr->v,
									arr->v,
									idx
								);
}

HOWTO_LD						(	Point3d_t,
									ptr,
									arr,
									idx
								)
{
	LD							(	Vec3_t,
									ptr->v,
									arr->v,
									idx
								);
}

HOWTO_STR						(	Point2d_t,	ptr,	arr,	idx	)
{
	STR							(	Vec2_t,
									ptr->v,
									arr->v,
									idx
								);
}

HOWTO_STR						(	Point3d_t,	ptr,	arr,	idx	)
{
	STR							(	Vec3_t,
									ptr->v,
									arr->v,
									idx
								);
}


HOWTO_PUSH						(	Point2d_t,	ptr,	arr		)
{
	PUSH						(	Vec2_t,
									ptr->v,
									arr->v
								);

	arr->count++;
}

HOWTO_PUSH						(	Point3d_t,	ptr,	arr		)
{
	PUSH						(	Vec3_t,
									ptr->v,
									arr->v
								);

	arr->count++;
}


HOWTO_CPY						(	Point2d_t,	to,		from	)
{
	CPY							(	Vec2_t,
									to->v,
									from->v
								);
}

HOWTO_CPY						(	Point3d_t,	to,		from	)
{
	CPY							(	Vec3_t,
									to->v,
									from->v
								);
}




HOWTO_ROT						(	Point2d_t,
									to,					from,
									Vec2_t				*angle
								)
{
}

HOWTO_ROT						(	Point3d_t,
									to,					from,
									Vec3_t				*angle
								)
{
	ROT							(	Vec3_t,	
									to->v,
									from->v,
									angle
								);
}




HOWTO_DRAW						(	Point2d_t,
									self,
									Point2d_t			*origin,
									Color_t				*color,
									Color_buffer_t		*colorbuf	)
{
	Rect_t							*rect		=	NULL;
	Point2d_t						*o_point	=	NULL;

	DEF							(	Point2d_t,
									o_point
								);

	//	By default all our points will be in the range (-1 * fov_scale) up to
	//	(+1 * fov_scale). This shifts the points to the center of the screen.

	ADD							(	Point2d_t,
									o_point,
									self,
									origin
								);

	int								posX	=	*o_point->v->x,
									posY	=	*o_point->v->y;

	NEW							(	Rect_t,
									rect,
									posX,
									posY,
									4,
									4
								);

	DRAW						(	Rect_t,
									rect,
									color,
									colorbuf
								);

	DEL							(	Rect_t,
									rect
								);

	DEL							(	Point2d_t,
									o_point
								);
}

HOWTO_DRAW						(	Point3d_t,
									self,
									Point2d_t			*origin,
									Color_t				*color,
									Color_buffer_t		*colorbuf	)
{
	Point2d_t						*proj	=	NULL;

	DEF							(	Point2d_t,
									proj
								);

	PROJ						(	Point2d_t,		Point3d_t,
									proj,			self,
									PERSPECTIVE
								);

	DRAW						(	Point2d_t,
									proj,
									origin,
									color,
									colorbuf
								);

	DEL							(	Point2d_t,
									proj
								);
}




HOWTO_PROJ						(	Point2d_t,			Point3d_t,
									to,					from,
									Projection_type_t	type		)
{

	PROJ						(	Vec2_t,				Vec3_t,
									to->v,				from->v,
									type
								);
}




//////////////////////////////////////////////////////////////////////////////////
//				Arithmetic Operations Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ADD					(	Point2d_t,	dst,	op1,	op2	)
{
	ADD						(	Vec2_t,
								dst->v,
								op1->v,
								op2->v
							);
}

HOWTO_ADD					(	Point3d_t,	dst,	op1,	op2	)
{
	ADD						(	Vec3_t,
								dst->v,
								op1->v,
								op2->v
							);
}


HOWTO_SUB					(	Point2d_t,	dst,	op1,	op2	)
{
	SUB						(	Vec2_t,
								dst->v,
								op1->v,	
								op2->v
							);
}

HOWTO_SUB					(	Point3d_t,	dst,	op1,	op2	)
{
	SUB						(	Vec3_t,
								dst->v,
								op1->v,
								op2->v
							);
}


HOWTO_MUL					(	Point2d_t,	dst,	src,	factor	)
{
	MUL						(	Vec2_t,
								dst->v,
								src->v,
								factor
							);

}

HOWTO_MUL					(	Point3d_t,	dst,	src,	factor	)
{
	MUL						(	Vec3_t,
								dst->v,
								src->v,
								factor
							);
}


HOWTO_DIV					(	Point2d_t,	dst,	src,	factor	)
{
	DIV						(	Vec2_t,
								dst->v,
								src->v,
								factor
							);

}

HOWTO_DIV					(	Point3d_t,	dst,	src,	factor	)
{
	DIV						(	Vec3_t,
								dst->v,
								src->v,
								factor
							);
}


HOWTO_DOTP					(	Point2d_t,	dst,	src1,	src2	)
{
	DOTP					(	Vec2_t,
								dst,
								src1->v,
								src2->v
							);
}

HOWTO_DOTP					(	Point3d_t,	dst,	src1,	src2	)
{
	DOTP					(	Vec3_t,
								dst,
								src1->v,
								src2->v
							);
}


HOWTO_CROSP					(	Point3d_t,	dst,	src1,	src2	)
{
	CROSP					(	Vec3_t,
								dst->v,
								src1->v,
								src2->v
							);
}