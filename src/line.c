/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "line.h"


HOWTO_COPY					(	Line_t, to, from	)
{
	COPY					(	Point2d_t,	&to->p1,	&from->p1	);
	COPY					(	Point2d_t,	&to->p2,	&from->p2	);
}


HOWTO_DRAW					(	Line_t,
								line,
								Point2d_t*			origin,
								Color_t*			color, 
								Color_buffer_t*		colorbuf	)
{
	int							delta_X	 = (int) ( line->p2.v.x	- line->p1.v.x ),
								delta_Y	 = (int) ( line->p2.v.y	- line->p1.v.y );

	int							side_len = max ( abs ( delta_X ), abs ( delta_Y ) );

	float						delX  = ( delta_X / (float)	side_len ),
								delY  = ( delta_Y / (float)	side_len );

	Point2d_t					point = { 0 };

	COPY					(	Point2d_t,	&point,	&line->p1	);

	for						(	int i = 0;	i <= side_len;	i++	)
	{
		paint_color			(	color,
								colorbuf,
								(int) ( point.v.x	+	origin->v.x ),
								(int) ( point.v.y	+	origin->v.y ),
								0	);

		point.v.x			+=	delX;
		point.v.y			+=	delY;
	}
}

