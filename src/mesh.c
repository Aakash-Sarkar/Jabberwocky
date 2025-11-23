/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "mesh.h"




////////////////////////////////////////////////////////////////////////////////
//					Mesh Structures Implementation
////////////////////////////////////////////////////////////////////////////////


struct									Mesh
{
////////////////////////////////////////////////////////////////////////////////
//
//		Points array is where we store all the vertices of our mesh from
//		the obj file. This array should remain constant throughout the
//		lifetime of our Mesh.
//
////////////////////////////////////////////////////////////////////////////////

	const ARRAY ( Point3d_t ) *			points;

////////////////////////////////////////////////////////////////////////////////
//
//		Faces array is where we store all the triangle faces of our mesh
//		from the obj file. This array ( like the points array ) should
//		remain constant throughout the life time of our Mesh.
//
////////////////////////////////////////////////////////////////////////////////

	const ARRAY ( Face_t ) *			faces;

////////////////////////////////////////////////////////////////////////////////
//
//		Triangles array store all the triangles of our mesh; composed
//		using the vertex and face data above. Any operation done on our
//		mesh amounts to that operation done on each of the triangles in
//		this array.
//
////////////////////////////////////////////////////////////////////////////////

	ARRAY ( Triangle3d_t ) *			triangles;

	ARRAY ( Point3d_t ) *				normals;

	Vec3_t *							rotation;
}	;




//////////////////////////////////////////////////////////////////////////////////
//
//
//		In Graphics, we define a triangle face using the indices of the
//		its three end points in the points array.
//
//		At first glance, this may sound like an overkill. It's perfectly
//		valid to ask: why can't we have just one triangle array in our
//		mesh instead of two separate vertex and faces array. The answer
//		will become clear once you start to notice how the vertices are
//		shared amongst different triangles in a mesh.
//
//
//						2.						3.
//
//						@	-	-	-	-	-	@
//					+		+				+		+	
//				+				+		+				+
//		4.	@	-	-	-	-	-	@	-	-	-	-	-	@	5.
//				+				+	1.	+				+
//					+		+				+		+
//						@	-	-	-	-	-	@
//
//						6.						7.
//
//
//		Notice how the vertex (1) = { 0.0800, 0.000, 0.000 } is shared
//		between the triangles: [ 1, 2, 3 ] , [ 1, 2, 4 ] , [ 1, 4, 6 ],
//		[ 1, 3, 5 ] , [ 1, 6, 7 ] and [ 1, 5, 7 ]. If we only keep the
//		values of the vertices of our triangles inside a single array,
//		then the value of our vertex (1) will appear six times in our
//		triangles array without any way for us to know whether it's the
//		same vertex or not. Keeping the data for the vertices and the
//		faces isolated in separate arrays helps us to reduce the number
//		of redundent vertex data in the memory.
//
//
//////////////////////////////////////////////////////////////////////////////////


struct					Face		{	int		idx1;
										int		idx2;
										int		idx3;
									};


DECL_ARRAY			( Face_t )		{	int *	idx1;
										int *	idx2;
										int *	idx3;
										int		count;
									};




////////////////////////////////////////////////////////////////////////////////
//					Mesh Operations Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_CPY							(	Face_t,		to,	from	)
{
	to->idx1						=	from->idx1;
	to->idx2						=	from->idx2;
	to->idx3						=	from->idx3;
}


HOWTO_CONSTRUCT						(	Face_t,
										self,
										int			idx1,
										int			idx2,
										int			idx3
									)
{
	self->idx1						=	idx1;
	self->idx2						=	idx2;
	self->idx3						=	idx3;
}


HOWTO_CONSTRUCT						(	Mesh_t,
										self,
										char*	filename
									)
{

	int									idx	= 0;
	char								buf [ 512 ]	= { 0 };


	FILE								*file	=	NULL;
	Face_t								*face	=	NULL;


	DEF								(	ARRAY ( Face_t ),
										self->faces
									);

	DEF								(	ARRAY ( Point3d_t ),
										self->points
									);

	DEF								(	ARRAY ( Point3d_t ),
										self->normals
									);

	DEF								(	ARRAY ( Triangle3d_t ),
										self->triangles
									);	


	DEF								(	Vec3_t,
										self->rotation
									);


	fopen							(	&file,
										filename,
										"r"
									);

	if								(	!file	)
	{
		LOG							(	"File not found: %s\n",
										filename
									)	;
		RETURN						(	EMPTY	);
	}

	while							(	fgets	(	buf,
													sizeof ( buf ),
													file
												)
									)
	{
		Point3d_t						*point	=	NULL;

		int								tmp		=	0;
		int								x		=	0,
										y		=	0,
										z		=	0;

		if							(	!strncmp	(	buf, "v ", 2	)	)
		{
			sscanf					(	buf,
										"v %f %f %f",
										&x, &y, &z
									);

			NEW						(	Point3d_t,
										point,
										x, y, z
									);

			PUSH					(	Point3d_t,
										point,
										self->points
									);

			DEL						(	Point3d_t,
										point
									);
		}


		else if						(	!strncmp	(	buf, "f ", 2	)	)
		{
			DEF						(	Face_t,
										face
									);

			sscanf					(	buf,
										"f %d/%d/%d %d/%d/%d %d/%d/%d",
										&face->idx1,	&tmp,	&tmp,
										&face->idx2,	&tmp,	&tmp,
										&face->idx3,	&tmp,	&tmp
									);

			PUSH					(	Face_t,
										face,
										self->faces
									);

			DEL						(	Face_t,
										face
									);
		}
	}


	//for_each_face_in_mesh			(	face,	self,	idx		)
	//{

	//	TMP							(	Point3d_t,
	//									normal,
	//									1
	//								);

	//	get_surface_normal			(	face,
	//									self,
	//									normal
	//								);

	//	STORE						(	Point3d_t,
	//									normal,
	//									self->normals,
	//									idx
	//								);
	//}

	for_each_face_in_mesh			(	face,	self,	idx	)
	{
		Triangle3d_t					*triangle	=	NULL;

		DEF							(	Triangle3d_t,
										triangle
									);

		triangle					=	create_triangle_from_face ( face,	self );

		STR							(	Triangle3d_t,
										triangle,
										self->triangles,
										idx
									);
	}

	RETURN							(	self	);
}


/////////////////////////////////////////////////////////////////////////////////
//				Dynamic Array Operations Implementation
/////////////////////////////////////////////////////////////////////////////////




HOWTO_ARRAY_INIT					(	ARRAY ( Face_t ),	self	)
{
	self->idx1						=	EMPTY;
	self->idx2						=	EMPTY;
	self->idx3						=	EMPTY;

	self->count						=	0;
}


HOWTO_ARRAY_RESET					(	ARRAY ( Face_t ),	self	)
{
	array_free						(	self->idx1	);
	array_free						(	self->idx2	);
	array_free						(	self->idx3	);

	self->count						=	0	;
}


HOWTO_CONSTRUCT						(	ARRAY ( Face_t ),
										self,
										void*	null
									)
{
	INIT							(	ARRAY ( Face_t ),	self	);
}


HOWTO_DESTRUCT					(	ARRAY ( Face_t ),	self	)
{
}


HOWTO_LD							(	Face_t,	self,	array,	idx	)
{
	self->idx1						=	array->idx1	[ idx ];
	self->idx2						=	array->idx2	[ idx ];
	self->idx3						=	array->idx3	[ idx ];
}

HOWTO_STR							(	Face_t,	self,	array,	idx		)
{
	array->idx1 [ idx ]				=	self->idx1;
	array->idx2 [ idx ]				=	self->idx2;
	array->idx3 [ idx ]				=	self->idx3;
}


void
get_surface_normal					(	Face_t*			face,
										Mesh_t*			mesh,
										Point3d_t*		normal
									)
{
	Point3d_t							*p1		=	NULL,
										*p2		=	NULL,
										*p3		=	NULL;

	Point3d_t							*p12	=	NULL,
										*p13	=	NULL;


	LD								(	Point3d_t,
										p1,
										mesh->points,
										face->idx1	-	1
									);

	LD								(	Point3d_t,
										p2,
										mesh->points,
										face->idx2	-	1
									);

	LD								(	Point3d_t,
										p3,
										mesh->points,
										face->idx3	-	1
									);


	SUB								(	Point3d_t,
										p12,
										p2,
										p1
									);

	SUB								(	Point3d_t,
										p13,
										p3,
										p1
									);


	CROSSP							(	Point3d_t,
										normal,
										p12,
										p13
									);


	NORM							(	Point3d_t,
										normal
									);
}






Triangle3d_t*
create_triangle_from_face			(	Face_t * face,	Mesh_t * mesh	)
{
	Triangle3d_t						*triangle	=	NULL;

	Point3d_t							*p1	=	NULL,
										*p2	=	NULL,
										*p3	=	NULL;

	LD								(	Point3d_t,
										p1,
										mesh->points,
										face->idx1	-	1
									);

	LD								(	Point3d_t,
										p2,
										mesh->points,
										face->idx2	-	1
									);

	LD								(	Point3d_t,
										p3,
										mesh->points,
										face->idx3	-	1
									);

	float								x1	=	0,
										y1	=	0,
										z1	=	0;

	MSG								(	Point3d_t,
										decompose,
										p1,
										&x1,	&y1,	&z1
									);

	float								x2	=	0,
										y2	=	0,
										z2	=	0;

	MSG								(	Point3d_t,
										decompose,
										p2,
										&x2,	&y2,	&z2
									);

	float								x3	=	0,
										y3	=	0,
										z3	=	0;

	MSG								(	Point3d_t,
										decompose,
										p3,
										&x3,	&y3,	&z3
									);

	NEW								(	Triangle3d_t,
										triangle,
										x1,		y1,		z1,
										x2,		y2,		z2,
										x3,		y3,		z3
									);

	RETURN							(	triangle	);
}



HOWTO_ROT							(	Mesh_t,
										self,
										Vec3_t*		rotation
									)
{
	int									idx	=	0;

	Triangle3d_t						*triangle	=	NULL:

	INC								(	vec3_t,
										self->rotation,
										rotation
									);


	for_each_triangle_in_mesh		(	triangle,	self,	idx		)
	{
		ROT							(	Triangle3d_t,
										triangle,
										rotation
									);

		STR							(	Triangle3d_t,
										triangle,
										self->triangles,
										idx
									);
	}
}


METHOD							(	Mesh_t,
									create_triangle_from_face,
									self,
									Face_t *		face,
									Triangle3d_t *	out
								)
{
	Point3d_t						*p1	=	NULL,
									*p2	=	NULL,
									*p3	=	NULL;

	Triangle3d_t					*triangle	=	NULL;


	DEF							(	Point3d_t,
									p1
								);

	DEF							(	Point3d_t,
									p2
								);

	DEF							(	Point3d_t,
									p3
								);

	DEF							(	Triangle3d_t,
									triangle
								);

	LD							(	Point3d_t,
									p1,
									self->points,
									face->idx1
								);

	LD							(	Point3d_t,
									p2,
									self->points,
									face->idx2
								);

	LD							(	Point3d_t,
									p3,
									self->points,
									face->idx3
								);
}

