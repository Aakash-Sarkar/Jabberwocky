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

struct Object;


////////////////////////////////////////////////////////////////////////////////
//								CONSTRUCTORS:
////////////////////////////////////////////////////////////////////////////////
//
//
//		Constructors are the methods through which objects are created.
//		Objects in modern applications are complex entities with lots
//		of internal state variables. Some of these variables can be
//		objects themselves with their own internal states. If any of
//		these variables are set incorrectly (or not set at all), then
//		the object will be in a inconsistent state. Calling a method
//		on an object in an inconsistent state can lead to undefined or
//		inexplicable behaviors that are hard to analyze or debug.
//
//
//		We can rely on the user to allocate the object and set each of
//		the member variable correctly on their own, before calling any
//		of its methods. But this has a lot of pitfalls:
//
//
//		First, the user may only have a surface level understanding of
//		the object. She may be aware of what some of the methods are
//		supposed to do and may know of the more common internal state
//		variables. However, expecting her to initialize all the internal
//		variables correctly plus be cognizant of the various pitfalls
//		that may occur in case she makes a mistake; is really too much
//		to ask from the user.
//
//
//		Second, there are generally multiple users of an object in a
//		modern software. If you are writing a framework library, you
//		can expect multiple applications to use your classes in their
//		program for one purpose or another (People typically like to
//		avoid writing things from the scratch). Therefore, the risk of
//		making mistakes while initializing an object increases
//		significantly with each new user.
//
//
//		Therefore,  most modern programming languages today, pin the
//		responsibility of intializing an object correctly on the class
//		designer (person who is responsible for defining the class and
//		its internal state variables). This is done through the use of
//		constructors. While designing the object class, the author is
//		responsible for writing a constructor method for that class.
//
//
//		This special method takes some arguments from the caller and
//		creates an object with a consistent initial state based on the
//		supplied arguments. The parameters requested from the caller
//		are the ones that are most commonly used (or, you can omit the
//		arguments altogether, if your object can have only a single
//		initial state).
//
//
//		Here's an example. Let's say we have an object that have more
//		than 20 member variables and functions and can be used in four
//		different states:
//
//
//		[	BEGINNER	]
//
//		[	INTERMEDIATE	]
//
//		[	EXPERT	]
//
//		[	EXPERIMENTAL	]
//
//
//		In |BEGINNER| state we only expose the most basic functions to
//		the user but hide away the rest of the more complex functions.
//		In |EXPERT| state we allow the user to call all the available
//		functions and use all the complex features of the object. In
//		|EXPERIMENTAL| state, we also expose to the user newly added
//		featrues that are not yet fully tested to work on all systems.
//
//
//		Instead of asking the user to provide the initial value of all
//		the 20 member variables, or keep four differernt copies of the
//		same class; we can instead ask the user to provide one of the
//		above 4 states; and based on the state provided we can set each
//		of the variables ourselves.
//
//
///////////////////////////////////////////////////////////////////////////////

#define ctor(class)							concat3(create, _, class)
#define dtor(class)							concat3(destroy, _, class)




#define CONSTRUCTOR(class, ...)				class* ctor(class) (__VA_ARGS__)

#define DESTRUCTOR(class)					void dtor(class) (class* object)


#define CONSTRUCT(ptr, class, ...)			ptr = ctor(class) (__VA_ARGS__)

#define DESTRUCT(ptr, class)				dtor(class) (ptr)




#define copy_ctor(class)					concat3(copy, _, class)

#define HOWTO_COPY(class, to, from)			void copy_ctor(class) (class* to, class* from)

#define COPY(class, to , from)				copy_ctor(class) (to, from)




#define	maker(class)						concat3(make, _, class)

#define HOWTO_MAKE(class, ptr, ...)			void maker(class) (class* ptr, __VA_ARGS__)

#define MAKE(class, ptr, ...)				maker(class) (ptr, __VA_ARGS__)



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

