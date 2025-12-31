/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "object.h"




HOWTO_DEF						(	char,	self	)
{
}

HOWTO_DEF						(	int,	self	)
{
}

HOWTO_DEF						(	long,	self	)
{
}

HOWTO_DEF						(	float,	self	)
{
}

HOWTO_DEF						(	double,	self	)
{
}


HOWTO_CONSTRUCT					(	char,
									self,
									char	c
								)
{
	*self						=	c;
}

HOWTO_CONSTRUCT					(	int,
									self,
									int		i
								)
{
	*self						=	i;
}

HOWTO_CONSTRUCT					(	long,
									self,
									long	l
								)
{
	*self						=	l;
}

HOWTO_CONSTRUCT					(	float,
									self,
									float	f
								)
{
	*self						=	f;
}

HOWTO_CONSTRUCT					(	double,
									self,
									double	d
								)
{
	*self						=	d;
}

HOWTO_DESTRUCT					(	char,	self	)
{
}

HOWTO_DESTRUCT					(	int,	self	)
{
}

HOWTO_DESTRUCT					(	long,	self	)
{
}

HOWTO_DESTRUCT					(	float,	self	)
{
}

HOWTO_DESTRUCT					(	double,	self	)
{
}


HOWTO_CPY						(	char,	to,	from	)
{
	*to							=	*from;
}

HOWTO_CPY						(	int,	to,	from	)
{
	*to							=	*from;
}

HOWTO_CPY						(	long,	to,	from	)
{
	*to							=	*from;
}

HOWTO_CPY						(	float,	to,	from	)
{
	*to							=	*from;
}

HOWTO_CPY						(	double,	to,	from	)
{
	*to							=	*from;
}
