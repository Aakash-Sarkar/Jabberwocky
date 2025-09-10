/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "line.h"
#include "mesh.h"
#include "triangle.h"




HOWTO_COPY					(	Face_t,			to,				from	)
{
	to->idx [ 0 ]			=	from->idx [ 0 ];
	to->idx [ 1 ]			=	from->idx [ 1 ];
	to->idx [ 2 ]			=	from->idx [ 2 ];
}

HOWTO_COPY					(	Triangle2d_t,	to,				from	)
{
	COPY					(	Point2d_t,		&to->p1,		&from->p1	);
	COPY					(	Point2d_t,		&to->p2,		&from->p2	);
	COPY					(	Point2d_t,		&to->p3,		&from->p3	);
}

HOWTO_COPY					(	Triangle3d_t,	to,				from	)
{
	COPY					(	Point3d_t,		&to->p1,		&from->p1	);
	COPY					(	Point3d_t,		&to->p2,		&from->p2	);
	COPY					(	Point3d_t,		&to->p3,		&from->p3	);
}


HOWTO_ROTATE				(	Triangle2d_t,	to,	from,		vec3_t angle	)
{

}

HOWTO_ROTATE				(	Triangle3d_t,	to,	from,		vec3_t angle	)
{
	ROTATE					(	Point3d_t,
								&to->p1,		&from->p1,		angle	);

	ROTATE					(	Point3d_t,
								&to->p2,		&from->p2,		angle	);

	ROTATE					(	Point3d_t,
								&to->p3,		&from->p3,		angle	);
}


HOWTO_DRAW					(	Triangle2d_t,
								triangle,
								Point2d_t*			origin,
								Color_t*			color,
								Color_buffer_t*		colorbuf	)
{

	Line_t						line1 = { 0 },
								line2 = { 0 },
								line3 = { 0 };

	COPY					(	Point2d_t,		&line1.p1,		&triangle->p1	);
	COPY					(	Point2d_t,		&line1.p2,		&triangle->p2	);

	COPY					(	Point2d_t,		&line2.p1,		&triangle->p2	);
	COPY					(	Point2d_t,		&line2.p2,		&triangle->p3	);

	COPY					(	Point2d_t,		&line3.p1,		&triangle->p1	);
	COPY					(	Point2d_t,		&line3.p2,		&triangle->p3	);

	// Draw the vertices
	DRAW					(	Point2d_t,		&triangle->p1,
								origin,			color,			colorbuf	);

	DRAW					(	Point2d_t,		&triangle->p2,
								origin,			color,			colorbuf	);

	DRAW					(	Point2d_t,		&triangle->p3,
								origin,			color,			colorbuf	);

	// Draw the edges
	DRAW					(	Line_t,			&line1,
								origin,			color,			colorbuf	);

	DRAW					(	Line_t,			&line2,
								origin,			color,			colorbuf	);

	DRAW					(	Line_t,			&line3,
								origin,			color,			colorbuf	);
}

HOWTO_DRAW					(	Triangle3d_t,
								triangle,
								Point2d_t*			origin,
								Color_t*			color,
								Color_buffer_t*		colorbuf	)
{

	Triangle2d_t				proj_triangle = { 0 };

	PROJECT					(	Triangle2d_t,		Triangle3d_t,
								&proj_triangle,		triangle,		PERSPECTIVE	);

	DRAW					(	Triangle2d_t,		&proj_triangle,
								origin,				color,			colorbuf	);
}


HOWTO_PROJECT				(	Triangle2d_t,		Triangle3d_t,
								to,					from,
								Projection_type_t	type		)
{
	Point2d_t					proj1 = { 0 },
								proj2 = { 0 },
								proj3 = { 0 };


	PROJECT					(	Point2d_t,			Point3d_t,
								&to->p1,			&from->p1,		type		);

	PROJECT					(	Point2d_t,			Point3d_t,
								&to->p2,			&from->p2,		type		);

	PROJECT					(	Point2d_t,			Point3d_t,
								&to->p3,			&from->p3,		type		);
}

