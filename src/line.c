/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "line.h"



HOWTO_INIT					(	Line_t,
								self,
								Point2d_t		*p1,
								Point2d_t		*p2
							)
{

	float						del_x	=	0.0f,
								del_y	=	0.0f;

	Point2d_t					*p12	=	NULL;

	MCPY					(	Point2d_t,
								( self )->p1,
								( p1 )
							);

	MCPY					(	Point2d_t,
								( self )->p2,
								( p2 )
							);

	//////////////////////////////////////////////////////////////////////////////////
	//
	//		We initialize our slope and inverse slope vectors as unit vectors
	//		( 1, 0 ) and ( 0, 1 ) along the X and Y co-ordinate axes. These
	//		values act as the default slope value if our line is vertical or
	//		horizontal and we need to avoid division by zero.
	// 
	//////////////////////////////////////////////////////////////////////////////////

	NEW						(	Point2d_t,
								( self )->slope,
								( 1.0f ),
								( 0.0f )
							);

	NEW						(	Point2d_t,
								( self )->inv_slope,
								( 0.0f ),
								( 1.0f )
							);


	DEF						(	Point2d_t,
								p12
							);

	SUB						(	Point2d_t,
								( p12 ),
								( self )->p2,
								( self )->p1
							);

	del_x					=	abs ( ( p12 )->v->x );
	del_y					=	abs ( ( p12 )->v->y );


	if						(	del_x != 0	)
	{
		DIV					(	Point2d_t,
								( self )->slope,
								( p12 ),
								( del_x )
							);
	}

	if						(	del_y != 0	)
	{
		DIV					(	Point2d_t,
								( self )->inv_slope,
								( p12 ),
								( del_y )
							);
	}

	DEL						(	Point2d_t,
								p12
							);
}


HOWTO_FINI					(	Line_t,		self	)
{

	DEL						(	Point2d_t,
								( self )->p1
							);

	DEL						(	Point2d_t,
								( self )->p2
							);

	DEL						(	Point2d_t,
								( self )->slope
							);

	DEL						(	Point2d_t,
								( self )->inv_slope
							);
}


HOWTO_CPY					(	Line_t,		to,		frm	)
{

	CPY						(	Point2d_t,
								( to )->p1,
								( frm )->p1
							);

	CPY						(	Point2d_t,
								( to )->p2,
								( frm )->p2
							);
}




//////////////////////////////////////////////////////////////////////////////////
//						Geomertic Operations Implementations
//////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////
//								DDA ALGORITHM:
//////////////////////////////////////////////////////////////////////////////////
//
//
//		One of the classic problems in Computer Graphics is that: given two
//		end points p1 and p2 how to draw a line between them. There are two
//		popular algorithms for drawing lines. One is called the DDA (Digital
//		Differential Analyzer ) algorithm; while the second one is Bresenham
//		algorithm. We are using the DDA algorithm here for drawing our lines,
//		since it's much easier to understand and to implement as compared to
//		Bresenham algorithm
//
//
//		The DDA Algorithm is intuitively very similar to how one would draw
//		a line using a pen and a paper. In order to draw our line we need as
//		our inputs the two end points of our line. First we hold our pen at
//		one of the end point and then start to move and color pixel by pixel
//		until we reach our other end point where we stop. Finding out which
//		pixel to color next is at the heart of the DDA Algorithm.
//
//
//		In order to find the next pixel to color, we use the property of a
//		line that the slope of a line is always constant. A very useful way
//		of thinking about this is the following: If we start off from any
//		point on a line and move a unit distance along the X-axis, then the
//		corresponding movement along the Y-axis will always remain constant;
//		no matter which point you choose to start from. The exact value of
//		the movement along the Y-axis is given by the slope of that line.
//		The inverse of this property is also true: If we pick a point on the
//		line and move a unit distance along the Y-axis, then the resulting
//		movement along the X-axis will always remain constant and is given
//		by the inverse of the slope of that line.
//
//
//
//												*
//											*	|
//										*	|	|
//									*	|	|	|	} --> Movement in Y
//								*	|	|	|	|
//							*	|	|	|	|	|
//						*---+---+---+---+---+---+
//						  1	  1   1   1   1   1
//
//
//
//		With the above background, let's define the DDA Algorithm:
//
//		1.	We have two end points (x0, y0) and (x1, y1) to draw our line.
//
//		2.	Find the run of the line:  max of y1 - y0, x1 - x0
//
//		3.	Find the rise of the line: min of y1 - y0, x1 - x0
//
//		4.	Find the slope of the line: rise / run
//
//		5.	Next pixel to draw would be at ( run ( x, y ) + 1 ),
//			( rise ( x, y ) + slope )
//
//
//////////////////////////////////////////////////////////////////////////////////



HOWTO_DRAW					(	Line_t,
								line,
								Point2d_t			*origin,
								Color_t				*color, 
								Color_buffer_t		*colorbuf
							)
{
	Point2d_t					*slope	=	NULL,
								*tmp	=	NULL;

	MCPY					(	Point2d_t,
								( tmp ),
								( line )->p1
							);

	int							x_start	=	round ( ( line )->p1->v->x ),
								y_start	=	round ( ( line )->p1->v->y );

	int							x_end	=	round ( ( line )->p2->v->x ),
								y_end	=	round ( ( line )->p2->v->y );

	int							start	=	0,
								end		=	0;

	if						(	x_start == x_end	)
	{
		GET					(	slope,	( line )->inv_slope	);

		start				=	( y_start < y_end )
							?	( y_start )
							:	( y_end );

		end					=	( y_start < y_end )
							?	( y_end )
							:	( y_start );
	}

	else if					(	y_start == y_end	)
	{
		GET					(	slope,	( line )->slope	);

		start				=	( x_start < x_end )
							?	( x_start )
							:	( x_end );

		end					=	( x_start < x_end )
							?	( x_end )
							:	( x_start );
	}

	else if					(	abs ( ( line )->slope->v->y ) < 1	)
	{
		GET					(	slope,	( line )->slope	);

		start				=	( x_start < x_end )
							?	( x_start )
							:	( x_end );

		end					=	( x_start < x_end )
							?	( x_end )
							:	( x_start );
	}

	else
	{
		GET					(	slope,	( line )->inv_slope	);

		start				=	( y_start < y_end )
							?	( y_start )
							:	( y_end );

		end					=	( y_start < y_end )
							?	( y_end )
							:	( y_start );
	}

	while					(	start <= end	)
	{
		DRAW				(	Point2d_t,
								tmp,
								origin,
								color,
								colorbuf
							);

		ADD					(	Point2d_t,
								tmp,
								tmp,
								slope
							);

		start++;
	}

	DEL						(	Point2d_t,
								tmp
							);
}


