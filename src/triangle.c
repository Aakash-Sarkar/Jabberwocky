/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "array.h"
#include "line.h"
#include "mesh.h"
#include "triangle.h"
#include "util.h"




HOWTO_DEF						(	Triangle2d_t,	self	)
{
	DEF							(	Point2d_t,
									self->p1
								);

	DEF							(	Point2d_t,
									self->p2
								);

	DEF							(	Point2d_t,
									self->p3
								);

	RET							(	self	);
}

HOWTO_CONSTRUCT					(	Triangle2d_t,
									self,
									Point2d_t		*p1,
									Point2d_t		*p2,
									Point2d_t		*p3
								)
{
	CPY							(	Point2d_t,
									self->p1,
									p1
								);

	CPY							(	Point2d_t,
									self->p2,
									p2
								);

	CPY							(	Point2d_t,
									self->p3,
									p3
								);

	RET							(	self	);
}

HOWTO_DESTRUCT					(	Triangle2d_t,	self	)
{
	DEL							(	Point2d_t,
									self->p1
								);

	DEL							(	Point2d_t,
									self->p2
								);

	DEL							(	Point2d_t,
									self->p3
								);
}

HOWTO_DEF						(	Triangle3d_t,	self	)
{
	DEF							(	Point3d_t,
									self->p1
								);

	DEF							(	Point3d_t,
									self->p2
								);

	DEF							(	Point3d_t,
									self->p3
								);

	RET							(	self	);
}

HOWTO_CONSTRUCT					(	Triangle3d_t,
									self,
									Point3d_t		*p1,
									Point3d_t		*p2,
									Point3d_t		*p3
								)
{
	CPY							(	Point3d_t,
									self->p1,
									p1
								);

	CPY							(	Point3d_t,
									self->p2,
									p2
								);

	CPY							(	Point3d_t,
									self->p3,
									p3
								);

	RET							(	self	);

}

HOWTO_DESTRUCT					(	Triangle3d_t,	self	)
{
	DEL							(	Point3d_t,
									self->p1
								);

	DEL							(	Point3d_t,
									self->p2
								);

	DEL							(	Point3d_t,
									self->p3
								);
}

HOWTO_DEF						(	ARRAY	(	Triangle2d_t	),	self	)
{

	DEF							(	ARRAY	(	Point2d_t	),
									self->p1
								);

	DEF							(	ARRAY	(	Point2d_t	),
									self->p2
								);

	DEF							(	ARRAY	(	Point2d_t	),
									self->p3
								);

	self->count					=	0;

	RET							(	self	);
}


HOWTO_DEF						(	ARRAY	(	Triangle3d_t	),	self	)
{
	DEF							(	ARRAY	(	Point3d_t	),
									self->p1
								);

	DEF							(	ARRAY	(	Point3d_t	),
									self->p2
								);

	DEF							(	ARRAY	(	Point3d_t	),
									self->p3
								);

	self->count					=	0;

	RET							(	self	);
}




HOWTO_DESTRUCT					(	ARRAY	( Face_t	),		self	)
{

	DEL							(	ARRAY	(	int		),
									self->idx1
								);

	DEL							(	ARRAY	(	int		),
									self->idx2
								);

	DEL							(	ARRAY	(	int		),
									self->idx3
								);

	self->count					=	0;
}

HOWTO_DESTRUCT					(	ARRAY	(	Triangle2d_t	),	self	)
{

	DEL							(	ARRAY	(	Point2d_t	),
									self->p1
								);

	DEL							(	ARRAY	(	Point2d_t	),
									self->p2
								);

	DEL							(	ARRAY	(	Point2d_t	),
									self->p3
								);

	self->count				=	0;
}

HOWTO_DESTRUCT					(	ARRAY	(	Triangle3d_t	),	self	)
{
	DEL							(	ARRAY	(	Point3d_t	),
									self->p1
								);

	DEL							(	ARRAY	(	Point3d_t	),
									self->p2
								);

	DEL							(	ARRAY	(	Point3d_t	),
									self->p3
								);

	self->count					=	0;
}




HOWTO_LD						(	Triangle2d_t,	ptr,	arr,	idx	)
{
	LD							(	Point2d_t,
									ptr->p1,
									arr->p1,
									idx
								);

	LD							(	Point2d_t,
									ptr->p2,
									arr->p2,
									idx
								);

	LD							(	Point2d_t,
									ptr->p3,
									arr->p3,
									idx
								);
}

HOWTO_LD						(	Triangle3d_t,	ptr,	arr,	idx	)
{
	LD							(	Point3d_t,
									ptr->p1,
									arr->p1,
									idx
								);

	LD							(	Point3d_t,
									ptr->p2,
									arr->p2,
									idx
								);

	LD							(	Point3d_t,
									ptr->p3,
									arr->p3,
									idx
								);
}


HOWTO_STR						(	Triangle2d_t,	ptr,	arr,	idx	)
{
	STR							(	Point2d_t,
									ptr->p1,
									arr->p1,
									idx
								);

	STR							(	Point2d_t,
									ptr->p2,
									arr->p2,
									idx
								);

	STR							(	Point2d_t,
									ptr->p3,
									arr->p3,
									idx
								);
}

HOWTO_STR						(	Triangle3d_t,	ptr,	arr,	idx	)
{
	STR							(	Point3d_t,
									ptr->p1,
									arr->p1,
									idx
								);

	STR							(	Point3d_t,
									ptr->p2,
									arr->p2,
									idx
								);

	STR							(	Point3d_t,
									ptr->p3,
									arr->p3,
									idx
								);
}


HOWTO_PUSH						(	Triangle2d_t,	ptr,	arr		)
{
	PUSH						(	Point2d_t,
									ptr->p1,
									arr->p1
								);

	PUSH						(	Point2d_t,
									ptr->p2,
									arr->p2
								);

	PUSH						(	Point2d_t,
									ptr->p3,
									arr->p3
								);
	arr->count++;
}

HOWTO_PUSH						(	Triangle3d_t,	ptr,	arr		)
{
	PUSH						(	Point3d_t,
									ptr->p1,
									arr->p1
								);

	PUSH						(	Point3d_t,
									ptr->p2,
									arr->p2
								);

	PUSH						(	Point3d_t,
									ptr->p3,
									arr->p3
								);

	arr->count++;
}


HOWTO_CPY						(	Triangle2d_t,	to,	from	)
{
	CPY							(	Point2d_t,
									to->p1,
									from->p1
								);

	CPY							(	Point2d_t,
									to->p2,
									from->p2
								);

	CPY							(	Point2d_t,
									to->p3,
									from->p3
								);
}

HOWTO_CPY						(	Triangle3d_t,	to,	from	)
{

	CPY							(	Point3d_t,
									to->p1,
									from->p1
								);

	CPY							(	Point3d_t,
									to->p2,
									from->p2
								);

	CPY							(	Point3d_t,
									to->p3,
									from->p3
								);
}




HOWTO_ROT						(	Triangle2d_t,
									to,			from,
									Vec2_t*		angle
								)
{
}

HOWTO_ROT						(	Triangle3d_t,
									to,			from,
									Vec3_t*		angle
								)
{

	ROT							(	Point3d_t,
									to->p1,
									from->p1,
									angle
								);

	ROT							(	Point3d_t,
									to->p2,
									from->p2,
									angle
								);

	ROT							(	Point3d_t,
									to->p3,
									from->p3,
									angle
								);
}




HOWTO_DRAW						(	Triangle2d_t,
									self,
									Point2d_t*			origin,
									Color_t*			color,
									Color_buffer_t*		colorbuf	)
{
	Line_t							*line1	=	NULL,
									*line2	=	NULL,
									*line3	=	NULL;

	NEW							(	Line_t,
									line1,
									self->p1,
									self->p2
								);

	NEW							(	Line_t,
									line2,
									self->p2,
									self->p3
								);

	NEW							(	Line_t,
									line3,
									self->p3,
									self->p1
								);

	//	Draw the vertices
	DRAW						(	Point2d_t,
									self->p1,
									origin,
									color,
									colorbuf
								);

	DRAW						(	Point2d_t,
									self->p2,
									origin,
									color,
									colorbuf
								);

	DRAW						(	Point2d_t,
									self->p3,
									origin,
									color,
									colorbuf
								);


	//	Draw the edges
	DRAW						(	Line_t,
									line1,
									origin,
									color,
									colorbuf
								);

	DRAW						(	Line_t,
									line2,
									origin,
									color,
									colorbuf
								);

	DRAW						(	Line_t,
									line3,
									origin,
									color,
									colorbuf
								);

	DEL							(	Line_t,		line1	);
	DEL							(	Line_t,		line2	);
	DEL							(	Line_t,		line3	);

}

HOWTO_DRAW						(	Triangle3d_t,
									self,
									Point2d_t			*origin,
									Color_t				*color,
									Color_buffer_t		*colorbuf
								)
{
	Triangle2d_t					*proj	=	NULL;

	DEF							(	Triangle2d_t,
									proj
								);

	PROJ						(	Triangle2d_t,	Triangle3d_t,
									proj,			self,
									PERSPECTIVE
								);

	DRAW						(	Triangle2d_t,
									proj,
									origin,
									color,
									colorbuf
								);

	DEL							(	Triangle2d_t,		proj	);
}




HOWTO_PROJ						(	Triangle2d_t,		Triangle3d_t,
									to,					from,
									Projection_type_t	type	)
{

	PROJ						(	Point2d_t,			Point3d_t,
									to->p1,				from->p1,
									type
								);

	PROJ						(	Point2d_t,			Point3d_t,
									to->p2,				from->p2,
									type
								);

	PROJ						(	Point2d_t,			Point3d_t,
									to->p3,				from->p3,
									type
								);
}


