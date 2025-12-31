/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "array.h"
#include "vector.h"
#include "object.h"
#include "geometry.h"
#include "color.h"




 //////////////////////////////////////////////////////////////////////////////////
 //									POINTS:
 //////////////////////////////////////////////////////////////////////////////////
 //
 //
 //		Points are one of the building blocks of a 3D model. Any object model
 //		that we see in a video game (tables, chairs, enemies e.t.c. ) are all
 //		described as a collection of points ( a.k.a. vertices ). These points
 //		collectively describe the silhouette of the object; on which we paint
 //		our colors.
 //
 //
 //		Typically, one would represent a point ( or vertex) as a set of three
 //		numbers describing the X, Y and Z co-ordinates of that point. However
 //		in Graphics it's much more convenient to think of a point as a vector
 //		with three components. i.e. we treat the X, Y and Z co-ordinates of a
 //		3D point as the components of a 3D vector.
 //
 //
 //		In other words, one can think of each point in a 3D space as a vector
 //		starting from the origin to that point.
 //
 //
 //							Y
 //							^
 //							|
 //							|		  Z
 //							|		/		@			-->  3D point
 //							|     /		+
 //							|   /	+					-->  Point vector
 //							| / +
 //							+ - - - - - - - - - >  X
 //
 //
 //
 //		This representation provides us with several advantages:
 //
 //		1.	We can now perform vector operations on our points, and follow
 //			the rules of vector algebra. This spares us from inventing our
 //			own mathematics for vertex processing.
 //
 // 
 //		2.	We can now change the position of any point in the manner that
 //			we want, by simply multiplying the corresponding vector with a
 //			matrix. we can use this property of vectors to move the object
 //			model around by moving the individual points on that model one
 //			by one.		
 //
 //
 //		3.	We can now transform the co-ordinate system of our point. That
 //			is, what will the point's (or vector's) co-ordinates look like
 //			if we take it to a new co-ordinate system. If we can determine
 //			the new co-ordinates for all of the points in our object, then
 //			we can find out how our object would look if viewed by someone
 //			else. This can be acheived by multiplying each point of object
 //			with an appropriate matrix (aka. linear transformations).
 //
 //
 //		All of the operations listed above, are conducted by a shader program
 //		during the vetex processing stage of the graphics pipeline before the
 //		next frame can be displayed to the user. 
 //
 //
 //////////////////////////////////////////////////////////////////////////////////



typedef						struct		{	Vec2_t		*v;	}		Point2d_t;



//////////////////////////////////////////////////////////////////////////////////
//
//
//		We could also do a `typedef vec3_t point3d_t` here, but then again,
//		someone would certainly try to pass a position vector in a function
//		for colors. Doing it this way will at least give us a compilation
//		error.
//
//
//		Another, more nuanced way of thinking about this is the following:
//
//		Each vector lives in a vector space and can only be added to or
//		subtracted from other vectors living in the same space. For e.g,
//		our point vectors as described by the X, Y and Z co-ordinates of
//		our point, together form a point space and can only be added to
//		or subtracted from other point vectors in the same space.
//
//
//		However,  if we choose a point vector from a different co-ordinate
//		system ( i.e, with different X, Y and Z axes ), and try to add it
//		to our point vector; then it's not a valid mathematical operation.
//		We may get some resulting vector by doing this, but in a geometric
//		sense this new vector doesn't have any valid meaning since the two
//		vectors come from different co-ordinate spaces.
//
//
//		To give another example of this from a different domain:
//
//		If we subtract two velocity vectors, we get the relative velocity
//		of one with respect to the other. Same goes with subtracting two
//		displacement vectors. But if we try to subtract a velocity vector
//		from a displacement vector; the resulting vector isn't a valid
//		physical quantity.
//
//
//		In physics textbooks this is described in terms of the two vectors
//		having different units; but in mathematical terms one could also
//		describe this as the two vectors living in different vector spaces.
//
//
//////////////////////////////////////////////////////////////////////////////////



typedef
struct						{	Vec3_t		*v;		}		Point3d_t;




DECL_ARRAY					(	Point2d_t,
								ARRAY	(	Vec2_t	)	*v;
							);

DECL_ARRAY					(	Point3d_t,
								ARRAY	(	Vec3_t	)	*v;
							);


//////////////////////////////////////////////////////////////////////////////////
//							Point Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_CPY					(	Point2d_t,	to,		from	);

HOWTO_CPY					(	Point3d_t,	to,		from	);

HOWTO_DEF					(	Point2d_t,	self	);

HOWTO_CONSTRUCT				(	Point2d_t,
								self,
								float		x,
								float		y
							);

HOWTO_DESTRUCT				(	Point2d_t,	self	);

HOWTO_DEF					(	Point3d_t,	self	);

HOWTO_CONSTRUCT				(	Point3d_t,
								self,
								float		x,
								float		y,
								float		z
							);

HOWTO_DESTRUCT				(	Point3d_t,	self	);


//////////////////////////////////////////////////////////////////////////////////
//							Dynamic Array Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_DEF					(	ARRAY	( Point2d_t ),	self	);

HOWTO_DEF					(	ARRAY	( Point3d_t ),	self	);


HOWTO_DESTRUCT				(	ARRAY	( Point2d_t ),	self	);

HOWTO_DESTRUCT				(	ARRAY	( Point3d_t ),	self	);



HOWTO_LD					(	Point2d_t,	ptr,	arr,	idx		);

HOWTO_LD					(	Point3d_t,	ptr,	arr,	idx		);


HOWTO_STR					(	Point2d_t,	ptr,	arr,	idx		);

HOWTO_STR					(	Point3d_t,	ptr,	arr,	idx		);


HOWTO_PUSH					(	Point2d_t,	ptr,	arr		);

HOWTO_PUSH					(	Point3d_t,	ptr,	arr		);


//////////////////////////////////////////////////////////////////////////////////
//								Geomertic Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ROT					(	Point2d_t,
								to,					from,
								Vec2_t				*angle	);

HOWTO_ROT					(	Point3d_t,
								to,					from,
								Vec3_t				*angle	);


HOWTO_DRAW					(	Point2d_t,
								self,
								Point2d_t			*origin,
								Color_t				*color,
								Color_buffer_t		*colorbuf	);


HOWTO_DRAW					(	Point3d_t,
								self,
								Point2d_t			*origin,
								Color_t				*color,
								Color_buffer_t		*colorbuf	);




HOWTO_PROJ					(	Point2d_t,			Point3d_t,
								to,					from,
								Projection_type_t	type		);


//////////////////////////////////////////////////////////////////////////////////
//								Arithmetic Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ADD					(	Point2d_t,	dst,	op1,	op2		);

HOWTO_ADD					(	Point3d_t,	dst,	op1,	op2		);


HOWTO_SUB					(	Point2d_t,	dst,	op1,	op2		);

HOWTO_SUB					(	Point3d_t,	dst,	op1,	op2		);


HOWTO_MUL					(	Point2d_t,	dst,	src,	factor	);

HOWTO_MUL					(	Point3d_t,	dst,	src,	factor	);


HOWTO_DIV					(	Point2d_t,	dst,	src,	factor	);

HOWTO_DIV					(	Point3d_t,	dst,	src,	factor	);


HOWTO_DOTP					(	Point2d_t,	dst,	src1,	src2	);

HOWTO_DOTP					(	Point3d_t,	dst,	src1,	src2	);


HOWTO_CROSSP				(	Point3d_t,	dst,	src1,	src2	);


