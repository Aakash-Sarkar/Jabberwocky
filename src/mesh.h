/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "point.h"
#include "triangle.h"



typedef						struct Face							Face_t;

typedef						DECL_ARRAY ( Face_t )				ARRAY ( Face_t );

typedef						struct Mesh							Mesh_t;




////////////////////////////////////////////////////////////////////////////////
//						Mesh Operations
////////////////////////////////////////////////////////////////////////////////


HOWTO_CPY						(	Face_t,		to,	from	);

HOWTO_CONSTRUCT					(	Face_t,
									self,
									int			idx1,
									int			idx2,
									int			idx3
								);

HOWTO_CONSTRUCT					(	Mesh_t,
									self,
									char *		filename
								);


HOWTO_DESTRUCT					(	Face_t,	self	);


HOWTO_DESTRUCT					(	Mesh_t,	self	);


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic Array Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ARRAY_INIT				(	ARRAY ( Face_t ),	self	);

HOWTO_ARRAY_RESET				(	ARRAY ( Face_t ),	self	);


HOWTO_CONSTRUCT					(	ARRAY ( Face_t ),
									self,
									void*	null
								);

HOWTO_DESTRUCT					(	ARRAY ( Face_t ),	self	);

HOWTO_LD						(	Face_t,		self,	array,	idx	);

HOWTO_STR						(	Face_t,		self,	array,	idx	);


Triangle3d_t*
create_triangle_from_face		(	Face_t * face,	Mesh_t * mesh	);


void
get_surface_normal				(	Face_t *		face,
									Mesh_t *		mesh,
									Point3d_t *		normal
								);



HOWTO_ROT						(	Mesh_t,
									self,
									Vec3_t *	rotation
								);




METHOD							(	Mesh_t,
									get_face_vertices,
									self,
									Face_t *	Face,
									Point3d_t*	points[3]
								);



#define																					\
for_each_face_in_mesh(	face,	mesh,	idx)	for	(	idx = 0,						\
														_LD		(	Face_t,				\
																	face,				\
																	mesh->faces,		\
																	0					\
																);						\
														idx	<	COUNT (					\
																	ARRAY ( Face_t ),	\
																	mesh->faces			\
																);						\
														idx++,							\
														_LD		(						\
																	Face_t,				\
																	face,				\
																	mesh->faces,		\
																	idx					\
																)						\
													)



#define																					\
for_each_point_in_mesh(point, mesh, idx)		for	(	idx = 0,						\
														_LD		(	Point3d_t,			\
																	point,				\
																	mesh->points,		\
																	0					\
																);						\
														idx	<	COUNT (					\
																	ARRAY ( Point3d_t ),\
																	mesh->points		\
																);						\
														idx++,							\
														_LD		(						\
																	Point3d_t,			\
																	point,				\
																	mesh->points,		\
																	idx					\
																)						\
													)




#define																					\
for_each_triangle_in_mesh(triangle, mesh, idx)	for	(	idx = 0,						\
														_LD		(	Triangle3d_t,		\
																	triangle,			\
																	mesh->triangles,	\
																	0					\
																);						\
														idx	<	COUNT (					\
																	ARRAY(Triangle3d_t),\
																	mesh->triangles		\
																);						\
														idx++,							\
														_LD		(						\
																	Triangle3d_t,		\
																	triangle,			\
																	mesh->triangles,	\
																	idx					\
																)						\
													)


