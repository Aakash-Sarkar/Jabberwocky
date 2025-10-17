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
//		Points are the building blocks of any 2D/3D object model. Any
//		object model that we see in a video game (tables, chairs, enemies
//		etc.) are all described as a collection of points (aka. vertices).
//		These points collectively describe the silhouette of the object
//		model on top of which we paint color.
//
//
//		Typically, one would represent a point as a set of three numbers
//		describing the X, Y and Z co-ordinates of the point. However, in
//		Computer Graphics it is much more convenient to represent a point
//		as a vector with three components. i.e. we treat the X, Y and Z
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


typedef						struct	Point3d							Point3d_t	;

typedef						struct	Point2d							Point2d_t	;


typedef						DECL_ARRAY	( Point2d_t )		ARRAY ( Point2d_t )	;

typedef						DECL_ARRAY	( Point3d_t )		ARRAY ( Point3d_t )	;




//////////////////////////////////////////////////////////////////////////////////
//							Point Operations
//////////////////////////////////////////////////////////////////////////////////




HOWTO_COPY					(	Point2d_t,	to,		from	)	;

HOWTO_COPY					(	Point3d_t,	to,		from	)	;


HOWTO_COMPOSE				(	Point2d_t,
								self,
								float		x,
								float		y
							)	;

HOWTO_COMPOSE				(	Point3d_t,
								self,
								float		x,
								float		y,
								float		z
							)	;


HOWTO_CONSTRUCT				(	Point2d_t,
								self,
								float		x,
								float		y
							)	;

HOWTO_CONSTRUCT				(	Point3d_t,
								self,
								float		x,
								float		y,
								float		z
							)	;


HOWTO_DESTRUCT				(	Point2d_t,
								self
							)	;

HOWTO_DESTRUCT				(	Point3d_t,
								self
							)	;




//////////////////////////////////////////////////////////////////////////////////
//							Dynamic Array Operations
//////////////////////////////////////////////////////////////////////////////////




HOWTO_ARRAY_INIT			(	Point2d_t,	self	)	;

HOWTO_ARRAY_INIT			(	Point3d_t,	self	)	;


HOWTO_ARRAY_RESET			(	Point2d_t,	self	)	;

HOWTO_ARRAY_RESET			(	Point3d_t,	self	)	;


HOWTO_CONSTRUCT				(	ARRAY ( Point2d_t ),
								self,
								void*	null
							)	;

HOWTO_CONSTRUCT				(	ARRAY ( Point3d_t ),
								self,
								void*	null
							)	;

HOWTO_DESTRUCT				(	ARRAY ( Point2d_t ),
								self
							)	;

HOWTO_DESTRUCT				(	ARRAY ( Point3d_t ),
								self
							)	;


HOWTO_LOAD					(	Point2d_t,	self,	array,	idx	)	;

HOWTO_LOAD					(	Point3d_t,	self,	array,	idx	)	;


HOWTO_STORE					(	Point2d_t,	self,	array,	idx	)	;

HOWTO_STORE					(	Point3d_t,	self,	array,	idx	)	;


HOWTO_PUSH					(	Point2d_t,	self,	array	)	;

HOWTO_PUSH					(	Point3d_t,	self,	array	)	;



//////////////////////////////////////////////////////////////////////////////////
//							Geomertic Operations
//////////////////////////////////////////////////////////////////////////////////




HOWTO_ROTATE				(	Point2d_t,
								self,
								Vec2_t*		angle
							)	;

HOWTO_ROTATE				(	Point3d_t,
								self,
								Vec3_t*		angle
							)	;


HOWTO_DRAW					(	Point2d_t,
								self,
								Color_t*			color,
								Renderer_t*			renderer
							)	;


HOWTO_DRAW					(	Point3d_t,
								self,
								Color_t*			color,
								Renderer_t*			renderer
							)	;




HOWTO_PROJECT				(	Point2d_t,			Point3d_t,
								to,					from,
								Projection_type_t	type
							)	;




//////////////////////////////////////////////////////////////////////////////////
//							Arithmetic Operations
//////////////////////////////////////////////////////////////////////////////////




HOWTO_ADD					(	Point2d_t,	dst,	op1,	op2	)	;

HOWTO_ADD					(	Point3d_t,	dst,	op1,	op2	)	;


HOWTO_SUB					(	Point2d_t,	dst,	op1,	op2	)	;

HOWTO_SUB					(	Point3d_t,	dst,	op1,	op2	)	;


HOWTO_MUL					(	Point2d_t,	dst,	src,	factor	)	;

HOWTO_MUL					(	Point3d_t,	dst,	src,	factor	)	;


HOWTO_DIV					(	Point2d_t,	dst,	src,	factor	)	;

HOWTO_DIV					(	Point3d_t,	dst,	src,	factor	)	;


HOWTO_NORM					(	Point2d_t,	self	)	;

HOWTO_NORM					(	Point3d_t,	self	)	;


HOWTO_INC					(	Point2d_t,	self,	inc		)	;

HOWTO_INC					(	Point3d_t,	self,	inc		)	;


HOWTO_DOTP					(	Point2d_t,	dst,	src1,	src2	)	;

HOWTO_DOTP					(	Point3d_t,	dst,	src1,	src2	)	;


HOWTO_CROSSP				(	Point3d_t,	dst,	src1,	src2	)	;


