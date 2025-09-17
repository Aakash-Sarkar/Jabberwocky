/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "line.h"




HOWTO_COPY					(	Line_t,		to,			from		)
{
	COPY					(	Point2d_t,	&to->p1,	&from->p1	);

	COPY					(	Point2d_t,	&to->p2,	&from->p2	);
}




//////////////////////////////////////////////////////////////////////////////////
//								DDA ALGORITHM:
//////////////////////////////////////////////////////////////////////////////////
//
//
//		One of the classic problems in Computer Graphics is how to draw a
//		line. There are two popular algorithms for this. One is called DDA
//		( Digital Differential Analyzer) and the other is Bresenham
//		Algorithm. We are using the DDA algorithm here for drawing our line
//		since it is much easier to understand and implement.
//
//
//		The DDA Algorithm is intuitively very similar to how one would draw
//		a line using a pen and a paper. In order to draw our line we need
//		as our input the two end points of our line. Then we hold our pen
//		at one of the end points and start to move and color pixel by pixel
//		until we reach our other end point where we stop. Finding which
//		pixel to color next is at the heart of the DDA Algorithm.
//
//
//		In order to find the next pixel to color, we use the property that
//		the slope of a line is always constant. A very useful way of
//		thinking about this is the following: If we start off at any point
//		in a line and move a unit distance along the X axis, then the
//		corresponding movement along the Y axis will always remain the same;
//		no matter which point you start from. The exact value of the movement
//		along the Y axis is given by the slope of the line. The inverse of
//		this is also true: If we move a unit distance along the Y axis, the
//		corresponding movement along the X axis will always remain the same
//		and is given by the inverse of the slope.
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
//		With the above background, let's define the DDA Algorithm:
//
//			1.	We have two end pixels (x0, y0) and (x1, y1) to draw line.
//
//			2.	Find the run of the line:  max of y1 - y0, x1 - x0
//
//			3.	Find the rise of the line: min of y1 - y0, x1 - x0
//
//			4.	Find the slope of the line: rise / run
//
//			5.	Next pixel to draw would be (x0 + 1), (y0 + slope)
//									  
//
//////////////////////////////////////////////////////////////////////////////////


HOWTO_DRAW					(	Line_t,
								line,
								Point2d_t*				origin,
								Color_t*				color, 
								Color_buffer_t*			colorbuf	)
{

	int							delta_X		= ( int ) ( line->p2.v.x	-	line->p1.v.x ),
								delta_Y		= ( int ) ( line->p2.v.y	-	line->p1.v.y );

	int							side_len	= max ( abs ( delta_X ), abs ( delta_Y ) );

	float						delX		= ( delta_X / ( float ) side_len ),
								delY		= ( delta_Y / ( float ) side_len );

	MEM						(	Point2d_t,	point,	1	);

	COPY					(	Point2d_t,	point,	&line->p1	);

	for						(	int i = 0;	i <= side_len;	i++		)
	{
		paint_color			(	color,
								colorbuf,
								PIXELFORMAT_ARGB8888,
								( int )	(	point->v.x	+	origin->v.x		),
								( int )	(	point->v.y	+	origin->v.y		),
								0
							);

		point->v.x			+=	delX;
		point->v.y			+=	delY;
	}
}

