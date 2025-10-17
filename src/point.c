/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "point.h"
#include "rect.h"




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


struct	Point3d					{	Vec3_t*		v;	};

struct	Point2d					{	Vec2_t*		v;	};


DECL_ARRAY						(	Point2d_t	)
{
	ARRAY ( Vec2_t )*				v;
	int								count;
};


DECL_ARRAY						(	Point3d_t	)
{
	ARRAY ( Vec3_t )*				v;
	int								count;
};


////////////////////////////////////////////////////////////////////////////////
//				Point Operations Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_COPY						(	Point2d_t,	to,		from	)
{
	COPY						(	vec2_t,
									to->v,
									from->v
								)	;
}

HOWTO_COPY						(	Point3d_t,	to,		from	)
{
	COPY						(	vec3_t,
									to->v,
									from->v
								)	;
}


HOWTO_COMPOSE					(	Point2d_t,
									self,
									float		x,
									float		y
								)
{
	COMPOSE						(	Vec2_t,
									self->v,
									x,
									y
								)	;
}

HOWTO_COMPOSE					(	Point3d_t,
									self,
									float		x,
									float		y,
									float		z
								)
{
	COMPOSE						(	Vec3_t,
									self->v,
									x,
									y,
									z
								)	;
}


HOWTO_CONSTRUCT					(	Point2d_t,
									self,
									float	x,
									float	y
								)
{
	ALLOC_ZEROED				(	Point2d_t,
									self,
									1
								);

	CONSTRUCT					(	Vec2_t,
									self->v,
									x,
									y
								);
}


HOWTO_CONSTRUCT					(	Point3d_t,
									self,
									float	x,
									float	y,
									float	z
								)
{
	ALLOC_ZEROED				(	Point3d_t,
									self,
									1
								);

	ASSERT						(	self != NULL, ""	);

	CONSTRUCT					(	Vec3_t,
									self->v,
									x,
									y,
									z
								);
}


HOWTO_DESTRUCT					(	Point2d_t,
									self
								)
{
	DESTRUCT					(	Vec2_t,
									self->v
								);

	DEALLOC						(	self	);
}


HOWTO_DESTRUCT					(	Point3d_t,
									self
								)
{
	DESTRUCT					(	Vec3_t,
									self->v
								);

	DEALLOC						(	self	);
}


/////////////////////////////////////////////////////////////////////////////////
//				Dynamic Array Operations Implementation
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ARRAY_INIT				(	Point2d_t,		self	)
{
	ARRAY_INIT					(	Vec2_t,
									self->v
								);

	self->count				=	0;
}

HOWTO_ARRAY_INIT				(	Point3d_t,		self	)
{
	ARRAY_INIT					(	Vec3_t,
									self->v
								);

	self->count				=	0;
}

HOWTO_ARRAY_RESET				(	Point2d_t,		self	)
{
	ARRAY_RESET					(	Vec2_t,
									self->v
								);

	self->count				=	0;
}

HOWTO_ARRAY_RESET				(	Point3d_t,		self	)
{
	ARRAY_RESET					(	Vec3_t,
									self->v
								);

	self->count				=	0;
}


HOWTO_CONSTRUCT				(	ARRAY ( Point2d_t ),
								self,
								void*	null
							)
{
	ALLOC_ZEROED			(	ARRAY ( Point2d_t ),
								self,
								1
							)	;

	ASSERT					(	self != NULL, ""	)	;

	CONSTRUCT				(	ARRAY ( Vec2_t ),
								self->v,
								NULL
							)	;

	ARRAY_INIT				(	Point2d_t,	self	)	;
}

HOWTO_CONSTRUCT				(	ARRAY ( Point3d_t ),
								self,
								void*	null
							)
{
	ALLOC_ZEROED			(	ARRAY ( Point3d_t ),
								self,
								1
							)	;

	ASSERT					(	self != NULL, ""	)	;

	CONSTRUCT				(	ARRAY ( Vec3_t ),
								self->v,
								NULL
							)	;

	ARRAY_INIT				(	Point3d_t,	self	)	;
}

HOWTO_DESTRUCT				(	ARRAY ( Point2d_t ),
								self
							)
{
}

HOWTO_DESTRUCT				(	ARRAY ( Point3d_t ),
								self
							)
{
}


HOWTO_LOAD						(	Point2d_t,	self,	array,	idx		)
{
	LOAD						(	Vec2_t,
									self->v,
									array->v,
									idx
								);
}

HOWTO_LOAD						(	Point3d_t,	self,	array,	idx		)
{
	LOAD						(	Vec3_t,
									self->v,
									array->v,
									idx
								);
}

HOWTO_PUSH						(	Point2d_t,	self,	array	)
{
	PUSH						(	Vec2_t,
									self->v,
									array->v
								);

	array->count++;
}

HOWTO_PUSH						(	Point3d_t,	self,	array	)

{
	PUSH						(	Vec3_t,
									self->v,
									array->v
								);

	array->count++;
}

HOWTO_STORE						(	Point2d_t,	self,	array,	idx		)
{
	Point2d_t						zero = { 0 };

	while						(	array->count	<=	idx		)
	{
		PUSH					(	Point2d_t,
									&zero,
									array
								);
	}

	STORE						(	Vec2_t,
									self->v,
									array->v,
									idx
								);
}

HOWTO_STORE						(	Point3d_t,	self,	array,	idx		)
{
	Point3d_t						zero = { 0 };

	while						(	array->count	<=	idx	)
	{
		PUSH					(	Point3d_t,
									&zero,
									array
								);
	}

	STORE						(	Vec3_t,
									self->v,
									array->v,
									idx
								);
}


//////////////////////////////////////////////////////////////////////////////////
//				Geomertic Operations Implementations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ROTATE					(	Point2d_t,
									self,
									Vec2_t*		angle
								)
{
}

HOWTO_ROTATE					(	Point3d_t,
									self,
									Vec3_t*		angle
								)
{
	ROTATE						(	Vec3_t,
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
	TMP							(	Rect_t,
									rect,
									1
								);

	TMP							(	Point2d_t,
									o_point,
									1
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
									&renderer->origin
								);

	rect->posX					=	( int )	o_point->v->x;
	rect->posY					=	( int )	o_point->v->y;
	
	rect->width					=	4;
	rect->height				=	4;

	DRAW						(	Rect_t,
									rect,
									color,
									renderer->buffer
								);
}

HOWTO_DRAW						(	Point3d_t,
									self,
									Color_t*			color,
									Renderer_t*			renderer
								)
{
	TMP							(	Point2d_t,
									proj,
									1
								);

	PROJECT						(	Point2d_t,			Point3d_t,
									proj,				self,
									PERSPECTIVE
								);

	DRAW						(	Point2d_t,
									proj,
									color,
									renderer
								);
}

HOWTO_PROJECT					(	Point2d_t,			Point3d_t,
									to,					from,
									Projection_type_t	type	)
{
	PROJECT						(	Vec2_t,				Vec3_t,
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

HOWTO_INC					(	Point2d_t,	self,	inc		)
{
	INC						(	Vec2_t,
								self->v,
								inc->v
							);
}

HOWTO_INC					(	Point3d_t,	self,	inc		)
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



