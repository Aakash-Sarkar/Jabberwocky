/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/////////////////////////////////////////////////////////////////////////////////
//								MACROS:
/////////////////////////////////////////////////////////////////////////////////
//
//		The core purpose of this file is to demonstrate how C style Macros
//		can be used to improve the readibilty and quality of your program.
//
//		You may have learned in school that it's safer to use variables,
//		but hopefully you'll see that if used carefully, it's much cooler
//		to use macros!
//
////////////////////////////////////////////////////////////////////////////////



#define SUCCESS							(true)
#define FAIL							(false)



#ifdef __GNUC__
#define asm(x)							__asm__(x)
#define typeof(x)						__typeof__(x)
#elif defined(_MSC_VER)
#define asm(x)							__asm(x)
#define typeof(x)						__typeof__ (x)
#define fopen							fopen_s
#define sscanf							sscanf_s
#endif


#define concat2(a, b)					a##b
#define concat3(a, b, c)				a##b##c
#define concat4(a, b, c, d)				a##b##c##d
#define concat5(a, b, c, d,e)			a##b##c##d#e

#define str(label)						#label



/////////////////////////////////////////////////////////////////////////////////
//
//		This is just a fancy way of writing `retval = who_why(args)` aka
//		function call!
//
//		But it's added here for a purpose. Writing it in this ways pulls
//		the attention of the reader to the line. It also hilights to the
//		reader that this function call is going outside our application
//		and into the SDL Layer. It may make code browsing difficult but
//		you can add your own style into your program!
//
//		You can also customize the CALL macro to add some extra logic
//		before the function	call (for eg, dumping the api name into a
//		debug file before calling the api etc!).
//
/////////////////////////////////////////////////////////////////////////////////

#define CALL(retval, who, why, ...)		retval = concat3(who, _, why)(__VA_ARGS__)


#define RETURN(x)						return x

#define PTR(class, name, val)			class* name = val




/////////////////////////////////////////////////////////////////////////////////
//
//		Helper macro for implementing while loops:
//
//		Use like this:
//
//		#include <stdio.h>
//
//		int global_variable;
//
//		DECLARE_LOOP(MYLOOP);
//
//		int main(void) {
//
//	 	LOOP(MYLOOP) {
// 			if (condition) {
// 				LOOP_BREAK(MYLOOP);
// 			}
// 		}
//
/////////////////////////////////////////////////////////////////////////////////

#define LOOP_VAR(x)						concat3(x, _, loop)

#define DECLARE_LOOP(x)					volatile bool LOOP_VAR(x)

#define LOOP(x)							for (LOOP_VAR(x) = true; LOOP_VAR(x) != false;)

#define LOOP_BREAK(x)					(LOOP_VAR(x) = false)




/////////////////////////////////////////////////////////////////////////////////
//
//		Good old calloc put behind a macro?
//		What next? free?
//
//		The reason behind renaming it to ALLOC_ZEROED is to remind myself
//		that we want a zero initialized memory here. Having a zeroed out
//		memory removes the burden from the programmer to zero initialize
//		it herself. But it also adds the extra overhead of zeroing the bytes
//		each time the memory is allocated.
//
/////////////////////////////////////////////////////////////////////////////////

#define ALLOC_ZEROED(class, ptr, n)		ptr = (class *)	calloc (	n, sizeof(class)	)


/////////////////////////////////////////////////////////////////////////////////
//
//		There are situations in which avoiding the cost of zeroing out memory
//		is more desirable. For eg. if the allocated memory is too large or if
//		the user is anyway going to set it to some other value. Color buffers
//		are an appropriate example of this. The buffers tend to be large and
//		are alway cleared out to some initial color before the next draw call.
//
/////////////////////////////////////////////////////////////////////////////////

#define ALLOC_NONZEROED(n, class)		(class *)	malloc (	(n) * (sizeof(class))	)


/////////////////////////////////////////////////////////////////////////////////
//
//		This is more or less to keep the theme going...
//
//		This is also to demonstrate an example usecase. Suppose it's required
//		to always set the pointer to null after freeing for whatever reason.
//		Having the two operations packed inside a macro is much easier to use;
//		and it's unlikely to forget to set the pointer to null. This is also an
//		example of code reuse.
//
/////////////////////////////////////////////////////////////////////////////////

#define DEALLOC(ptr)					do {								\
												if(ptr)						\
													free(ptr);				\
												ptr = NULL;					\
										}	while(0)


#define MEM(class, x, n)				class x [ n ] = { 0 }



#define BITS_PER_BYTE					(8)
#define BITS_TO_BYTES(n)				(( n ) /  ( BITS_PER_BYTE ))

#define LOG(...)						fprintf	(stderr,  __VA_ARGS__)

#define ASSERT(cond, ...)				do {								\
												if (!cond) {				\
													LOG  (__VA_ARGS__);		\
													exit (1);				\
												}							\
										}	while  (0)


