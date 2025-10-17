/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include <math.h>

#include "util.h"
#include "vector.h"




float							fov_scale		=	256;

Vec3_t							camera [ 1 ]	=	{{	.x	=	0.0,
														.y	=	0.0,
														.z	=	-5.0	}};


////////////////////////////////////////////////////////////////////////////////
//				Vector Structures Implementation
////////////////////////////////////////////////////////////////////////////////


struct							Vec2
{
	float						x	;

	float						y	;
};

struct							Vec3
{
	float						x	;

	float						y	;

	float						z	;
};

DECL_ARRAY					(	Vec2_t	)
{
	float*						x	;

	float*						y	;

	int							count	;
};

DECL_ARRAY					(	Vec3_t	)
{
	float*						x	;

	float*						y	;

	float*						z	;

	int							count	;
};


////////////////////////////////////////////////////////////////////////////////
//				Vector Operations Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_COPY					(	Vec2_t,		to,	from	)
{
	to->x					=	from->x	;

	to->y					=	from->y	;
}


HOWTO_COPY					(	Vec3_t,		to,	from	)
{
	to->x					=	from->x	;

	to->y					=	from->y	;

	to->z					=	from->z	;
}


HOWTO_COMPOSE				(	Vec2_t,
								self,
								float	x,
								float	y
							)
{
	self->x					=	x;

	self->y					=	y;
}


HOWTO_COMPOSE				(	Vec3_t,
								self,
								float	x,
								float	y,
								float	z
							)
{
	self->x					=	x	;

	self->y					=	y	;

	self->z					=	z	;
}


HOWTO_CONSTRUCT				(	Vec2_t,
								self,
								float x,
								float y
							)
{
	ALLOC_ZEROED			(	Vec2_t,
								self,
								1
							)	;

	ASSERT					(	self != NULL, " "	)	;

	COMPOSE					(	Vec2_t,
								self,
								x,	y
							)	;
}

HOWTO_CONSTRUCT				(	Vec3_t,
								self,
								float x,
								float y,
								float z
							)
{
	ALLOC_ZEROED			(	Vec3_t,
								self,
								1
							)	;

	ASSERT					(	self != NULL, ""	)	;

	COMPOSE					(	Vec3_t,
								self,
								x,	y,	z
							)	;
}

HOWTO_DESTRUCT				(	Vec2_t,
								self
							)
{
	DEALLOC					(	self	)	;
}

HOWTO_DESTRUCT				(	Vec3_t,
								self
							)
{
	DEALLOC					(	self	)	;
}




/////////////////////////////////////////////////////////////////////////////////
//				Dynamic Array Operations Implementation
/////////////////////////////////////////////////////////////////////////////////




HOWTO_ARRAY_INIT			(	Vec2_t,	self	)
{
	self->x					=	NULL	;

	self->y					=	NULL	;

	self->count				=	0	;
}


HOWTO_ARRAY_INIT			(	Vec3_t,	self	)
{
	self->x					=	NULL	;

	self->y					=	NULL	;

	self->z					=	NULL	;

	self->count				=	0	;
}


HOWTO_ARRAY_RESET			(	Vec2_t,	self	)
{
	array_free				(	self->x	)	;
	array_free				(	self->y	)	;

	self->x					=	NULL	;
	self->y					=	NULL	;

	self->count				=	0	;
}


HOWTO_ARRAY_RESET			(	Vec3_t,	self	)
{
	array_free				(	self->x	)	;
	array_free				(	self->y	)	;
	array_free				(	self->z	)	;

	self->x					=	NULL	;
	self->y					=	NULL	;
	self->z					=	NULL	;

	self->count				=	0	;
}


HOWTO_CONSTRUCT				(	ARRAY ( Vec2_t ),
								self,
								void*	null
							)
{
	ALLOC_ZEROED			(	ARRAY ( Vec2_t ),
								self,
								1
							)	;

	ASSERT					(	self != NULL, ""	)	;

	ARRAY_INIT				(	Vec2_t,		self	)	;
}

HOWTO_CONSTRUCT				(	ARRAY ( Vec3_t ),
								self,
								void*	null
							)
{
	ALLOC_ZEROED			(	ARRAY ( Vec3_t ),
								self,
								1
							)	;

	ASSERT					(	self != NULL, ""	)	;

	ARRAY_INIT				(	Vec3_t,		self	)	;
}

HOWTO_DESTRUCT				(	ARRAY ( Vec2_t ),
								self
							)
{
}

HOWTO_DESTRUCT				(	ARRAY ( Vec3_t ),
								self
							)
{
}

HOWTO_LOAD					(	Vec2_t,	self,	array,	idx	)
{
	self->x					=	array->x [ idx ]	;

	self->y					=	array->y [ idx ]	;
}


HOWTO_LOAD					(	Vec3_t,	self,	array,	idx	)
{
	self->x					=	array->x [ idx ]	;

	self->y					=	array->y [ idx ]	;

	self->z					=	array->z [ idx ]	;
}


HOWTO_PUSH					(	Vec2_t,	self,	array	)
{
	array_push				(	array->x,	self->x	)	;

	array_push				(	array->y,	self->y	)	;

	array->count++;
}


HOWTO_PUSH					(	Vec3_t,	self,	array	)
{
	array_push				(	array->x,	self->x	)	;

	array_push				(	array->y,	self->y	)	;

	array_push				(	array->z,	self->z	)	;

	array->count++;
}


HOWTO_STORE					(	Vec2_t,	self,	array,	idx		)
{
	Vec2_t						zero = { 0 };

	while					(	array->count	<=	idx		)
	{
		PUSH				(	Vec2_t,
								&zero,
								array
							);
	}

	array->x [ idx ]		=	self->x;
	array->y [ idx ]		=	self->y;
}


HOWTO_STORE					(	Vec3_t,	self,	array,	idx		)
{
	Vec3_t						zero = { 0 };

	while					(	array->count	<=	idx	)
	{
		PUSH				(	Vec3_t,
								&zero,
								array
							);
	}

	array->x [ idx ]		=	self->x;
	array->y [ idx ]		=	self->y;
	array->z [ idx ]		=	self->z;
}




//////////////////////////////////////////////////////////////////////////////////
//				Geomertic Operations Implementations
//////////////////////////////////////////////////////////////////////////////////




static
void
rotate_vector_x				(	Vec3_t* v,		float angle		)
{

	TMP						(	Vec3_t,
								transform_v,
								1
							);

	// X component remains same
	transform_v->x			=	v->x;
	transform_v->y			=	v->y * cos(	angle	)	-	v->z * sin(	angle	);
	transform_v->z			=	v->z * cos(	angle	)	+	v->y * sin(	angle	);

	COPY					(	Vec3_t,
								v,
								transform_v
							);
}

static
void
rotate_vector_y				(	Vec3_t*	v,		float angle		)
{
	TMP						(	Vec3_t,
								transform_v,
								1
							);

	// Y component remains same
	transform_v->x			=	v->x * cos(	angle	)	-	v->z * sin(	angle	);
	transform_v->y			=	v->y;
	transform_v->z			=	v->z * cos(	angle	)	+	v->x * sin(	angle	);

	COPY					(	Vec3_t,
								v,
								transform_v
							);
}


static
void
rotate_vector_z				(	Vec3_t* v,	float angle	)
{
	TMP						(	Vec3_t,
								transform_v,
								1
							);

	// Z component remains same
	transform_v->x			=	v->x * cos(	angle	)	-	v->y * sin(	angle	);
	transform_v->y			=	v->y * cos(	angle	)	+	v->x * sin(	angle	);
	transform_v->z			=	v->z;

	COPY					(	Vec3_t,
								v,
								transform_v
							);
}


HOWTO_ROTATE				(	Vec3_t,	self,	Vec3_t* angle	)
{
	if						(	angle->x != 0	)
	{
		rotate_vector_x		(	self,	angle->x	);
	}

	if						(	angle->y != 0	)
	{
		rotate_vector_y		(	self,	angle->y	);
	}

	if						(	angle->z != 0	)
	{
		rotate_vector_z		(	self,	angle->z	);
	}

}




static
Vec2_t
project_orthographic		(	Vec3_t*		vector		)
{
	TMP						(	Vec2_t,
								projection,
								1
							);

	projection->x			=	fov_scale	*	vector->x;
	projection->y			=	fov_scale	*	vector->y;

	RETURN					(	*projection		);
}

static
Vec2_t
project_isometric			(	Vec3_t*		vector	)
{
	TMP						(	Vec2_t,
								projection,
								1
							);
	// TODO: Implement this
	RETURN					(	*projection		);
}

static
Vec2_t
project_perspective			(	Vec3_t*	vector	)
{
	float						z = (	vector->z + camera->z	);

	TMP						(	Vec2_t,
								projection,
								1
							);

	projection->x			=	( (	vector->x * fov_scale	) / z	);
	projection->y			=	( (	vector->y * fov_scale	) / z	);

	RETURN					(	*projection		);
}




HOWTO_PROJECT				(	Vec2_t,				Vec3_t,
								to,					from,
								Projection_type_t	type	)
{

	switch					(	type	)
	{
		case				(	ORTHOGRAPHIC	):
			*to				=	project_orthographic	(	from	);
			break;
		case				(	ISOMETRIC		):
			*to				=	project_isometric		(	from	);
			break;
		case				(	PERSPECTIVE		):
			*to				=	project_perspective		(	from	);
			break;
		default:
			LOG				(	"Unsupported projection type: %d\n",
								type
							);
			break;
	}
}




//////////////////////////////////////////////////////////////////////////////////
//				Arithmetic Operations Implementation
//////////////////////////////////////////////////////////////////////////////////




HOWTO_ADD					(	Vec2_t,	dst,	op1,	op2	)
{
	dst->x					=	op1->x	+	op2->x;
	dst->y					=	op1->y	+	op2->y;
}

HOWTO_ADD					(	Vec3_t,	dst,	op1,	op2	)
{
	dst->x					=	op1->x	+	op2->x;
	dst->y					=	op1->y	+	op2->y;
	dst->z					=	op1->z	+	op2->z;
}


HOWTO_SUB					(	Vec2_t,	dst,	op1,	op2	)
{
	dst->x					=	op1->x	-	op2->x;
	dst->y					=	op1->y	-	op2->y;
}

HOWTO_SUB					(	Vec3_t,	dst,	op1,	op2	)
{
	dst->x					=	op1->x	-	op2->x;
	dst->y					=	op1->y	-	op2->y;
	dst->z					=	op1->z	-	op2->z;
}


HOWTO_MUL					(	Vec2_t,	dst,	src,	factor	)
{
	dst->x					=	factor	*	src->x;
	dst->y					=	factor	*	src->y;
}

HOWTO_MUL					(	Vec3_t,	dst,	src,	factor	)
{
	dst->x					=	factor	*	src->x;
	dst->y					=	factor	*	src->y;
	dst->z					=	factor	*	src->z;
}


HOWTO_DIV					(	Vec2_t,	dst,	src,	factor	)
{
	dst->x					=	src->x	/	factor;
	dst->y					=	src->y	/	factor;
}

HOWTO_DIV					(	Vec3_t,	dst,	src,	factor	)
{
	dst->x					=	src->x	/	factor;
	dst->y					=	src->y	/	factor;
	dst->z					=	src->z	/	factor;
}


HOWTO_NORM					(	Vec2_t,	self	)
{

	float						vlen_sqr	= 0,
								vlen		= 0;

	DOTP					(	Vec2_t,
								&vlen_sqr,
								self,
								self
							);

	vlen					=	sqrt	(	vlen_sqr	);

	DIV						(	vec2_t,
								self,
								self,
								vlen
							);
}


HOWTO_NORM					(	Vec3_t,	self	)
{

	float						vlen_sqr	= 0,
								vlen		= 0;

	DOTP					(	Vec3_t,
								&vlen_sqr,
								self,
								self
							);

	vlen					=	sqrt	(	vlen_sqr	);

	DIV						(	Vec3_t,
								self,
								self,
								vlen
							);
}


HOWTO_INC					(	Vec2_t,	self,	inc		)
{
	ADD						(	Vec2_t,
								self,
								self,
								inc
							);
}


HOWTO_INC					(	Vec3_t,	self,	inc		)
{
	ADD						(	Vec3_t,
								self,
								self,
								inc
							);
}


HOWTO_DOTP					(	Vec2_t,		dst,	src1,	src2	)
{
	*dst					=	src1->x		*	src2->x
							+	src1->y		*	src2->y;
}


HOWTO_DOTP					(	Vec3_t,		dst,	src1,	src2	)
{
	*dst					=	src1->x		*	src2->x
							+	src1->y		*	src2->y
							+	src1->z		*	src2->z;
}


HOWTO_CROSSP				(	Vec3_t,		dst,	src1,	src2	)
{
	dst->x					=	src1->y		*	src2->z
							-	src2->y		*	src1->z;

	dst->y					=	src1->z		*	src2->x
							-	src1->x		*	src2->z;

	dst->z					=	src1->x		*	src2->y
							-	src1->y		*	src2->x;
}

