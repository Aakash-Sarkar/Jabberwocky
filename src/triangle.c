/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "triangle.h"
#include "line.h"



 /////////////////////////////////////////////////////////////////////////////////
 //						Memory Ops Implementation
 //////////////////////////////////////////////////////////////////////////////////


HOWTO_DEF						(	Triangle2d_t,	self	)
{

	Point2d_t						*p1		=	NULL,
									*p2		=	NULL,
									*p3		=	NULL;


	DEF							(	Point2d_t,
									p1
								);

	DEF							(	Point2d_t,
									p2
								);

	DEF							(	Point2d_t,
									p3
								);

	NEW							(	Triangle2d_t,
									self,
									p1,
									p2,
									p3
								);


	DEL							(	Point2d_t,
									p1
								);

	DEL							(	Point2d_t,
									p2
								);

	DEL							(	Point2d_t,
									p3
								);

	RET							(	self	);
}


HOWTO_INIT						(	Triangle2d_t,
									self,
									Point2d_t		*p1,
									Point2d_t		*p2,
									Point2d_t		*p3
								)
{

	MCPY						(	Point2d_t,
									( self )->p1,
									( p1 )
								);

	MCPY						(	Point2d_t,
									( self )->p2,
									( p2 )
								);

	MCPY						(	Point2d_t,
									( self )->p3,
									( p3 )
								);
}


HOWTO_FINI						(	Triangle2d_t,	self	)
{

	DEL							(	Point2d_t,
									( self )->p1
								);

	DEL							(	Point2d_t,
									( self )->p2
								);

	DEL							(	Point2d_t,
									( self )->p3
								);
}


HOWTO_DEF						(	Triangle3d_t,	self	)
{
	Point3d_t						*p1		=	NULL,
									*p2		=	NULL,
									*p3		=	NULL;


	DEF							(	Point3d_t,
									p1
								);

	DEF							(	Point3d_t,
									p2
								);

	DEF							(	Point3d_t,
									p3
								);

	NEW							(	Triangle3d_t,
									self,
									p1,		p2,		p3
								);


	DEL							(	Point3d_t,
									p1
								);

	DEL							(	Point3d_t,
									p2
								);

	DEL							(	Point3d_t,
									p3
								);

	RET							(	self	);
}


HOWTO_INIT						(	Triangle3d_t,
									self,
									Point3d_t		*p1,
									Point3d_t		*p2,
									Point3d_t		*p3
								)
{

	MCPY						(	Point3d_t,
									( self )->p1,
									( p1 )
								);

	MCPY						(	Point3d_t,
									( self )->p2,
									( p2 )
								);

	MCPY						(	Point3d_t,
									( self )->p3,
									( p3 )
								);
}

HOWTO_FINI						(	Triangle3d_t,	self	)
{

	DEL							(	Point3d_t,
									( self )->p1
								);

	DEL							(	Point3d_t,
									( self )->p2
								);

	DEL							(	Point3d_t,
									( self )->p3
								);
}


HOWTO_CPY						(	Triangle2d_t,	to,	from	)
{

	MCPY						(	Point2d_t,
									( to )->p1,
									( from )->p1
								);

	MCPY						(	Point2d_t,
									( to )->p2,
									( from )->p2
								);

	MCPY						(	Point2d_t,
									( to )->p3,
									( from )->p3
								);
}

HOWTO_CPY						(	Triangle3d_t,	to,	from	)
{

	MCPY						(	Point3d_t,
									( to )->p1,
									( from )->p1
								);

	MCPY						(	Point3d_t,
									( to )->p2,
									( from )->p2
								);

	MCPY						(	Point3d_t,
									( to )->p3,
									( from )->p3
								);
}


/////////////////////////////////////////////////////////////////////////////////
//						Iterator Ops Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT						(	itr ( Triangle2d_t ),
									self,
									const Triangle2d_t		*ptr,
									unsigned int			pos,
									IterType_t				typ
								)
{
	INITITR						(	Triangle2d_t,
									self,
									ptr,
									pos,
									typ	
								);
}

HOWTO_INIT						(	itr ( Triangle3d_t ),
									self,
									const Triangle3d_t		*ptr,
									unsigned int			pos,
									IterType_t				typ
								)
{
	INITITR						(	Triangle3d_t,
									self,
									ptr,
									pos,
									typ
								);
}


HOWTO_FINI						(	itr ( Triangle2d_t ),	self	)
{
	FINIITR						(	Triangle2d_t,
									( self )
								);
}

HOWTO_FINI						(	itr ( Triangle3d_t ),	self	)
{
	FINIITR						(	Triangle3d_t,
									( self )
								);
}


HOWTO_DEF						(	itr ( Triangle2d_t ),	self	)
{
	NEW							(	itr ( Triangle2d_t ),
									( self ),
									( NULL ),
									( 0 ),
									( MAX_ITER )
								);

	RET							(	self	);
}

HOWTO_DEF						(	itr ( Triangle3d_t ),	self	)
{
	NEW							(	itr ( Triangle3d_t ),
									self,
									NULL,
									0,
									MAX_ITER
								);

	RET							(	self	);
}


HOWTO_CMP						(	itr ( Triangle2d_t ),	it1,	it2		)
{
	CMPITR						(	Triangle2d_t,
									( it1 ),
									( it2 )
								);
}

HOWTO_CMP						(	itr ( Triangle3d_t ),	it1,	it2		)
{
	CMPITR						(	Triangle3d_t,
									( it1 ),
									( it2 )
								);
}


HOWTO_INC						(	itr ( Triangle2d_t ),	self		)
{
	INCITR						(	Triangle2d_t,
									( self )
								);
}

HOWTO_INC						(	itr ( Triangle3d_t ),	self		)
{
	INCITR						(	Triangle3d_t,
									( self )
								);
}


HOWTO_DEC						(	itr ( Triangle2d_t ),	self		)
{
	DECITR						(	Triangle2d_t,
									( self )
								);
}

HOWTO_DEC						(	itr ( Triangle3d_t ),	self		)
{
	DECITR						(	Triangle3d_t,
									( self )
								);
}


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic array Ops Implementation
/////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT						(	arr ( Triangle2d_t ),
									self,
									const Triangle2d_t		*init_list,
									unsigned int			count
								)
{
	INITARR						(	Triangle2d_t,
									self,
									init_list,
									count
								);
}

HOWTO_INIT						(	arr ( Triangle3d_t ),
									self,
									const Triangle3d_t		*init_list,
									unsigned int			count
								)
{
	INITARR						(	Triangle3d_t,
									self,
									init_list,
									count
								);
}


HOWTO_DEF						(	arr	( Triangle2d_t ),	self	)
{
	NEW							(	arr ( Triangle2d_t ),
									( self ),
									( NULL ),
									( 0 )
								);

	RET							(	self	);
}


HOWTO_DEF						(	arr ( Triangle3d_t ),	self	)
{
	NEW							(	arr ( Triangle3d_t ),
									( self ),
									( NULL ),
									( 0 )
								);

	RET							(	self	);
}


HOWTO_FINI						(	arr ( Triangle2d_t ),	self	)
{
	FINIARR						(	Triangle2d_t,
									( self )
								);
}

HOWTO_FINI						(	arr	( Triangle3d_t ),	self	)
{
	FINIARR						(	Triangle3d_t,
									( self )
								);
}


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic array Ops Implementation
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ROT						(	Triangle2d_t,
									self,
									Vec2_t			*angle
								)
{
}

HOWTO_ROT						(	Triangle3d_t,
									self,
									Vec3_t			*angle
								)
{

	ROT							(	Point3d_t,
									( self )->p1,
									( angle )
								);

	ROT							(	Point3d_t,
									( self )->p2,
									( angle )
								);

	ROT							(	Point3d_t,
									( self )->p3,
									( angle )
								);
}




HOWTO_DRAW						(	Triangle2d_t,
									self,
									Point2d_t			*origin,
									Color_t				*color,
									Color_buffer_t		*colorbuf
								)
{

	Line_t							*line1		=	NULL,
									*line2		=	NULL,
									*line3		=	NULL;


	NEW							(	Line_t,
									( line1 ),
									( self )->p2,
									( self )->p1
								);

	NEW							(	Line_t,
									( line2 ),
									( self )->p3,
									( self )->p2
								);

	NEW							(	Line_t,
									( line3 ),
									( self )->p1,
									( self )->p3
								);

	//	Draw the edges

	DRAW						(	Line_t,
									line1,
									origin,
									color,
									colorbuf
								);

	DRAW						(	Line_t,
									line2,
									origin,
									color,
									colorbuf
								);

	DRAW						(	Line_t,
									line3,
									origin,
									color,
									colorbuf
								);

	//	Draw the vertices

	DRAW						(	Point2d_t,
									( self )->p1,
									origin,
									color,
									colorbuf
								);

	DRAW						(	Point2d_t,
									( self )->p2,
									origin,
									color,
									colorbuf
								);

	DRAW						(	Point2d_t,
									( self )->p3,
									origin,
									color,
									colorbuf
								);

	//FILL						(	Triangle2d_t,
	//								self,
	//								origin,
	//								color,
	//								colorbuf
	//							);

	DEL							(	Line_t,
									line1
								);

	DEL							(	Line_t,
									line2
								);

	DEL							(	Line_t,
									line3
								);
}

HOWTO_DRAW						(	Triangle3d_t,
									self,
									Point2d_t			*origin,
									Color_t				*color,
									Color_buffer_t		*colorbuf
								)
{

	Triangle2d_t					*proj	=	NULL;

	DEF							(	Triangle2d_t,
									proj
								);

	PROJ						(	Triangle2d_t,		Triangle3d_t,
									proj,				self,
									PERSPECTIVE
								);

	DRAW						(	Triangle2d_t,
									proj,
									origin,
									color,
									colorbuf
								);

	DEL							(	Triangle2d_t,
									proj
								);
}




HOWTO_PROJ						(	Triangle2d_t,		Triangle3d_t,
									to,					from,
									Projection_type_t	type
								)
{

	PROJ						(	Point2d_t,			Point3d_t,
									( to )->p1,			( from )->p1,
									type
								);

	PROJ						(	Point2d_t,			Point3d_t,
									( to )->p2,			( from )->p2,
									type
								);

	PROJ						(	Point2d_t,			Point3d_t,
									( to )->p3,			( from )->p3,
									type
								);
}


HOWTO_FILL						(	Triangle2d_t,
									self,
									Point2d_t			*origin,
									Color_t				*color,
									Color_buffer_t		*colorbuf
								)
{

	Triangle2d_t					*top		=		NULL,
									*bot		=		NULL;

	Point2d_t						*slope1		=		NULL,
									*slope2		=		NULL;

	Line_t							*edge1		=		NULL,
									*edge2		=		NULL;

	float							x_start		=		0,
									x_end		=		0;

	float							y_start		=		0,
									y_end		=		0;

	float							x_inc1		=		0,
									x_inc2		=		0;

	float							y_inc1		=		0,
									y_inc2		=		0;

	float							origin_x	=		0,
									origin_y	=		0;


	DEF							(	Triangle2d_t,
									top
								);

	DEF							(	Triangle2d_t,
									bot
								);

	DEF							(	Point2d_t,
									slope1
								);

	DEF							(	Point2d_t,
									slope2
								);

	REQ							(	Triangle2d_t,
									get_flat_top_bottom,
									self,
									top,
									bot
								);

	NEW							(	Line_t,
									edge1,
									( top )->p1,
									( top )->p2
								);

	NEW							(	Line_t,
									edge2,
									( top )->p1,
									( top )->p3
								);

	REQ							(	Line_t,
									get_slope,
									edge1,
									slope1
								);

	REQ							(	Line_t,
									get_slope,
									edge2,
									slope2
								);

	y_start						=	( top )->p1->v->y;
	y_end						=	( top )->p2->v->y;

	x_start						=	( top )->p1->v->x;
	x_end						=	( top )->p1->v->x;

	x_inc1						=	( slope1 )->v->x;
	x_inc2						=	( slope2 )->v->x;

	origin_x					=	( origin )->v->x;
	origin_y					=	( origin )->v->y;


	_FILL						(	x_start,		x_end,
									y_start,		y_end,
									x_inc1,			x_inc2,
									y_inc1,			y_inc2,
									origin_x,		origin_y,
									color,			colorbuf
								);
}






//////////////////////////////////////////////////////////////////////////////
//							SURFACE NORMAL:
//////////////////////////////////////////////////////////////////////////////
//
//
//		Surface normal of a triangle gives us a point vector that is
//		orthogonal to the plane containing the triangle. That means
//		the normal vector should be at a right angle to all the three
//		edges that form the surface of the triangle.
// 
//
//															p3
//								      	^					+
//									  	:			"	+
//									  N :	"		+
//									"   :		+
//							"				+
//				+	+	+	+	+	+	+
//				p1						p2	
//
//
//		The easiest way to find the normal vector to a triangle is to
//		perform a cross product between any two edges of the triangle.
//		So our first step is to find the vectors that form any two
//		edges of our triangle. For e.g. in the diagram above the lines
//		[ p1, p2 ] and [ p1, p3 ] form the two edges of triangle [ p1,
//		p2, p3 ]. If we do a cross product between the two lines p12
//		and p13 then we can get a third vector N that'll be orthogonal
//		to both p12 and p13.
//
//
//		We can easily get the vectors p12 and p13 by subtracting b/w
//		the two end points [ p1, p2 ] and [ p1, p3 ].
//
//
//		[ p12 ]		=	vector [ p1 --> p2 ]	=	p2	-	p1
//
//		[ p13 ]		=	vector [ p1 --> p3 ]	=	p3	-	p1
//
//
//		Then we can do a cross product b/w p12 and p13 in order to
//		get our surface normal N.
//
// 
//		[  N ]		=	[ p12 ]		x	[ p13 ]
//
// 		[ -N ]		=	[ p13 ]		x	[ p12 ]
//
//
//		Note that there are two possible normal vectors [N] and [-N]
//		depending on the order of the arguments.
//
//
//////////////////////////////////////////////////////////////////////////////


METHOD							(	Triangle3d_t,
									get_surface_normal,
									self,
									Point3d_t			*out
								)
{

	Point3d_t						*p12	=	NULL,
									*p13	=	NULL;


	DEF							(	Point3d_t,
									p12
								);

	DEF							(	Point3d_t,
									p13
								);

	//	p12 is the point vector from p1 to p2

	SUB							(	Point3d_t,
									( p12 ),
									( self )->p2,
									( self )->p1
								);

	//	p13 is the point vector from p1 to p3

	SUB							(	Point3d_t,
									( p13 ),
									( self )->p3,
									( self )->p1
								);

	//////////////////////////////////////////////////////////////////////////////
	//
	//
	//		Since p12 and p13 form a plane that is parallel to the surface
	//		of our triangle; their cross product will give us a vector
	//		perpendicular to our triangle.
	//
	//		Note that we can have two normal vectors in opposite directions
	//		for our triangle face depending on whether we are doing p12 x p13
	//		or p13 x p12.
	//
	//
	//////////////////////////////////////////////////////////////////////////////


	CROSP						(	Point3d_t,
									out,
									p12,
									p13
								);

	assert						(	out	);

	DEL							(	Point3d_t,
									p12
								);

	DEL							(	Point3d_t,
									p13
								);

	//NORM							(	Point3d_t,
	//									normal
	//								);

	RET							(	self	);
}


//////////////////////////////////////////////////////////////////////////////
//							BACK FACE CULLING:
//////////////////////////////////////////////////////////////////////////////
//
//
//		Back face culling is a optimization technique used in 3D Graphics
//		where we discard the triangle surfaces, that are facing away from
//		the camera, from the rendering process. The idea here being that
//		the triangle faces in an object model facing away from the camera
//		will be occluded by the triangle faces of the same object facing
//		towards the camera.
// 
//
//										^
//										:
//									"	:	"
//								"		:		"
//								|	"		"	|
//								|		"		|
//								|		|		|
//								"		|		"
//									"	|	"
//										"
//										:
//										:	Y-axis
//										v
//
// 
// 
//		In the diagram above, assume that the cube is rotating along the
//		Y-axis. As the cube rotates only two or three out of the six cube
//		faces will be visible to the user at any given point in time. The
//		remaining faces will always be out of sight. They'll always stay
//		hidden behind the visible faces. If we drop the hidden faces from
//		the rendering process, the user will not notice any difference in
//		the resulting image; and we can get away with rendering only half
//		of the triangles. Backface culling is intended to do exactly this.
// 
// 
//		With the above background let's describe how the backface culling
//		works under the hood.
// 
// 
//									
//									:					"
//									:				"		"
//									:			"		x		"
//									:			|	"		"	|
//					camera ray		:			|		"		|
//		<0 < - - - - - - - - - - - -: - - -  - -|- x	|	x	|
//		eye							:O			"		|		"
//									:				"	|	"
//									:					"
//									:
//									
//								Image plane
// 
// 
//		First let us assume that at the centre of each of the six cube
//		faces there's a vector attached. This vector is of unit length
//		and is perpendicular to the face where it is attached to. Let's
//		call this vector the normal vector to the cube face ( marked
//		with x in the diagram above).
// 
// 
//		Next let's define the camera ray. Our camera ray is a vector
//		that is pointing outwards from the cube face towards the eye of
//		the user. We can find the camera ray by subtracting any of the
//		three triangle vertices from the co-ordinates of the eye. For
//		e.g. if our origin is at the center of the screen, and the user
//		is 5 units away from the screen, then our eye co-odrinates will
//		be { 0.0f, 0.0f, -5.0f }.
//
//
//		[ ray ]		=	[ eye ]	-	[ a vertex of the triangle ]
//
// 
//		Notice when a cube face is facing directly towards the user eye;
//		the normal vector and the camera ray will be completely aligned
//		with each other ( i.e. pointing in the same direction ). As the
//		cube starts to rotate, the normal vector and the camera ray will
//		start to spread out and move away from each other. When the cube
//		face is facing away from the eye, the normal vector and the cam
//		ray will point in opposite directions.
// 
// 
//		We can detect how aligned the camera ray is to the normal vector
//		by checking the dot product between them. If the dot product is
//		positive, that means the normal vector and the camera ray are
//		roughly pointing in the same direction ( i.e. the cube face is
//		visible to the eye ). When the dot product becomes negative that
//		means the camera ray and the face normal vector have begun to
//		move in the opposite directions and the face is now out of sight
//		and can be culled ( dropped from the rendering process ).
// 
// 
//////////////////////////////////////////////////////////////////////////////


METHOD							(	Triangle3d_t,
									is_back_facing,
									self,
									bool		*out
								)
{
	assert						(	out	);

	Point3d_t						*normal	=	NULL,
									*cam	=	NULL,
									*ray	=	NULL;

	float							*dotp	=	NULL;

	DEF							(	Point3d_t,
									normal
								);

	DEF							(	Point3d_t,
									ray
								);

	DEF							(	float,
									dotp
								);

	REQ							(	Triangle3d_t,
									get_surface_normal,
									self,
									normal
								);

	assert						(	normal	);

	NEW							(	Point3d_t,
									cam,
									0.00f,	0.00f,	-5.00f
								);

	SUB							(	Point3d_t,
									ray,
									cam,
									( self )->p1
								);

	assert						(	ray		);

	DOTP						(	Point3d_t,
									dotp,
									normal,
									ray
								);

	assert						(	dotp	);

	*out						=	(	*dotp	<	0	)
								?	true	:	false;

	DEL							(	float,
									dotp
								);

	DEL							(	Point3d_t,
									ray
								);

	DEL							(	Point3d_t,
									normal
								);

	RET							(	self	);
}


METHOD							(	Triangle2d_t,
									get_flat_top_bottom,
									self,
									Triangle2d_t	*out_top,
									Triangle2d_t	*out_bot
								)
{

	assert						(	out_top		);
	assert						(	out_bot		);

	Point2d_t						*midp	=	NULL;

	//	Sort triangles based on increasing y co-ordinate

	if							(	( self )->p1->v->y > ( self )->p2->v->y	)
	{

		SWP						(	Point2d_t,
									( self )->p1,
									( self )->p2
								);
	}

	if							(	( self )->p2->v->y > ( self )->p3->v->y	)
	{

		SWP						(	Point2d_t,
									( self )->p2,
									( self )->p3
								);
	}

	if							(	( self )->p1->v->y > ( self )->p2->v->y	)
	{

		SWP						(	Point2d_t,
									( self )->p1,
									( self )->p2
								);
	}

	assert						(	( self )->p1->v->y <= ( self )->p2->v->y	);
	assert						(	( self )->p2->v->y <= ( self )->p3->v->y	);



	//////////////////////////////////////////////////////////////////////////////
	//							Calculating the midpoint:
	//////////////////////////////////////////////////////////////////////////////
	//
	//
	//		Lat's assume we have a triangle with three vetices p1 = ( x1, y1 ),
	//		p2 = ( x2, y2 ), p3 = ( x3, y3 ). 
	// 
	//
	//					Y
	//					^
	//					|
	//				 y1 + - - - - - - - @  p1 = ( x0, y0 )
	//					|			   /:|
	//					|			  / : |
	//					|			 /	:  |
	//					|			/   :   |
	//			My = y2 + - - - - @ - - + - -@  Mp = ( Mx, My )
	//					|	   p2 : \_	: q  :|
	//					|		  :	   \_	 : |
	//					|		  :		: \_ :	|
	//					|		  :	    :	 \_	 |
	//				 y3 + - - - - + - - + - -+ -\_@  p3 = ( x3, y3 )
	//					|		  :	  r :	 :	  :
	//					|		  :		:	 :	  :
	//					+---------+-----+----+----+------ >	X
	//							  x2	x1	Mx	 x3
	//
	// 
	//		First thing to note here is: since p1, p2 and p3 are sorted based
	//		on increasing order of y; My will be equal to y2. So, we have our
	//		first equation as follows:
	// 
	//				My	=	y2							-- ( 1 )
	//
	//		Next we need to find Mx. We'll use triangle similarity along with
	//		the above equation ( 1 ) to find Mx.
	//
	//
	//		Since, triangle {p1, q, Mp} is similar to triangle {p1, r, p3} we
	//		have the following equation:
	// 
	//				( Mx - x1 )			( y2 - y1 )	
	//				-----------		=	-----------
	//				( x3 - x1 )			( y3 - y1 )	
	//
	// 
	//		Rearranging this gives us the equation for Mx:
	// 
	//				Mx	=	x1	+	( y2 - y1 ) * ( x3 - x1 ) / ( y3 - y1 )
	// 
	// 
	//////////////////////////////////////////////////////////////////////////////


	float							midx	=	0.0f,
									midy	=	0.0f;

	float							x1	=	( self )->p1->v->x,
									y1	=	( self )->p1->v->y;


	float							x2	=	( self )->p2->v->x,
									y2	=	( self )->p2->v->y;

	float							x3	=	( self )->p3->v->x,
									y3	=	( self )->p3->v->y;

	midy						=	y1;

	midx						=	x1	+	(
										(	y2	-	y1	)
									*	(	x3	-	x1	)
									/	(	y3	-	y1	)
								);

	NEW							(	Point2d_t,
									midp,
									midx,
									midy
								);

	Triangle2d_t					*top	=	NULL,
									*bot	=	NULL;

	NEW							(	Triangle2d_t,
									top,
									( self )->p1,
									( self )->p2,
									( midp )
								);

	NEW							(	Triangle2d_t,
									bot,
									( self )->p2,
									( midp ),
									( self )->p3
								);

	CPY							(	Triangle2d_t,
									out_top,
									top
								);

	CPY							(	Triangle2d_t,
									out_bot,
									bot
								);

	DEL							(	Triangle2d_t,
									top
								);

	DEL							(	Triangle2d_t,
									bot
								);

	RET							(	self	);
}
