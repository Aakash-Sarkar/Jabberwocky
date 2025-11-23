/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include <math.h>

#include "util.h"
#include "vector.h"
#include "types.h"
#include "object.h"




float						fov_scale			=	256;

Vec3_t						camera [ 1 ]		=	{{	.x		=	0.0,
														.y		=	0.0,
														.z		=	-5.0
													}};






////////////////////////////////////////////////////////////////////////////////
//				Vector Structures Implementation
////////////////////////////////////////////////////////////////////////////////


struct						Vec2				{	float		x;
													float		y;
												};

struct						Vec3				{	float		x;
													float		y;
													float		z;
												};

DECL_ARRAY				(	Vec2_t	)			{	float *		x;
													float *		y;
													int			count;
												};

DECL_ARRAY				(	Vec3_t	)			{	float *		x;
													float *		y;
													float *		z;
													int			count;
												};


////////////////////////////////////////////////////////////////////////////////
//				Vector Operations Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_CPY					(	Vec2_t,	to,		from	)
{
	to->x					=	from->x;
	to->y					=	from->y;
}


HOWTO_CPY					(	Vec3_t,	to,		from	)
{
	to->x					=	from->x;
	to->y					=	from->y;
	to->z					=	from->z;
}


HOWTO_CONSTRUCT				(	Vec2_t,
								self,
								float x,
								float y
							)
{
	self->x					=	x;
	self->y					=	y;
}

HOWTO_CONSTRUCT				(	Vec3_t,
								self,
								float x,
								float y,
								float z
							)
{
	self->x					=	x;
	self->y					=	y;
	self->z					=	z;
}

HOWTO_DESTRUCT				(	Vec2_t,	this	)
{
}

HOWTO_DESTRUCT				(	Vec3_t,	this	)
{
}




/////////////////////////////////////////////////////////////////////////////////
//				Dynamic Array Operations Implementation
/////////////////////////////////////////////////////////////////////////////////




HOWTO_ARRAY_INIT			(	ARRAY( Vec2_t ),		self	)
{
	self->x					=	NULL;
	self->y					=	NULL;

	self->count				=	0	;
}


HOWTO_ARRAY_INIT			(	ARRAY( Vec3_t ),		self	)
{
	self->x					=	EMPTY	;
	self->y					=	EMPTY	;
	self->z					=	EMPTY	;

	self->count				=	0	;
}


HOWTO_ARRAY_RESET			(	ARRAY ( Vec2_t ),	self	)
{
	array_free				(	self->x	)	;
	array_free				(	self->y	)	;

	self->x					=	EMPTY	;
	self->y					=	EMPTY	;

	self->count				=	0	;
}


HOWTO_ARRAY_RESET			(	ARRAY ( Vec3_t ),	self	)
{
	array_free				(	self->x	);
	array_free				(	self->y	);
	array_free				(	self->z	);

	self->x					=	NULL;
	self->y					=	NULL;
	self->z					=	NULL;

	self->count				=	0	;
}


HOWTO_CONSTRUCT				(	ARRAY ( Vec2_t ),
								self,
								void*	null
							)
{
	assert					(	self	);

	INIT					(	ARRAY ( Vec2_t ),	self	);
}

HOWTO_CONSTRUCT				(	ARRAY ( Vec3_t ),
								self,
								void*	null
							)
{
	assert					(	self	);

	INIT					(	ARRAY ( Vec3_t ),	self	);
}

HOWTO_DESTRUCT				(	ARRAY ( Vec2_t ), self	)
{
}

HOWTO_DESTRUCT				(	ARRAY ( Vec3_t ), self	)
{
}

HOWTO_LD					(	Vec2_t,	self,	array,	idx	)
{
	self->x					=	array->x [ idx ];
	self->y					=	array->y [ idx ];
}

HOWTO_LD					(	Vec3_t,	self,	array,	idx	)
{
	self->x					=	array->x [ idx ];
	self->y					=	array->y [ idx ];
	self->z					=	array->z [ idx ];
}

HOWTO_STR					(	Vec2_t,	self,	array,	idx		)
{
	array->x [ idx ]		=	self->x;
	array->y [ idx ]		=	self->y;
}


HOWTO_STR					(	Vec3_t,	self,	array,	idx		)
{
	array->x [ idx ]		=	self->x;
	array->y [ idx ]		=	self->y;
	array->z [ idx ]		=	self->z;
}


HOWTO_COUNT					(	ARRAY ( Vec2_t ),	self	)
{
	RETURN					(	self->count	);
}

HOWTO_COUNT					(	ARRAY ( Vec3_t ),	self	)
{
	RETURN					(	self->count	);
}


HOWTO_INC					(	ARRAY( Vec2_t ),	self,	int inc	)
{
	TMP						(	Vec2_t,
								zero,
								1
							);

	for						(	int count = 0; count < inc; count++	)
	{
		PUSH				(	Vec2_t,
								zero,
								self
							);
	}

	self->count				+=	inc;
}

HOWTO_INC					(	ARRAY( Vec3_t ),	self,	int	inc	)
{
	TMP						(	Vec3_t,
								zero,
								1
							);

	for						(	int count = 0; count < inc; count++	)
	{
		PUSH				(	Vec3_t,
								zero,
								self
							);
	}

	self->count				+=	inc;
}




//////////////////////////////////////////////////////////////////////////////////
//				Geomertic Operations Implementations
//////////////////////////////////////////////////////////////////////////////////




static
void
rotate_vector_x				(	Vec3_t* v,		float angle		)
{
	Vec3_t						*transform_v	=	NULL;

	DEF						(	Vec3_t,	transform_v		);

	// X component remains same

	transform_v->x			=	v->x;

	transform_v->y			=	v->y * cos (	angle	)
							-	v->z * sin (	angle	);

	transform_v->z			=	v->z * cos (	angle	)
							+	v->y * sin (	angle	);

	CPY						(	Vec3_t,	v,	transform_v	);

	DEL						(	Vec3_t,	transform_v	);
}

static
void
rotate_vector_y				(	Vec3_t*	v,		float angle		)
{
	Vec3_t						*transform_v	=	NULL;

	DEF						(	Vec3_t,	transform_v		);

	transform_v->x			=	v->x * cos (	angle	)
							-	v->z * sin (	angle	);

	// Y component remains same

	transform_v->y			=	v->y;

	transform_v->z			=	v->z * cos (	angle	)
							+	v->x * sin (	angle	);

	CPY						(	Vec3_t,	v,	transform_v		);

	DEL						(	Vec3_t, transform_v	);
}


static
void
rotate_vector_z				(	Vec3_t *v,	float angle	)
{
	Vec3_t						*transform_v	=	NULL;

	DEF						(	Vec3_t,	transform_v		);

	transform_v->x			=	v->x * cos (	angle	)
							-	v->y * sin (	angle	);

	transform_v->y			=	v->y * cos (	angle	)
							+	v->x * sin (	angle	);

	// Z component remains same

	transform_v->z			=	v->z;

	CPY						(	Vec3_t,	v,	transform_v		);

	DEL						(	Vec3_t,	transform_v		);
}


HOWTO_ROT					(	Vec3_t,	self,	Vec3_t* angle	)
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
void
project_orthographic		(	Vec2_t *proj,	Vec3_t *vector	)
{
	proj->x					=	fov_scale	*	vector->x;
	proj->y					=	fov_scale	*	vector->y;
}

static
void
project_isometric			(	Vec2_t *proj,	Vec3_t *vector	)
{
	// TODO: Implement self
}

static
void
project_perspective			(	Vec2_t *proj,	Vec3_t *vector	)
{
	float						z = 0;

	z						=	vector->z + camera->z;

	proj->x					=	( (	vector->x * fov_scale	) / z	);
	proj->y					=	( (	vector->y * fov_scale	) / z	);
}




HOWTO_PROJ					(	Vec2_t,				Vec3_t,
								to,					from,
								Projection_type_t	type	)
{

	switch					(	type	)
	{
		case				(	ORTHOGRAPHIC	):
			project_orthographic	(	to, from	);
			break;
		case				(	ISOMETRIC		):
			project_isometric		(	to, from	);
			break;
		case				(	PERSPECTIVE		):
			project_perspective		(	to, from	);
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

	vlen					=	sqrt (	vlen_sqr	);

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


HOWTO_INC					(	Vec2_t,	self,	Vec2_t * inc	)
{
	ADD						(	Vec2_t,
								self,
								self,
								inc
							);
}


HOWTO_INC					(	Vec3_t,	self,	Vec3_t * inc	)
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


DEFINE_TYPE					(	Vec2_t,		Type_t	);

