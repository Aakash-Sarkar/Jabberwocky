/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "arithmetic.h"




HOWTO_ADD		(	char,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				+	*( op2 );
}

HOWTO_ADD		(	int,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				+	*( op2 );
}

HOWTO_ADD		(	long,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				+	*( op2 );
}

HOWTO_ADD		(	float,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				+	*( op2 );
}

HOWTO_ADD		(	double,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				+	*( op2 );
}


HOWTO_SUB		(	char,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				-	*( op2 );
}

HOWTO_SUB		(	int,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				-	*( op2 );
}

HOWTO_SUB		(	long,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				-	*( op2 );
}

HOWTO_SUB		(	float,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				-	*( op2 );
}

HOWTO_SUB		(	double,	dst,	op1,	op2	)
{
	*( dst )	=	*( op1 )
				-	*( op2 );
}


HOWTO_MUL		(	char,	dst,	src,	fac	)
{
	*( dst )	=	*( src )
				*	 ( fac );
}

HOWTO_MUL		(	int,	dst,	src,	fac	)
{
	*( dst )	=	*( src )
				*	 ( fac );
}

HOWTO_MUL		(	long,	dst,	src,	fac	)
{
	*( dst )	=	*( src )
				*	 ( fac );
}

HOWTO_MUL		(	float,	dst,	src,	fac	)
{
	*( dst )	=	*( src )
				*	 ( fac );
}

HOWTO_MUL		(	double,	dst,	src,	fac	)
{
	*( dst )	=	*( src )
				*	 ( fac );
}




HOWTO_DIV		(	char,	dst,	src,	fac	)
{
	*( dst )	=	( char )	*( src )
				/	( fac );
}

HOWTO_DIV		(	int,	dst,	src,	fac	)
{
	*( dst )	=	( int )	*( src )
				/	( fac );
}

HOWTO_DIV		(	long,	dst,	src,	fac	)
{
	*( dst )	=	( long )	*( src )
				/	( fac );
}

HOWTO_DIV		(	float,	dst,	src,	fac	)
{
	*( dst )	=	( float )	*( src )
				/	( fac );
}

HOWTO_DIV		(	double,	dst,	src,	fac	)
{
	*( dst )	=	( double )	*( src )
				/	( fac );
}



