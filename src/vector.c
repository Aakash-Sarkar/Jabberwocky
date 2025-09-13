/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include <math.h>

#include "geometry.h"
#include "util.h"
#include "vector.h"




float						fov_scale = 256;

vec3_t						camera[1] = {{	.x = 0.0,
											.y = 0.0,
											.z = -5.0	}};




HOWTO_INIT_ARRAY			(	vec2_t,	array	)
{
	array->x				=	NULL;
	array->y				=	NULL;
	array->count			=	0;
}

HOWTO_INIT_ARRAY			(	vec3_t,	array	)
{
	array->x				=	NULL;
	array->y				=	NULL;
	array->z				=	NULL;
	array->count			=	0;
}


HOWTO_RESET_ARRAY			(	vec2_t,	array	)
{
	array_free				(	array->x	);
	array_free				(	array->y	);

	array->x				=	NULL;
	array->y				=	NULL;
	array->count			=	0;
}

HOWTO_RESET_ARRAY			(	vec3_t,	array	)
{
	array_free				(	array->x	);
	array_free				(	array->y	);
	array_free				(	array->z	);


	array->x				=	NULL;
	array->y				=	NULL;
	array->z				=	NULL;
	array->count			=	0;
}


HOWTO_LOAD					(	vec2_t,		ptr,	array,	idx	)
{
	ptr->x					=	array->x [ idx ];
	ptr->y					=	array->y [ idx ];
}

HOWTO_LOAD					(	vec3_t,		ptr,	array,	idx	)
{
	ptr->x					=	array->x [ idx ];
	ptr->y					=	array->y [ idx ];
	ptr->z					=	array->z [ idx ];
}

HOWTO_STORE					(	vec2_t,		ptr,	array	)
{
	array_push				(	array->x,	ptr->x	);

	array_push				(	array->y,	ptr->y	);

	array->count++;
}

HOWTO_STORE					(	vec3_t,		ptr,	array	)
{
	array_push				(	array->x,	ptr->x	);

	array_push				(	array->y,	ptr->y	);

	array_push				(	array->z,	ptr->z	);

	array->count++;
}




HOWTO_COPY				(	vec2_t,	to,	from	)
{
	to->x				=	from->x;
	to->y				=	from->y;
}

HOWTO_COPY				(	vec3_t, to,	from	)
{
	to->x				=	from->x;
	to->y				=	from->y;
	to->z				=	from->z;
}




static
vec3_t
rotate_vector_x			(	vec3_t* v, float angle	)
{
	MEM					(	vec3_t,		transform_v,	1	);

	// X component remains same
	transform_v->x		=	v->x;
	transform_v->y		=	v->y * cos(	angle	)	-	v->z * sin(	angle	);
	transform_v->z		=	v->z * cos(	angle	)	+	v->y * sin(	angle	);

	RETURN				(	*transform_v	);
}

static
vec3_t
rotate_vector_y			(	vec3_t*	v, float angle	)
{
	MEM					(	vec3_t,		transform_v,	1	);

	// Y component remains same
	transform_v->x		=	v->x * cos(	angle	)	-	v->z * sin(	angle	);
	transform_v->y		=	v->y;
	transform_v->z		=	v->z * cos(	angle	)	+	v->x * sin(	angle	);

	RETURN				(	*transform_v	);
}


static
vec3_t
rotate_vector_z			(	vec3_t* v,	float angle	)
{
	MEM					(	vec3_t,		transform_v,	1	);

	// Z component remains same
	transform_v->x		=	v->x * cos(	angle	)	-	v->y * sin(	angle	);
	transform_v->y		=	v->y * cos(	angle	)	+	v->x * sin(	angle	);
	transform_v->z		=	v->z;

	RETURN				(	*transform_v	);
}


HOWTO_ROTATE			(	vec3_t,		to,		from,	vec3_t* angle	)
{
	if					(	angle->x != 0	)
	{
		*to				= rotate_vector_x	(	from,	angle->x	);
	}

	if					(	angle->y != 0	)
	{
		*to				= rotate_vector_y	(	from,	angle->y	);
	}

	if					(	angle->z != 0	)
	{
		*to				= rotate_vector_z	(	from,	angle->z	);
	}
}




static
vec2_t
project_orthographic	(	vec3_t*		vector		)
{
	MEM					(	vec2_t,		projection,		1	);

	projection->x		=	fov_scale	*	vector->x;
	projection->y		=	fov_scale	*	vector->y;

	RETURN				(	*projection		);
}

static
vec2_t
project_isometric		(	vec3_t*		vector	)
{
	MEM					(	vec2_t,		projection,		1	);
	// TODO: Implement this
	RETURN				(	*projection		);
}

static
vec2_t
project_perspective		(	vec3_t*	vector	)
{
	float				z	=	(	vector->z + camera->z	);

	MEM					(	vec2_t,		projection,		1	);

	projection->x		=	((	vector->x * fov_scale	) / z	)	*	camera->z;
	projection->y		=	((	vector->y * fov_scale	) / z	)	*	camera->z;

	RETURN				(	*projection		);
}




HOWTO_PROJECT			(	vec2_t,	vec3_t,	to,		from,	Projection_type_t	type	)
{
	switch				(	type	)
	{
		case			(	ORTHOGRAPHIC	):
			*to			= project_orthographic	(	from	);
			break;
		case			(	ISOMETRIC		):
			*to			= project_isometric		(	from	);
			break;
		case			(	PERSPECTIVE		):
			*to			= project_perspective	(	from	);
			break;
		default:
			LOG			(	"Unsupported projection type: %d\n", type	);
			break;
	}
}

