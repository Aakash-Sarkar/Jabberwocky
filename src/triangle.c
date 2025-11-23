/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "array.h"
#include "line.h"
#include "renderer.h"
#include "triangle.h"




struct							Triangle3d
{
	Point3d_t *					p1;
	Point3d_t *					p2;
	Point3d_t *					p3;
};


struct							Triangle2d
{
	Point2d_t *					p1;
	Point2d_t *					p2;
	Point2d_t *					p3;
};


DECL_ARRAY					(	Triangle2d_t	)
{
	ARRAY ( Point2d_t ) *		p1;
	ARRAY ( Point2d_t ) *		p2;
	ARRAY ( Point2d_t ) *		p3;
};


DECL_ARRAY					(	Triangle3d_t	)
{
	ARRAY ( Point3d_t ) *		p1;
	ARRAY ( Point3d_t ) *		p2;
	ARRAY ( Point3d_t ) *		p3;
};


////////////////////////////////////////////////////////////////////////////////
//				Triangle Operations Implementation
////////////////////////////////////////////////////////////////////////////////



HOWTO_CPY					(	Triangle2d_t,	to,	from	)
{
	CPY						(	Point2d_t,
								to->p1,
								from->p1
							);

	CPY						(	Point2d_t,
								to->p2,
								from->p2
							);

	CPY						(	Point2d_t,
								to->p3,
								from->p3
							);
}


HOWTO_CPY					(	Triangle3d_t,	to,	from	)
{
	CPY						(	Point3d_t,
								to->p1,
								from->p1
							);

	CPY						(	Point3d_t,
								to->p2,
								from->p2
							);

	CPY						(	Point3d_t,
								to->p3,
								from->p3
							);
}


HOWTO_CONSTRUCT				(	Triangle2d_t,
								self,
								float	x1,		float	y1,
								float	x2,		float	y2,
								float	x3,		float	y3
							)
{
	NEW						(	Point2d_t,
								self->p1,
								x1,		y1
							);

	NEW						(	Point2d_t,
								self->p2,
								x2,		y2
							);

	NEW						(	Point2d_t,
								self->p3,
								x3,		y3
							);
}


HOWTO_CONSTRUCT				(	Triangle3d_t,
								self,
								float	x1,		float	y1,		float	z1,
								float	x2,		float	y2,		float	z2,
								float	x3,		float	y3,		float	z3
							)
{
	NEW						(	Point3d_t,
								self->p1,
								x1,		y1,		z1
							);

	NEW						(	Point3d_t,
								self->p2,
								x2,		y2,		z2
							);

	NEW						(	Point3d_t,
								self->p3,
								x3,		y3,		z3
							);
}


HOWTO_DESTRUCT				(	Triangle2d_t,
								self
							)
{
	DEL						(	Point2d_t,
								self->p1
							);

	DEL						(	Point2d_t,
								self->p2
							);

	DEL						(	Point2d_t,
								self->p3
							);
}


HOWTO_DESTRUCT				(	Triangle3d_t,
								self
							)
{
	DEL						(	Point3d_t,
								self->p1
							);

	DEL						(	Point3d_t,
								self->p2
							);

	DEL						(	Point3d_t,
								self->p3
							);
}




/////////////////////////////////////////////////////////////////////////////////
//				Dynamic Array Operations Implementation
/////////////////////////////////////////////////////////////////////////////////




HOWTO_ARRAY_INIT			(	ARRAY ( Triangle2d_t ),	self	)
{
	INIT					(	ARRAY ( Point2d_t ),
								self->p1
							);

	INIT					(	ARRAY ( Point2d_t ),
								self->p2
							);

	INIT					(	ARRAY ( Point2d_t ),
								self->p3
							);
}


HOWTO_ARRAY_INIT			(	ARRAY ( Triangle3d_t ),	self	)
{
	INIT					(	ARRAY ( Point3d_t ),
								self->p1
							);

	INIT					(	ARRAY ( Point3d_t ),
								self->p2
							);

	INIT					(	ARRAY ( Point3d_t ),
								self->p3
							);
}



HOWTO_ARRAY_RESET			(	ARRAY ( Triangle2d_t ),	self	)
{
	ARRAY_RESET				(	ARRAY ( Point2d_t ),
								self->p1
							)	;

	ARRAY_RESET				(	ARRAY ( Point2d_t ),
								self->p2
							)	;

	ARRAY_RESET				(	ARRAY ( Point2d_t ),
								self->p3
							)	;
}


HOWTO_ARRAY_RESET			(	ARRAY ( Triangle3d_t ),	self	)
{
	ARRAY_RESET				(	ARRAY ( Point3d_t ),
								self->p1
							)	;

	ARRAY_RESET				(	ARRAY ( Point3d_t ),
								self->p2
							)	;

	ARRAY_RESET				(	ARRAY ( Point3d_t ),
								self->p3
							)	;
}


HOWTO_CONSTRUCT				(	ARRAY ( Triangle2d_t ),
								self,
								void*	null
							)
{
	DEF						(	ARRAY ( Point2d_t ),
								self->p1
							);

	DEF						(	ARRAY ( Point2d_t ),
								self->p2
							);

	DEF						(	ARRAY ( Point2d_t ),
								self->p3
							);

	INIT					(	ARRAY ( Triangle2d_t ),	self	)	;
}


HOWTO_CONSTRUCT				(	ARRAY ( Triangle3d_t ),
								self,
								void*	null
							)
{
	DEF						(	ARRAY ( Point3d_t ),
								self->p1
							);

	DEF						(	ARRAY ( Point3d_t ),
								self->p2
							);

	DEF						(	ARRAY ( Point3d_t ),
								self->p3
							);

	INIT					(	ARRAY ( Triangle3d_t ),	self	)	;
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


HOWTO_LD					(	Triangle2d_t,	self,	array,	idx	)
{
	LD						(	Point2d_t,
								self->p1,
								array->p1,
								idx
							);

	LD						(	Point2d_t,
								self->p2,
								array->p2,
								idx
							);

	LD						(	Point2d_t,
								self->p3,
								array->p3,
								idx
							);
}


HOWTO_LD					(	Triangle3d_t,	self,	array,	idx	)
{
	LD						(	Point3d_t,
								self->p1,
								array->p1,
								idx
							);

	LD						(	Point3d_t,
								self->p2,
								array->p2,
								idx
							);

	LD						(	Point3d_t,
								self->p3,
								array->p3,
								idx
							);
}


HOWTO_STR					(	Triangle2d_t,	self,	array,	idx	)
{

	STR						(	Point2d_t,
								self->p1,
								array->p1,
								idx
							)	;

	STR						(	Point2d_t,
								self->p2,
								array->p2,
								idx
							)	;

	STR						(	Point2d_t,
								self->p3,
								array->p3,
								idx
							)	;
}


HOWTO_STR					(	Triangle3d_t,	self,	array,	idx	)
{
	STR						(	Point3d_t,
								self->p1,
								array->p1,
								idx
							);

	STR						(	Point3d_t,
								self->p2,
								array->p2,
								idx
							);

	STR						(	Point3d_t,
								self->p3,
								array->p3,
								idx
							)	;
}


HOWTO_COUNT					(	ARRAY ( Triangle2d_t ),	self	)
{
	ASSERT					(	self != EMPTY, ""	);

	RETURN					(	COUNT ( ARRAY( Point2d_t ),
								self->p1 )
							);
}

HOWTO_COUNT					(	ARRAY ( Triangle3d_t ),	self	)
{
	ASSERT					(	self != EMPTY, ""	);

	RETURN					(	COUNT ( ARRAY ( Point3d_t ),
								self->p1 )
							);
}


HOWTO_INC					(	ARRAY ( Triangle2d_t ), self, int inc	)
{
	assert					(	self->p1 and
								self->p2 and
								self->p3
							);

	INC						(	ARRAY ( Point2d_t ),
								self->p1,
								inc
							);

	INC						(	ARRAY ( Point2d_t ),
								self->p2,
								inc
							);

	INC						(	ARRAY ( Point2d_t ),
								self->p3,
								inc
							);
}

HOWTO_INC					(	ARRAY ( Triangle3d_t ),	self, int inc	)
{
	assert					(	self->p1 and
								self->p2 and
								self->p3
							);

	INC						(	ARRAY ( Point3d_t ),
								self->p1,
								inc
							);

	INC						(	ARRAY ( Point3d_t ),
								self->p2,
								inc
							);

	INC						(	ARRAY ( Point3d_t ),
								self->p3,
								inc
							);
}


//////////////////////////////////////////////////////////////////////////////////
//				Geomertic Operations Implementations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ROT					(	Triangle2d_t,
								self,
								Vec2_t*			angle
							)
{
}


HOWTO_ROT					(	Triangle3d_t,
								self,
								Vec3_t*			angle
							)
{

	ROT						(	Point3d_t,
								self->p1,
								angle
							)	;

	ROT						(	Point3d_t,
								self->p2,
								angle
							)	;

	ROT						(	Point3d_t,
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
	Line_t						*line1	=	NULL,
								*line2	=	NULL,
								*line3	=	NULL;

	// Compose the edges	

	NEW						(	Line_t,
								line1,
								self->p1,
								self->p2
							);

	NEW						(	Line_t,
								line2,
								self->p2,
								self->p3
							);

	NEW						(	Line_t,
								line3,
								self->p1,
								self->p3
							);


	// Draw the vertices	

	DRAW					(	Point2d_t,
								self->p1,
								color,
								renderer
							);

	DRAW					(	Point2d_t,
								self->p2,
								color,
								renderer
							);

	DRAW					(	Point2d_t,
								self->p3,
								color,
								renderer
							);


	// Draw the edges

	DRAW					(	Line_t,
								line1,
								color,
								renderer
							);

	DRAW					(	Line_t,
								line2,
								color,
								renderer
							);

	DRAW					(	Line_t,
								line3,
								color,
								renderer
							);

	DEL						(	Line_t,
								line1
							);

	DEL						(	Line_t,
								line2
							);

	DEL						(	Line_t,
								line3
							);
}


HOWTO_DRAW					(	Triangle3d_t,
								self,
								Color_t*			color,
								Renderer_t*			renderer
							)
{
	Triangle2d_t				*proj	=	NULL;

	PROJ					(	Triangle2d_t,		Triangle3d_t,
								proj,				self,
								PERSPECTIVE	
							);

	DRAW					(	Triangle2d_t,
								proj,
								color,
								renderer
							);

	DEL						(	Triangle2d_t,
								proj
							);
}


HOWTO_PROJ					(	Triangle2d_t,		Triangle3d_t,
								to,					from,
								Projection_type_t	type
							)
{
	PROJ					(	Point2d_t,			Point3d_t,
								to->p1,				from->p1,
								type
							)	;

	PROJ					(	Point2d_t,			Point3d_t,
								to->p2,				from->p2,
								type
							)	;

	PROJ					(	Point2d_t,			Point3d_t,
								to->p3,				from->p3,
								type
							)	;
}

