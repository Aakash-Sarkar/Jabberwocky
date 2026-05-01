/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "object.h"





#define																				\
HOWTO_DEF( class, _self )					class* def ( class ) ( class *_self )

#define																				\
_DEF( class, _self )						(	_self			=	def ( class )	\
																		( _self )	\
											)
#define																				\
DEF( class, _self )							do										\
											{										\
												assert			(	!(_self)	);	\
																					\
												_DEF			(	class,			\
																	_self			\
																);					\
																					\
											} while				(	0	)

#define																				\
NEW( class, _self, ... )					do										\
											{										\
												assert			(	!_self	);		\
																					\
												ALLOC_ZEROED	(	class,			\
																	_self,			\
																	1				\
																);					\
																					\
												assert			(	_self	);		\
																					\
												INIT			(	class,			\
																	_self,			\
																__VA_ARGS__			\
																);					\
											}	while			(	0	)

#define																				\
DEL( class, _self )							do										\
											{										\
												assert			(	_self	);		\
																					\
												FINI			(	class,			\
																	_self			\
																);					\
																					\
												DEALLOC			(	_self	);		\
																					\
											}	while			(	0	)

//	Shallow Copy

#define																				\
CP( class, _to, _frm )						(										\
												*( _to )			=	*( _frm )	\
											)

#define																				\
HOWTO_CPY( class, _to, _frm )				void									\
											copy ( class )		(	class* _to,		\
																	class* _frm		\
																)

#define																				\
_CPY( class, _to , _frm )					(	copy ( class )	(	_to,			\
																	_frm			\
																)					\
											)

#define																				\
CPY( class, _to , _frm )					do										\
											{										\
												assert			(	_to		);		\
												assert			(	_frm	);		\
																					\
												_CPY			(	class,			\
																	_to,			\
																	_frm			\
																);					\
																					\
											}	while			(	0	)


#define																				\
MCPY( class, _to, _frm )					do										\
											{										\
												if				(	!_to	)		\
												{									\
													DEF			(	class,			\
																	_to				\
																);					\
																					\
												}									\
																					\
												CPY				(	class,			\
																	_to,			\
																	_frm			\
																);					\
											}	while			(	0	)



#define																				\
MOV( class, _to, _frm )						do										\
											{										\
												CPY				(	class,			\
																	_to,			\
																	_frm			\
																);					\
																					\
												DEL				(	class,			\
																	_frm			\
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