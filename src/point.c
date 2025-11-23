/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "point.h"
#include "rect.h"




////////////////////////////////////////////////////////////////////////////////
//				Point Structures Implementation
////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////
//
//
//		We could also do a `typedef vec3_t point3d_t` here, but then again,
//		someone would certainly try to pass a position vector in a function
//		for colors. Doing it this way will at least give us a compilation
//		error.
//
//
//		Another, more nuanced way of thinking about this is the following:
//
//		Each vector lives in a vector space and can only be added to or
//		subtracted from other vectors living in the same space. For e.g,
//		our point vectors as described by the X, Y and Z co-ordinates of
//		our point, together form a point space and can only be added to
//		or subtracted from other point vectors in the same space.
//
//
//		However,  if we choose a point vector from a different co-ordinate
//		system ( i.e, with different X, Y and Z axes ), and try to add it
//		to our point vector; then it's not a valid mathematical operation.
//		We may get some resulting vector by doing this, but in a geometric
//		sense this new vector doesn't have any valid meaning since the two
//		vectors come from different co-ordinate spaces.
//
//
//		To give another example of this from a different domain:
//
//		If we subtract two velocity vectors, we get the relative velocity
//		of one with respect to the other. Same goes with subtracting two
//		displacement vectors. But if we try to subtract a velocity vector
//		from a displacement vector; the resulting vector isn't a valid
//		physical quantity.
//
//
//		In physics textbooks this is described in terms of the two vectors
//		having different units; but in mathematical terms one could also
//		describe this as the two vectors living in different vector spaces.
//
//
//////////////////////////////////////////////////////////////////////////////////


struct	Point2d					{	Vec2_t *	v;	};


struct	Point3d					{	Vec3_t *	v;	};


DECL_ARRAY	(	Point2d_t	)	{	ARRAY ( Vec2_t ) *	v;
									int					count;
								};


DECL_ARRAY	(	Point3d_t	)	{	ARRAY ( Vec3_t ) *	v;
									int					count;
								};


////////////////////////////////////////////////////////////////////////////////
//				Point Operations Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_CPY						(	Point2d_t,	to,	from	)
{
	CPY							(	Vec2_t,
									to->v,
									from->v
								);
}

HOWTO_CPY						(	Point3d_t,	to,	from	)
{
	CPY							(	Vec3_t,
									to->v,
									from->v
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


HOWTO_DESTRUCT					(	Point2d_t,
									self
								)
{
	DEL							(	Vec2_t,
									self->v
								);
}


HOWTO_DESTRUCT					(	Point3d_t,	self	)
{
	DEL							(	Vec3_t,
									self->v
								);
}


/////////////////////////////////////////////////////////////////////////////////
//				Dynamic Array Operations Implementation
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ARRAY_INIT				(	ARRAY ( Point2d_t ),	self	)
{
	INIT						(	Vec2_t,
									self->v
								);

	self->count					=	0;
}

HOWTO_ARRAY_INIT				(	ARRAY ( Point3d_t ),	self	)
{
	INIT						(	Vec3_t,
									self->v
								);

	self->count					=	0;
}

HOWTO_ARRAY_RESET				(	ARRAY ( Point2d_t ),	self	)
{
	ARRAY_RESET					(	Vec2_t,	self->v	);

	self->count					=	0;
}

HOWTO_ARRAY_RESET				(	ARRAY ( Point3d_t ),	self	)
{
	ARRAY_RESET					(	Vec3_t,	self->v	);

	self->count					=	0;
}


HOWTO_CONSTRUCT					(	ARRAY ( Point2d_t ),
									self,
									void*	null
								)
{
	DEF							(	ARRAY ( Vec2_t ),
									self->v
								);

	INIT						(	ARRAY ( Point2d_t ),	self	);
}

HOWTO_CONSTRUCT					(	ARRAY ( Point3d_t ),
									self,
									void*	null
								)
{
	DEF							(	ARRAY ( Vec3_t ),
									self->v
								);

	INIT						(	ARRAY ( Point3d_t ),	self	)	;
}

HOWTO_DESTRUCT					(	ARRAY ( Point2d_t ),	self	)
{
}

HOWTO_DESTRUCT					(	ARRAY ( Point3d_t ),	self	)
{
}


HOWTO_LD						(	Point2d_t,	self,	array,	idx		)
{
	LD							(	Vec2_t,
									self->v,
									array->v,
									idx
								);
}

HOWTO_LD						(	Point3d_t,	self,	array,	idx		)
{
	LD							(	Vec3_t,
									self->v,
									array->v,
									idx
								);
}

HOWTO_STR						(	Point2d_t,	self,	array,	idx		)
{
	STR							(	Vec2_t,
									self->v,
									array->v,
									idx
								);
}

HOWTO_STR						(	Point3d_t,	self,	array,	idx		)
{
	STR							(	Vec3_t,
									self->v,
									array->v,
									idx
								);
}


HOWTO_COUNT					(	ARRAY ( Point2d_t ),	self	)
{
	ASSERT					(	self != EMPTY, ""	);

	RETURN					(	COUNT	( ARRAY( Vec2_t ),
										self->v
										)
							);
}

HOWTO_COUNT					(	ARRAY ( Point3d_t ),	self	)
{
	ASSERT					(	self != EMPTY, ""	);

	RETURN					(	COUNT	( ARRAY( Vec3_t ),
										self->v
										)
							);
}


HOWTO_INC					(	ARRAY ( Point2d_t ),	self,	int inc	)
{
	INC						(	ARRAY ( Vec2_t ),
								self->v,
								inc
							);
}

HOWTO_INC					(	ARRAY ( Point3d_t ),	self,	int inc	)
{
	INC						(	ARRAY ( Vec3_t ),
								self->v,
								inc
							);
}



//////////////////////////////////////////////////////////////////////////////////
//				Geomertic Operations Implementations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ROT						(	Point2d_t,
									self,
									Vec2_t*		angle
								)
{
}

HOWTO_ROT						(	Point3d_t,
									self,
									Vec3_t*		angle
								)
{
	ROT							(	Vec3_t,
									self->v,
									angle
								);
}

HOWTO_DRAW						(	Point2d_t,
									self,
									Color_t*		color,
									Renderer_t*		renderer
								)
{
	Rect_t							*rect	=	NULL;

	Point2d_t						*o_point	=	NULL,
									*origin		=	NULL;


	DEF							(	Point2d_t,
									o_point
								);

	DEF							(	Point2d_t,
									origin
								);

	MSG							(	Renderer_t,
									get_origin,
									renderer,
									origin
								);


//////////////////////////////////////////////////////////////////////////////////
//
//
//		By default all our points will be in the range (-1 * fov_scale) up to
//		(+1 * fov_scale). This shifts the points to the center of the screen.
//
//
//////////////////////////////////////////////////////////////////////////////////


	ADD							(	Point2d_t,
									o_point,
									self,
									origin
								);

	float							posX	=	0,
									posY	=	0;

	MSG							(	Point2d_t,
									decompose,
									o_point,
									&posX,	&posY
								);

	NEW							(	Rect_t,
									rect,
									posX,	posY,
									4,		4
								);

	DRAW						(	Rect_t,
									rect,
									color,
									renderer
								);

	DEL							(	Rect_t,
									rect
								);

	DEL							(	Point2d_t,
									o_point
								);

	DEL							(	Point2d_t,
									origin
								);
}

HOWTO_DRAW						(	Point3d_t,
									self,
									Color_t*			color,
									Renderer_t*			renderer
								)
{
	Point2d_t						*proj	=	NULL;

	DEF							(	Point2d_t,
									proj
								);

	PROJ						(	Point2d_t,			Point3d_t,
									proj,				self,
									PERSPECTIVE
								);

	DRAW						(	Point2d_t,
									proj,
									color,
									renderer
								);

	DEL							(	Point2d_t,
									proj
								);
}

HOWTO_PROJ						(	Point2d_t,			Point3d_t,
									to,					from,
									Projection_type_t	type	)
{
	PROJ						(	Vec2_t,				Vec3_t,
									to->v,				from->v,
									type
								);
}


//////////////////////////////////////////////////////////////////////////////////
//				Arithmetic Operations Implementation
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//
//
//		Adding or subtracting two points may be strange, but adding or
//		subtracting two point vectors is a valid mathematical operation.
//		This is why we treat points as vectors in Computer Graphics
//
//
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ADD					(	Point2d_t,	dst,	op1,	op2		)
{
	ADD						(	Vec2_t,
								dst->v,
								op1->v,
								op2->v
							);
}

HOWTO_ADD					(	Point3d_t,	dst,	op1,	op2		)
{
	ADD						(	Vec3_t,
								dst->v,
								op1->v,
								op2->v
							);
}

HOWTO_SUB					(	Point2d_t,	dst,	op1,	op2		)
{
	SUB						(	Vec2_t,
								dst->v,
								op1->v,
								op2->v
							);
}

HOWTO_SUB					(	Point3d_t,	dst,	op1,	op2		)
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

HOWTO_NORM					(	Point2d_t,	self	)
{
	NORM					(	Vec2_t,
								self->v
							);
}

HOWTO_NORM					(	Point3d_t,	self	)
{
	NORM					(	Vec3_t,
								self->v
							);
}

HOWTO_INC					(	Point2d_t,	self,	Point2d_t * inc		)
{
	INC						(	Vec2_t,
								self->v,
								inc->v
							);
}

HOWTO_INC					(	Point3d_t,	self,	Point2d_t * inc		)
{
	INC						(	Vec3_t,
								self->v,
								inc->v
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

HOWTO_CROSSP				(	Point3d_t,	dst,	src1,	src2	)
{
	CROSSP					(	Vec3_t,
								dst->v,
								src1->v,
								src2->v
							);
}



DEFINE_TYPE					(	Point3d_t,	NULL	);



