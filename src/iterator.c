/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "iterator.h"
#include "object.h"



HOWTO_INIT					(	itr ( bool ),
								self,
								const bool		*ptr,
								unsigned int	pos,
								IterType_t		typ
							)
{
	INITITR					(	bool,
								self,
								ptr,
								pos,
								typ
							);
}

HOWTO_INIT					(	itr ( char ),
								self,
								const char		*ptr,
								unsigned int	pos,
								IterType_t		type
							)
{
	INITITR					(	char,
								self,
								ptr,
								pos,
								type
							);
}

HOWTO_INIT					(	itr ( int ),
								self,
								const int		*ptr,
								unsigned int	pos,
								IterType_t		type
							)
{
	INITITR					(	int,
								self,
								ptr,
								pos,
								type
							);
}


HOWTO_INIT					(	itr ( long ),
								self,
								const long		*ptr,
								unsigned int	pos,
								IterType_t		type
							)
{
	INITITR					(	long,
								self,
								ptr,
								pos,
								type
							);
}


HOWTO_INIT					(	itr ( float ),
								self,
								const float		*ptr,
								unsigned int	pos,
								IterType_t		type
							)
{
	INITITR					(	float,
								self,
								ptr,
								pos,
								type
							);
}


HOWTO_INIT					(	itr ( double ),
								self,
								const double	*ptr,
								unsigned int	pos,
								IterType_t		type
							)
{
	INITITR					(	double,
								self,
								ptr,
								pos,
								type
							);
}


HOWTO_FINI                  (   itr ( bool ),   self    )
{
	FINIITR					(	bool,
								self
							);
}

HOWTO_FINI                  (   itr ( char ),   self    )
{
	FINIITR					(	char,
								self
							);
}

HOWTO_FINI                  (   itr ( int ),    self    )
{
	FINIITR					(	int,
								self
							);
}

HOWTO_FINI                  (   itr ( long ),   self    )
{
	FINIITR					(	long,
								self
							);
}

HOWTO_FINI                  (   itr ( float ),  self    )
{
	FINIITR					(	float,
								self
							);
}

HOWTO_FINI                  (   itr ( double ), self    )
{
	FINIITR					(	double,
								self
							);
}


HOWTO_DEF                   (   itr ( bool ),   self    )
{
	NEW						(	itr ( bool ),
								self,
								NULL,
								0,
								MAX_ITER
							);

	RET						(	self	);
}

HOWTO_DEF                   (   itr ( char ),   self    )
{
	NEW						(	itr ( char ),
								self,
								NULL,
								0,
								MAX_ITER
							);

	RET						(	self	);
}

HOWTO_DEF                   (   itr ( int ),    self    )
{
	NEW						(	itr ( int ),
								self,
								NULL,
								0,
								MAX_ITER
							);

	RET						(	self	);
}

HOWTO_DEF                   (   itr ( long ),   self   )
{
	NEW						(	itr ( long ),
								self,
								NULL,
								0,
								MAX_ITER
							);

	RET						(	self	);
}

HOWTO_DEF                   (   itr ( float ),  self    )
{
	NEW						(	itr ( float ),
								self,
								NULL,
								0,
								MAX_ITER
							);

	RET						(	self	);
}

HOWTO_DEF                   (   itr ( double ), self    )
{
	NEW						(	itr ( double ),
								self,
								NULL,
								0,
								MAX_ITER
							);

	RET						(	self	);
}


HOWTO_CMP                   (   itr ( bool ),   it1,    it2    )
{
	CMPITR					(	bool,
								it1,
								it2
							);
}

HOWTO_CMP                   (   itr ( char ),   it1,    it2    )
{
	CMPITR					(	char,
								it1,
								it2
							);
}

HOWTO_CMP                   (   itr ( int ),    it1,    it2    )
{
	CMPITR					(	int,
								it1,
								it2
							);
}

HOWTO_CMP                   (   itr ( long ),   it1,    it2    )
{
	CMPITR					(	long,
								it1,
								it2
							);
}

HOWTO_CMP                   (   itr ( float ),  it1,    it2    )
{
	CMPITR					(	float,
								it1,
								it2
							);
}

HOWTO_CMP                   (   itr ( double ), it1,    it2    )
{
	CMPITR					(	double,
								it1,
								it2
							);
}


HOWTO_INC                   (   itr ( bool ),   self    )
{
	INCITR					(	bool,
								self
							);
}

HOWTO_INC                   (   itr ( char ),   self    )
{
	INCITR					(	char,
								self
							);
}

HOWTO_INC                   (   itr ( int ),    self    )
{
	INCITR					(	int,
								self
							);
}

HOWTO_INC                   (   itr ( long ),   self    )
{
	INCITR					(	long,
								self
							);
}

HOWTO_INC                   (   itr ( float ),  self    )
{
	INCITR					(	float,
								self
							);
}

HOWTO_INC                   (   itr ( double ), self    )
{
	INCITR					(	double,
								self
							);
}


HOWTO_DEC                   (   itr ( bool ),   self    )
{
	DECITR					(	bool,
								self
							);
}

HOWTO_DEC                   (   itr ( char ),   self    )
{
	DECITR					(	char,
								self
							);
}

HOWTO_DEC                   (   itr ( int ),    self    )
{
	DECITR					(	int,
								self
							);
}

HOWTO_DEC                   (   itr ( long ),   self    )
{
	DECITR					(	long,
								self
							);
}

HOWTO_DEC                   (   itr ( float ),  self    )
{
	DECITR					(	float,
								self
							);
}

HOWTO_DEC                   (   itr ( double ), self    )
{
	DECITR					(	double,
								self
							);
}
