/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "array.h"
#include "object.h"
#include "geometry.h"
#include "arithmetic.h"




 /////////////////////////////////////////////////////////////////////////////////
 //									VECTORS:
 /////////////////////////////////////////////////////////////////////////////////


typedef
struct				Vec2	{	float		x;
								float		y;	}	Vec2_t;

typedef	
struct				Vec3	{	float		x;
								float		y;
								float		z;	}	Vec3_t;

typedef
struct				Vec4	{	float		x;
								float		y;
								float		z;
								float		w;	}	Vec4_t;


DECL_ITER					(	Vec2_t	);

DECL_ARRAY					(	Vec2_t	);


DECL_ITER					(	Vec3_t	);

DECL_ARRAY					(	Vec3_t	);


DECL_ITER					(	Vec4_t	);

DECL_ARRAY					(	Vec4_t	);



/////////////////////////////////////////////////////////////////////////////////
//									PROJECTION:
/////////////////////////////////////////////////////////////////////////////////
//
//
//		Projection is the method by which a 3D object is represented on a 2D
//		plane. The methods of projection is used to determine how a 3D object
//		would look when viewed from a certain angle.
//
//
//										^						+ C
//										|               +		
//										|		+				
//										+ A              - - - - - - - - -
//								+		:              -:              - :
//						+		        :           -   :            -   :
//		E		+		   				: F       - - - - - - - - - -    :
//		< 0 ) - - - - - - - - - - - - - +         :     :           :    :
//		  :		+			1			:         :     :           :    :
//		  :				+	:		    :         :     :- - - - - -:- - -
//		  :					:	+       :         :    -            :   -
//		  :					:			+ B       :  -              : -
//		  :					:			|		+ - - - - - - - - - -
//		  :					:			|				+	:
//		  :					:			|					:    +
//		  v					v			v					v       D
//
//		Eye Frame		  focal		Image Plane			Virtual 3D
//		( Camera )		 length							Object
// 
// 
//		In the above diagram, assume that E is the eye of the player, and AB
//		is the length of our display. Let's also assume that between A and B
//		is sitting an array of pixels each one at an equal distance from the
//		another. Our job then is to light each of these pixels in such a way
//		that it gives the impression of a 3D cube sitting behind the monitor
//		(AB).
// 
// 
// 
/////////////////////////////////////////////////////////////////////////////////


typedef					enum	Projection_type		{	ORTHOGRAPHIC = 0,
														ISOMETRIC,
														PERSPECTIVE
													}	Projection_type_t;




////////////////////////////////////////////////////////////////////////////////
//						Vector Operations
////////////////////////////////////////////////////////////////////////////////


HOWTO_DEF							(	Vec2_t,		self	);

HOWTO_INIT							(	Vec2_t,
										self,
										float		x,
										float		y
									);

HOWTO_FINI							(	Vec2_t,		self	);

HOWTO_DEF							(	Vec3_t,		self	);

HOWTO_INIT							(	Vec3_t,
										self,
										float		x,
										float		y,
										float		z
									);

HOWTO_FINI							(	Vec3_t,		self	);


HOWTO_CPY							(	Vec2_t,		to,		from	);

HOWTO_CPY							(	Vec3_t,		to,		from	);


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic Array Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT							(	itr ( Vec2_t ),
										self,
										const Vec2_t		*ptr,
	                                    unsigned int		pos,
                                        IterType_t			typ
									);


HOWTO_INIT							(	itr ( Vec3_t ),
										self,
										const Vec3_t		*ptr,
                                        unsigned int		pos,
                                        IterType_t			typ
									);

HOWTO_DEF							(	itr ( Vec2_t ),		self	);

HOWTO_DEF							(	itr ( Vec3_t ),		self	);


HOWTO_FINI							(	itr ( Vec2_t ),		self	);

HOWTO_FINI							(	itr ( Vec3_t ),		self	);


HOWTO_CMP							(	itr ( Vec2_t ),		itr1,	itr2	);

HOWTO_CMP							(	itr ( Vec3_t ),		itr1,	itr2	);


HOWTO_INC							(	itr ( Vec2_t ),		self	);

HOWTO_INC							(	itr ( Vec3_t ),		self	);


HOWTO_DEC							(	itr ( Vec2_t ),		self	);

HOWTO_DEC							(	itr ( Vec3_t ),		self	);


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic Array Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT							(	arr ( Vec2_t ),
										self,
										const Vec2_t		*init_list,
										unsigned int		count
									);

HOWTO_INIT							(	arr ( Vec3_t ),
										self,
										const Vec3_t		*init_list,
										unsigned int		count
									);


HOWTO_DEF							(	arr ( Vec2_t ),		self	);

HOWTO_DEF							(	arr ( Vec3_t ),		self	);


HOWTO_FINI							(	arr ( Vec2_t ),		self	);

HOWTO_FINI							(	arr ( Vec3_t ),		self	);


HOWTO_CPY							(	arr ( Vec2_t ),		to,		frm	);

HOWTO_CPY							(	arr ( Vec3_t ),		to,		frm	);


/////////////////////////////////////////////////////////////////////////////////
//						Geomertic Operations
/////////////////////////////////////////////////////////////////////////////////


HOWTO_ROT							(	Vec3_t,
										self,
										Vec3_t					*angle
									);


HOWTO_PROJ							(	Vec2_t,					Vec3_t,
										to,						frm,
										Projection_type_t		typ
									);


/////////////////////////////////////////////////////////////////////////////////
//				Arithmetic Operations
/////////////////////////////////////////////////////////////////////////////////

HOWTO_ADD							(	Vec2_t,	dst,	op1,	op2		);

HOWTO_ADD							(	Vec3_t,	dst,	op1,	op2		);


HOWTO_SUB							(	Vec2_t,	dst,	op1,	op2		);

HOWTO_SUB							(	Vec3_t,	dst,	op1,	op2		);


HOWTO_MUL							(	Vec2_t,	dst,	src,	fac	);

HOWTO_MUL							(	Vec3_t,	dst,	src,	fac	);


HOWTO_DIV							(	Vec2_t,	dst,	src,	fac	);

HOWTO_DIV							(	Vec3_t,	dst,	src,	fac	);


HOWTO_DOTP							(	Vec2_t, dst,	src1,	src2	);

HOWTO_DOTP							(	Vec3_t, dst,	src1,	src2	);


HOWTO_CROSP							(	Vec3_t,	dst,	src1,	src2	);


METHOD								(	Vec2_t,
										get_max_abs_x_y,
										self,
										float					*out
									);