/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "util.h"
#include "unit.h"
//#include "operation.h"



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
//		this is the typical procedure oriented approach. We decompose
//		the process of determining the output from the given inputs
//		into a sequence of function calls or procedures. Each function
//		is itthis composed of smaller functions and so on, down to the
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
//		if-else or branch statement! this can be a headache with just
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


struct Object
{
	Object_t						*parent;
	int								self_idx;
	int								idx;
	Type_t							*type;
	int								refcount;
	bool							lock;
	void							*priv;
};

typedef								struct	Object				Object_t;




/////////////////////////////////////////////////////////////////////////////////
//								METHOD:
/////////////////////////////////////////////////////////////////////////////////
//
//
//		One of the reasons that people use higher level languages like ( C++
//		or Java ) is because they provide a way to provide isolation between
//		different component objects via the use of interface methods. This
//		means every memory address inside the object boundary is inacessible
//		to any function except for the member functions of the class. If you
//		want to update a memory address inside the object boundary, you need
//		to first get a handle to the object, and then request the object to
//		the update the memory location; by calling one of its methods. If we
//		don't have any method to access the address that we want, that means
//		the class doesn't allow us to update that address.
//
//
//		+---------------+					+--------------+
//		|	Process		|					|	 Object    |
//		+-------+-------+					+-------+------+
//				|									|
//				|									|
//				|				Mehtod A			|
//				+ --------------------------------> +
//				|									|	Access A	+-------+
//				|									+ ----------- > +	A	|
//				|				Method B			|				+-------+
//				+ --------------------------------> +
//				|									|	Access B	+-------+
//				|									+ ----------- > +	B	|
//				|		( C is inacessible )		|				+-------+
//				+ ----------------X---------------> +
//				|									|	Access C	+-------+
//				|									+ ----------- > +	C	|
//				|				Method D			|				+-------+
//				+ --------------------------------> +
//				|									|	Access D	+-------+
//				|									+ ----------- > +	D	|
//				|									|				+-------+
//				v									v
//
//
//		To understand why people like to do it this way, we need a little bit
//		of historical context. In early days of computing, people weren't so
//		much bothered about the structure of the programs. They mostly focused
//		on solving the burning problems inside their heads through the use of
//		this new cool machine. At that time the programs were structured as a
//		collection of procedures. A procedure is a collection of instructions
//		that can operate on the available addresses in the memory and IO space
//		and produce the desired result in the memory. In a sense an executable
//		file generated by a compiler is a procedure.
//
//
//		Soon, people realized that this approach was creating for them hard to
//		manage programs. This was happening because of the illegal use of non
//		local references ( i.e. a procedure accessing a memory address that it
//		has no bussiness with ).
//
//
//		To understand why this is such a big problem, let's take the following
//		example from the real world. Assume that you are an electrical engineer
//		tasked to fix a faulty traffic light where a Red bulb signals when it's
//		expected to be a Green signal. Let us assume that the circuitry for the
//		Red and Green bulbs are locked behind the Red and Green cabinets that
//		hold the respective light bulbs. If there's a chance that a wire inside
//		the Green cabinet could drive the current in the Red bulb, then our job
//		becomes exponentially more difficult. It's much more convinient to find
//		out where the problem is if only the wires inside the Red cabinet could
//		drive the current in the Red bulb and vice versa. And the wires in the
//		Red and Green cabinets are fully isolated from one another. Similarly a
//		problem can occur if there is a possibility that a procedure can update
//		an address that doesn't belong to it.
//
//
//		To get around this problem, people came up with the idea of functions.
//		A programming lanuage function is like a mathematical function: which
//		can take as input some arguments and produces a result. For e.g, if a
//		function takes two floating point numbers in1 and in2 as inputs, and
//		produces a floating point result; then it can also be thought of as a
//		mathematical function with R2 as the domain and R1 as the range.
//
//
//		All the memory used by the function is allocated on the program stack
//		which is automatically cleaned up once the function call returns. The
//		arguments for the function are copied in the stack and the result is
//		copied back to the caller stack before the stack is cleaned up. In a
//		sense the function call ( or, rather the compiler that generates the
//		assembly code for the function) is responsible for freeing up all the
//		memory that it uses.
//
//
//				  Program Stack
//				+---------------+
//				:	function 1	:		}	Stack memory for function 1
//				+---------------+
//				:	function 2	:		}	Stack memory for function 2
//				+---------------+
//				:	function 3	:		}	Stack memory for function 3
//				+---------------+
//				:	function 4	:		}	Stack memory for function 4
//				:				:		( freed up once call returns to 3 )
//				+---------------+
//
//
//		As the software industry started to take shape, programs were written
//		as a collaborative effort between multiple teams instead of the usual
//		small number of programmers. Naturally, architects wanted to put more
//		restrictions on what the programmers can do in their programs. One of
//		the ideas that emerged was to use methods instead of function calls.
//
//
//		A method is a function that is bound to an object. That is the method
//		can only be called by specifying the object that it belong to and can
//		only access the memory addresses inside the object boundary. A method
//		can access non local references inside the object boundary along with
//		its stack region; but is otherwise fully isloated from other object's
//		memory. This structure helps the programmers to associate an object's
//		behavior with its state. In simple terms this means that the possible
//		arrangement of bits inside the object's memory is completely defined
//		by the methods of that object. This paradigm helps prevent an objects
//		memory to be spuriously updated by another object.
//
// 
/////////////////////////////////////////////////////////////////////////////////





#define																				\
method(class, name)					concat3(class, _, name)

#define																				\
METHOD(class, name, this, ...)		class*											\
									method	( class, name ) ( class* this,			\
															__VA_ARGS__ )

#define																				\
CLASS_METHOD(class, name, ...)		int	method	(	class, name	) (	__VA_ARGS__	)	\

#define																				\
__MSG(class, name, this, ...)		this	=	method ( class, name ) ( this, __VA_ARGS__ )

#define																				\
__CALL(class, name, ...)			method		( class, name ) ( __VA_ARGS__ )

#define																				\
CALL(class, name, ...)				do	{											\
											int					ret	=	-1;			\
																					\
											ret				=	__CALL	(	class,	\
																			name,	\
																		 __VA_ARGS__\
																		);			\
											assert			(	!ret	);			\
									}	while				(	0	)

#define																				\
MSG(class, name, this, ...)			do	{											\
											Object_t			*obj	=	NULL;	\
											bool				status	=	FAIL;	\
																					\
											CALL			(	Object_t,			\
																get_object,			\
																this,				\
																obj					\
															);						\
																					\
											if				(	obj	)				\
											{										\
												do {								\
													__MSG	(	Object_t,			\
																lock,				\
																obj,				\
																&status				\
															);						\
												} while		(	status == FAIL	);	\
																					\
												__MSG		(	class,				\
																name,				\
																this,				\
															__VA_ARGS__				\
															);						\
																					\
												__MSG		(	Object_t,			\
																unlock,				\
																obj,				\
																&status				\
															);						\
											}										\
									}	while				(	0	)




#define																			\
ctor(class)							concat3			(	create, _, class	)

#define																			\
dtor(class)							concat3			(	destroy, _, class	)




#define																				\
HOWTO_CONSTRUCT(class, this, ...)	class*											\
									ctor			(	class	) (	class* this,	\
																	__VA_ARGS__		\
																  )

#define																				\
CONSTRUCT(class, this, ...)			this			=	ctor	(	class	)		\
																(	this,			\
																	__VA_ARGS__		\
																)


#define																				\
HOWTO_DESTRUCT(class, this)			void				dtor	(	class	)		\
																(	class* this		)



#define																				\
__NEW( class, this )						Object_t		*obj	=	NULL;		\
											Type_t			*type	=	NULL;		\
																					\
											int				idx		=	-1;			\
																					\
											CALL		(	Type_t,					\
															lookup,					\
															str ( class ),			\
															type					\
														);							\
																					\
											if			(	type	)				\
											{										\
												MSG		(	Type_t,					\
															create_instance,		\
															type,					\
															obj,					\
															&idx					\
														);							\
											}										\
																					\
											if			(	obj		)				\
											{										\
												MSG		(	Object_t,				\
															create_object,			\
															obj,					\
															type,					\
															idx						\
														);							\
																					\
												MSG		(	Object_t,				\
															get_instance,			\
															obj,					\
															this					\
														);							\
											}

#define																				\
NEW( class, this, ... )				do	{											\
											__NEW		(	class,					\
															this					\
														);							\
																					\
											assert		(	this	);				\
																					\
											CONSTRUCT	(	class,					\
															this,					\
															__VA_ARGS__				\
														);							\
									}	while			(	0	)

#define																				\
DEF( class, this )					do	{											\
											if			(	!this	)				\
											{										\
												__NEW	(	class,					\
															this					\
														);							\
																					\
												assert	(	this	);				\
											}										\
									}	while			(	0	)




#define																				\
DESTRUCT(class, this)					dtor			(	class	) (	this	)

#define																				\
_DEL( class, this )						Object_t			*obj	=	NULL;		\
										Type_t				*type	=	NULL;		\
																					\
										CALL			(	Object_t,				\
															get_object,				\
															this,					\
															obj						\
														);							\
																					\
										if				(	obj	)					\
										{											\
											MSG			(	Object_t,				\
															put_instance,			\
															obj,					\
															NULL					\
														);							\
										}

#define																				\
DEL( class, this )					do												\
									{												\
										DESTRUCT		(	class, this	);			\
										_DEL			(	class, this	);			\
									} while				(	0	)



#define																			\
copy_ctor(class)					concat3				(	copy, _, class	)

#define																				\
HOWTO_CPY(class, to, from)			void copy_ctor		( class ) (	class* to,		\
																	class* from		\
																  )
#define																				\
_CPY( class, to, from )				copy_ctor			( class ) ( to, from )

#define																				\
CPY( class, to , from )				do	{											\
											if			(	!to		)				\
											{										\
												__NEW	(	class,					\
															to						\
														);							\
											}										\
																					\
											assert		(	to	);					\
																					\
											_CPY		(	class,					\
															to,						\
															from					\
														);							\
									}	while			(	0	)





/////////////////////////////////////////////////////////////////////////////////
//								INHERITANCE:
/////////////////////////////////////////////////////////////////////////////////
//
//		Inheritance is what grandpa leaves behind.
//
/////////////////////////////////////////////////////////////////////////////////


#define																				\
baseclass(module, class)			concat3(module, _, class)

#define																				\
INHERIT(module, class, ...)			struct class	{								\
										baseclass(module, class) *sdl;				\
												__VA_ARGS__							\
											}


