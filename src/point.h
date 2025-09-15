/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "array.h"
#include "vector.h"
#include "object.h"
#include "geometry.h"
#include "color.h"





/**
 * POINTS:
 *
 * Points are the building blocks of any 2D/3D object model. Any object model
 * that we see in a video game (tables, chairs, enemies etc) are described as
 * a collection of points (also called vertices). These points collectively
 * describe the silhouette of the object on which we paint color.
 *
 * Typically, one would represent a point as a set of three numbers describing
 * the X, Y and Z co-ordinates of the point. However, in Graphics it is much
 * more convenient to represent a point as a vector with three components. i.e,
 * we treat the X, Y, Z co-ordinates of a point as the components of a 3D vector.
 * 
 * This gives us several advantages:
 * 
 * 1. We can now perform vector operations on the points and follow the rules of
 *    vector algebra.
 * 
 * 2. We can change or tranform the position of a point in any way we want by
 *    multiplying it with a matrix. we can use this property to move the object
 *    model around by moving the individual points on the model one by one.
 * 
 * 3. We can change the co-ordinate system of the point. i.e, how would the
 *    object look if viewed by someone else. When Artists create an object
 *    model, they choose the co-ordinate system as viewed by the object itself.
 *    i.e, the origin would be the centre of the object or somewhere inside the
 *    object itself. This co-ordinate system is also called as the object space.
 *    The game needs to change these points to the co-ordinate system as viewed
 *    by the user.
 *
 * How do we know which matrix to use with which point for the desired movement?
 * This is where game physics comes into play. By using simplified equations of
 * physics we can get matrices to create simple motions (oscillations, rotations
 * etc). We can create complex animations by composing together these simple
 * motions.
 */



typedef					struct		{	vec2_t v;	}		Point2d_t;

/* We could also do `typedef vec3_t point3d_t` here, but then someone would
 * certainly try to pass a position vector in a function for colors. Doing
 * it this way will at least give a compilation error.
 */

typedef					struct		{	vec3_t v;	}		Point3d_t;




typedef					DECL_ARRAY	(	Point2d_t,	ARRAY ( vec2_t )	v;	);

typedef					DECL_ARRAY	(	Point3d_t,	ARRAY ( vec3_t )	v;	);




HOWTO_ARRAY_INIT		(	Point2d_t,	array	);

HOWTO_ARRAY_INIT		(	Point3d_t,	array	);


HOWTO_ARRAY_RESET		(	Point2d_t,	array	);

HOWTO_ARRAY_RESET		(	Point3d_t,	array	);



HOWTO_LOAD				(	Point2d_t,	ptr,	array,	idx	);

HOWTO_LOAD				(	Point3d_t,	ptr,	array,	idx	);


HOWTO_STORE				(	Point2d_t,	ptr,	array	);

HOWTO_STORE				(	Point3d_t,	ptr,	array	);




HOWTO_COPY				(	Point2d_t,	to,		from	);

HOWTO_COPY				(	Point3d_t,	to,		from	);




HOWTO_ROTATE			(	Point2d_t,	to,		from,	vec2_t* angle	);

HOWTO_ROTATE			(	Point3d_t,	to,		from,	vec3_t* angle	);




HOWTO_DRAW				(	Point2d_t,
							point,
							Point2d_t*			origin,
							Color_t*			color,
							Color_buffer_t*		colorbuf	);

HOWTO_DRAW				(	Point3d_t,
							point,
							Point2d_t*			origin,
							Color_t*			color,
							Color_buffer_t*		colorbuf	);




HOWTO_PROJECT			(	Point2d_t,			Point3d_t,
							to,					from,
							Projection_type_t	type		);

