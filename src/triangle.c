/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "array.h"
#include "line.h"
#include "mesh.h"
#include "triangle.h"




HOWTO_INIT_ARRAY			(	Face_t,			array		)
{
	array->idx1				=	NULL;
	array->idx2				=	NULL;
	array->idx3				=	NULL;

	array->count			=	0;
}

HOWTO_INIT_ARRAY			(	Triangle2d_t,	array		)
{
	INIT_ARRAY				(	Point2d_t,		&array->p1	);
	INIT_ARRAY				(	Point2d_t,		&array->p2	);
	INIT_ARRAY				(	Point2d_t,		&array->p3	);

	array->count			=	0;
}

HOWTO_INIT_ARRAY			(	Triangle3d_t,	array		)
{
	INIT_ARRAY				(	Point3d_t,		&array->p1	);
	INIT_ARRAY				(	Point3d_t,		&array->p2	);
	INIT_ARRAY				(	Point3d_t,		&array->p3	);

	array->count			=	0;
}




HOWTO_RESET_ARRAY			(	Face_t,			array		)
{
	array_free				(	array->idx1		);
	array_free				(	array->idx2		);
	array_free				(	array->idx3		);

	array->count			=	0;
}

HOWTO_RESET_ARRAY			(	Triangle2d_t,	array		)
{
	RESET_ARRAY				(	Point2d_t,		&array->p1	);
	RESET_ARRAY				(	Point2d_t,		&array->p2	);
	RESET_ARRAY				(	Point2d_t,		&array->p3	);

	array->count			=	0;
}

HOWTO_RESET_ARRAY			(	Triangle3d_t,	array		)
{
	RESET_ARRAY				(	Point3d_t,		&array->p1	);
	RESET_ARRAY				(	Point3d_t,		&array->p2	);
	RESET_ARRAY				(	Point3d_t,		&array->p3	);

	array->count			=	0;
}




HOWTO_LOAD					(	Face_t,			ptr,		array,			idx	)
{
	ptr->idx1				=	array->idx1 [ idx ];
	ptr->idx2				=	array->idx2 [ idx ];
	ptr->idx3				=	array->idx3 [ idx ];
}

HOWTO_LOAD					(	Triangle2d_t,	ptr,		array,			idx	)
{
	LOAD					(	Point2d_t,		&ptr->p1,	&array->p1,		idx	);
	LOAD					(	Point2d_t,		&ptr->p2,	&array->p2,		idx	);
	LOAD					(	Point2d_t,		&ptr->p3,	&array->p3,		idx	);
}

HOWTO_LOAD					(	Triangle3d_t,	ptr,		array,			idx	)
{
	LOAD					(	Point3d_t,		&ptr->p1,	&array->p1,		idx	);
	LOAD					(	Point3d_t,		&ptr->p2,	&array->p2,		idx	);
	LOAD					(	Point3d_t,		&ptr->p3,	&array->p3,		idx	);
}




HOWTO_STORE					(	Face_t,			ptr,		array	)
{
	array_push				(	array->idx1,	ptr->idx1	);
	array_push				(	array->idx2,	ptr->idx2	);
	array_push				(	array->idx3,	ptr->idx3	);

	array->count++;
}

HOWTO_STORE					(	Triangle2d_t,	ptr,		array	)
{
	STORE					(	Point2d_t,		&ptr->p1,	&array->p1		);
	STORE					(	Point2d_t,		&ptr->p2,	&array->p2		);
	STORE					(	Point2d_t,		&ptr->p3,	&array->p3		);

	array->count++;
}

HOWTO_STORE					(	Triangle3d_t,	ptr,		array	)
{
	STORE					(	Point3d_t,		&ptr->p1,	&array->p1		);
	STORE					(	Point3d_t,		&ptr->p2,	&array->p2		);
	STORE					(	Point3d_t,		&ptr->p3,	&array->p3		);

	array->count++;
}




HOWTO_COPY					(	Face_t,			to,				from	)
{
	to->idx1				=	from->idx1;
	to->idx2				=	from->idx2;
	to->idx3				=	from->idx3;
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




HOWTO_ROTATE				(	Triangle2d_t,	to,	from,		vec2_t* angle	)
{

}

HOWTO_ROTATE				(	Triangle3d_t,	to,	from,		vec3_t* angle	)
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

	MEM						(	Line_t,			line1,			1	);
	MEM						(	Line_t,			line2,			1	);
	MEM						(	Line_t,			line3,			1	);



	COPY					(	Point2d_t,		&line1->p1,		&triangle->p1	);
	COPY					(	Point2d_t,		&line1->p2,		&triangle->p2	);

	COPY					(	Point2d_t,		&line2->p1,		&triangle->p2	);
	COPY					(	Point2d_t,		&line2->p2,		&triangle->p3	);

	COPY					(	Point2d_t,		&line3->p1,		&triangle->p1	);
	COPY					(	Point2d_t,		&line3->p2,		&triangle->p3	);




	// Draw the vertices
	DRAW					(	Point2d_t,		&triangle->p1,
								origin,			color,			colorbuf	);

	DRAW					(	Point2d_t,		&triangle->p2,
								origin,			color,			colorbuf	);

	DRAW					(	Point2d_t,		&triangle->p3,
								origin,			color,			colorbuf	);




	// Draw the edges
	DRAW					(	Line_t,			line1,
								origin,			color,			colorbuf	);

	DRAW					(	Line_t,			line2,
								origin,			color,			colorbuf	);

	DRAW					(	Line_t,			line3,
								origin,			color,			colorbuf	);
}

HOWTO_DRAW					(	Triangle3d_t,
								triangle,
								Point2d_t*			origin,
								Color_t*			color,
								Color_buffer_t*		colorbuf	)
{

	MEM						(	Triangle2d_t,		proj_triangle,	1	);

	PROJECT					(	Triangle2d_t,		Triangle3d_t,
								proj_triangle,		triangle,		PERSPECTIVE	);

	DRAW					(	Triangle2d_t,		proj_triangle,
								origin,				color,			colorbuf	);
}




HOWTO_PROJECT				(	Triangle2d_t,		Triangle3d_t,
								to,					from,
								Projection_type_t					type	)
{

	PROJECT					(	Point2d_t,			Point3d_t,
								&to->p1,			&from->p1,		type		);

	PROJECT					(	Point2d_t,			Point3d_t,
								&to->p2,			&from->p2,		type		);

	PROJECT					(	Point2d_t,			Point3d_t,
								&to->p3,			&from->p3,		type		);
}


