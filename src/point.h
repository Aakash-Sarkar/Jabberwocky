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
//		Points are the building blocks of any 2D/3D object model. Any
//		object model that we see in a video game (tables, chairs, enemies
//		etc.) are all described as a collection of points ( also known as
//		vertices). These points collectively describe the silhouette of
//		the object model on top of which we paint color.
//
//
//		Typically, one would represent a point as a set of three numbers
//		describing the X, Y and Z co-ordinates of the point. However, in
//		Computer Graphics it is much more convenient to represent a point
//		as a vector with three components. i.e. we treat the X, Y and  Z
//		co-ordinates of a 3D point as the components of a 3D vector.
//
//
//		In other words, one can also think of each point in a 3D space as
//		a vector starting from the origin to that point.
//
//
//							Y
//							^
//							|
//							|		 
//							|		/		@			-->  3D point
//							|     /		+
//							|   /	+					-->  Point vector
//							| / +
//							+------------------ >  X
//
//
//
//		This gives us several advantages:
//
//		1.	We can now perform vector operations on the points and follow
//			the rules of vector algebra.
//
// 
//		2.	We can change or tranform the position of a point in any way
//			we like by multiplying it with a matrix. we can use this
//			property of a line to move the object model around by moving
//			the individual points on the model one by one.		
//
//
//		3.	We can change the co-ordinate system of the point. i.e, how
//			would the object look if viewed by someone else. When Artists
//			create an object model, they choose the co-ordinate system as
//			viewed by the object itself. i.e, the origin would be located
//			near the centre of the object or somewhere inside the object
//			itself. This co-ordinate system is also called as the object
//			space. The game needs to change these points to a co-ordinate
//			system as viewed by the user ( camera space ).
//
//
//		How do we know which matrix to use with which point in order to get
//		the desired movement? This is where game physics comes into play.
//		By using simplified equations of physics, we can obtain matrices to
//		create simple motions (oscillations, rotations etc). We can create
//		more complex animations by composing together these simple motions.
//
//
//////////////////////////////////////////////////////////////////////////////////



typedef						struct		{	vec2_t v;	}		Point2d_t;




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

typedef						struct		{	vec3_t v;	}		Point3d_t;




typedef						DECL_ARRAY	(	Point2d_t,	ARRAY ( vec2_t )	v;	);

typedef						DECL_ARRAY	(	Point3d_t,	ARRAY ( vec3_t )	v;	);


//////////////////////////////////////////////////////////////////////////////////
//								Point Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_COPY					(	Point2d_t,	to,		from	);

HOWTO_COPY					(	Point3d_t,	to,		from	);


//////////////////////////////////////////////////////////////////////////////////
//								Dynamic Array Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ARRAY_INIT			(	Point2d_t,	array	);

HOWTO_ARRAY_INIT			(	Point3d_t,	array	);


HOWTO_ARRAY_RESET			(	Point2d_t,	array	);

HOWTO_ARRAY_RESET			(	Point3d_t,	array	);



HOWTO_LOAD					(	Point2d_t,	ptr,	array,	idx	);

HOWTO_LOAD					(	Point3d_t,	ptr,	array,	idx	);


HOWTO_STORE					(	Point2d_t,	ptr,	array	);

HOWTO_STORE					(	Point3d_t,	ptr,	array	);



//////////////////////////////////////////////////////////////////////////////////
//								Geomertic Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ROTATE				(	Point2d_t,	to,		from,	vec2_t* angle	);

HOWTO_ROTATE				(	Point3d_t,	to,		from,	vec3_t* angle	);


HOWTO_DRAW					(	Point2d_t,
								point,
								Point2d_t*			origin,
								Color_t*			color,
								Color_buffer_t*		colorbuf	);


HOWTO_DRAW					(	Point3d_t,
								point,
								Point2d_t*			origin,
								Color_t*			color,
								Color_buffer_t*		colorbuf	);




HOWTO_PROJECT				(	Point2d_t,			Point3d_t,
								to,					from,
								Projection_type_t	type		);


//////////////////////////////////////////////////////////////////////////////////
//								Arithmetic Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ADD					(	Point2d_t,	dst,	op1,	op2	);

HOWTO_ADD					(	Point3d_t,	dst,	op1,	op2	);


HOWTO_SUB					(	Point2d_t,	dst,	op1,	op2	);

HOWTO_SUB					(	Point3d_t,	dst,	op1,	op2	);


HOWTO_MUL					(	Point2d_t,	dst,	src,	factor	);

HOWTO_MUL					(	Point3d_t,	dst,	src,	factor	);


HOWTO_DIV					(	Point2d_t,	dst,	src,	factor	);

HOWTO_DIV					(	Point3d_t,	dst,	src,	factor	);


HOWTO_DOTP					(	Point2d_t,	dst,	src1,	src2	);

HOWTO_DOTP					(	Point3d_t,	dst,	src1,	src2	);


HOWTO_CROSSP				(	Point3d_t,	dst,	src1,	src2	);


