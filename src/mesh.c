/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "mesh.h"




CONSTRUCTOR					(	Mesh_t,
								char*		filename	)
{

	PTR						(	Mesh_t,		mesh,	NULL	);
	PTR						(	FILE,		file,	NULL	);

	char						buf [ 512 ];

	ALLOC_ZEROED			(	Mesh_t,		mesh,	1	);
	if						(	!mesh	)
		RETURN				(	NULL	);

	ARRAY_INIT				(	Face_t,		&mesh->faces	);

	ARRAY_INIT				(	Point3d_t,	&mesh->points	);

	fopen					(	&file,		filename, "r"	);
	if						(	!file	)
	{
		LOG					(	"File not found: %s\n",
								filename
							);
		RETURN				(	NULL	);
	}

	while					(	fgets	(	buf,
											sizeof ( buf ),
											file	)
							)
	{
		MEM					(	Point3d_t,	point,	1	);
		MEM					(	Face_t,		face,	1	);

		int						tmp = 0;

		if					(	!strncmp	(	buf, "v ", 2	)	)
		{
			sscanf			(	buf,
								"v %f %f %f",
								&point->v.x,
								&point->v.y,
								&point->v.z
							);

			STORE			(	Point3d_t,
								point,			&mesh->points	);
		}

		else if				(	!strncmp	(	buf, "f ", 2	)	)
		{
			sscanf			(	buf,
								"f %d/%d/%d %d/%d/%d %d/%d/%d",
								&face->idx1,	&tmp,	&tmp,
								&face->idx2,	&tmp,	&tmp,
								&face->idx3,	&tmp,	&tmp
							);

			STORE			(	Face_t,
								face,			&mesh->faces
							);
		}
	}

	RETURN					(	mesh	);
}

Triangle3d_t
create_triangle_from_face	(	Face_t* face,	Mesh_t* mesh	)
{
	MEM						(	Triangle3d_t,
								triangle,		1	);

	LOAD					(	Point3d_t,
								&triangle->p1,
								&mesh->points,
								face->idx1 - 1
							);

	LOAD					(	Point3d_t,
								&triangle->p2,
								&mesh->points,
								face->idx2 - 1
							);

	LOAD					(	Point3d_t,
								&triangle->p3,
								&mesh->points,
								face->idx3 - 1
							);

	RETURN					(	*triangle	);
}

