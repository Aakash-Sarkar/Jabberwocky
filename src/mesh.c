/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "mesh.h"




CONSTRUCTOR					(	Mesh_t,
								vec3_t*		points,
								Face_t*		faces,
								int			num_points,
								int			num_faces	)
{
	DECL_PTR				(	mesh,	Mesh_t,		NULL	);

	int							i	=	0;

	if						(	!points	||	num_points <= 0	)
		RETURN				(	NULL	);

	if						(	!faces	||	num_faces <= 0	)
		RETURN				(	NULL	);

	ALLOC_ZEROED			(	1,		Mesh_t,		mesh	);
	if						(	!mesh	)
		RETURN				(	NULL	);

	ARRAY_INIT				(	Face_t,		&mesh->faces	);

	ARRAY_INIT				(	Point3d_t,	&mesh->points	);


	for						(	int i = 0;	i < num_points;		i++		)
	{
		MEM					(	Point3d_t,	point,	1	);

		COPY				(	vec3_t,		&point->v,	points + i		);

		STORE				(	Point3d_t,	point,		&mesh->points	);
	}

	for						(	int i = 0;		i < num_faces;		i++		)
		STORE				(	Face_t,			faces +	i,			&mesh->faces	);

	RETURN					(	mesh	);
}


Triangle3d_t
create_triangle_from_face	(	Face_t* face,	Mesh_t* mesh	)
{
	MEM						(	Triangle3d_t,	triangle,			1	);

	LOAD					(	Point3d_t,
								&triangle->p1,	&mesh->points,		face->idx1 - 1	);

	LOAD					(	Point3d_t,
								&triangle->p2,	&mesh->points,		face->idx2 - 1 	);

	LOAD					(	Point3d_t,
								&triangle->p3,	&mesh->points,		face->idx3 - 1 	);

	RETURN					(	*triangle	);
}
