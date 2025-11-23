/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "line.h"




////////////////////////////////////////////////////////////////////////////////
//						Line Structures Implementation
////////////////////////////////////////////////////////////////////////////////


struct						Line		{	Point2d_t*		p1;
											Point2d_t*		p2;
										};


////////////////////////////////////////////////////////////////////////////////
//						Line Operations Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_CONSTRUCT				(	Line_t,
								self,
								Point2d_t*		p1,
								Point2d_t*		p2
							)
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


HOWTO_CPY					(	Line_t,		to,	from	)
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
//		One of the classic problems in Computer Graphics is how to draw a
//		line. There are two popular algorithms for drawing lines. One is the
//		DDA ( Digital Differential Analyzer) alogorithm and the other is the
//		Bresenham algorithm. We are using the DDA algorithm here for drawing
//		our lines, since it is much easier to understand and to implement.
//
//
//		The DDA Algorithm is intuitively very similar to how one would draw
//		a line using a pen and a paper. In order to draw our line we need
//		as our inputs the two end points of our line. Then we hold our pen
//		at one of the end points and start to move and color pixel by pixel
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
								Color_t*			color,
								Renderer_t*			renderer
							)
{
	Point2d_t					*p12	=	NULL,
								*slope	=	NULL;

	SUB						(	Point2d_t,
								p12,
								self->p2,
								self->p1
							);

	float						x = 0,
								y = 0;

	MSG						(	Point2d_t,
								decompose,
								p12,
								&x, &y
							);

	float						run	= max (	abs ( x ), abs ( y ) );


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
								run
							);

	Point2d_t					*point		=	NULL,
								*o_point	=	NULL,
								*origin		=	NULL;

	CPY						(	Point2d_t,
								point,
								self->p1
							);

	MSG						(	Renderer_t,
								get_origin,
								renderer,
								origin
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

		MSG					(	Point2d_t,
								decompose,
								o_point,
								&posX,
								&posY
							);

		MSG					(	Renderer_t,
								paint_color,
								renderer,
								color,
								round ( posX ),
								round ( posY ),
								0
							);

		INC					(	Point2d_t,
								point,
								slope
							);
	}

	DEL						(	Point2d_t,
								p12
							);

	DEL						(	Point2d_t,
								slope
							);

	DEL						(	Point2d_t,
								point
							);

	DEL						(	Point2d_t,
								o_point
							);

	DEL						(	Point2d_t,
								origin
							);


}

