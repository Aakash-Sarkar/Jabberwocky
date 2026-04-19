/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "mesh.h"



HOWTO_DEF						(	Face_t,	self	)
{
	NEW							(	Face_t,
									self,
									0,
									0,
									0
								);

	RET							(	self	);
}


HOWTO_INIT						(	Face_t,
									self,
									int			idx1,
									int			idx2,
									int			idx3
								)
{
	( self )->idx1				=	idx1;
	( self )->idx2				=	idx2;
	( self )->idx3				=	idx3;
}

HOWTO_INIT						(	Mesh_t,
									self,
									char		*filename
								)
{

	FILE							*file	=	NULL;
	char							buf		[	512	];

	Point3d_t						*point	=	NULL;
	Face_t							*face	=	NULL;

	itr ( Face_t )					face_it	=	{ 0 };


	DEF							(	arr ( Face_t ),
									( self )->faces
								);

	DEF							(	arr ( Point3d_t ),
									( self )->points
								);

	DEF							(	arr ( Triangle3d_t ),
									( self )->triangles
								);

	DEF							(	arr ( bool ),
									( self )->cull
								);

	DEF							(	Vec3_t,
									( self )->rotation
								);

	fopen						(	&file,
									filename,
									"r"
								);

	assert						(	file	);

	while						(	fgets	(	buf,
												sizeof ( buf ),
												file
											)
								)
	{
		int							tmp = 0;

		if						(	!strncmp	(	buf, "v ", 2	)	)
		{
			float					x	=	0,
									y	=	0,
									z	=	0;

			sscanf				(	buf,
									"v %f %f %f",
									&x, &y, &z
								);

			assert				(	!point	);

			NEW					(	Point3d_t,
									point,
									x,	y,	z
								);

			PUSH				(	Point3d_t,
									point,
									( self )->points
								);

			DEL					(	Point3d_t,
									point
								);
		}

		else if					(	!strncmp	(	buf, "f ", 2	)	)
		{
			int						idx1	=	0,
									idx2	=	0,
									idx3	=	0;

			sscanf				(	buf,
									"f %d/%d/%d %d/%d/%d %d/%d/%d",
									&idx1,	&tmp,		&tmp,
									&idx2,	&tmp,		&tmp,
									&idx3,	&tmp,		&tmp
								);

			NEW					(	Face_t,
									face,
									idx1,	idx2,	idx3
								);

			PUSH				(	Face_t,
									face,
									( self )->faces
								);

			DEL					(	Face_t,
									face
								);
		}
	}

	Triangle3d_t					*tr	=	NULL;

	for_each_face_in_mesh		(	&face_it,	self	)
	{
		bool						*cull	=	NULL;

		DEF						(	Triangle3d_t,
									tr
								);

		NEW						(	bool,
									cull,
									false
								);

		REQ						(	Mesh_t,
									create_triangle_from_face,
									self,
									( face_it ).ptr,
									tr
								);

		PUSH					(	Triangle3d_t,
									tr,
									( self )->triangles
								);

		PUSH					(	bool,
									cull,
									( self )->cull
								);

		DEL						(	Triangle3d_t,
									tr
								);

		DEL						(	bool,
									cull
								);
	}
}


HOWTO_DEF						(	Mesh_t,	self	)
{
	NEW							(	Mesh_t,
									( self ),
									"assets/cube.obj"
								);

	RET							(	self	);
}

HOWTO_FINI						(	Face_t,	self	)
{
}

HOWTO_FINI						(	Mesh_t,	self	)
{
}


HOWTO_CPY						(	Face_t,	to,	from	)
{
	CP							(	int,
									&( to )->idx1,
									&( from )->idx1
								);

	CP							(	int,
									&( to )->idx2,
									&( from )->idx2
								);

	CP							(	int,
									&( to )->idx3,
									&( from )->idx3
								);
}


HOWTO_CPY						(	Mesh_t,	to,	from	)
{
}




/////////////////////////////////////////////////////////////////////////////////
//						Iterator Ops Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT						(	itr ( Face_t ),
									self,
									Face_t				*ptr,
									unsigned int		pos,
									IterType_t			typ
								)
{
	INITITR						(	Face_t,
									self,
									ptr,
									pos,
									typ
								);
}

HOWTO_INIT						(	itr ( Mesh_t ),
									self,
									Mesh_t				*ptr,
									unsigned int		pos,
									IterType_t			typ
								)
{
	INITITR						(	Mesh_t,
									self,
									ptr,
									pos,
									typ
								);
}


HOWTO_FINI						(	itr ( Face_t ),		self	)
{
	FINIITR						(	Face_t,
									self
								);
}

HOWTO_FINI						(	itr ( Mesh_t ),		self	)
{
	FINIITR						(	Mesh_t,
									self
								);
}


HOWTO_DEF						(	itr ( Face_t ),		self	)
{
	NEW							(	itr ( Face_t ),
									self,
									NULL,
									0,
									MAX_ITER
								);

	RET							(	self	);
}

HOWTO_DEF						(	itr ( Mesh_t ),		self	)
{
	NEW							(	itr ( Mesh_t ),
									self,
									NULL,
									0,
									MAX_ITER
								);

	RET							(	self	);
}


HOWTO_CMP						(	itr ( Face_t ),		it1,	it2	)
{
	CMPITR						(	Face_t,
									it1,
									it2
								);
}

HOWTO_CMP						(	itr ( Mesh_t ),		it1,	it2	)
{
	CMPITR						(	Mesh_t,
									it1,
									it2
								);
}


HOWTO_INC						(	itr ( Face_t ),		self	)
{
	INCITR						(	Face_t,
									self
								);
}

HOWTO_INC						(	itr ( Mesh_t ),		self	)
{
	INCITR						(	Mesh_t,
									self
								);
}


HOWTO_DEC						(	itr ( Face_t ),		self	)
{
	DECITR						(	Face_t,
									self
								);
}

HOWTO_DEC						(	itr ( Mesh_t ),		self	)
{
	DECITR						(	Mesh_t,
									self
								);
}


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic array Ops Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT						(	arr ( Face_t ),
									self,
									const Face_t		*init_list,
									unsigned int		count
								)
{
	INITARR						(	Face_t,
									self,
									init_list,
									count
								);
}

HOWTO_INIT						(	arr ( Mesh_t ),
									self,
									const Mesh_t		*init_list,
									unsigned int		count
								)
{
	INITARR						(	Mesh_t,
									self,
									init_list,
									count
								);
}


HOWTO_FINI						(	arr ( Face_t ),		self	)
{
	FINIARR						(	Face_t,
									self
								);
}

HOWTO_FINI						(	arr ( Mesh_t ),		self	)
{
	FINIARR						(	Mesh_t,
									self
								);
}


HOWTO_DEF						(	arr	( Face_t ),		self	)
{
	NEW							(	arr ( Face_t ),
									self,
									NULL,
									0
								);

	RET							(	self	);
}

HOWTO_DEF						(	arr	( Mesh_t ),		self	)
{
	NEW							(	arr ( Mesh_t ),
									( self ),
									( NULL ),
									( 0 )
								);

	RET							(	self	);
}


/////////////////////////////////////////////////////////////////////////////////
//						Geometric Ops Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ROT						(	Mesh_t,
									self,
									Vec3_t				*angle
								)
{
	itr ( Triangle3d_t )			tr	=	{ 0 };
	int								idx	=	0;

	for_each_triangle_in_mesh	(	&tr,		self	)
	{
		bool						cull	=	false;

		ROT						(	Triangle3d_t,
									( tr ).ptr,
									angle
								);

		STR						(	Triangle3d_t,
									( tr ).ptr,
									( self )->triangles,
									( tr ).pos
								);

		REQ						(	Triangle3d_t,
									is_back_facing,
									( tr ).ptr,
									&cull
								);

		STR						(	bool,
									&cull,
									( self )->cull,
									idx
								);

		idx++;
	}

	ADD							(	Vec3_t,
									( self )->rotation,
									( self )->rotation,
									( angle )
								);
}


METHOD							(	Mesh_t,
									create_triangle_from_face,
									self,
									Face_t			*face,
									Triangle3d_t	*out
								)
{
	Point3d_t						*p1		=	NULL,
									*p2		=	NULL,
									*p3		=	NULL;

	Triangle3d_t					*tr		=	NULL;

	assert						(	face	);

	DEF							(	Point3d_t,
									p1
								);

	DEF							(	Point3d_t,
									p2
								);

	DEF							(	Point3d_t,
									p3
								);

	LD							(	Point3d_t,
									p1,
									( self )->points,
									( face )->idx1	-	1
								);

	LD							(	Point3d_t,
									p2,
									( self )->points,
									( face )->idx2	-	1
								);

	LD							(	Point3d_t,
									p3,
									( self )->points,
									( face )->idx3	-	1
								);

	NEW							(	Triangle3d_t,
									tr,
									p1,		p2,		p3
								);

	MOV							(	Triangle3d_t,
									out,
									tr
								);

	DEL							(	Point3d_t,
									p1
								);

	DEL							(	Point3d_t,
									p2
								);

	DEL							(	Point3d_t,
									p3
								);

	RET							(	self	);
}

