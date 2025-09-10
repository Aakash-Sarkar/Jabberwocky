/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "point.h"
#include "rect.h"




HOWTO_COPY				(	Point2d_t,		to,			from	)
{
	COPY				(	vec2_t,			&to->v,		&from->v	);
}

HOWTO_COPY				(	Point3d_t,		to,			from	)
{
	COPY				(	vec3_t,			&to->v,		&from->v	);
}

HOWTO_ROTATE			(	Point2d_t,
							to,				from,		vec3_t	angle	)
{
}

HOWTO_ROTATE			(	Point3d_t,
							to,				from,		vec3_t	angle	)
{
	ROTATE				(	vec3_t,
							&to->v,			&from->v,	angle	);
}

HOWTO_DRAW				(	Point2d_t,
							point,
							Point2d_t*					origin,
							Color_t*					color,
							Color_buffer_t*				colorbuf	)
{

	int						posX = 0,
							posY = 0;

	Rect_t					rect = { 0 };

	posX				=	( int )	(	point->v.x	+	origin->v.x		);
	posY				=	( int )	(	point->v.y	+	origin->v.y		);

	rect.posX			=	posX;
	rect.posY			=	posY;
	rect.width			=	4;
	rect.height			=	4;

	DRAW				(	Rect_t,		&rect,
							color,		colorbuf	);
}

HOWTO_DRAW				(	Point3d_t,
							point,
							Point2d_t*					origin,
							Color_t*					color,
							Color_buffer_t*				colorbuf	)
{

	Point2d_t				proj = { 0 };

	PROJECT				(	Point2d_t,	Point3d_t,
							&proj,		point,			PERSPECTIVE	);

	DRAW				(	Point2d_t,	&proj,
							origin,		color,			colorbuf	);
}

HOWTO_PROJECT			(	Point2d_t,	Point3d_t,
							to,			from,
							Projection_type_t			type	)
{
	PROJECT				(	vec2_t,		vec3_t,
							&to->v,		&from->v,		type	);
}