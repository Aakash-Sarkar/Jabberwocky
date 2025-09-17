#pragma once

#include "util.h"
#include "color.h"





#define rotator(class)								concat3(rotate, _, class)

#define																									\
HOWTO_ROTATE(class, to, from, ...)					void												\
													rotator(class)	(	class*	to,						\
																		class*	from,					\
																		__VA_ARGS__		)

#define																									\
ROTATE(class, to, from, angle)						rotator(class) (	to,	from,	angle	)




#define projector(class1, class2)					project_##class2##_to_##class1

#define																									\
HOWTO_PROJECT(class1, class2, to, from, ...)		void												\
													projector(class1, class2) (	class1* to,				\
																				class2* from,			\
																				__VA_ARGS__		)

#define																									\
PROJECT(class1, class2, to, from, ...)				projector(class1, class2) (	to,						\
																				from,					\
																				__VA_ARGS__		)




#define painter(class)								concat3(draw, _, class)

#define																									\
HOWTO_DRAW(class, obj, ...)							void												\
													painter(class) (	class* obj,						\
																		__VA_ARGS__		)

#define	DRAW(class, obj, ...)						painter(class) (	obj,							\
																		__VA_ARGS__		)

