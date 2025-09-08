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

HOWTO_COPY					(	Triangle_t,		to,				from	)
{
	COPY					(	Point3d_t,		&to->p1,		&from->p1	);

	COPY					(	Point3d_t,		&to->p2,		&from->p2	);

	COPY					(	Point3d_t,		&to->p3,		&from->p3	);
}

HOWTO_ROTATE				(	Triangle_t,
								to,				from,			vec3_t	angle	)
{
	ROTATE					(	Point3d_t,
								&to->p1,		&from->p1,		angle	);

	ROTATE					(	Point3d_t,
								&to->p2,		&from->p2,		angle	);

	ROTATE					(	Point3d_t,
								&to->p3,		&from->p3,		angle	);
}

HOWTO_DRAW					(	Triangle_t,
								triangle,
								Point2d_t*						origin,
								Color_t*						color,
								Color_buffer_t*					colorbuf	)
{

	Line_t						line1 = { 0 },
								line2 = { 0 },
								line3 = { 0 };

	Point2d_t					proj1 = { 0 },
								proj2 = { 0 },
								proj3 = { 0 };


	DRAW					(	Point3d_t,		&triangle->p1,
								origin,			color,			colorbuf	);

	DRAW					(	Point3d_t,		&triangle->p2,
								origin,			color,			colorbuf	);

	DRAW					(	Point3d_t,		&triangle->p3,
								origin,			color,			colorbuf	);


	PROJECT					(	Point2d_t,		Point3d_t,
								&proj1,			&triangle->p1,	PERSPECTIVE	);

	PROJECT					(	Point2d_t,		Point3d_t,
								&proj2,			&triangle->p2,	PERSPECTIVE	);

	PROJECT					(	Point2d_t,		Point3d_t,
								&proj3,			&triangle->p3,	PERSPECTIVE	);


	COPY					(	Point2d_t,		&line1.p1,		&proj1		);
	COPY					(	Point2d_t,		&line1.p2,		&proj2		);

	COPY					(	Point2d_t,		&line2.p1,		&proj2		);
	COPY					(	Point2d_t,		&line2.p2,		&proj3		);

	COPY					(	Point2d_t,		&line3.p1,		&proj1		);
	COPY					(	Point2d_t,		&line3.p2,		&proj3		);


	DRAW					(	Line_t,			&line1,
								origin,			color,			colorbuf	);

	DRAW					(	Line_t,			&line2,
								origin,			color,			colorbuf	);

	DRAW					(	Line_t,			&line3,
								origin,			color,			colorbuf	);

	// Use the force, Luke!
	return SUCCESS;
}