/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "cube.h"
#include "rect.h"

CONSTRUCTOR							(	Cube_t,
										int			len,
										int			width,
										int			height	)
{

	DECL_PTR						(	cube,		Cube_t,		NULL	);
	DECL_PTR						(	point,		Point3d_t,	NULL	);

	int									num_points	= 0;

	float								step_l		= 0.0,
										step_w		= 0.0,
										step_h		= 0.0;

	ALLOC_ZEROED					(	1,			Cube_t,		cube	);

	if								(	!cube	)
	{
		LOG							(	"Couldn't allocate memory\n"	);
		RETURN						(	NULL	);
	}

	cube->len						=	len;
	cube->width						=	width;
	cube->height					=	height;

	num_points						=	(	len	*	width	*	height	);
	cube->num_points				=	num_points;

	ALLOC_ZEROED					(	num_points,	Point3d_t,	cube->points	);
	if								(	!cube->points	)
	{
		LOG							(	"Couldn't allocate memory\n"	);
		DEALLOC						(	cube	);
		RETURN						(	NULL	);
	}

	step_l							=	( float ) (	2.0 / (	cube->len		- 1	));
	step_w							=	( float ) (	2.0 / (	cube->width		- 1	));
	step_h							=	( float ) (	2.0 / (	cube->height	- 1	));

	point							=	&cube->points[ 0 ];

	int									n = 0;
	for								(	float l = -1.0; l < 1.0; l += step_l	)
		for							(	float w = -1.0; w < 1.0; w += step_w	)
			for						(	float h = -1.0; h < 1.0; h += step_h	)
			{
				ASSERT				(	( n < num_points ),
										"Out of bounds access at idx: %d\n",
										n	);

				point->v.x			=	l;
				point->v.y			=	w;
				point->v.z			=	h;
				point++;
				n++;
			}
	RETURN							(	cube	);
}

void
rotate_cube_x						(	Cube_t *cube,	float angle	)
{

	//Point2d_t							proj		= { 0 };
	//Point3d_t							t_point		= { 0 },
	//									*point		= NULL;

	//Rect_t							rect;
	//int								i			= 0;

	//for_each_point_in_cube		(	cube,   point,	i	)
	//{
	//	t_point						=	rotate_point_x		(	*point, angle	);
	//	proj						=	project_perspective	(	*point	);
	//}
}