/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "mesh.h"




//CONSTRUCTOR					(	Mesh_t,
//								vec3_t*		points,
//								Face_t*		faces,
//								int			num_points,
//								int			num_faces	)
//{
//	DECL_PTR				(	mesh,	Mesh_t,		NULL	);
//
//	int							i	=	0;
//
//	if						(	!points	||	num_points <= 0	)
//		RETURN				(	NULL	);
//
//	if						(	!faces	||	num_faces <= 0	)
//		RETURN				(	NULL	);
//
//	ALLOC_ZEROED			(	1,		Mesh_t,		mesh	);
//	if						(	!mesh	)
//		RETURN				(	NULL	);
//
//	ARRAY_INIT				(	Face_t,		&mesh->faces	);
//
//	ARRAY_INIT				(	Point3d_t,	&mesh->points	);
//
//
//	for						(	int i = 0;	i < num_points;		i++		)
//	{
//		MEM					(	Point3d_t,	point,	1	);
//
//		COPY				(	vec3_t,		&point->v,	points + i		);
//
//		STORE				(	Point3d_t,	point,		&mesh->points	);
//	}
//
//	for						(	int i = 0;		i < num_faces;		i++		)
//		STORE				(	Face_t,			faces +	i,			&mesh->faces	);
//
//	RETURN					(	mesh	);
//}


CONSTRUCTOR					(	Mesh_t,
								char*		filename	)
{
	DECL_PTR				(	mesh,	Mesh_t,	NULL	);
	DECL_PTR				(	file,	FILE,	NULL	);

	char						buf [ 512 ];

	ALLOC_ZEROED			(	1,		Mesh_t,		mesh	);
	if						(	!mesh	)
		RETURN				(	NULL	);

	ARRAY_INIT				(	Face_t,		&mesh->faces	);

	ARRAY_INIT				(	Point3d_t,	&mesh->points	);

	fopen					(	&file,	filename, "r"	);
	if						(	!file	)
	{
		LOG					(	"File not found: %s\n", filename	);
		RETURN				(	NULL	);
	}

	while					(	fgets	(	buf,	sizeof ( buf ),	file	))
	{
		MEM					(	Point3d_t,	point,	1	);
		MEM					(	Face_t,		face,	1	);

		int						tmp = 0;

		if					(	strncmp	(	buf,	"v ",	2	) == 0	)
		{
			sscanf			(	buf,			"v %f %f %f",
								&point->v.x,	&point->v.y, &point->v.z	);

			STORE			(	Point3d_t,		point,	&mesh->points	);
		}

		else if				(	strncmp	(	buf,	"f ",	2	) == 0	)
		{
			sscanf			(	buf,
								"f %d/%d/%d %d/%d/%d %d/%d/%d",
								&face->idx1,	&tmp,	&tmp,
								&face->idx2,	&tmp,	&tmp,
								&face->idx3,	&tmp,	&tmp	);

			STORE			(	Face_t,			face,	&mesh->faces	);

		}
	}

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

