/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include <math.h>

#include "vector.h"




float						fov_scale = 680;

//Vec3_t						camera[1] = {{	.x = 0.0,
//											.y = 0.0,
//											.z = -5.0
//										}};

Vec3_t						*Camera	=	NULL;



////////////////////////////////////////////////////////////////////////////////
//						Memory Ops Implementation
////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT					(	Vec2_t,
								self,
								float			x,
								float			y
							)
{
	( self )->x				=	x;
	( self )->y				=	y;
}


HOWTO_DEF					(	Vec2_t,			self	)
{
	NEW						(	Vec2_t,
								self,
								0.0f,
								0.0f
							);

	RET						(	self	);
}


HOWTO_FINI					(	Vec2_t,			self	)
{
}


HOWTO_INIT					(	Vec3_t,
								self,
								float			x,
								float			y,
								float			z
							)
{
	( self )->x				=	x;
	( self )->y				=	y;
	( self )->z				=	z;
}


HOWTO_DEF					(	Vec3_t,			self	)
{
	NEW						(	Vec3_t,
								self,
								0.0f,
								0.0f,
								0.0f
							);

	RET						(	self	);
}

HOWTO_FINI					(	Vec3_t,				self	)
{
}

HOWTO_CPY					(	Vec2_t,		to,		from	)
{
	( to )->x				=	( from )->x;
	( to )->y				=	( from )->y;
}


HOWTO_CPY					(	Vec3_t,		to,		from	)
{
	( to )->x				=	( from )->x;
	( to )->y				=	( from )->y;
	( to )->z				=	( from )->z;
}

/////////////////////////////////////////////////////////////////////////////////
//					Iterator Ops Implementation
/////////////////////////////////////////////////////////////////////////////////



HOWTO_INIT					(	itr ( Vec2_t ),
								self,
								const Vec2_t		*ptr,
								unsigned int		pos,
								IterType_t			typ
							)
{
	INITITR					(	Vec2_t,
								self,
								ptr,
								pos,
								typ 
							);
}


HOWTO_INIT					(	itr ( Vec3_t ),
								self,
								const Vec3_t		*ptr,
								unsigned int		pos,
								IterType_t			typ
							)
{
	INITITR					(	Vec3_t,
								self,
								ptr,
								pos,
								typ
							);
}


HOWTO_DEF					(	itr ( Vec2_t ),		self	)
{
	NEW						(	itr ( Vec2_t ),
								self,
								NULL,
								0,
								MAX_ITER
							);

	RET						(	self	);
}


HOWTO_DEF					(	itr ( Vec3_t ),		self	)
{
	NEW						(	itr ( Vec3_t ),
								self,
								NULL,
								0,
								MAX_ITER
							);

	RET						(	self	);
}


HOWTO_FINI					(	itr ( Vec2_t ),		self	)
{
	FINIITR					(	Vec2_t,
								self
							);
}

HOWTO_FINI					(	itr ( Vec3_t ),		self	)
{
	FINIITR					(	Vec3_t,
								self
							);
}

HOWTO_CMP					(	itr ( Vec2_t ),		itr1,	itr2	)
{
	CMPITR					(	Vec2_t,
								itr1,
								itr2
							);
}

HOWTO_CMP					(	itr ( Vec3_t ),		itr1,	itr2	)
{
	CMPITR					(	Vec3_t,
								itr1,
								itr2
							);
}


HOWTO_INC					(	itr ( Vec2_t ),		self	)
{
	INCITR					(	Vec2_t,
								self
							);
}

HOWTO_INC					(	itr ( Vec3_t ),		self	)
{
	INCITR					(	Vec2_t,
								self
							);
}


HOWTO_DEC					(	itr ( Vec2_t ),		self	)
{
	DECITR					(	Vec2_t,
								self
							);
}

HOWTO_DEC					(	itr ( Vec3_t ),		self	)
{
	DECITR					(	Vec3_t,
								self
							);
}


/////////////////////////////////////////////////////////////////////////////////
//					Dynamic Array Ops Implementation
/////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT					(	arr ( Vec2_t ),
								self,
								const Vec2_t		*init_list,
								unsigned int		count
							)
{
	INITARR					(	Vec2_t,
								self,
								init_list,
								count
							);
}

HOWTO_INIT					(	arr ( Vec3_t ),
								self,
								const Vec3_t		*init_list,
								unsigned int		count
							)
{
	INITARR					(	Vec3_t,
								self,
								init_list,
								count
							);
}


HOWTO_DEF					(	arr ( Vec2_t ),		self	)
{
	NEW						(	arr ( Vec2_t ),
								self,
								NULL,
								0
							);

	RET						(	self	);
}

HOWTO_DEF					(	arr ( Vec3_t ),		self	)
{
	NEW						(	arr ( Vec3_t ),
								self,
								NULL,
								0
							);

	RET						(	self	);
}


HOWTO_FINI					(	arr ( Vec2_t ),		self	)
{
	FINIARR					(	Vec2_t,
								self
							);
}

HOWTO_FINI					(	arr ( Vec3_t ),		self	)
{
	FINIARR					(	Vec3_t,
								self
							);
}


HOWTO_CPY					(	arr ( Vec2_t ),		to,		frm	)
{
	CPYARR					(	Vec2_t,
								to,
								frm
							);
}

HOWTO_CPY					(	arr ( Vec3_t ),		to,		frm	)
{
	CPYARR					(	Vec3_t,
								to,
								frm
							);
}


//////////////////////////////////////////////////////////////////////////////////
//						Geomertic Ops Implementations
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

	( tmp )->x				=	( self )->x;


	( tmp )->y				=	( self )->y		*	cos ( angle )
							-	( self )->z		*	sin ( angle );


	( tmp )->z				=	( self )->z		*	cos ( angle )
							+	( self )->y		*	sin ( angle );


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
rotate_vector_y				(	Vec3_t		*v,
								float		angle
							)
{
	Vec3_t						*tmp	=	NULL;

	DEF						(	Vec3_t,
								tmp
							);

	( tmp )->x				=	( v )->x	*	cos ( angle )
							-	( v )->z	*	sin ( angle );


	//	Y component remains same

	( tmp )->y				=	( v )->y;


	( tmp )->z				=	( v )->z	*	cos ( angle )
							+	( v )->x	*	sin ( angle );

	CPY						(	Vec3_t,
								v,
								tmp
							);

	DEL						(	Vec3_t,
								tmp
							);
}


static
void
rotate_vector_z				(	Vec3_t		*v,
								float		angle
							)
{
	Vec3_t						*tmp	=	NULL;

	DEF						(	Vec3_t,
								tmp
							);


	( tmp )->x				=	( v )->x	*	cos ( angle )
							-	( v )->y	*	sin ( angle );


	( tmp )->y				=	( v )->y	*	cos ( angle )
							+	( v )->x	*	sin ( angle );

	//	Z component remains same

	( tmp )->z				=	( v )->z;


	CPY						(	Vec3_t,
								v,
								tmp
							);

	DEL						(	Vec3_t,
								tmp
							);
}


HOWTO_ROT					(	Vec3_t,
								self,
								Vec3_t				*angle
							)
{
	assert					(	self	);
	assert					(	angle	);

	if						(	( angle )->x	)
	{
		rotate_vector_x		(	( self ),	( angle )->x	);
	}

	if						(	( angle )->y	)
	{
		rotate_vector_y		(	( self ),	( angle )->y	);
	}

	if						(	( angle )->z	)
	{
		rotate_vector_z		(	( self ),	( angle )->z	);
	}
}




static
void
project_orth				(	Vec2_t	*to,	Vec3_t	*from	)
{
	( to )->x				=	( from )->x
							*	( fov_scale );

	( to )->y				=	( from )->y
							*	( fov_scale );
}

static
void
project_iso					(	Vec2_t	*to,	Vec3_t	*from	)
{
	// TODO: Implement this
}

static
void
project_pers				(	Vec2_t *to,		Vec3_t *frm	)
{
	Vec3_t						*cam	=		NULL;

	float						z		=		0.0f;

	NEW						(	Vec3_t,
								cam,
								0.0,
								0.0,
								-5.0
							);

	z						=	( frm )->z
							-	( cam )->z;

	( to )->x				=	( frm )->x
							*	( fov_scale )
							/	( z );

	( to )->y				=	( frm )->y
							*	( fov_scale )
							/	( z );

	DEL						(	Vec3_t,
								cam
							);

}




HOWTO_PROJ					(	Vec2_t,					Vec3_t,
								to,						frm,
								Projection_type_t		typ
							)
{
	assert					(	to	);
	assert					(	frm	);

	switch					(	typ	)
	{
		case				(	ORTHOGRAPHIC	):
			project_orth	(	to,
								frm
							);
			break;
		case				(	ISOMETRIC		):
			project_iso		(	to,
								frm
							);
			break;
		case				(	PERSPECTIVE		):
			project_pers	(	to,
								frm
							);
			break;
		default:
			LOG				(	"Unsupported projection type: %d\n",
								typ
							);
			break;
	}
}




//////////////////////////////////////////////////////////////////////////////////
//				Arithmetic Operations Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_CMP					(	Vec2_t,	v1,	v2	)
{
	assert					(	v1	);
	assert					(	v2	);

	bool						res		=	false;

	res						=	(	( v1 )->x == ( v2 )->x	)
							&&	(	( v1 )->y == ( v2 )->y	);

	RET						(	res	);
}

HOWTO_CMP					(	Vec3_t,	v1,	v2	)
{
	assert					(	v1	);
	assert					(	v2	);

	bool						res		=	false;

	res						=	(	( v1 )->x == ( v2 )->x	)
							&&	(	( v1 )->y == ( v2 )->y	)
							&&	(	( v1 )->z == ( v2 )->z	);

	RET						(	res	);
}

HOWTO_ADD					(	Vec2_t,	dst,	op1,	op2	)
{
	( dst )->x				=	( op1 )->x
							+	( op2 )->x;

	( dst )->y				=	( op1 )->y
							+	( op2 )->y;
}


HOWTO_ADD					(	Vec3_t,	dst,	op1,	op2	)
{
	( dst )->x				=	( op1 )->x
							+	( op2 )->x;

	( dst )->y				=	( op1 )->y
							+	( op2 )->y;

	( dst )->z				=	( op1 )->z
							+	( op2 )->z;
}


HOWTO_SUB					(	Vec2_t,	dst,	op1,	op2	)
{
	( dst )->x				=	( op1 )->x
							-	( op2 )->x;

	( dst )->y				=	( op1 )->y
							-	( op2 )->y;
}


HOWTO_SUB					(	Vec3_t,	dst,	op1,	op2	)
{
	( dst )->x				=	( op1 )->x
							-	( op2 )->x;

	( dst )->y				=	( op1 )->y
							-	( op2 )->y;

	( dst )->z				=	( op1 )->z
							-	( op2 )->z;
}


HOWTO_MUL					(	Vec2_t,	dst,	src,	fac	)
{
	( dst )->x				=	( src )->x
							*	( fac );

	( dst )->y				=	( src )->y
							*	( fac );
}


HOWTO_MUL					(	Vec3_t,	dst,	src,	fac	)
{
	( dst )->x				=	( src )->x
							*	( fac );

	( dst )->y				=	( src )->y
							*	( fac );

	( dst )->z				=	( src )->z
							*	( fac );
}


HOWTO_DIV					(	Vec2_t,	dst,	src,	fac	)
{
	( dst )->x				=	( src )->x
							/	( fac );

	( dst )->y				=	( src )->y
							/	( fac );
}


HOWTO_DIV					(	Vec3_t,	dst,	src,	fac	)
{
	( dst )->x				=	( src )->x
							/	( fac );

	( dst )->y				=	( src )->y
							/	( fac );

	( dst )->z				=	( src )->z
							/	( fac );
}


HOWTO_DOTP					(	Vec2_t,	dst,	src1,	src2	)
{
	*( dst )				=	( src1 )->x		*	( src2 )->x
							+	( src1 )->y		*	( src2 )->y;
}


HOWTO_DOTP					(	Vec3_t,	dst,	src1,	src2	)
{
	*( dst )				=	( src1 )->x		*	( src2 )->x
							+	( src1 )->y		*	( src2 )->y
							+	( src1 )->z		*	( src2 )->z;
}


HOWTO_CROSP					(	Vec3_t,	dst,	src1,	src2	)
{
	( dst )->x				=	( src1 )->y		*	( src2 )->z
							-	( src2 )->y		*	( src1 )->z;


	( dst )->y				=	( src1 )->z		*	( src2 )->x
							-	( src1 )->x		*	( src2 )->z;


	( dst )->z				=	( src1 )->x		*	( src2 )->y
							-	( src1 )->y		*	( src2 )->x;
}


