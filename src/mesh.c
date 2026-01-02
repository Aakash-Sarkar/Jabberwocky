/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "mesh.h"




HOWTO_DEF					(	Face_t,	self	)
{
	DEF						(	int,
								self->idx1
							);

	DEF						(	int,
								self->idx2
							);

	DEF						(	int,
								self->idx3
							);
}

HOWTO_CONSTRUCT				(	Mesh_t,
								self,
								char*		filename
							)
{

	FILE						*file	=	NULL;
	char						buf		[	512	];

	Point3d_t					*point	=	NULL;
	Face_t						*face	=	NULL;

	DEF						(	Face_t,
								face
							);

	DEF						(	ARRAY	(	Face_t	),
								self->faces
							);

	DEF						(	ARRAY	(	Point3d_t	),
								self->points
							);

	DEF						(	Vec3_t,
								self->rotation
							);

	fopen					(	&file,
								filename,
								"r"
							);

	assert					(	file	);

	while					(	fgets	(	buf,
											sizeof ( buf ),
											file
										)
							)
	{
		int						tmp = 0;

		if					(	!strncmp	(	buf, "v ", 2	)	)
		{
			float				x	=	0,
								y	=	0,
								z	=	0;

			sscanf			(	buf,
								"v %f %f %f",
								&x, &y, &z
							);

			assert			(	!point	);

			NEW				(	Point3d_t,
								point,
								x,	y,	z
							);

			PUSH			(	Point3d_t,
								point,
								self->points
							);

			DEL				(	Point3d_t,
								point
							);
		}

		else if				(	!strncmp	(	buf, "f ", 2	)	)
		{
			sscanf			(	buf,
								"f %d/%d/%d %d/%d/%d %d/%d/%d",
								face->idx1,		&tmp,		&tmp,
								face->idx2,		&tmp,		&tmp,
								face->idx3,		&tmp,		&tmp
							);

			PUSH			(	Face_t,
								face,
								self->faces
							);
		}
	}
}

HOWTO_DESTRUCT				(	Face_t,	self	)
{
	DEL						(	int,
								self->idx1
							);

	DEL						(	int,
								self->idx2
							);

	DEL						(	int,
								self->idx3
							);
}

HOWTO_DESTRUCT				(	Mesh_t,	self	)
{
}

HOWTO_DEF					(	ARRAY	(	Face_t	),	self	)
{
	DEF						(	ARRAY	(	int		),
								self->idx1
							);

	DEF						(	ARRAY	(	int		),
								self->idx2
							);

	DEF						(	ARRAY	(	int		),
								self->idx3
							);

	self->count				=	0;
}


Triangle3d_t
create_triangle_from_face	(	Face_t* face,	Mesh_t* mesh	)
{
	Triangle3d_t				*tr	=	NULL;

	Point3d_t					*p1	=	NULL,
								*p2	=	NULL,
								*p3	=	NULL;

	NEW						(	Point3d_t,
								p1,
								0,	0,	0
							);

	NEW						(	Point3d_t,
								p2,
								0,	0,	0
							);

	NEW						(	Point3d_t,
								p3,
								0,	0,	0
							);

	LD						(	Point3d_t,
								p1,
								mesh->points,
								*( face->idx1 )	-	1
							);

	LD						(	Point3d_t,
								p2,
								mesh->points,
								*( face->idx2 )	-	1
							);

	LD						(	Point3d_t,
								p3,
								mesh->points,
								*( face->idx3 )	-	1
							);

	NEW						(	Triangle3d_t,
								tr,
								p1,		p2,		p3
							);

	RET						(	*tr		);
}


HOWTO_LD					(	Face_t,	ptr,	arr,	idx	)
{

	LD						(	int,
								ptr->idx1,
								arr->idx1,
								idx
							);

	LD						(	int,
								ptr->idx2,
								arr->idx2,
								idx
							);

	LD						(	int,
								ptr->idx3,
								arr->idx3,
								idx
							);
}


HOWTO_STR					(	Face_t,	ptr,	arr,	idx	)
{
	STR						(	int,
								ptr->idx1,
								arr->idx1,
								idx
							);

	STR						(	int,
								ptr->idx2,
								arr->idx2,
								idx
							);

	STR						(	int,
								ptr->idx3,
								arr->idx3,
								idx
							);
}


HOWTO_PUSH					(	Face_t,		ptr,	arr		)
{
	PUSH					(	int,
								ptr->idx1,
								arr->idx1
							);

	PUSH					(	int,
								ptr->idx2,
								arr->idx2
							);

	PUSH					(	int,
								ptr->idx3,
								arr->idx3
							);
	arr->count++;
}


HOWTO_CPY					(	Face_t,	to,	from	)
{
	CPY						(	int,
								to->idx1,
								from->idx1
							);

	CPY						(	int,
								to->idx2,
								from->idx2
							);

	CPY						(	int,
								to->idx3,
								from->idx3
							);
}


METHOD						(	Mesh_t,
								create_triangle_from_face,
								self,
								Face_t			*face,
								Triangle3d_t	*out
							)
{
	Point3d_t					*p1	=	NULL,
								*p2	=	NULL,
								*p3	=	NULL;

	Triangle3d_t				*tr	=	NULL;

	assert					(	face	);

	DEF						(	Point3d_t,
								p1
							);

	DEF						(	Point3d_t,
								p2
							);

	DEF						(	Point3d_t,
								p3
							);

	LD						(	Point3d_t,
								p1,
								self->points,
								*( face->idx1 )	-	1
							);

	LD						(	Point3d_t,
								p2,
								self->points,
								*( face->idx2 )	-	1
							);

	LD						(	Point3d_t,
								p3,
								self->points,
								*( face->idx3 )	-	1
							);

	NEW						(	Triangle3d_t,
								tr,
								p1,		p2,		p3
							);

	CPY						(	Triangle3d_t,
								out,
								tr
							);

	DEL						(	Point3d_t,
								p1
							);

	DEL						(	Point3d_t,
								p2
							);

	DEL						(	Point3d_t,
								p3
							);
}

