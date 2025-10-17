/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "object.h"
#include "point.h"
#include "triangle.h"
#include "geometry.h"



typedef								struct Face							Face_t;

typedef								DECL_ARRAY ( Face_t )				ARRAY( Face_t );

typedef								struct Mesh							Mesh_t;




////////////////////////////////////////////////////////////////////////////////
//						Mesh Operations
////////////////////////////////////////////////////////////////////////////////


HOWTO_COPY						(	Face_t,		to,	from	)	;

HOWTO_CONSTRUCT					(	Face_t,
									self,
									int		idx1,
									int		idx2,
									int		idx3
								)	;

HOWTO_CONSTRUCT					(	Mesh_t,
									self,
									char*		filename
								)	;


HOWTO_DESTRUCT					(	Face_t,
									self
								)	;


HOWTO_DESTRUCT					(	Mesh_t,
									self
								)	;


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic Array Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ARRAY_INIT				(	Face_t,		self	)	;

HOWTO_ARRAY_RESET				(	Face_t,		self	)	;


HOWTO_CONSTRUCT					(	ARRAY ( Face_t ),
									self,
									void*	null
								)	;

HOWTO_DESTRUCT					(	ARRAY ( Face_t ),
									self
								)	;

HOWTO_LOAD						(	Face_t,		self,	array,	idx		)	;

HOWTO_PUSH						(	Face_t,		self,	array	)	;

HOWTO_STORE						(	Face_t,		self,	array,	idx		)	;


Triangle3d_t
create_triangle_from_face		(	Face_t* face,	Mesh_t* mesh	)	;


void
get_surface_normal				(	Face_t *			face,
									Mesh_t *			mesh,
									Point3d_t *			normal
								)	;



HOWTO_ROTATE					(	Mesh_t,
									self,
									Vec3_t*		rotation
								)	;




#define																					\
for_each_face_in_mesh(	face,	mesh,	idx)	for	(	idx = 0,						\
														LOAD	(	Face_t,				\
																	face,				\
																	mesh->faces,		\
																	0					\
																);						\
														idx	<	mesh->faces->count;		\
														idx++,							\
														LOAD	(						\
																	Face_t,				\
																	face,				\
																	mesh->faces,		\
																	idx					\
																)						\
													)



#define																					\
for_each_point_in_mesh(point, mesh, idx)		for	(	idx = 0,						\
														LOAD	(	Point3d_t,			\
																	point,				\
																	mesh->points,		\
																	0					\
																);						\
														idx	<	mesh->points->count;	\
														idx++,							\
														LOAD	(						\
																	Point3d_t,			\
																	point,				\
																	mesh->points,		\
																	idx					\
																)						\
													)




#define																					\
for_each_triangle_in_mesh(triangle, mesh, idx)	for	(	idx = 0,						\
														LOAD	(	Triangle3d_t,		\
																	triangle,			\
																	mesh->triangles,	\
																	0					\
																);						\
														idx	<	mesh->triangles->count;	\
														idx++,							\
														LOAD	(						\
																	Triangle3d_t,		\
																	triangle,			\
																	mesh->triangles,	\
																	idx					\
																)						\
													)


