/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "object.h"




HOWTO_DEF						(	char,	self	)
{
	RET							(	self	);
}

HOWTO_DEF						(	int,	self	)
{
	RET							(	self	);
}

HOWTO_DEF						(	long,	self	)
{
	RET							(	self	);
}

HOWTO_DEF						(	float,	self	)
{
	RET							(	self	);
}

HOWTO_DEF						(	double,	self	)
{
	RET							(	self	);
}


HOWTO_CONSTRUCT					(	char,
									self,
									char	c
								)
{
	*self						=	c;
	RET							(	self	);
}

HOWTO_CONSTRUCT					(	int,
									self,
									int		i
								)
{
	*self						=	i;
	RET							(	self	);
}

HOWTO_CONSTRUCT					(	long,
									self,
									long	l
								)
{
	*self						=	l;
	RET							(	self	);
}

HOWTO_CONSTRUCT					(	float,
									self,
									float	f
								)
{
	*self						=	f;
	RET							(	self	);
}

HOWTO_CONSTRUCT					(	double,
									self,
									double	d
								)
{
	*self						=	d;
	RET							(	self	);
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
