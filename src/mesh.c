/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "mesh.h"

vec3_t	mesh_vertices[ ]	=
{
	{	.x = -1,		.y = -1,		.z = -1		},
	{	.x = -1,		.y =  1,		.z = -1		},
	{	.x =  1,		.y =  1,		.z = -1		},
	{	.x =  1,		.y = -1,		.z = -1		},
	{	.x =  1,		.y =  1,		.z =  1		},
	{	.x =  1,		.y = -1,		.z =  1		},
	{	.x = -1,		.y =  1,		.z =  1		},
	{	.x = -1,		.y = -1,		.z =  1		},
};

Face_t	mesh_faces[ ] =
{
	{	.idx[0] = 1,	.idx[1] = 2,	.idx[2] = 3		},
	{	.idx[0] = 1,	.idx[1] = 3,	.idx[2] = 4		},

	{	.idx[0] = 4,	.idx[1] = 3,	.idx[2] = 5		},
	{	.idx[0] = 4,	.idx[1] = 5,	.idx[2] = 6		},

	{	.idx[0] = 6,	.idx[1] = 5,	.idx[2] = 7		},
	{	.idx[0] = 6,	.idx[1] = 7,	.idx[2] = 8		},

	{	.idx[0] = 8,	.idx[1] = 7,	.idx[2] = 2		},
	{	.idx[0] = 8,	.idx[1] = 2,	.idx[2] = 1		},

	{	.idx[0] = 2,	.idx[1] = 7,	.idx[2] = 5		},
	{	.idx[0] = 2,	.idx[1] = 5,	.idx[2] = 3		},

	{	.idx[0] = 6,	.idx[1] = 8,	.idx[2] = 1		},
	{	.idx[0] = 6,	.idx[1] = 1,	.idx[2] = 4		},
};




CONSTRUCTOR					(	Mesh_t,
								vec3_t*				points,
								Face_t*				faces,
								int					num_points,
								int					num_faces		)
{
	DECL_PTR				(	mesh,	Mesh_t,		NULL	);
	DECL_PTR				(	point,	Point3d_t,	NULL	);
	DECL_PTR				(	face,	Face_t,		NULL	);

	int							i = 0;

	if						(	!points	||	num_points <= 0	)
		RETURN				(	NULL	);

	if						(	!faces	||	num_faces <= 0	)
		RETURN				(	NULL	);

	ALLOC_ZEROED			(	1,			Mesh_t,		mesh	);
	if						(	!mesh	)
		RETURN				(	NULL	);

	ALLOC_ZEROED			(	num_points,	Point3d_t,	mesh->points	);
	if						(	!mesh->points	)
	{
		DEALLOC				(	mesh	);
		RETURN				(	NULL	);
	}

	ALLOC_ZEROED			(	num_faces,	Face_t,		mesh->faces		);
	if						(	!mesh->faces	)
	{
		DEALLOC				(	mesh->points	);
		DEALLOC				(	mesh	);
		RETURN				(	NULL	);
	}


	mesh->num_points		=	num_points;

	for_each_point_in_mesh	(	point,		i,		mesh	)
		COPY				(	Point3d_t,	point,	( Point3d_t* ) points + i	);


	mesh->num_faces			=	num_faces;

	for_each_face_in_mesh	(	face,		i,		mesh	)
		COPY				(	Face_t,		face,	faces	+	i	);

	RETURN					(	mesh	);
}


Triangle3d_t
create_triangle_from_face	(	Face_t* face,	Mesh_t* mesh	)
{
	Triangle3d_t				triangle = {	0	};

	COPY					(	Point3d_t,
								&triangle.p1,
								&mesh->points [ face->idx [ 0 ] - 1 ]	);

	COPY					(	Point3d_t,
								&triangle.p2,
								&mesh->points [ face->idx [ 1 ] - 1 ]	);

	COPY					(	Point3d_t,
								&triangle.p3,
								&mesh->points [ face->idx [ 2 ] - 1 ]	);

	RETURN					(	triangle	);
}
