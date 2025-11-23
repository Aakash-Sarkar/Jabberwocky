/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "util.h"
#include "object.h"




#define																						\
adder(class)							concat3					(	add, _, class	)

#define																						\
HOWTO_ADD( class, dest, op1, op2 )		class* adder( class )	(	class* dest,			\
																	class* op1,				\
																	class* op2				\
																)

#define																						\
__ADD( class, dest, op1, op2 )			adder	(	class	)	(	dest, op1, op2	)

#define																						\
ADD( class, dest, op1, op2 )			do	{												\
												if				(	!dest	)				\
												{											\
													DEF			(	class,					\
																	dest					\
																);							\
												}											\
																							\
												if				(	dest	)				\
												{											\
													__ADD		(	class,					\
																	dest,					\
																	op1,					\
																	op2						\
																);							\
												}											\
										}	while				(	0	)




#define																						\
subtractor( class )						concat3					(	sub, _, class	)

#define																						\
HOWTO_SUB( class, dest, op1, op2 )		class* subtractor( class ) (	class* dest,		\
																		class* op1,			\
																		class* op2			\
																)

#define																						\
__SUB( class, dest, op1, op2 )				subtractor			(	class	)	(	dest,	\
																					op1,	\
																					op2		\
																				)

#define																						\
SUB( class, dest, op1, op2 )			do	{												\
												if				(	!dest	)				\
												{											\
													DEF			(	class,					\
																	dest					\
																);							\
												}											\
																							\
												assert			(	dest	);				\
																							\
												__SUB			(	class,					\
																	dest,					\
																	op1,					\
																	op2						\
																);							\
										}	while				(	0	)




#define																						\
scaler_mul( class )							concat3				(	scaler_mul, _, class	)

#define																						\
HOWTO_MUL( class, dest, src, factor )		class*											\
											scaler_mul	( class ) ( class* dest,			\
																	class* src,				\
																	float  factor			\
																  )

#define																						\
__MUL( class, dest, src, factor )			scaler_mul	( class ) ( dest, src, factor )

#define																						\
MUL( class, dest, src, factor )			do	{												\
												if				(	!dest	)				\
												{											\
													DEF			(	class,					\
																	dest					\
																);							\
												}											\
																							\
												assert			(	dest	);				\
																							\
												__MUL			(	class,					\
																	dest,					\
																	src,					\
																	factor					\
																);							\
										}	while				(	0	)




#define																						\
scaler_div( class )						concat3					( scaler_div, _, class )

#define																						\
HOWTO_DIV( class, dest, src, factor )	class*												\
										scaler_div				( class ) ( class* dest,	\
																			class* src,		\
																			float  factor	\
																		  )

#define																						\
__DIV( class, dest, src, factor )		scaler_div				( class ) ( dest, src, factor )

#define																						\
DIV(class, dest, src, factor)			do	{												\
												if				(	!dest	)				\
												{											\
													DEF			(	class,					\
																	dest					\
																);							\
												}											\
																							\
												assert			(	dest	);				\
																							\
												__DIV			(	class,					\
																	dest,					\
																	src,					\
																	factor					\
																);							\
										}	while				(	0	)





#define																						\
normalizer( class )						concat3				(	norm, _, class	)

#define																						\
HOWTO_NORM( class, self )				void												\
										normalizer			( class ) ( class* self )

#define																						\
__NORM( class, self )					normalizer			( class ) ( self )

#define																						\
NORM( class, self )						do	{												\
												assert		(	self	);					\
																							\
												__NORM		(	class,	self	);			\
										}	while			(	0	)




#define																						\
incrementer( class )					concat3				(	inc, _, class	)

#define																						\
HOWTO_INC( class, self, ... )			class*												\
										incrementer ( class ) (	class* self,				\
																__VA_ARGS__					\
															  )

#define																						\
__INC( class, self, inc )				incrementer			( class ) ( self, inc )

#define																						\
INC( class, self, inc )					do	{												\
												assert		(	self	);					\
																							\
												__INC		(	class,						\
																self,						\
																inc							\
															);								\
										}	while			(	0	)




#define																						\
dot_prod( class )						concat3				( dotp, _, class )

#define																						\
HOWTO_DOTP( class, dest, src1, src2 )	float* dot_prod		( class ) (	float* dest,		\
																		class* src1,		\
																		class* src2			\
																	)

#define																						\
__DOTP( class, dest, src1, src2 )		dot_prod			( class ) ( dest, src1, src2 )

#define																						\
DOTP( class, dest, src1, src2 )			do	{												\
												assert		(	dest	);					\
												__DOTP		(	class,						\
																dest,						\
																src1,						\
																src2						\
															);								\
										}	while			(	0	)



#define																						\
cross_prod( class )						concat3				( crossp, _, class )

#define																						\
HOWTO_CROSSP( class, dest, src1, src2 )	class* cross_prod	( class ) ( class* dest,		\
																		 class* src1,		\
																		 class* src2		\
																	  )

#define																						\
CROSSP( class, dest, src1, src2 )		cross_prod			( class ) ( dest, src1, src2 )


