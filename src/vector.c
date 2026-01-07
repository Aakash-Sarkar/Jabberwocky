/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include <math.h>

#include "geometry.h"
#include "util.h"
#include "vector.h"




float						fov_scale = 680;

//Vec3_t						camera[1] = {{	.x = 0.0,
//											.y = 0.0,
//											.z = -5.0
//										}};

Vec3_t						*Camera	=	NULL;



////////////////////////////////////////////////////////////////////////////////
//		Vector Operations Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_DEF						(	Vec2_t,		self	)
{
	DEF							(	float,
									self->x
								);

	DEF							(	float,
									self->y
								);
}

HOWTO_CONSTRUCT					(	Vec2_t,
									self,
									float		x,
									float		y	)
{
	NEW							(	float,
									self->x,
									x
								);

	NEW							(	float,
									self->y,
									y
								);
}

HOWTO_DESTRUCT					(	Vec2_t,	self	)
{
	DEL							(	float,
									self->x
								);

	DEL							(	float,
									self->y
								);
}

HOWTO_DEF						(	Vec3_t,		self	)
{
	DEF							(	float,
									self->x
								);

	DEF							(	float,
									self->y
								);

	DEF							(	float,
									self->z
								);
}

HOWTO_CONSTRUCT					(	Vec3_t,
									self,
									float		x,
									float		y,
									float		z
								)
{

	NEW							(	float,
									self->x,
									x
								);

	NEW							(	float,
									self->y,
									y
								);

	NEW							(	float,
									self->z,
									z
								);
}

HOWTO_DESTRUCT					(	Vec3_t,	self	)
{

	DEL							(	float,
									self->x
								);

	DEL							(	float,
									self->y
								);

	DEL							(	float,
									self->z
								);
}

/////////////////////////////////////////////////////////////////////////////////
//		Dynamic Array Operations Implementation
/////////////////////////////////////////////////////////////////////////////////


HOWTO_DEF					(	ARRAY	(	Vec2_t	),	self	)
{

	DEF						(	ARRAY	(	float	),
								self->x
							);

	DEF						(	ARRAY	(	float	),
								self->y
							);
	self->count				=	0;
}

HOWTO_DEF					(	ARRAY	(	Vec3_t	),	self	)
{

	DEF						(	ARRAY	(	float	),
								self->x
							);

	DEF						(	ARRAY	(	float	),
								self->y
							);

	DEF						(	ARRAY	(	float	),
								self->z
							);

	self->count				=	0;
}


HOWTO_DESTRUCT				(	ARRAY	(	Vec2_t	),	self	)
{

	DEL						(	ARRAY	(	float	),
								self->x
							);

	DEL						(	ARRAY	(	float	),
								self->y
							);

	self->count				=	0;
}

HOWTO_DESTRUCT				(	ARRAY	(	Vec3_t	),	self	)
{

	DEL						(	ARRAY	(	float	),
								self->x
							);

	DEL						(	ARRAY	(	float	),
								self->y
							);

	DEL						(	ARRAY	(	float	),
								self->y
							);

	self->count				=	0;
}


HOWTO_LD					(	Vec2_t,		ptr,	arr,	idx	)
{

	LD						(	float,
								ptr->x,
								arr->x,
								idx
							);

	LD						(	float,
								ptr->y,
								arr->y,
								idx
							);
}

HOWTO_LD					(	Vec3_t,		ptr,	arr,	idx	)
{

	LD						(	float,
								ptr->x,
								arr->x,
								idx
							);

	LD						(	float,
								ptr->y,
								arr->y,
								idx
							);

	LD						(	float,
								ptr->z,
								arr->z,
								idx
							);
}

HOWTO_STR					(	Vec2_t,		ptr,	arr,	idx	)
{

	STR						(	float,
								ptr->x,
								arr->x,
								idx
							);

	STR						(	float,
								ptr->y,
								arr->y,
								idx
							);
}

HOWTO_STR					(	Vec3_t,		ptr,	arr,	idx	)
{

	STR						(	float,
								ptr->x,
								arr->x,
								idx
							);

	STR						(	float,
								ptr->y,
								arr->y,
								idx
							);

	STR						(	float,
								ptr->z,
								arr->z,
								idx
							);
}


HOWTO_PUSH					(	Vec2_t,		ptr,	arr	)
{

	PUSH					(	float,
								ptr->x,
								arr->x
							);

	PUSH					(	float,
								ptr->y,
								arr->y
							);

	arr->count++;
}

HOWTO_PUSH					(	Vec3_t,		ptr,	arr	)
{

	PUSH					(	float,
								ptr->x,
								arr->x
							);

	PUSH					(	float,
								ptr->y,
								arr->y
							);

	PUSH					(	float,
								ptr->z,
								arr->z
							);

	arr->count++;
}




HOWTO_CPY					(	Vec2_t,		to,		from	)
{
	CPY						(	float,
								to->x,
								from->x
							);

	CPY						(	float,
								to->y,
								from->y
							);
}

HOWTO_CPY					(	Vec3_t,		to,		from	)
{
	CPY						(	float,
								to->x,
								from->x
							);

	CPY						(	float,
								to->y,
								from->y
							);

	CPY						(	float,
								to->z,
								from->z
							);
}




//////////////////////////////////////////////////////////////////////////////////
//				Geomertic Operations Implementations
//////////////////////////////////////////////////////////////////////////////////


static
void
rotate_vector_x				(	Vec3_t		*self,
								float		angle
							)
{
	Vec3_t						*tmp	=	NULL;

	DEF						(	Vec3_t,
								tmp
							);

	//	X component remains same

	CPY						(	float,
								tmp->x,
								self->x
							);

	float						y	=	*self->y	*	cos(	angle	)
									-	*self->z	*	sin(	angle	);

	CPY						(	float,
								tmp->y,
								&y
							);

	float						z	=	*self->z	*	cos(	angle	)
									+	*self->y	*	sin(	angle	);

	CPY						(	float,
								tmp->z,
								&z
							);

	CPY						(	Vec3_t,
								self,
								tmp
							);

	DEL						(	Vec3_t,
								tmp
							);
}

static
void
rotate_vector_y				(	Vec3_t		*self,
								float		angle
							)
{
	Vec3_t						*tmp	=	NULL;

	DEF						(	Vec3_t,
								tmp
							);

	float						x	=	*self->x	*	cos(	angle	)
									-	*self->z	*	sin(	angle	);

	CPY						(	float,
								tmp->x,
								&x
							);

	//	Y component remains same

	CPY						(	float,
								tmp->y,
								self->y
							);

	float						z	=	*self->z	*	cos(	angle	)
									+	*self->x	*	sin(	angle	);

	CPY						(	float,
								tmp->z,
								&z
							);

	CPY						(	Vec3_t,
								self,
								tmp
							);

	DEL						(	Vec3_t,
								tmp
							);
}


static
void
rotate_vector_z				(	Vec3_t		*self,
								float		angle
							)
{
	Vec3_t						*tmp	=	NULL;

	DEF						(	Vec3_t,
								tmp
							);

	float						x	=	*self->x	*	cos(	angle	)
									-	*self->y	*	sin(	angle	);

	CPY						(	float,
								tmp->x,
								&x
							);

	float						y	=	*self->y	*	cos(	angle	)
									+	*self->x	*	sin(	angle	);

	CPY						(	float,
								tmp->y,
								&y
							);

	//	Z component remains same

	CPY						(	float,
								tmp->z,
								self->z
							);

	CPY						(	Vec3_t,
								self,
								tmp
							);

	DEL						(	Vec3_t,
								tmp
							);
}


HOWTO_ROT					(	Vec3_t,
								self,
								Vec3_t*		angle
							)
{
	assert					(	self	&&	angle	);

	if						(	*angle->x	)
	{
		rotate_vector_x		(	self,
								*angle->x
							);
	}

	if						(	*angle->y	)
	{
		rotate_vector_y		(	self,
								*angle->y
							);
	}

	if						(	*angle->z	!=	0	)
	{
		rotate_vector_z		(	self,
								*angle->z
							);
	}
}




static
void
project_orthographic		(	Vec2_t	*to,	Vec3_t	*from	)
{
	float						*x	=	NULL,
								*y	=	NULL;
	
	NEW						(	float,
								x,
								fov_scale	*	*( from->x )
							);

	CPY						(	float,
								to->x,
								x
							);
	
	NEW						(	float,
								y,
								fov_scale	*	*( from->y )
							);

	CPY						(	float,
								to->y,
								y
							);

	DEL						(	float,
								x
							);

	DEL						(	float,
								y
							);
}

static
void
project_isometric			(	Vec2_t	*to,	Vec3_t	*from	)
{
	// TODO: Implement this
}

static
void
project_perspective			(	Vec2_t	*to,	Vec3_t	*from	)
{
	Vec3_t						*cam	=	NULL;

	float						*z		=	NULL;

	NEW						(	Vec3_t,
								cam,
								0.0,	0.0,	-5.0
							);

	NEW						(	float,
								z,
								*from->z
							);

	SUB						(	float,
								z,
								from->z,
								cam->z
							);

	float						x	=	((	*( from->x ) * fov_scale	) / *z	);

	CPY						(	float,
								to->x,
								&x
							);

	float						y	=	((	*( from->y ) * fov_scale	) / *z	);

	CPY						(	float,
								to->y,
								&y
							);

	DEL						(	Vec3_t,
								cam
							);
}




HOWTO_PROJ					(	Vec2_t,				Vec3_t,
								to,					from,
								Projection_type_t	type	)
{
	assert					(	to &&	from	);

	switch					(	type	)
	{
		case				(	ORTHOGRAPHIC	):
			project_orthographic	(	to,	from	);
			break;
		case				(	ISOMETRIC		):
			project_isometric		(	to,	from	);
			break;
		case				(	PERSPECTIVE		):
			project_perspective		(	to,	from	);
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
	ADD						(	float,
								dst->x,
								op1->x,
								op2->x
							);

	ADD						(	float,
								dst->y,
								op1->y,
								op2->y
							);
}

HOWTO_ADD					(	Vec3_t,	dst,	op1,	op2	)
{

	ADD						(	float,
								dst->x,
								op1->x,
								op2->x
							);

	ADD						(	float,
								dst->y,
								op1->y,
								op2->y
							);

	ADD						(	float,
								dst->z,
								op1->z,
								op2->z
							);
}


HOWTO_SUB					(	Vec2_t,	dst,	op1,	op2	)
{

	SUB						(	float,
								dst->x,
								op1->x,
								op2->x
							);

	SUB						(	float,
								dst->y,
								op1->y,
								op2->y
							);
}

HOWTO_SUB					(	Vec3_t,	dst,	op1,	op2	)
{

	SUB						(	float,
								dst->x,
								op1->x,
								op2->x
							);

	SUB						(	float,
								dst->y,
								op1->y,
								op2->y
							);

	SUB						(	float,
								dst->z,
								op1->z,
								op2->z
							);
}


HOWTO_MUL					(	Vec2_t,	dst,	src,	factor	)
{

	MUL						(	float,
								dst->x,
								src->x,
								factor
							);

	MUL						(	float,
								dst->y,
								src->y,
								factor
							);
}

HOWTO_MUL					(	Vec3_t,	dst,	src,	factor	)
{

	MUL						(	float,
								dst->x,
								src->x,
								factor
							);

	MUL						(	float,
								dst->y,
								src->y,
								factor
							);

	MUL						(	float,
								dst->z,
								src->z,
								factor
							);
}


HOWTO_DIV					(	Vec2_t,	dst,	src,	factor	)
{

	DIV						(	float,
								dst->x,
								src->x,
								factor
							);

	DIV						(	float,
								dst->y,
								src->y,
								factor
							);
}

HOWTO_DIV					(	Vec3_t,	dst,	src,	factor	)
{

	DIV						(	float,
								dst->x,
								src->x,
								factor
							);

	DIV						(	float,
								dst->y,
								src->y,
								factor
							);

	DIV						(	float,
								dst->z,
								src->z,
								factor
							);
}




HOWTO_DOTP					(	Vec2_t,	dst,	src1,	src2	)
{
	//*dst					=	*( src1->x )	*	*( src2->x )
	//						+	*( src1->y )	*	*( src2->y );

	float						*tmp	=	NULL;

	DEF						(	float,
								tmp
							);

	MUL						(	float,
								dst,
								src1->x,
								src2->x
							);

	MUL						(	float,
								tmp,
								src1->y,
								src2->y
							);

	ADD						(	float,
								dst,
								dst,
								tmp
							);

	DEL						(	float,
								tmp
							);
}

HOWTO_DOTP					(	Vec3_t,	dst,	src1,	src2	)
{
	//*dst					=	*( src1->x )	*	*( src2->x )
	//						+	*( src1->y )	*	*( src2->y )
	//						+	*( src1->z )	*	*( src2->z );

	float						*y12	=	NULL,
								*z12	=	NULL;

	MUL						(	float,
								dst,
								src1->x,
								src2->x
							);

	MUL						(	float,
								y12,
								src1->y,
								src2->y
							);

	ADD						(	float,
								dst,
								dst,
								y12
							);

	MUL						(	float,
								z12,
								src1->z,
								src2->z
							);

	ADD						(	float,
								dst,
								dst,
								z12
							);

	DEL						(	float,
								y12
							);

	DEL						(	float,
								z12
							);
}


HOWTO_CROSP					(	Vec3_t,	dst,	src1,	src2	)
{
	*dst->x					=	*src1->y	*	*src2->z
							-	*src2->y	*	*src1->z;

	*dst->y					=	*src1->z	*	*src2->x
							-	*src1->x	*	*src2->z;

	*dst->z					=	*src1->x	*	*src2->y
							-	*src1->y	*	*src2->x;
}