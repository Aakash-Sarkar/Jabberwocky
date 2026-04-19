/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "object.h"



#define																				\
HOWTO_DEF( class, _self )					class* def ( class ) ( class *self )

#define																				\
_DEF( class, self )							(	self			=	def ( class )	\
																		( self )	\
											)
#define																				\
DEF( class, self )							do										\
											{										\
												assert			(	!(self)	);		\
																					\
												_DEF			(	class,			\
																	self			\
																);					\
																					\
											} while				(	0	)

#define																				\
NEW( class, self, ... )						do										\
											{										\
												assert			(	!(self)	);		\
																					\
												ALLOC_ZEROED	(	class,			\
																	self,			\
																	1				\
																);					\
																					\
																					\
												assert			(	self	);		\
																					\
												INIT			(	class,			\
																	self,			\
																__VA_ARGS__			\
																);					\
											}	while			(	0	)

#define																				\
DEL( class, self )							do										\
											{										\
												assert			(	self	);		\
																					\
												FINI			(	class,			\
																	self			\
																);					\
																					\
												DEALLOC			(	self	);		\
																					\
											}	while			(	0	)

//	Shallow Copy

#define																				\
CP( class, to, from )						(										\
												*( to )			=	*( from )		\
											)

#define																				\
HOWTO_CPY( class, to, from )				void									\
											copy ( class )		(	class* to,		\
																	class* from		\
																)

#define																				\
_CPY( class, to , from )					(	copy ( class )	(	to,	from	)	)


#define																				\
CPY( class, to , from )						do										\
											{										\
												assert			(	to	);			\
												assert			(	from	);		\
																					\
												_CPY			(	class,			\
																	to,				\
																	from			\
																);					\
																					\
											}	while			(	0	)


#define																				\
MCPY( class, to, from )						do										\
											{										\
												if				(	!to	)			\
												{									\
													DEF			(	class,			\
																	to				\
																);					\
																					\
												}									\
																					\
												CPY				(	class,			\
																	to,				\
																	from			\
																);					\
											}	while			(	0	)



#define																				\
MOV( class, to, from )						do										\
											{										\
												CPY				(	class,			\
																	to,				\
																	from			\
																);					\
																					\
												DEL				(	class,			\
																	from			\
																);					\
																					\
											}	while			(	0	)



HOWTO_DEF									(	bool,	self	);

HOWTO_DEF									(	char,	self	);

HOWTO_DEF									(	int,	self	);

HOWTO_DEF									(	long,	self	);

HOWTO_DEF									(	float,	self	);

HOWTO_DEF									(	double,	self	);


HOWTO_CPY									(	bool,	to,	frm	);

HOWTO_CPY									(	char,	to,	frm	);

HOWTO_CPY									(	int,	to,	frm	);

HOWTO_CPY									(	long,	to,	frm	);

HOWTO_CPY									(	float,	to,	frm	);

HOWTO_CPY									(	double,	to,	frm	);