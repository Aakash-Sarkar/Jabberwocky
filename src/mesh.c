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

	const ARRAY ( Point3d_t ) *			points	;

////////////////////////////////////////////////////////////////////////////////
//
//		Faces array is where we store all the triangle faces of our mesh
//		from the obj file. This array ( like the points array ) should
//		remain constant throughout the life time of our Mesh.
//
////////////////////////////////////////////////////////////////////////////////

	const ARRAY ( Face_t ) *			faces	;

////////////////////////////////////////////////////////////////////////////////
//
//		Triangles array store all the triangles of our mesh; composed
//		using the vertex and face data above. Any operation done on our
//		mesh amounts to that operation done on each of the triangles in
//		this array.
//
////////////////////////////////////////////////////////////////////////////////

	ARRAY ( Triangle3d_t ) *			triangles	;

	ARRAY ( Point3d_t ) *				normals	;

	Vec3_t *							rotation	;
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


struct									Face
{
	int									idx1	;

	int									idx2	;

	int									idx3	;
}	;


DECL_ARRAY							(	Face_t	)
{
	int *								idx1	;

	int *								idx2	;

	int *								idx3	;

	int									count	;
}	;




////////////////////////////////////////////////////////////////////////////////
//					Mesh Operations Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_COPY							(	Face_t,		to,	from	)
{
	to->idx1						=	from->idx1	;

	to->idx2						=	from->idx2	;

	to->idx3						=	from->idx3	;
}


HOWTO_CONSTRUCT						(	Face_t,
										self,
										int		idx1,
										int		idx2,
										int		idx3
									)
{
	ALLOC_ZEROED					(	Face_t,
										self,
										1
									);

	ASSERT							(	self != NULL, " "	)	;

	self->idx1						=	idx1	;
	self->idx2						=	idx2	;
	self->idx3						=	idx3	;
}


HOWTO_CONSTRUCT						(	Mesh_t,
										self,
										char*	filename
									)
{

	int									idx	= 0;
	char								buf [ 512 ]	= { 0 };


	PTR								(	FILE,
										file,
										NULL
									)	;


	TMP								(	Face_t,
										face,
										1
									)	;



	ALLOC_ZEROED					(	Mesh_t,
										self,
										1
									)	;

	ASSERT							(	self != NULL, " "	)	;


	CONSTRUCT						(	ARRAY ( Face_t ),
										self->faces,
										NULL
									)	;

	CONSTRUCT						(	ARRAY ( Point3d_t ),
										self->points,
										NULL
									)	;

	CONSTRUCT						(	ARRAY ( Point3d_t ),
										self->normals,
										NULL
									)	;

	CONSTRUCT						(	ARRAY ( Triangle3d_t ),
										self->triangles,
										NULL
									)	;	


	CONSTRUCT						(	Vec3_t,
										self->rotation,
										0,	0,	0
									)	;


	fopen							(	&file,
										filename,
										"r"
									)	;

	if								(	!file	)
	{
		LOG							(	"File not found: %s\n",
										filename
									)	;
		RETURN						(	NULL	);
	}

	while							(	fgets	(	buf,
													sizeof ( buf ),
													file
												)
									)
	{

		PTR							(	Point3d_t,
										point,
										1
									)	;

		TMP							(	Face_t,
										face,
										1
									)	;

		int								tmp = 0;
		int								x = 0,
										y = 0,
										z = 0;

		if							(	!strncmp	(	buf, "v ", 2	)	)
		{
			sscanf					(	buf,
										"v %f %f %f",
										&x, &y, &z
									)	;

			CONSTRUCT				(	Point3d_t,
										point,
										x, y, z
									)	;

			PUSH					(	Point3d_t,
										point,
										&self->points
									)	;

			DESTRUCT				(	Point3d_t,
										point
									)	;
		}


		else if						(	!strncmp	(	buf, "f ", 2	)	)
		{
			sscanf					(	buf,
										"f %d/%d/%d %d/%d/%d %d/%d/%d",
										&face->idx1,	&tmp,	&tmp,
										&face->idx2,	&tmp,	&tmp,
										&face->idx3,	&tmp,	&tmp
									)	;

			PUSH					(	Face_t,
										face,
										self->faces
									)	;
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

		TMP							(	Triangle3d_t,
										triangle,
										1
									);

		*triangle					=	create_triangle_from_face	(	face,	self	);

		STORE						(	Triangle3d_t,
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




HOWTO_ARRAY_INIT					(	Face_t,		self	)
{
	self->idx1						=	NULL	;
	self->idx2						=	NULL	;
	self->idx3						=	NULL	;

	self->count						=	0	;
}


HOWTO_ARRAY_RESET					(	Face_t,		self	)
{
	array_free						(	self->idx1	)	;
	array_free						(	self->idx2	)	;
	array_free						(	self->idx3	)	;

	self->count						=	0	;
}


HOWTO_CONSTRUCT						(	ARRAY ( Face_t ),
										self,
										void*	null
									)
{
	ALLOC_ZEROED					(	ARRAY( Face_t ),
										self,
										1
									);

	ASSERT							(	self != NULL, " "	)	;

	ARRAY_INIT						(	Face_t,	self	)	;
}


HOWTO_LOAD							(	Face_t,	self,	array,	idx	)
{
	self->idx1						=	array->idx1	[ idx ]	;

	self->idx2						=	array->idx2	[ idx ]	;

	self->idx3						=	array->idx3	[ idx ]	;
}

HOWTO_PUSH							(	Face_t,	self,	array	)
{
	array_push						(	array->idx1,	self->idx1	)	;

	array_push						(	array->idx2,	self->idx2	)	;

	array_push						(	array->idx3,	self->idx3	)	;

	array->count++	;
}


HOWTO_STORE							(	Face_t,	self,	array,	idx		)
{

	TMP								(	Face_t,
										zero,
										1
									)	;

	while							(	array->count	<=	idx		)
	{
		PUSH						(	Face_t,
										zero,
										array
									)	;
	}

	array->idx1 [ idx ]				=	self->idx1	;

	array->idx2 [ idx ]				=	self->idx2	;

	array->idx3 [ idx ]				=	self->idx3	;
}


void
get_surface_normal					(	Face_t*			face,
										Mesh_t*			mesh,
										Point3d_t*		normal
									)
{

	TMP								(	Point3d_t,
										point,
										3
									)	;

	TMP								(	Point3d_t,
										p12,
										1
									)	;

	TMP								(	Point3d_t,
										p13,
										1
									)	;


	LOAD							(	Point3d_t,
										point,
										mesh->points,
										face->idx1	-	1
									)	;

	LOAD							(	Point3d_t,
										point + 1,
										mesh->points,
										face->idx2	-	1
									)	;

	LOAD							(	Point3d_t,
										point + 2,
										mesh->points,
										face->idx3	-	1
									)	;


	SUB								(	Point3d_t,
										p12,
										point	+	1,
										point
									)	;

	SUB								(	Point3d_t,
										p13,
										point	+	2,
										point
									)	;


	CROSSP							(	Point3d_t,
										normal,
										p12,
										p13
									)	;


	NORM							(	Point3d_t,
										normal
									)	;
}






Triangle3d_t
create_triangle_from_face			(	Face_t* face,	Mesh_t* mesh	)
{

	TMP								(	Triangle3d_t,
										triangle,
										1
									);

	TMP								(	Point3d_t,
										point,
										3
									);

	TMP								(	Point3d_t,
										normal,
										1
									);

	LOAD							(	Point3d_t,
										point,
										&mesh->points,
										face->idx1	-	1
									);

	LOAD							(	Point3d_t,
										point + 1,
										&mesh->points,
										face->idx2	-	1
									);

	LOAD							(	Point3d_t,
										point + 2,
										&mesh->points,
										face->idx3	-	1
									);

	COMPOSE							(	Triangle3d_t,
										triangle,
										point,
										point		+	1,
										point		+	2
									);

	RETURN							(	*triangle	);
}



HOWTO_ROTATE						(	Mesh_t,
										self,
										Vec3_t*		rotation
									)
{
	int									idx	=	0;

	PTR								(	Triangle3d_t,
										triangle,
										1
									);

	INC								(	vec3_t,
										self->rotation,
										rotation
									);


	for_each_triangle_in_mesh		(	triangle,	self,	idx		)
	{
		ROTATE						(	Triangle3d_t,
										triangle,
										rotation
									);

		STORE						(	Triangle3d_t,
										triangle,
										&mesh->triangles,
										idx
									);
	}
}

