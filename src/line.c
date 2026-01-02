/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "line.h"



HOWTO_CONSTRUCT				(	Line_t,
								self,
								Point2d_t	*p1,
								Point2d_t	*p2		)
{
	CPY						(	Point2d_t,
								self->p1,
								p1
							);

	CPY						(	Point2d_t,
								self->p2,
								p2
							);
}

HOWTO_DESTRUCT				(	Line_t,		self	)
{
	DEL						(	Point2d_t,
								self->p1
							);

	DEL						(	Point2d_t,
								self->p2
							);
}

HOWTO_CPY					(	Line_t,		to,		from	)
{
	CPY						(	Point2d_t,
								to->p1,
								from->p1
							);

	CPY						(	Point2d_t,
								to->p2,
								from->p2
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
//			( rise (x, y) + slope )
//
//
//////////////////////////////////////////////////////////////////////////////////



HOWTO_DRAW					(	Line_t,
								self,
								Point2d_t*				origin,
								Color_t*				color, 
								Color_buffer_t*			colorbuf
							)
{
	Point2d_t					*p12	=	NULL,
								*slope	=	NULL;

	SUB						(	Point2d_t,
								p12,
								self->p2,
								self->p1
							);

	float						x	=	*p12->v->x,
								y	=	*p12->v->y;

	float						run	=	max	(	abs(x),	abs(y)	);


	//////////////////////////////////////////////////////////////////////////////
	//
	//		Depending on which component becomes our run, our slope vector
	//		will have one of the component as (run/run) = 1, and the other
	//		as (rise/run) = slope
	//
	//////////////////////////////////////////////////////////////////////////////


	DIV						(	Point2d_t,
								slope,
								p12,
								&run
							);

	Point2d_t					*point		=	NULL,
								*o_point	=	NULL;

	DEF						(	Point2d_t,
								point
							);

	DEF						(	Point2d_t,
								o_point
							);

	CPY						(	Point2d_t,
								point,
								self->p1
							);

	for						(	int i = 0;	i <= run;	i++		)
	{
		ADD					(	Point2d_t,
								o_point,
								point,
								origin
							);

		float					posX	=	0,
								posY	=	0;

		posX				=	*o_point->v->x;
		posY				=	*o_point->v->y;

		paint_color			(	color,
								colorbuf,
								PIXELFORMAT_ARGB8888,
								round( 	posX ),
								round(	posY ),
								0
							);

		ADD					(	Point2d_t,
								point,
								point,
								slope
							);
	}

	DEL						(	Point2d_t,
								point
							);

	DEL						(	Point2d_t,
								o_point
							);

	DEL						(	Point2d_t,
								p12
							);

	DEL						(	Point2d_t,
								slope
							);
}

