/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "util.h"



////////////////////////////////////////////////////////////////////////////////
//									OBJECTS:
////////////////////////////////////////////////////////////////////////////////
//
//
//		The concept of objects is so fundamental in Software Design that
//		even C programmers have found out a way to emulate it in their
//		programs. But why is it needed? And can I get away with writing
//		my program without having to know or rely upon object oriented
//		programming principles? The question is a little complex to
//		answer; so please follow along till the end.
//
//
//		You are free to write your program in any way that you see fit.
//		However if you're writing a complex program with lots of state
//		variables and functions, you'll increasingly begin to realize
//		that using some of the features of object oriented programming
//		in your design, makes certain things a lot easier for you. I'm
//		noting down an example below, but you can also browse through
//		the code and find out your own.
//
//
//		One is the idea of thinking in terms of objects:
//
//		Imagine you're writing a commercial application and you start
//		off with the following approach:
//
//
//		1.	My program will begin at the main function and within that
//			it'll have a for loop.
//
//		2.	At every iteration of the loop, collect the inputs from
//			the user.
//
//		3.	Based on the inputs given, make some function calls with
//			arguments based on the supplied inputs.
//
//		4.	Each function will in turn make some other function calls
//			based on the arguments given and so on...
//
//
//		This is the typical procedure oriented approach. We decompose
//		the process of determining the output from the given inputs
//		into a sequence of function calls or procedures. Each function
//		is itself composed of smaller functions and so on, down to the
//		level of a single processor instruction!
//
//
//
//		The problem with this approach is the following:
//
//		In order to make sure that any new change that we introduce in
//		our program, does not introduce any new bugs, we need to keep
//		track of every sequence of function calls that our program can
//		take and check if it's still correct with this new change. And
//		remember that our program can take a different path at every
//		if-else or branch statement! This can be a headache with just
//		2 or 3 source files. But in a commercial application with
//		thousands of functions and branches, it'll become like keeping
//		track of each thread in a spider's web!
//
//
//
//		Therefore,  a more managable approach would be the following:
//
//
//		1.	Our application will consist of N number of objects (structs)
//
//		2.	Each object can take N number of different states (values).
//			Each state is defined by the state (value) of its internal
//			variables.
//
//		3.	The internal variables of an object can be objects
//			themselves with their own internal states (values).
//
//		4.	In order to take an object from state A to state B, one
//			needs to call a method of that object.
//
//
//			+-------------+		method		+-------------+
//			|   STATE A   +--------------->	+   STATE B   |
//			+-------------+					+-------------+
//
//
//		5.	Defining the state of all the objects at a time will define
//			the state of your application at that point in time.
//
//		6.	At the start of the application all these objects will be in
//			their initial ( default ) states. Inside our main loop we
//			change the state of each object based on the user input.
//
//
////////////////////////////////////////////////////////////////////////////////


typedef						struct Object				Object_t;







#define ctor(class)							concat3(create, _, class)

#define dtor(class)							concat3(destroy, _, class)




#define HOWTO_CONSTRUCT(class, self, ...)	class* ctor(class) (class* self, __VA_ARGS__)

#define HOWTO_DESTRUCT(class, self)			void dtor(class) (class* self)


#define CONSTRUCT(class, self, ...)			self = ctor(class) (self, __VA_ARGS__)

#define DESTRUCT(class, self)				dtor(class) (self)




#define copy_ctor(class)					concat3(copy, _, class)

#define HOWTO_COPY(class, to, from)			void copy_ctor(class) ( class* to,	\
																	class* from)

#define COPY(class, to , from)				copy_ctor(class) (to, from)




#define	composer(class)						concat3(compose, _, class)

#define HOWTO_COMPOSE(class, self, ...)		void								\
											composer(class) (	class* self,	\
																	__VA_ARGS__	)

#define COMPOSE(class, self, ...)			composer(class) (self, __VA_ARGS__)




/////////////////////////////////////////////////////////////////////////////////
//								INHERITANCE:
/////////////////////////////////////////////////////////////////////////////////
//
//		Inheritance is what grandpa leaves behind.
//
/////////////////////////////////////////////////////////////////////////////////


#define baseclass(module, class)			concat3(module, _, class)

#define INHERIT(module, class, ...)			struct class	{					\
												baseclass(module, class) *sdl;	\
												__VA_ARGS__						\
											}




/////////////////////////////////////////////////////////////////////////////////
//								METHOD:
/////////////////////////////////////////////////////////////////////////////////

#define method(class, name)					concat3(class, _, name)
#define METHOD(class, name, self, ...)		class*									\
											method(class, name) (	class* self,	\
																	__VA_ARGS__ )

#define CALLM(class, name, self, ...)		self = method(class, name) (	self,	\
																		__VA_ARGS__)

