/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "point.h"
#include "rect.h"



 /////////////////////////////////////////////////////////////////////////////////
 //						Memory Ops Implementation
 //////////////////////////////////////////////////////////////////////////////////


HOWTO_DEF						(	Point2d_t,		self	)
{
	NEW							(	Point2d_t,
									self,
									0.0f,
									0.0f
								);

	RET							(	self	);
}

HOWTO_INIT						(	Point2d_t,
									self,
									float			x,
									float			y
								)
{
	NEW							(	Vec2_t,
									( self )->v,
									x,
									y
								);
}

HOWTO_FINI						(	Point2d_t,		self	)
{
	DEL							(	Vec2_t,	
									( self )->v
								);
}

HOWTO_DEF						(	Point3d_t,		self	)
{

	NEW							(	Point3d_t,
									self ,
									0.0f,
									0.0f,
									0.0f
								);

	RET							(	self	);
}

HOWTO_INIT						(	Point3d_t,
									self,
									float			x,
									float			y,
									float			z
								)
{

	NEW							(	Vec3_t,
									( self )->v,
									x,	y,	z
								);
}


HOWTO_FINI						(	Point3d_t,		self	)
{

	DEL							(	Vec3_t,
									( self )->v
								);
}


HOWTO_CPY						(	Point2d_t,	to,		frm	)
{

	MCPY						(	Vec2_t,
									( to )->v,
									( frm )->v
								);
}

HOWTO_CPY						(	Point3d_t,	to,		frm	)
{

	MCPY						(	Vec3_t,
									( to )->v,
									( frm )->v
								);
}


/////////////////////////////////////////////////////////////////////////////////
//						Iterator Ops Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT						(	itr ( Point2d_t ),
									self,
									const Point2d_t			*ptr,
									unsigned int			pos,
									IterType_t				typ
								)
{

	INITITR						(	Point2d_t,
									self,
									ptr,
									pos,
									typ
								);
}

HOWTO_INIT						(	itr ( Point3d_t ),
									self,
									const Point3d_t			*ptr,
									unsigned int			pos,
									IterType_t				typ
								)
{
	INITITR						(	Point3d_t,
									self,
									ptr,
									pos,
									typ
								);
}

HOWTO_DEF						(	itr ( Point2d_t ),		self	)
{
	NEW							(	itr ( Point2d_t ),
									self,
									NULL,
									0,
									MAX_ITER
								);

	RET							(	self	);
}


HOWTO_DEF						(	itr ( Point3d_t ),		self	)
{

	NEW							(	itr ( Point3d_t ),
									self,
									NULL,
									0,
									MAX_ITER
								);

	RET							(	self	);
}


HOWTO_FINI						(	itr ( Point2d_t ),		self	)
{
	FINIITR						(	Point2d_t,
									self
								);
}

HOWTO_FINI						(	itr ( Point3d_t ),		self	)
{
	FINIITR						(	Point3d_t,
									self
								);
}


HOWTO_CMP						(	itr ( Point2d_t ),		it1,	it2	)
{
	CMPITR						(	Point2d_t,
									it1,
									it2
								);
}

HOWTO_CMP						(	itr ( Point3d_t ),		it1,	it2	)
{
	CMPITR						(	Point3d_t,
									it1,
									it2
								);
}


HOWTO_INC						(	itr ( Point2d_t ),		self	)
{
	INCITR						(	Point2d_t,
									self
								);
}

HOWTO_INC						(	itr ( Point3d_t ),		self	)
{
	INCITR						(	Point3d_t,
									self
								);
}


HOWTO_DEC						(	itr ( Point2d_t ),		self	)
{
	DECITR						(	Point2d_t,
									( self )
								);
}

HOWTO_DEC						(	itr ( Point3d_t ),		self	)
{
	DECITR						(	Point3d_t,
									( self )
								);
}


/////////////////////////////////////////////////////////////////////////////////
//						Dynamic array Operations Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_INIT						(	arr ( Point2d_t ),
									self,
									const Point2d_t			*init_list,
									unsigned int			count
								)
{
	INITARR						(	Point2d_t,
									self,
									init_list,
									count
								);
}

HOWTO_INIT						(	arr ( Point3d_t ),
									self,
									const Point3d_t			*init_list,
									unsigned int			count
								)
{
	INITARR						(	Point3d_t,
									self,
									init_list,
									count
								);
}


HOWTO_DEF						(	arr ( Point2d_t ),		self	)
{

	NEW							(	arr ( Point2d_t ),
									self,
									NULL,
									0
								);

	RET							(	self	);

}

HOWTO_DEF						(	arr ( Point3d_t ),		self	)
{

	NEW							(	arr ( Point3d_t ),
									self,
									NULL,
									0
								);

	RET							(	self	);
}


HOWTO_FINI						(	arr ( Point2d_t ),		self	)
{

	FINIARR						(	Point2d_t,
									self
								);
}

HOWTO_FINI						(	arr ( Point3d_t ),		self	)
{

	FINIARR						(	Point3d_t,
									self
								);
}

HOWTO_CPY						(	arr ( Point2d_t ),	to,	from	)
{

	CPYARR						(	Point2d_t,
									to,
									from
								);
}

HOWTO_CPY						(	arr ( Point3d_t ),	to,	from	)
{

	CPYARR						(	Point3d_t,
									to,
									from
								);
}


/////////////////////////////////////////////////////////////////////////////////
//						Geometric Operations Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_ROT						(	Point2d_t,
									self,
									Vec2_t				*angle
								)
{
}

HOWTO_ROT						(	Point3d_t,
									self,
									Vec3_t				*angle
								)
{

	ROT							(	Vec3_t,	
									( self )->v,
									( angle )
								);
}




HOWTO_DRAW						(	Point2d_t,
									self,
									Point2d_t			*origin,
									Color_t				*clr,
									Color_buffer_t		*clrbuf
								)
{

	Rect_t							*rect		=		NULL;
	Point2d_t						*o_point	=		NULL;

	DEF							(	Point2d_t,
									o_point
								);

	//	By default all our points will be in the range (-1 * fov_scale) up to
	//	(+1 * fov_scale). This shifts the points to the center of the screen.

	ADD							(	Point2d_t,
									o_point,
									self,
									origin
								);


	int								posX	=	round( ( o_point )->v->x ),
									posY	=	round( ( o_point )->v->y );


	NEW							(	Rect_t,
									rect,
									posX,
									posY,
									2,	2
								);

	DRAW						(	Rect_t,
									rect,
									clr,
									clrbuf
								);

	DEL							(	Rect_t,
									rect
								);

	DEL							(	Point2d_t,
									o_point
								);
}



HOWTO_DRAW					(	Point3d_t,
								self,
								Point2d_t			*orig,
								Color_t				*clr,
								Color_buffer_t		*clrbuf
							)
{

	Point2d_t					*prj	=	NULL;

	DEF						(	Point2d_t,
								prj
							);

	PROJ					(	Point2d_t,			Point3d_t,
								prj,				self,
								PERSPECTIVE
							);

	DRAW					(	Point2d_t,
								prj,
								orig,
								clr,
								clrbuf
							);

	DEL						(	Point2d_t,
								prj
							);
}




HOWTO_PROJ					(	Point2d_t,			Point3d_t,
								to,					frm,
								Projection_type_t	typ
							)
{

	PROJ					(	Vec2_t,				Vec3_t,
								( to  )->v,			( frm )->v,
								( typ )
							);
}


//////////////////////////////////////////////////////////////////////////////////
//						Arithmetic Operations Implementation
//////////////////////////////////////////////////////////////////////////////////


HOWTO_CMP					(	Point2d_t,	p1,	p2	)
{
	assert					(	p1	);
	assert					(	p2	);

	bool						res		=	false;

	res						=	CMP		(	Vec2_t,
											( p1 )->v,
											( p2 )->v
										);

	RET						(	res	);
}

HOWTO_CMP					(	Point3d_t,	p1,	p2	)
{
	assert					(	p1	);
	assert					(	p2	);

	bool						res		=	false;

	res						=	CMP		(	Vec3_t,
											( p1 )->v,
											( p2 )->v
										);

	RET						(	res	);
}


HOWTO_ADD					(	Point2d_t,	dst,	op1,	op2	)
{

	ADD						(	Vec2_t,
								( dst )->v,
								( op1 )->v,
								( op2 )->v
							);
}

HOWTO_ADD					(	Point3d_t,	dst,	op1,	op2	)
{

	ADD						(	Vec3_t,
								( dst )->v,
								( op1 )->v,
								( op2 )->v
							);
}


HOWTO_SUB					(	Point2d_t,	dst,	op1,	op2	)
{

	SUB						(	Vec2_t,
								( dst )->v,
								( op1 )->v,	
								( op2 )->v
							);
}

HOWTO_SUB					(	Point3d_t,	dst,	op1,	op2	)
{

	SUB						(	Vec3_t,
								( dst )->v,
								( op1 )->v,
								( op2 )->v
							);
}


HOWTO_MUL					(	Point2d_t,	dst,	src,	fac	)
{

	MUL						(	Vec2_t,
								( dst )->v,
								( src )->v,
								( fac )
							);

}

HOWTO_MUL					(	Point3d_t,	dst,	src,	fac	)
{

	MUL						(	Vec3_t,
								( dst )->v,
								( src )->v,
								( fac )
							);
}


HOWTO_DIV					(	Point2d_t,	dst,	src,	fac	)
{

	DIV						(	Vec2_t,
								( dst )->v,
								( src )->v,
								( fac )
							);

}

HOWTO_DIV					(	Point3d_t,	dst,	src,	fac	)
{

	DIV						(	Vec3_t,
								( dst )->v,
								( src )->v,
								( fac )
							);
}


HOWTO_DOTP					(	Point2d_t,	dst,	src1,	src2	)
{

	DOTP					(	Vec2_t,
								( dst ),
								( src1 )->v,
								( src2 )->v
							);
}

HOWTO_DOTP					(	Point3d_t,	dst,	src1,	src2	)
{

	DOTP					(	Vec3_t,
								( dst ),
								( src1 )->v,
								( src2 )->v
							);
}


HOWTO_CROSP					(	Point3d_t,	dst,	src1,	src2	)
{
	CROSP					(	Vec3_t,
								( dst )->v,
								( src1 )->v,
								( src2 )->v
							);
}
