/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "triangle.h"




 //////////////////////////////////////////////////////////////////////////////////
 //
 //
 //		In Graphics, we define a triangle face using the indices of the
 //		its three end points in the points array.
 //
 //		At first glance, this may sound like an overkill. It's perfectly
 //		valid to ask: why can't we have just one triangle array in our
 //		mesh instead of two separate vertex and faces array. The answer
 //		will become clear once you start to notice how the vertices are
 //		shared amongst different triangles in a mesh.
 //
 //
 //						2.						3.
 //
 //						@	-	-	-	-	-	@
 //					+		+				+		+	
 //				+				+		+				+
 //		4.	@	-	-	-	-	-	@	-	-	-	-	-	@	5.
 //				+				+	1.	+				+
 //					+		+				+		+
 //						@	-	-	-	-	-	@
 //
 //						6.						7.
 //
 //
 //		Notice how the vertex (1) = { 0.0800, 0.000, 0.000 } is shared
 //		between the triangles: [ 1, 2, 3 ] , [ 1, 2, 4 ] , [ 1, 4, 6 ],
 //		[ 1, 3, 5 ] , [ 1, 6, 7 ] and [ 1, 5, 7 ]. If we only keep the
 //		values of the vertices of our triangles inside a single array,
 //		then the value of our vertex (1) will appear six times in our
 //		triangles array without any way for us to know whether it's the
 //		same vertex or not. Keeping the data for the vertices and the
 //		faces isolated in separate arrays helps us to reduce the number
 //		of redundent vertex data in the memory.
 //
 //
 //////////////////////////////////////////////////////////////////////////////////



typedef
struct	Face				{	int						idx1;
								int						idx2;
								int						idx3;
							}							Face_t;


DECL_ITER					(	Face_t	);

DECL_ARRAY					(	Face_t	);



typedef
struct	Mesh				{	arr ( Point3d_t )		*points;
								arr ( Face_t )			*faces;
								arr ( Triangle3d_t )	*triangles;
								arr ( bool )			*cull;
								Vec3_t					*rotation;
							}												Mesh_t;


DECL_ITER					(	Mesh_t	);

DECL_ARRAY					(	Mesh_t	);



HOWTO_DEF					(	Face_t,		self	);

HOWTO_INIT					(	Face_t,
								self,
								int			idx1,
								int			idx2,
								int			idx3
							);


HOWTO_DEF					(	Mesh_t,		self	);

HOWTO_INIT					(	Mesh_t,
								self,
								char		*filename
							);

HOWTO_FINI					(	Face_t,		self	);

HOWTO_FINI					(	Mesh_t,		self	);


HOWTO_CPY					(	Face_t,		to,	from	);

HOWTO_CPY					(	Mesh_t,		to,	from	);




HOWTO_INIT					(	itr ( Face_t ),
								self,
								Face_t				*ptr,
								unsigned int		pos,
								IterType_t			typ
							);

HOWTO_INIT					(	itr ( Mesh_t ),
								self,
								Mesh_t				*ptr,
								unsigned int		pos,
								IterType_t			typ
							);


HOWTO_DEF					(	itr ( Face_t ),		self	);

HOWTO_DEF					(	itr ( Mesh_t ),		self	);


HOWTO_CMP					(	itr ( Face_t ),		it1,	it2	);

HOWTO_CMP					(	itr ( Mesh_t ),		it1,	it2	);


HOWTO_INC					(	itr ( Face_t ),		self	);

HOWTO_INC					(	itr ( Mesh_t ),		self	);


HOWTO_DEC					(	itr ( Face_t ),		self	);

HOWTO_DEC					(	itr ( Mesh_t ),		self	);


HOWTO_INIT					(	arr ( Face_t ),
								self,
								const Face_t		*init_list,
								unsigned int		count
							);

HOWTO_INIT					(	arr ( Mesh_t ),
								self,
								const Mesh_t		*init_list,
								unsigned int		count
							);


HOWTO_DEF					(	arr	( Face_t ),		self	);

HOWTO_DEF					(	arr	( Mesh_t ),		self	);


HOWTO_ROT					(	Mesh_t,
								self,
								Vec3_t			*angle
							);

METHOD						(	Mesh_t,
								create_triangle_from_face,
								self,
								Face_t			*face,
								Triangle3d_t	*out
							);




#define																							\
for_each_face_in_mesh( face,	mesh )			for_each_item_in_array	(	Face_t,				\
																			( face ),			\
																			( mesh )->faces		\
																		)


#define																							\
for_each_triangle_in_mesh( tr, mesh )			for_each_item_in_array	(	Triangle3d_t,		\
																			( tr ),				\
																			( mesh )->triangles	\
																		)

