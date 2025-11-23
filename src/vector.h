/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "array.h"
#include "object.h"
#include "geometry.h"
#include "arithmetic.h"




/////////////////////////////////////////////////////////////////////////////////
//								VECTORS:
/////////////////////////////////////////////////////////////////////////////////




typedef					struct	Vec2					Vec2_t;

typedef					struct	Vec3					Vec3_t;

typedef					struct	Vec4					vec4_t;


typedef					DECL_ARRAY ( Vec2_t )			ARRAY ( Vec2_t );

typedef					DECL_ARRAY ( Vec3_t )			ARRAY ( Vec3_t );


extern Vec3_t			camera [ ];


/////////////////////////////////////////////////////////////////////////////////
//								PROJECTION:
/////////////////////////////////////////////////////////////////////////////////
//
//		Projection is the method by which a 3D object is represented on a 2D
//		plane. The methods of projection is used to determine how a 3D object
//		will look when viewed from a certain angle.
//
/////////////////////////////////////////////////////////////////////////////////


typedef					enum	Projection_type	{	ORTHOGRAPHIC = 0,
													ISOMETRIC,
													PERSPECTIVE		}	Projection_type_t;




////////////////////////////////////////////////////////////////////////////////
//								Vector Operations
////////////////////////////////////////////////////////////////////////////////


HOWTO_CPY							(	Vec2_t,		to,	from	);

HOWTO_CPY							(	Vec3_t,		to,	from	);


HOWTO_CONSTRUCT						(	Vec2_t,
										self,
										float x,
										float y
									);

HOWTO_CONSTRUCT						(	Vec3_t,
										self,
										float x,
										float y,
										float z
									);


HOWTO_DESTRUCT						(	Vec2_t,	this	);

HOWTO_DESTRUCT						(	Vec3_t,	this	);

/////////////////////////////////////////////////////////////////////////////////
//							Dynamic Array Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ARRAY_INIT					(	ARRAY ( Vec2_t ),	self	);

HOWTO_ARRAY_INIT					(	ARRAY ( Vec3_t ),	self	);


HOWTO_ARRAY_RESET					(	ARRAY ( Vec2_t ),	self	);

HOWTO_ARRAY_RESET					(	ARRAY ( Vec3_t ),	self	);


HOWTO_CONSTRUCT						(	ARRAY ( Vec2_t ),
										self,
										void*	null
									);

HOWTO_CONSTRUCT						(	ARRAY ( Vec3_t ),
										self,
										void*	null
									);

HOWTO_DESTRUCT						(	ARRAY ( Vec2_t ),
										self
									);

HOWTO_DESTRUCT						(	ARRAY ( Vec3_t ),
										self
									);


HOWTO_LD							(	Vec2_t,		self,	array,	idx	);

HOWTO_LD							(	Vec3_t,		self,	array,	idx	);


HOWTO_STR							(	Vec2_t,		self,	array,	idx	);

HOWTO_STR							(	Vec3_t,		self,	array,	idx	);


HOWTO_COUNT							(	ARRAY ( Vec2_t ),	self	);

HOWTO_COUNT							(	ARRAY ( Vec3_t ),	self	);


HOWTO_INC							(	ARRAY ( Vec2_t ),	self,	int inc	);

HOWTO_INC							(	ARRAY ( Vec3_t ),	self,	int	inc	);




/////////////////////////////////////////////////////////////////////////////////
//							Geomertic Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ROT							(	Vec3_t,	
										self,
										Vec3_t*		angle
									);

HOWTO_PROJ							(	Vec2_t,					Vec3_t,
										to,						from,
										Projection_type_t		type
									);


/////////////////////////////////////////////////////////////////////////////////
//							Arithmetic Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ADD							(	Vec2_t,	dst,	op1,	op2	);

HOWTO_ADD							(	Vec3_t,	dst,	op1,	op2	);


HOWTO_SUB							(	Vec2_t,	dst,	op1,	op2	);

HOWTO_SUB							(	Vec3_t,	dst,	op1,	op2	);


HOWTO_MUL							(	Vec2_t,	dst,	src,	factor	);

HOWTO_MUL							(	Vec3_t,	dst,	src,	factor	);


HOWTO_DIV							(	Vec2_t,	dst,	src,	factor	);

HOWTO_DIV							(	Vec3_t,	dst,	src,	factor	);


HOWTO_NORM							(	Vec2_t,	self	);

HOWTO_NORM							(	Vec3_t,	self	);


HOWTO_INC							(	Vec2_t,	self,	Vec2_t * inc	);

HOWTO_INC							(	Vec3_t,	self,	Vec3_t * inc	);



HOWTO_DOTP							(	Vec2_t, dst,	src1,	src2	);

HOWTO_DOTP							(	Vec3_t, dst,	src1,	src2	);


HOWTO_CROSSP						(	Vec3_t,	dst,	src1,	src2	);

