/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "memory.h"



HOWTO_DEF						(	bool,		self	)
{

	NEW							(	bool,
									self,
									false
								);

	RET							(	self	);
}

HOWTO_DEF						(	char,		self	)
{

	NEW							(	char,
									self,
									'\0'
								);

	RET							(	self	);
}

HOWTO_DEF						(	int,		self	)
{

	NEW							(	int,
									self,
									0
								);

	RET							(	self	);
}

HOWTO_DEF						(	long,		self	)
{

	NEW							(	long,
									self,
									0
								);

	RET							(	self	);
}

HOWTO_DEF						(	float,		self	)
{

	NEW							(	float,
									self,
									0.0f
								);

	RET							(	self	);
}

HOWTO_DEF						(	double,		self	)
{

	NEW							(	double,
									self,
									0.0
								);

	RET							(	self	);
}


HOWTO_CPY						(	bool,	to,	frm	)
{
	CP							(	bool,
									to,
									frm
								);
}

HOWTO_CPY						(	char,	to,	frm	)
{
	CP							(	char,
									to,
									frm
								);
}

HOWTO_CPY						(	int,	to,	frm	)
{
	CP							(	int,
									to,
									frm
								);
}

HOWTO_CPY						(	long,	to,	frm	)
{
	CP							(	long,
									to,
									frm
								);
}

HOWTO_CPY						(	float,	to,	frm	)
{
	CP							(	float,
									to,
									frm
								);
}

HOWTO_CPY						(	double,	to,	frm	)
{
	CP							(	double,
									to,
									frm
								);
}