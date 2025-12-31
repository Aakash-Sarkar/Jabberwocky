/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "arithmetic.h"




HOWTO_ADD										(	char,	dest,	op1,	op2	)
{
	*dest										=	*op1	+	*op2;
}

HOWTO_ADD										(	int,	dest,	op1,	op2	)
{
	*dest										=	*op1	+	*op2;
}

HOWTO_ADD										(	long,	dest,	op1,	op2	)
{
	*dest										=	*op1	+	*op2;
}

HOWTO_ADD										(	float,	dest,	op1,	op2	)
{
	*dest										=	*op1	+	*op2;
}

HOWTO_ADD										(	double,	dest,	op1,	op2	)
{
	*dest										=	*op1	+	*op2;
}


HOWTO_SUB										(	char,	dest,	op1,	op2	)
{
	*dest										=	*op1	-	*op2;
}

HOWTO_SUB										(	int,	dest,	op1,	op2	)
{
	*dest										=	*op1	-	*op2;
}

HOWTO_SUB										(	long,	dest,	op1,	op2	)
{
	*dest										=	*op1	-	*op2;
}

HOWTO_SUB										(	float,	dest,	op1,	op2	)
{
	*dest										=	*op1	-	*op2;
}

HOWTO_SUB										(	double,	dest,	op1,	op2	)
{
	*dest										=	*op1	-	*op2;
}


HOWTO_MUL										(	char,	dest,	src,	factor	)
{
	*dest										=	*src	*	*factor;
}

HOWTO_MUL										(	int,	dest,	src,	factor	)
{
	*dest										=	*src	*	*factor;
}

HOWTO_MUL										(	long,	dest,	src,	factor	)
{
	*dest										=	*src	*	*factor;
}

HOWTO_MUL										(	float,	dest,	src,	factor	)
{
	*dest										=	*src	*	*factor;
}

HOWTO_MUL										(	double,	dest,	src,	factor	)
{
	*dest										=	*src	*	*factor;
}




HOWTO_DIV										(	char,	dest,	src,	factor	)
{
	*dest										=	( char )	*src	/	*factor;
}

HOWTO_DIV										(	int,	dest,	src,	factor	)
{
	*dest										=	( int )		*src	/	*factor;
}

HOWTO_DIV										(	long,	dest,	src,	factor	)
{
	*dest										=	( long )	*src	/	*factor;
}

HOWTO_DIV										(	float,	dest,	src,	factor	)
{
	*dest										=	( float )	*src	/	*factor;
}

HOWTO_DIV										(	double,	dest,	src,	factor	)
{
	*dest										=	( double )	*src	/	*factor;
}



