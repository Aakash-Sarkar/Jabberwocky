/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "array.h"
#include "line.h"
#include "renderer.h"
#include "triangle.h"




struct							Triangle3d
{
	Point3d_t *					p1	;

	Point3d_t *					p2	;

	Point3d_t *					p3	;
};


struct							Triangle2d
{
	Point2d_t *					p1	;

	Point2d_t *					p2	;

	Point2d_t *					p3	;
};


DECL_ARRAY					(	Triangle2d_t	)
{
	ARRAY ( Point2d_t ) *		p1	;

	ARRAY ( Point2d_t ) *		p2	;

	ARRAY ( Point2d_t ) *		p3	;

	int							count	;
};


DECL_ARRAY					(	Triangle3d_t	)
{
	ARRAY ( Point3d_t ) *		p1	;

	ARRAY ( Point3d_t ) *		p2	;

	ARRAY ( Point3d_t ) *		p3	;

	int							count	;
};


////////////////////////////////////////////////////////////////////////////////
//				Triangle Operations Implementation
////////////////////////////////////////////////////////////////////////////////



HOWTO_COPY					(	Triangle2d_t,	to,	from	)
{
	COPY					(	Point2d_t,
								to->p1,
								from->p1
							)	;

	COPY					(	Point2d_t,
								to->p2,
								from->p2
							)	;

	COPY					(	Point2d_t,
								to->p3,
								from->p3
							)	;
}


HOWTO_COPY					(	Triangle3d_t,	to,	from	)
{
	COPY					(	Point3d_t,
								to->p1,
								from->p1
							)	;

	COPY					(	Point3d_t,
								to->p2,
								from->p2
							)	;

	COPY					(	Point3d_t,
								to->p3,
								from->p3
							)	;
}


HOWTO_COMPOSE				(	Triangle3d_t,
								self,
								Point3d_t*		p1,
								Point3d_t*		p2,
								Point3d_t*		p3
							)
{
	COPY					(	Point3d_t,
								self->p1,
								p1
							)	;

	COPY					(	Point3d_t,
								self->p2,
								p2
							)	;

	COPY					(	Point3d_t,
								self->p3,
								p3
							)	;
}


HOWTO_CONSTRUCT				(	Triangle2d_t,
								self,
								float	x1,		float	y1,
								float	x2,		float	y2,
								float	x3,		float	y3
							)
{
	ALLOC_ZEROED			(	Triangle2d_t,
								self,
								1
							)	;

	ASSERT					(	self != NULL, ""	);

	CONSTRUCT				(	Point2d_t,
								self->p1,
								x1,		y1
							)	;

	CONSTRUCT				(	Point2d_t,
								self->p2,
								x2,		y2
							)	;

	CONSTRUCT				(	Point2d_t,
								self->p3,
								x3,		y3
							)	;
}


HOWTO_CONSTRUCT				(	Triangle3d_t,
								self,
								float	x1,		float	y1,		float	z1,
								float	x2,		float	y2,		float	z2,
								float	x3,		float	y3,		float	z3
							)
{
	ALLOC_ZEROED			(	Triangle3d_t,
								self,
								1
							)	;

	ASSERT					(	self != NULL, " "	)	;

	CONSTRUCT				(	Point3d_t,
								self->p1,
								x1,		y1,		z1
							)	;

	CONSTRUCT				(	Point3d_t,
								self->p2,
								x2,		y2,		z2
							)	;

	CONSTRUCT				(	Point3d_t,
								self->p3,
								x3,		y3,		z3
							)	;
}


HOWTO_DESTRUCT				(	Triangle2d_t,
								self
							)
{
	DESTRUCT				(	Point2d_t,
								self->p1
							)	;

	DESTRUCT				(	Point2d_t,
								self->p2
							)	;

	DESTRUCT				(	Point2d_t,
								self->p3
							)	;

	DEALLOC					(	self	);
}


HOWTO_DESTRUCT				(	Triangle3d_t,
								self
							)
{
	DESTRUCT				(	Point3d_t,
								self->p1
							)	;

	DESTRUCT				(	Point3d_t,
								self->p2
							)	;

	DESTRUCT				(	Point3d_t,
								self->p3
							)	;

	DEALLOC					(	self	)	;
}




/////////////////////////////////////////////////////////////////////////////////
//				Dynamic Array Operations Implementation
/////////////////////////////////////////////////////////////////////////////////




HOWTO_ARRAY_INIT			(	Triangle2d_t,	self	)
{
	ARRAY_INIT				(	Point2d_t,
								self->p1
							)	;

	ARRAY_INIT				(	Point2d_t,
								self->p2
							)	;

	ARRAY_INIT				(	Point2d_t,
								self->p3
							)	;

	self->count				=	0	;
}


HOWTO_ARRAY_INIT			(	Triangle3d_t,	self	)
{
	ARRAY_INIT				(	Point3d_t,
								self->p1
							)	;

	ARRAY_INIT				(	Point3d_t,
								self->p2
							)	;

	ARRAY_INIT				(	Point3d_t,
								self->p3
							)	;

	self->count				=	0	;
}



HOWTO_ARRAY_RESET			(	Triangle2d_t,	self	)
{
	ARRAY_RESET				(	Point2d_t,
								self->p1
							)	;

	ARRAY_RESET				(	Point2d_t,
								self->p2
							)	;

	ARRAY_RESET				(	Point2d_t,
								self->p3
							)	;

	self->count				=	0	;
}


HOWTO_ARRAY_RESET			(	Triangle3d_t,	self	)
{
	ARRAY_RESET				(	Point3d_t,
								self->p1
							)	;

	ARRAY_RESET				(	Point3d_t,
								self->p2
							)	;

	ARRAY_RESET				(	Point3d_t,
								self->p3
							)	;

	self->count				=	0	;
}


HOWTO_CONSTRUCT				(	ARRAY ( Triangle2d_t ),
								self,
								void*	null
							)
{
	ALLOC_ZEROED			(	ARRAY ( Triangle2d_t ),
								self,
								1
							)	;

	ASSERT					(	self != NULL, " "	)	;

	CONSTRUCT				(	ARRAY ( Point2d_t ),
								self->p1,
								NULL
							)	;

	CONSTRUCT				(	ARRAY ( Point2d_t ),
								self->p2,
								NULL
							)	;

	CONSTRUCT				(	ARRAY ( Point2d_t ),
								self->p3,
								NULL
							)	;

	ARRAY_INIT				(	Triangle2d_t,	self	)	;
}


HOWTO_CONSTRUCT				(	ARRAY ( Triangle3d_t ),
								self,
								void*	null
							)
{
	ALLOC_ZEROED			(	ARRAY ( Triangle3d_t ),
								self,
								1
							)	;

	ASSERT					(	self != NULL, " "	)	;

	CONSTRUCT				(	ARRAY ( Point3d_t ),
								self->p1,
								NULL
							)	;

	CONSTRUCT				(	ARRAY ( Point3d_t ),
								self->p2,
								NULL
							)	;

	CONSTRUCT				(	ARRAY ( Point3d_t ),
								self->p3,
								NULL
							)	;

	ARRAY_INIT				(	Triangle3d_t,	self	)	;
}


HOWTO_DESTRUCT				(	ARRAY ( Triangle2d_t ),
								self
							)
{
}

HOWTO_DESTRUCT				(	ARRAY ( Triangle3d_t ),
								self
							)
{
}


HOWTO_LOAD					(	Triangle2d_t,	self,	array,	idx	)
{
	LOAD					(	Point2d_t,
								self->p1,
								array->p1,
								idx
							)	;

	LOAD					(	Point2d_t,
								self->p2,
								array->p2,
								idx
							)	;

	LOAD					(	Point2d_t,
								self->p3,
								array->p3,
								idx
							)	;
}


HOWTO_LOAD					(	Triangle3d_t,	self,	array,	idx	)
{
	LOAD					(	Point3d_t,
								self->p1,
								array->p1,
								idx
							)	;

	LOAD					(	Point3d_t,
								self->p2,
								array->p2,
								idx
							)	;

	LOAD					(	Point3d_t,
								self->p3,
								array->p3,
								idx
							)	;
}


HOWTO_PUSH					(	Triangle2d_t,	self,	array	)
{
	PUSH					(	Point2d_t,
								self->p1,
								array->p1
							)	;

	PUSH					(	Point2d_t,
								self->p2,
								array->p2
							)	;

	PUSH					(	Point2d_t,
								self->p3,
								array->p3
							)	;

	array->count++	;
}


HOWTO_PUSH					(	Triangle3d_t,	self,	array	)
{
	PUSH					(	Point3d_t,
								self->p1,
								array->p1
							)	;

	PUSH					(	Point3d_t,
								self->p2,
								array->p2
							)	;

	PUSH					(	Point3d_t,
								self->p3,
								array->p3
							)	;

	array->count++	;
}


HOWTO_STORE					(	Triangle2d_t,	self,	array,	idx	)
{
	TMP						(	Triangle2d_t,
								zero,
								1
							)	;

	while					(	array->count <= idx	)
	{
		PUSH				(	Triangle2d_t,
								zero,
								array
							)	;
	}

	STORE					(	Point2d_t,
								self->p1,
								array->p1,
								idx
							)	;

	STORE					(	Point2d_t,
								self->p2,
								array->p2,
								idx
							)	;

	STORE					(	Point2d_t,
								self->p3,
								array->p3,
								idx
							)	;
}


HOWTO_STORE					(	Triangle3d_t,	self,	array,	idx	)
{
	TMP						(	Triangle3d_t,
								zero,
								1
							)	;

	while					(	array->count <= idx		)
	{
		PUSH				(	Triangle3d_t,
								zero,
								array
							)	;
	}

	STORE					(	Point3d_t,
								self->p1,
								array->p1,
								idx
							)	;

	STORE					(	Point3d_t,
								self->p2,
								array->p2,
								idx
							)	;

	STORE					(	Point3d_t,
								self->p3,
								array->p3,
								idx
							)	;
}


//////////////////////////////////////////////////////////////////////////////////
//				Geomertic Operations Implementations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ROTATE				(	Triangle2d_t,
								self,
								Vec2_t*			angle
							)
{
}


HOWTO_ROTATE				(	Triangle3d_t,
								self,
								Vec3_t*			angle
							)
{

	ROTATE					(	Point3d_t,
								self->p1,
								angle
							)	;

	ROTATE					(	Point3d_t,
								self->p2,
								angle
							)	;

	ROTATE					(	Point3d_t,
								self->p3,
								angle
							)	;
}


HOWTO_DRAW					(	Triangle2d_t,
								self,
								Color_t*		color,
								Renderer_t*		renderer
							)
{

	TMP						(	Line_t,
								line1,
								1
							)	;

	TMP						(	Line_t,
								line2,
								1
							)	;

	TMP						(	Line_t,
								line3,
								1
							)	;

	// Compose the edges	

	COMPOSE					(	Line_t,
								line1,
								self->p1,
								self->p2
							)	;

	COMPOSE					(	Line_t,
								line2,
								self->p2,
								self->p3
							)	;

	COMPOSE					(	Line_t,
								line3,
								self->p1,
								self->p3
							)	;


	// Draw the vertices	

	DRAW					(	Point2d_t,
								self->p1,
								color,
								renderer
							)	;

	DRAW					(	Point2d_t,
								self->p2,
								color,
								renderer
							)	;

	DRAW					(	Point2d_t,
								self->p3,
								color,
								renderer
							)	;


	// Draw the edges

	DRAW					(	Line_t,
								line1,
								color,
								renderer
							)	;

	DRAW					(	Line_t,
								line2,
								color,
								renderer
							)	;

	DRAW					(	Line_t,
								line3,
								color,
								renderer
							)	;
}


HOWTO_DRAW					(	Triangle3d_t,
								self,
								Color_t*			color,
								Renderer_t*			renderer
							)
{

	TMP						(	Triangle2d_t,
								projection,
								1
							)	;

	PROJECT					(	Triangle2d_t,		Triangle3d_t,
								projection,			self,
								PERSPECTIVE	
							)	;

	DRAW					(	Triangle2d_t,
								projection,
								color,
								renderer
							)	;
}


HOWTO_PROJECT				(	Triangle2d_t,		Triangle3d_t,
								to,					from,
								Projection_type_t	type
							)
{
	PROJECT					(	Point2d_t,			Point3d_t,
								to->p1,				from->p1,
								type
							)	;

	PROJECT					(	Point2d_t,			Point3d_t,
								to->p2,				from->p2,
								type
							)	;

	PROJECT					(	Point2d_t,			Point3d_t,
								to->p3,				from->p3,
								type
							)	;
}

