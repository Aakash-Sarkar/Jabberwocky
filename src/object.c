/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "object.h"



HOWTO_INIT						(	bool,
									self,
									bool	b
								)
{
	*self						=	b;
}

HOWTO_INIT						(	char,
									self,
									char	c
								)
{
	*self						=	c;
}

HOWTO_INIT						(	int,
									self,
									int		i
								)
{
	*self						=	i;
}

HOWTO_INIT						(	long,
									self,
									long	l
								)
{
	*self						=	l;
}

HOWTO_INIT						(	float,
									self,
									float	f
								)
{
	*self						=	f;
}

HOWTO_INIT						(	double,
									self,
									double	d
								)
{
	*self						=	d;
}

HOWTO_FINI						(	bool,	self	)
{
}

HOWTO_FINI						(	char,	self	)
{
}

HOWTO_FINI						(	int,	self	)
{
}

HOWTO_FINI						(	long,	self	)
{
}

HOWTO_FINI						(	float,	self	)
{
}

HOWTO_FINI						(	double,	self	)
{
}
