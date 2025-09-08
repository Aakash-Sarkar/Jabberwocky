/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "object.h"
#include "point.h"



typedef							struct Cube	{	int			len;
												int			width;
												int			height;
												int			num_points;
												Point3d_t*	points;		}	Cube_t;





#define																				\
for_each_point_in_cube(cube, point, itr)		for (	itr		= 0,				\
														point	= cube->points;		\
														itr		< cube->num_points;	\
														point++,					\
														itr++						\
													)


CONSTRUCTOR				(	Cube_t,
							int			len,
							int			width,
							int			height	);



void
rotate_cube_x			(	Cube_t*	cube,		float angle	);

void
rotate_cube_y			(	Cube_t*	cube,		float angle	);

void
rotate_cube_z			(	Cube_t*	cube,		float angle	);
