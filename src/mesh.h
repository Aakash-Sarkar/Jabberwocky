/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "object.h"
#include "point.h"
#include "triangle.h"

typedef						struct Mesh {	int				num_points;
											Point3d_t*		points;
											int				num_faces;
											Face_t*			faces;		}	Mesh_t;


extern						vec3_t			mesh_vertices[];
extern						Face_t			mesh_faces[];


CONSTRUCTOR					(	Mesh_t,
								vec3_t*		points,
								Face_t*		faces,
								int			num_points,
								int			num_faces	);

DESTRUCTOR					(	Mesh_t	);




Triangle3d_t
create_triangle_from_face	(	Face_t* face,	Mesh_t* mesh	);


#define																							\
for_each_point_in_mesh(point, itr, mesh)		for (	itr		= 0,							\
														point	= mesh->points;					\
														itr		< mesh->num_points;				\
														point++,								\
														itr++									\
													)

#define																							\
for_each_face_in_mesh(face, itr, mesh)			for (	itr		= 0,							\
														face	= mesh->faces;					\
														itr		< mesh->num_faces;				\
														face++,									\
														itr++									\
													)

#define																									\
for_each_point_in_face(point, face, itr, mesh)	for (	itr		= 0,									\
														point	= &mesh->points[ face->idx[itr] -1 ];	\
														itr		< 3;									\
														itr++,											\
														point	= &mesh->points[ face->idx[itr] -1 ]	\
													)

