/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#pragma once

#include "color.h"
#include "point.h"




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




typedef						struct Triangle3d	{	Point3d_t	p1;
													Point3d_t	p2;
													Point3d_t	p3;
												}						Triangle3d_t;


typedef						struct Triangle2d	{	Point2d_t	p1;
													Point2d_t	p2;
													Point2d_t	p3;
												}						Triangle2d_t;




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
//						@	-	-	-	-	-	@
//					+		+				+		+	
//				+				+		+				+
//		4.	@	-	-	-	-	-	@	-	-	-	-	-	@ 5.
//				+				+	1.	+				+
//					+		+				+		+
//						@	-	-	-	-	-	@
//						6.						7.
//
//
//		Notice how the vertex (1) = { 0.0800, 0.000, 0.000 } is shared
//		between the triangles: [1,2,3] , [1,2,4] , [1,4,6] , [1,3,5] ,
//		[1,6,7] and [1,5,7]. If we only keep the value of the vertices
//		of our triangles inside a single array, then the value of our
//		vertex (1) will appear 6 times in our triangles array without
//		any way for us to know it's the same vertex. Keeping the data
//		for the vertices and the faces isolated within separate arrays
//		helps us to minimize the number of redundent vertices in the
//		memory.
//
//
//////////////////////////////////////////////////////////////////////////////////


typedef						struct Face			{	int		idx1;
													int		idx2;
													int		idx3;
												}						Face_t;




typedef						DECL_ARRAY			(	Face_t,
													int*	idx1;
													int*	idx2;
													int*	idx3;
												);


typedef						DECL_ARRAY			(	Triangle2d_t,
													ARRAY ( Point2d_t )		p1;
													ARRAY ( Point2d_t )		p2;
													ARRAY ( Point2d_t )		p3;
												);


typedef						DECL_ARRAY			(	Triangle3d_t,
													ARRAY ( Point3d_t )		p1;
													ARRAY ( Point3d_t )		p2;
													ARRAY ( Point3d_t )		p3;
												);


////////////////////////////////////////////////////////////////////////////////
//				Triangle Operations
////////////////////////////////////////////////////////////////////////////////


HOWTO_COPY						(	Face_t,			to,	from	);

HOWTO_COPY						(	Triangle2d_t,	to,	from	);

HOWTO_COPY						(	Triangle3d_t,	to,	from	);


/////////////////////////////////////////////////////////////////////////////////
//				Dynamic Array Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ARRAY_INIT				(	Face_t,			array	);

HOWTO_ARRAY_INIT				(	Triangle2d_t,	array	);

HOWTO_ARRAY_INIT				(	Triangle3d_t,	array	);


HOWTO_ARRAY_RESET				(	Face_t,			array	);

HOWTO_ARRAY_RESET				(	Triangle2d_t,	array	);

HOWTO_ARRAY_RESET				(	Triangle3d_t,	array	);


HOWTO_LOAD						(	Face_t,			ptr,	array,	idx		);

HOWTO_LOAD						(	Triangle2d_t,	ptr,	array,	idx		);

HOWTO_LOAD						(	Triangle3d_t,	ptr,	array,	idx		);


HOWTO_STORE						(	Face_t,			ptr,	array	);

HOWTO_STORE						(	Triangle2d_t,	ptr,	array	);

HOWTO_STORE						(	Triangle3d_t,	ptr,	array	);


/////////////////////////////////////////////////////////////////////////////////
//				Geomertic Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ROTATE					(	Triangle3d_t,	to,	from,	vec3_t* angle	);

HOWTO_ROTATE					(	Triangle2d_t,	to,	from,	vec2_t* angle	);


HOWTO_DRAW						(	Triangle2d_t,
									triangle,
									Point2d_t*			origin,
									Color_t*			color,
									Color_buffer_t*		colorbuf	);

HOWTO_DRAW						(	Triangle3d_t,
									triangle,
									Point2d_t*			origin,
									Color_t*			color,
									Color_buffer_t*		colorbuf	);


HOWTO_PROJECT					(	Triangle2d_t,		Triangle3d_t,
									to,					from,
									Projection_type_t	type	);





