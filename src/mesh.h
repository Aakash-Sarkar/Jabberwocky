/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "object.h"
#include "point.h"
#include "triangle.h"
#include "geometry.h"




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
struct	Face				{	int							*idx1;
								int							*idx2;
								int							*idx3;
							}												Face_t;


DECL_ARRAY					(	Face_t,
								ARRAY	(	int		)		*idx1;
								ARRAY	(	int		)		*idx2;
								ARRAY	(	int		)		*idx3;
							);


typedef
struct	Mesh				{
								ARRAY	(	Point3d_t	)	*points;
								ARRAY	(	Face_t		)	*faces;
								Vec3_t						*rotation;
							}												Mesh_t;



HOWTO_DEF					(	Face_t,		self	);

HOWTO_CONSTRUCT				(	Mesh_t,
								self,
								char*		filename	);

HOWTO_DESTRUCT				(	Face_t,		self	);

HOWTO_DESTRUCT				(	Mesh_t,		self	);


HOWTO_CPY					(	Face_t,		to,	from	);


Triangle3d_t
create_triangle_from_face	(	Face_t* face,	Mesh_t* mesh	);




HOWTO_DEF					(	ARRAY	( Face_t ),		self	);

HOWTO_DESTRUCT				(	ARRAY	( Face_t ),		self	);

HOWTO_LD					(	Face_t,	ptr,	arr,	idx		);

HOWTO_STR					(	Face_t,	ptr,	arr,	idx		);

HOWTO_PUSH					(	Face_t,	ptr,	arr		);

