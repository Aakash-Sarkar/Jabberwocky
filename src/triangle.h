/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#pragma once

#include "color.h"
#include "point.h"
#include "renderer.h"




//////////////////////////////////////////////////////////////////////////////////
//								TRIANGLES:
//////////////////////////////////////////////////////////////////////////////////
//
//
//		Aside from points ( or vertices ), another building block of a 3D
//		object are the triangle faces formed by set of three consecutive
//		points. Triangle faces are needed since we need some surface area
//		to fill color into our object model.
//
//
//		In other words, we fill the color into our object model by filling
//		colors into each of the triangle faces separately. We can give our
//		object a realistic 3D look by choosing the color for each of our
//		triangle faces a little bit differently.
//
//
//		To give an example of this, imagine if we have a 3D sphere as our
//		object model. If we fill the sphere with a uniform red color and
//		display it on the screen; then it'll look like just a red circle
//		without any visible realism. However if we pick all the triangles
//		facing towards the sun and fill them with little bright red color
//		whereas, fill all the triangles facing away from the sun with a
//		little darker red color; then we could have a much more realistic
//		looking sphere with 3D characteristics.
//
//
//							  *				-->  light source
//
//								\		+
//								 \	+  +
//								+ \	  +		-->  triangle facing towards 
//							+		 +			 light source
//						+ + + + + + +
//
//
//		Learning how to do this in a effective way is what makes Computer
//		Graphics interesting. There are many interesting algorithms for
//		shading our triangles, each with their own pros and cons. Some of
//		them give more realisitic images but are more complex, whereas
//		others are simpler but give less realistic images.
//
//
//		Another thing to point out here is that the quality of our final
//		image depends directly on the number of triangles in our object
//		model. With more number of triangles at our disposal, we can set
//		the color of our objects in a more fine grained manner. However,
//		this requires us to allocate a lot more memory for each one of
//		our object models and a lot more processing power to process all
//		these triangles in real time.
//
//
//		In order to get around this problem, what many video games do is
//		keep two copies of an object model: one high resolution copy with
//		more number of triangles, and one low resolution with less number
//		of triangles. When the player is at proximity to the object, the
//		game loads the high resolution model whereas, when the player is
//		distant from the object, the game loads the low resolution model.
//
//
//////////////////////////////////////////////////////////////////////////////////




typedef					struct Triangle3d						Triangle3d_t;

typedef					struct Triangle2d						Triangle2d_t;


typedef					DECL_ARRAY ( Triangle2d_t )		ARRAY ( Triangle2d_t );


typedef					DECL_ARRAY ( Triangle3d_t )		ARRAY ( Triangle3d_t );




////////////////////////////////////////////////////////////////////////////////
//						Triangle Operations
////////////////////////////////////////////////////////////////////////////////




HOWTO_CPY						(	Triangle2d_t,	to,	from	);

HOWTO_CPY						(	Triangle3d_t,	to,	from	);


HOWTO_CONSTRUCT					(	Triangle2d_t,
									self,
									float	x1,		float	y1,
									float	x2,		float	y2,
									float	x3,		float	y3
								);


HOWTO_CONSTRUCT					(	Triangle3d_t,
									self,
									float	x1,		float	y1,		float	z1,
									float	x2,		float	y2,		float	z2,
									float	x3,		float	y3,		float	z3
								);


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic Array Operations
/////////////////////////////////////////////////////////////////////////////////




HOWTO_ARRAY_INIT				(	ARRAY ( Triangle2d_t ),	self	);

HOWTO_ARRAY_INIT				(	ARRAY ( Triangle3d_t ),	self	);


HOWTO_ARRAY_RESET				(	ARRAY ( Triangle2d_t ),	self	);

HOWTO_ARRAY_RESET				(	ARRAY ( Triangle3d_t ),	self	);


HOWTO_CONSTRUCT					(	ARRAY ( Triangle2d_t ),
									self,
									void*	null
								);

HOWTO_CONSTRUCT					(	ARRAY ( Triangle3d_t ),
									self,
									void*	null
								);

HOWTO_DESTRUCT					(	ARRAY ( Triangle2d_t ),
									self
								);

HOWTO_DESTRUCT					(	ARRAY ( Triangle3d_t ),
									self
								);


HOWTO_LD						(	Triangle2d_t,	self,	array,	idx		);

HOWTO_LD						(	Triangle3d_t,	self,	array,	idx		);


HOWTO_STR						(	Triangle2d_t,	self,	array,	idx		);

HOWTO_STR						(	Triangle3d_t,	self,	array,	idx		);


HOWTO_COUNT						(	ARRAY ( Triangle2d_t ),	self	);

HOWTO_COUNT						(	ARRAY ( Triangle3d_t ),	self	);


HOWTO_INC						(	ARRAY ( Triangle2d_t ), self, int inc	);

HOWTO_INC						(	ARRAY ( Triangle3d_t ),	self, int inc	);




/////////////////////////////////////////////////////////////////////////////////
//						Geomertic Operations
/////////////////////////////////////////////////////////////////////////////////




HOWTO_ROT						(	Triangle3d_t,	self,	Vec3_t* angle	);

HOWTO_ROT						(	Triangle2d_t,	self,	Vec2_t* angle	);


HOWTO_DRAW						(	Triangle2d_t,
									self,
									Color_t*			color,
									Renderer_t*			renderer
								);

HOWTO_DRAW						(	Triangle3d_t,
									self,
									Color_t *			color,
									Renderer_t *		renderer
								);


HOWTO_PROJ						(	Triangle2d_t,		Triangle3d_t,
									to,					from,
									Projection_type_t	type
								);

