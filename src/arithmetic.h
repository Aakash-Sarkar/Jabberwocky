/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "memory.h"



#define																						\
HOWTO_CMP( class, _item1, _item2 )				bool cmp ( class )	(	class	*_item1,	\
																		class	*_item2		\
																	)

#define																						\
CMP( class, _item1, _item2 )					cmp ( class )		(	( _item1 ),			\
																		( _item2 )			\
																	)

#define																						\
HOWTO_ADD( class, _dst, _op1, _op2 )			void add ( class )	(	class	*_dst,		\
																		class	*_op1,		\
																		class	*_op2		\
																	)

#define																						\
ADD( class, _dst, _op1, _op2 )					do											\
												{											\
													assert			(	_dst	);			\
													assert			(	_op1	);			\
													assert			(	_op2	);			\
																							\
													add	( class )	(	( _dst ),			\
																		( _op1 ),			\
																		( _op2 )			\
																	);						\
																							\
												}	while			(	0	)



#define																						\
HOWTO_SUB( class, _dst, _op1, _op2 )			void sub ( class )	(	class	*_dst,		\
																		class	*_op1,		\
																		class	*_op2		\
																	)

#define																						\
SUB( class, _dst, _op1, _op2 )					do											\
												{											\
													assert			(	_dst	);			\
													assert			(	_op1	);			\
													assert			(	_op2	);			\
																							\
													sub ( class )	(	( _dst ),			\
																		( _op1 ),			\
																		( _op2 )			\
																	);						\
																							\
												}	while			(	0	)

#define																						\
HOWTO_INC( class, _self )						void inc ( class )	(	class	*_self	)

#define																						\
INC( class, _self )								inc ( class )		(	_self	)



#define																						\
HOWTO_DEC( class, _self )						void dec ( class )	(	class	*_self	)

#define																						\
DEC( class, _self, _dec )						dec ( class )		(	_self	)


#define																						\
HOWTO_MUL( class, _dest, _src, _factor )		void										\
												mul ( class )		(	class	*_dest,		\
																		class	*_src,		\
																		float	_factor		\
																	)

#define																						\
MUL( class, _dest, _src, _factor )				do											\
												{											\
													assert			(	_dest	);			\
													assert			(	_src	);			\
													assert			(	_factor	);			\
																							\
													mul ( class )	(	( _dest ),			\
																		( _src ),			\
																		( _factor )			\
																	);						\
																							\
												}	while			(	0	)





#define																						\
HOWTO_DIV( class, _dest, _src, _factor )		void										\
												div ( class )		(	class	*_dest,		\
																		class	*_src,		\
																		float	_factor		\
																	)

#define																						\
DIV( class, _dest, _src, _factor )			do												\
											{												\
												assert				(	_dest	);			\
												assert				(	_src	);			\
												assert				(	_factor	);			\
																							\
												div ( class )		(	( _dest ),			\
																		( _src ),			\
																		( _factor )			\
																	);						\
																							\
											}	while				(	0	)


#define																						\
HOWTO_DOTP( class, _dest, _src1, _src2 )		void										\
												dotp ( class )		(	float	*_dest,		\
																		class	*_src1,		\
																		class	*_src2		\
																	)

#define																						\
DOTP( class, _dest, _src1, _src2 )			do												\
											{												\
												assert				(	_dest	);			\
												assert				(	_src1	);			\
												assert				(	_src2	);			\
																							\
												dotp ( class )		(	( _dest ),			\
																		( _src1 ),			\
																		( _src2 )			\
																	);						\
																							\
											}	while				(	0	)





#define																						\
HOWTO_CROSP( class, _dest, _src1, _src2 )		void										\
												crosp ( class )		(	class	*_dest,		\
																		class	*_src1,		\
																		class	*_src2		\
																	)

#define																						\
CROSP( class, _dest, _src1, _src2 )				do											\
												{											\
													assert			(	_dest	);			\
													assert			(	_src1	);			\
													assert			(	_src2	);			\
																							\
													crosp ( class )	(	( _dest ),			\
																		( _src1 ),			\
																		( _src2	)			\
																	);						\
																							\
												}	while			(	0	)


#define																						\
SWP( class, _item1, _item2 )					do											\
												{											\
													assert		(	_item1	);				\
													assert		(	_item2	);				\
																							\
													class			*tmp	=	NULL;		\
																							\
													DEF			(	class,					\
																	( tmp )					\
																);							\
																							\
													CPY			(	class,					\
																	( tmp ),				\
																	( _item1 )				\
																);							\
																							\
													CPY			(	class,					\
																	( _item1 ),				\
																	( _item2 )				\
																);							\
																							\
													CPY			(	class,					\
																	( _item2 ),				\
																	( tmp )					\
																);							\
																							\
													DEL			(	class,					\
																	( tmp )					\
																);							\
																							\
												}	while		(	0	)




HOWTO_ADD										(	char,	dst,	op1,	op2		);

HOWTO_ADD										(	int,	dst,	op1,	op2		);

HOWTO_ADD										(	long,	dst,	op1,	op2		);

HOWTO_ADD										(	float,	dst,	op1,	op2		);

HOWTO_ADD										(	double,	dst,	op1,	op2		);




HOWTO_SUB										(	char,	dst,	op1,	op2		);

HOWTO_SUB										(	int,	dst,	op1,	op2		);

HOWTO_SUB										(	long,	dst,	op1,	op2		);

HOWTO_SUB										(	float,	dst,	op1,	op2		);

HOWTO_SUB										(	double,	dst,	op1,	op2		);




HOWTO_MUL										(	char,	dst,	src,	fac	);

HOWTO_MUL										(	int,	dst,	src,	fac	);

HOWTO_MUL										(	long,	dst,	src,	fac	);

HOWTO_MUL										(	float,	dst,	src,	fac	);

HOWTO_MUL										(	double,	dst,	src,	fac	);




HOWTO_DIV										(	char,	dst,	src,	fac	);

HOWTO_DIV										(	int,	dst,	src,	fac	);

HOWTO_DIV										(	long,	dst,	src,	fac	);

HOWTO_DIV										(	float,	dst,	src,	fac	);

HOWTO_DIV										(	double,	dst,	src,	fac	);



