/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "array.h"
#include "memory.h"



HOWTO_INIT					(	arr ( bool ),
								self,
								const bool			*init_list,
								unsigned int		count
							)
{
	INITARR					(	bool,
								self,
								init_list,
								count
							);

}

HOWTO_INIT					(	arr ( char ),
								self,
								const char			*init_list,
								unsigned int		count
							)
{
	INITARR					(	char,
								self,
								init_list,
								count
							);
}

HOWTO_INIT					(	arr ( int ),
								self,
								const int			*init_list,
								unsigned int		count
							)
{
	INITARR					(	int,
								self,
								init_list,
								count
							);
}

HOWTO_INIT					(	arr ( long ),
								self,
								const long			*init_list,
								unsigned int		count
							)
{
	INITARR					(	long,
								self,
								init_list,
								count
							);

}

HOWTO_INIT					(	arr ( float ),
								self,
								const float			*init_list,
								unsigned int		count
							)
{
	INITARR					(	float,
								self,
								init_list,
								count
							);
}

HOWTO_INIT					(	arr ( double ),
								self,
								const double		*init_list,
								unsigned int		count
							)
{
	INITARR					(	double,
								self,
								init_list,
								count
							);
}


HOWTO_DEF					(	arr ( bool ),		self	)
{
	NEW						(	arr ( bool ),
								self,
								NULL,
								0
							);

	RET						(	self	);
}

HOWTO_DEF					(	arr ( char ),		self	)
{
	NEW						(	arr ( char ),
								self,
								NULL,
								0
							);

	RET						(	self	);
}

HOWTO_DEF					(	arr ( int ),		self	)
{
	NEW						(	arr ( int ),
								self,
								NULL,
								0
							);

	RET						(	self	);
}

HOWTO_DEF					(	arr ( long ),		self	)
{
	NEW						(	arr ( long ),
								self,
								NULL,
								0
							);

	RET						(	self	);
}

HOWTO_DEF					(	arr ( float ),		self	)
{
	NEW						(	arr ( float ),
								self,
								NULL,
								0
							);

	RET						(	self	);
}

HOWTO_DEF					(	arr ( double ),		self	)
{
	NEW						(	arr ( double ),
								self,
								NULL,
								0
							);

	RET						(	self	);
}


HOWTO_FINI					(	arr ( bool ),		self	)
{
	FINIARR					(	bool,
								self
							);
}

HOWTO_FINI					(	arr ( char ),		self	)
{
	FINIARR					(	char,
								self
							);
}

HOWTO_FINI					(	arr ( int ),		self	)
{
	FINIARR					(	int,
								self
							);
}

HOWTO_FINI					(	arr ( long ),		self	)
{
	FINIARR					(	long,
								self
							);
}

HOWTO_FINI					(	arr ( float ),		self	)
{
	FINIARR					(	float,
								self
							);
}

HOWTO_FINI					(	arr ( double ),		self	)
{
	FINIARR					(	double,
								self
							);
}


HOWTO_CPY					(	arr ( bool ),		to,	frm	)
{

	CPYARR					(	bool,
								to,
								frm
							);
}

HOWTO_CPY					(	arr ( char ),		to,	frm	)
{

	CPYARR					(	char,
								to,
								frm
							);
}

HOWTO_CPY					(	arr ( int ),		to,	frm	)
{

	CPYARR					(	int,
								to,
								frm
							);
}

HOWTO_CPY					(	arr ( long ),		to,	frm	)
{

	CPYARR					(	long,
								to,
								frm
							);
}

HOWTO_CPY					(	arr ( float ),		to,	frm	)
{

	CPYARR					(	float,
								to,
								frm
							);
}

HOWTO_CPY					(	arr ( double ),		to, frm	)
{

	CPYARR					(	double,
								to,
								frm
							);
}

