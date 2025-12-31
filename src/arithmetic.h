/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "util.h"
#include "object.h"




#define																					\
adder( class )									concat3		(	add,	_,	class	)

#define																					\
HOWTO_ADD( class, dest, op1, op2 )				void adder		(	class	)			\
																(	class	*dest,		\
																	class	*op1,		\
																	class	*op2		\
																)

#define																					\
_ADD( class, dest, op1, op2 )					do										\
												{										\
													assert		(	dest	);			\
													assert		(	op1		);			\
													assert		(	op2		);			\
																						\
													adder		(	class	)			\
																(	dest,				\
																	op1,				\
																	op2					\
																);						\
												}	while		(	0	)


#define																					\
ADD( class, dest, op1, op2 )					do										\
												{										\
													if			(	!dest	)			\
														DEF		(	class,				\
																	dest				\
																);						\
																						\
													_ADD		(	class,				\
																	dest,				\
																	op1,				\
																	op2					\
																);						\
												}	while		(	0	)


#define																					\
sub( class )									concat3			(	sub,	_,	class	)

#define																					\
HOWTO_SUB( class, dest, op1, op2 )				void sub		(	class	)			\
																(	class	*dest,		\
																	class	*op1,		\
																	class	*op2		\
																)

#define																					\
_SUB( class, dest, op1, op2 )					do										\
												{										\
													assert		(	dest	);			\
													assert		(	op1		);			\
													assert		(	op2		);			\
																						\
													sub			(	class	)			\
																(	dest,				\
																	op1,				\
																	op2					\
																);						\
												}	while		(	0	)


#define																					\
SUB( class, dest, op1, op2 )					do										\
												{										\
													if			(	!dest	)			\
														DEF		(	class,				\
																	dest				\
																);						\
																						\
													_SUB		(	class,				\
																	dest,				\
																	op1,				\
																	op2					\
																);						\
												}	while		(	0	)


#define																					\
scaler_mul( class )								concat3			(	scaler_mul,			\
																	_,					\
																	class				\
																)

#define																					\
HOWTO_MUL( class, dest, src, factor )			void									\
												scaler_mul		(	class	)			\
																(	class	*dest,		\
																	class	*src,		\
																	float	factor		\
																)

#define																					\
_MUL( class, dest, src, factor )				do										\
												{										\
													assert		(	dest	);			\
													assert		(	src		);			\
																						\
													scaler_mul	(	class	)			\
																(	dest,				\
																	src,				\
																	factor				\
																);						\
												}	while		(	0	)


#define																					\
MUL( class, dest, src, factor )					do										\
												{										\
													if			(	!dest	);			\
														DEF		(	class,				\
																	dest				\
																);						\
																						\
													_MUL		(	class,				\
																	dest,				\
																	src,				\
																	factor				\
																);						\
												}	while		(	0	)



#define																					\
scaler_div( class )								concat3			(	scaler_div,			\
																	_,					\
																	class				\
																)

#define																					\
HOWTO_DIV( class, dest, src, factor )			void									\
												scaler_div		(	class	)			\
																(	class* dest,		\
																	class* src,			\
																	float  factor		\
																)

#define																					\
_DIV( class, dest, src, factor )			do											\
											{											\
												assert			(	dest	);			\
												assert			(	src		);			\
																						\
												scaler_div		(	class	)			\
																(	dest,				\
																	src,				\
																	factor				\
																);						\
											}	while			(	0	)

#define																					\
DIV(class, dest, src, factor)				do											\
											{											\
												if				(	!dest	)			\
												{										\
													DEF			(	class,				\
																	dest				\
																);						\
												}										\
																						\
												_DIV			(	class,				\
																	dest,				\
																	src,				\
																	factor				\
																);						\
										}	while				(	0	)



#define																					\
dot_prod( class )								concat3			(	dotp,				\
																	_,					\
																	class				\
																)

#define																					\
HOWTO_DOTP( class, dest, src1, src2 )			void									\
												dot_prod		(	class	)			\
																(	float	*dest,		\
																	class	*src1,		\
																	class	*src2		\
																)

#define																					\
_DOTP( class, dest, src1, src2 )				do										\
												{										\
													assert		(	src1	);			\
													assert		(	src2	);			\
																						\
													dot_prod	(	class	)			\
																(	dest,				\
																	src1,				\
																	src2				\
																);						\
												}	while		(	0	)


#define																					\
DOTP( class, dest, src1, src2 )					do										\
												{										\
													if			(	!dest	)			\
														DEF		(	float,				\
																	dest				\
																);						\
																						\
													_DOTP		(	class,				\
																	dest,				\
																	src1,				\
																	src2				\
																);						\
												}	while		(	0	)



#define																					\
cross_prod( class )								concat3			(	crossp,				\
																	_,					\
																	class				\
																)

#define																					\
HOWTO_CROSSP( class, dest, src1, src2 )			void									\
												cross_prod		(	class	)			\
																(	class	*dest,		\
																	class	*src1,		\
																	class	*src2		\
																)

#define																					\
_CROSP( class, dest, src1, src2 )				do										\
												{										\
													assert		(	dest	);			\
													assert		(	src1	);			\
													assert		(	src2	);			\
																						\
													cross_prod	(	class	)			\
																(	dest,				\
																	src1,				\
																	src2				\
																);						\
												}	while		(	0	)


#define																					\
CROSSP( class, dest, src1, src2 )				do										\
												{										\
													if			(	!dest	)			\
														DEF		(	class,				\
																	dest				\
																);						\
																						\
													_CROSP		(	class,				\
																	dest,				\
																	src1,				\
																	src2				\
																);						\
												}	while		(	0	)




HOWTO_ADD										(	char,	dest,	op1,	op2		);

HOWTO_ADD										(	int,	dest,	op1,	op2		);

HOWTO_ADD										(	long,	dest,	op1,	op2		);

HOWTO_ADD										(	float,	dest,	op1,	op2		);

HOWTO_ADD										(	double,	dest,	op1,	op2		);




HOWTO_SUB										(	char,	dest,	op1,	op2		);

HOWTO_SUB										(	int,	dest,	op1,	op2		);

HOWTO_SUB										(	long,	dest,	op1,	op2		);

HOWTO_SUB										(	float,	dest,	op1,	op2		);

HOWTO_SUB										(	double,	dest,	op1,	op2		);




HOWTO_MUL										(	char,	dest,	src,	factor	);

HOWTO_MUL										(	int,	dest,	src,	factor	);

HOWTO_MUL										(	long,	dest,	src,	factor	);

HOWTO_MUL										(	float,	dest,	src,	factor	);

HOWTO_MUL										(	double,	dest,	src,	factor	);




HOWTO_DIV										(	char,	dest,	src,	factor	);

HOWTO_DIV										(	int,	dest,	src,	factor	);

HOWTO_DIV										(	long,	dest,	src,	factor	);

HOWTO_DIV										(	float,	dest,	src,	factor	);

HOWTO_DIV										(	double,	dest,	src,	factor	);



