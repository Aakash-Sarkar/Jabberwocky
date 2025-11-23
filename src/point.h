/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "array.h"
#include "vector.h"
#include "object.h"
#include "color.h"
#include "renderer.h"



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


typedef						struct	Point3d							Point3d_t;

typedef						struct	Point2d							Point2d_t;


typedef						DECL_ARRAY	( Point2d_t )		ARRAY ( Point2d_t );

typedef						DECL_ARRAY	( Point3d_t )		ARRAY ( Point3d_t );




//////////////////////////////////////////////////////////////////////////////////
//							Point Operations
//////////////////////////////////////////////////////////////////////////////////




HOWTO_CPY					(	Point2d_t,	to,	from	);

HOWTO_CPY					(	Point3d_t,	to,	from	);




HOWTO_CONSTRUCT				(	Point2d_t,
								self,
								float		x,
								float		y
							);

HOWTO_CONSTRUCT				(	Point3d_t,
								self,
								float		x,
								float		y,
								float		z
							);


HOWTO_DESTRUCT				(	Point2d_t,
								self
							);

HOWTO_DESTRUCT				(	Point3d_t,
								self
							);




//////////////////////////////////////////////////////////////////////////////////
//							Dynamic Array Operations
//////////////////////////////////////////////////////////////////////////////////




HOWTO_ARRAY_INIT			(	ARRAY ( Point2d_t ),	self	);

HOWTO_ARRAY_INIT			(	ARRAY ( Point3d_t ),	self	);


HOWTO_ARRAY_RESET			(	ARRAY ( Point2d_t ),	self	);

HOWTO_ARRAY_RESET			(	ARRAY ( Point3d_t ),	self	);


HOWTO_CONSTRUCT				(	ARRAY ( Point2d_t ),
								self,
								void*	null
							);

HOWTO_CONSTRUCT				(	ARRAY ( Point3d_t ),
								self,
								void*	null
							);

HOWTO_DESTRUCT				(	ARRAY ( Point2d_t ),
								self
							);

HOWTO_DESTRUCT				(	ARRAY ( Point3d_t ),
								self
							);


HOWTO_LD					(	Point2d_t,	self,	array,	idx	);

HOWTO_LD					(	Point3d_t,	self,	array,	idx	);


HOWTO_STR					(	Point2d_t,	self,	array,	idx	);

HOWTO_STR					(	Point3d_t,	self,	array,	idx	);


HOWTO_COUNT					(	ARRAY ( Point2d_t ),	self	);

HOWTO_COUNT					(	ARRAY ( Point3d_t ),	self	);


HOWTO_INC					(	ARRAY ( Point2d_t ),	self,	int inc	);

HOWTO_INC					(	ARRAY ( Point3d_t ),	self,	int inc	);



//////////////////////////////////////////////////////////////////////////////////
//							Geomertic Operations
//////////////////////////////////////////////////////////////////////////////////




HOWTO_ROT					(	Point2d_t,
								self,
								Vec2_t*		angle
							);

HOWTO_ROT					(	Point3d_t,
								self,
								Vec3_t*		angle
							);


HOWTO_DRAW					(	Point2d_t,
								self,
								Color_t*			color,
								Renderer_t*			renderer
							);


HOWTO_DRAW					(	Point3d_t,
								self,
								Color_t*			color,
								Renderer_t*			renderer
							);




HOWTO_PROJ					(	Point2d_t,			Point3d_t,
								to,					from,
								Projection_type_t	type
							);




//////////////////////////////////////////////////////////////////////////////////
//							Arithmetic Operations
//////////////////////////////////////////////////////////////////////////////////




HOWTO_ADD					(	Point2d_t,	dst,	op1,	op2	);

HOWTO_ADD					(	Point3d_t,	dst,	op1,	op2	);


HOWTO_SUB					(	Point2d_t,	dst,	op1,	op2	);

HOWTO_SUB					(	Point3d_t,	dst,	op1,	op2	);


HOWTO_MUL					(	Point2d_t,	dst,	src,	factor	);

HOWTO_MUL					(	Point3d_t,	dst,	src,	factor	);


HOWTO_DIV					(	Point2d_t,	dst,	src,	factor	);

HOWTO_DIV					(	Point3d_t,	dst,	src,	factor	);


HOWTO_NORM					(	Point2d_t,	self	);

HOWTO_NORM					(	Point3d_t,	self	);


HOWTO_INC					(	Point2d_t,	self,	Point2d_t * inc		);

HOWTO_INC					(	Point3d_t,	self,	Point2d_t * inc		);


HOWTO_DOTP					(	Point2d_t,	dst,	src1,	src2	);

HOWTO_DOTP					(	Point3d_t,	dst,	src1,	src2	);


HOWTO_CROSSP				(	Point3d_t,	dst,	src1,	src2	);


