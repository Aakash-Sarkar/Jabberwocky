#pragma once

#include "util.h"




#define adder(class)							concat3(add, _, class)

#define HOWTO_ADD(class, dest, op1, op2)		void adder(class) ( class* dest,			\
																	class* op1,				\
																	class* op2 )

#define ADD(class, dest, op1, op2)				adder(class) (dest, op1, op2)




#define subtractor(class)						concat3(sub, _, class)

#define HOWTO_SUB(class, dest, op1, op2)		void subtractor(class) (class* dest,		\
																		class* op1,			\
																		class* op2)

#define SUB(class, dest, op1, op2)				subtractor(class) (dest, op1, op2)




#define scaler_mul(class)						concat3(scaler_mul, _, class)

#define HOWTO_MUL(class, dest, src, factor)		void scaler_mul(class) (class* dest,		\
																		class* src,			\
																		float  factor)

#define MUL(class, dest, src, factor)			scaler_mul(class) (dest, src, factor)




#define scaler_div(class)						concat3(scaler_div, _, class)

#define HOWTO_DIV(class, dest, src, factor)		void scaler_div(class) (class* dest,		\
																		class* src,			\
																		float  factor)

#define DIV(class, dest, src, factor)			scaler_div(class) (dest, src, factor)




#define dot_prod(class)							concat3(dotp, _, class)

#define																						\
HOWTO_DOTP(class, dest, src1, src2)				void dot_prod(class)	(	float* dest,	\
																			class* src1,	\
																			class* src2)

#define DOTP(class, dest, src1, src2)			dot_prod(class)	(dest, src1, src2)



#define cross_prod(class)						concat3(crossp, _, class)

#define																						\
HOWTO_CROSSP(class, dest, src1, src2)			void cross_prod(class)	(class* dest,		\
																		class* src1,		\
																		class* src2)

#define CROSSP(class, dest, src1, src2)			cross_prod(class)	(dest, src1, src2)
