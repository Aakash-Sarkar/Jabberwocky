/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "object.h"
#include "point.h"
#include "triangle.h"
#include "geometry.h"

typedef						struct Mesh {	ARRAY ( Point3d_t )		points;
											ARRAY ( Face_t )		faces;
											vec3_t					rotation;	}	Mesh_t;




CONSTRUCTOR					(	Mesh_t,
								vec3_t*		points,
								Face_t*		faces,
								int			num_points,
								int			num_faces	);

DESTRUCTOR					(	Mesh_t	);




Triangle3d_t
create_triangle_from_face	(	Face_t* face,	Mesh_t* mesh	);




