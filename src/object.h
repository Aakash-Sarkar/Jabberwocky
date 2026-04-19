/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "generics.h"


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
 //		Therefore a more managable approach would be the following:
 //
 //
 //		1.	Our application will consist of N number of objects (structs)
 //
 //		2.	Each object can take N number of different states. Each state
 //			is defined by the state (value) of its internal variables.
 //
 //		3.	Each internal variable of an object can be an object itself
 //			with its own internal state.
 //
 //		4.	In order to take an object from state A to state B, one needs
 //			to call a method of that object.
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
//						CONSTRUCTORS:
////////////////////////////////////////////////////////////////////////////////
//
//
//		Constructors are the methods through which objects are created.
//		Objects in modern applications are complex entities with lots of
//		internal state variables. Some of these variables can be objects
//		themselves with their own internal states. If any of these
//		variables are set incorrectly (or not set at all), then the object
//		will be in a inconsistent state. Calling a method on an object in
//		an inconsistent state can lead to undefined or inexplicable
//		behaviors that are hard to analyze or debug.
//
//
//		We can rely on the user to allocate the object and set each member
//		variable correctly, before calling any of its methods. But this has
//		a lot of pitfalls:
//
//
//		First, the user may only have a surface level understanding of the
//		object. She may be aware of what some of the methods are supposed
//		to do and may know of the more common internal variables. However,
//		expecting her to initialize all the internal variables correctly
//		plus be cognizant of the various pitfalls that may occur in case she
//		makes a mistake; is really too much to ask from the user.
//
//
//		Second, there are generally multiple users of an object in a modern
//		software. If you are writing a framework library, you can expect
//		multiple applications to use your object in their program for one
//		purpose or another (People typically like to avoid writing things
//		from the scratch). Therefore, the risk of making mistakes while
//		initializing the object increases significantly with each new user.
//
//
//		Therefore, most modern programming languages pin the responsibility
//		of intializing the object correctly on the class desinger (person
//		who is defining the object and its internal variables). This is done
//		through the use of constructors. While designing the object class,
//		the programmer is responsible to write a constructor method for that
//		class. This special method takes some arguments from the user and
//		create an object with a consistent initial state based on the
//		supplied arguments. The parameters requested from the user are the
//		ones that are most commonly used (or, you can omit the arguments
//		altogether, if your object can have only a single initial state).
//
//
//		Here's an example. Let's say we have an object that have more than
//		20 member variables and functions and can be used in four different
//		states:
//
//		[ BEGINNER ]
//
//		[ INTERMEDIATE ]
//
//		[ EXPERT ]
//
//		[ EXPERIMENTAL ]
//
//		In |BEGINNER| state we only expose the most basic functions to the
//		user but hide away the rest of the functions. In |EXPERT| state we
//		allow the user to call all the available functions and use all the
//		complex features of the object. In |EXPERIMENTAL| state, we also
//		expose to the user the experimental featrues that are not yet fully
//		tested to work on all systems.
//
//
//		Instead of asking the user to provide the initial value of all the
//		20 member variables, or keep four differernt copies of the same
//		class; we can instead ask the user to provide one of the above 4
//		states; and based on the state provided we can set each of the
//		variables ourselves.
//
//
///////////////////////////////////////////////////////////////////////////////



#define																				\
HOWTO_INIT( class, self, ... )					void								\
												init ( class )	( class *self,		\
																	__VA_ARGS__		\
																)

#define																				\
_INIT( class, self, ... )						init ( class )( self,__VA_ARGS__ )

#define																				\
INIT( class, self, ... )						do									\
												{									\
													assert		(	self	);		\
																					\
													_INIT		(	class,			\
																	self,			\
																__VA_ARGS__ );		\
																					\
												} while			(	0	)

#define																				\
HOWTO_FINI( class, self )						void								\
												fini ( class )	( class* self )


#define																				\
FINI( class, self )								fini ( class )	( self )




#define																				\
GET( to, from )								do										\
											{										\
												to				=	from;			\
											}	while			(	0	)

#define																				\
PUT( ptr )									do										\
											{										\
												ptr				=	NULL;			\
											}	while			(	0	)



/////////////////////////////////////////////////////////////////////////////////
//								INHERITANCE:
/////////////////////////////////////////////////////////////////////////////////
//
//		Inheritance is what grandpa leaves behind.
//
/////////////////////////////////////////////////////////////////////////////////

#define																			\
baseclass( module, class )				concat3 ( module, _, class )

#define																			\
INHERIT( module, class, name, ... )		struct class	{						\
											baseclass(module, class) *name;		\
											__VA_ARGS__							\
										}


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
//		behavior with its state. i.e. how the object behaves is defined solely
//		by the member variables inside the object boundary.
//		
//
/////////////////////////////////////////////////////////////////////////////////




#define																				\
method( class, name )				concat3 (	class, _, name	)

#define																				\
METHOD(class, name, self, ...)		class*											\
									method	( class, name ) (	class*	self,		\
																__VA_ARGS__			\
															)



/////////////////////////////////////////////////////////////////////////////////
//
//
//		A useful mental model for visualizing the state-behavior relationship
//		is to think of an object as a piece of a hardware ( like an AND gate ).
//
//
//									 -----------			
//									:			+----- out1	
//									:			|			
//						in1	--------+			+----- out2	
//									:	MUX		|			
//						in2	--------+			+----- out3	
//									:			|		
//									:			+----- out4	
//									 -----------			
//
//
//		The above diagram depicts a multiplexer that has two input lines and
//		four output lines. At any point in time the state of the output lines
//		is completely defined by the state of the two input lines. If we need
//		to change the output lines to something else, we need to set the in
//		lines appropriately and the next clock cyle the out lines will update
//		accordingly. The two input lines and four output lines above defines
//		the state of our multiplexer, and how the out lines are set depending
//		on the in lines defines its behavior.
//
// 
//						class	MUX
// 						{
//							public:
// 								void reset( int in  )
// 								void set  ( int in  );
//								bool get  ( int out );
//
// 							private:
// 								bool in[2];
// 								bool out[4];
// 						}
// 
// 
//		The above diagram is a programming language representation of this
//		unit. The member variables in[2] and out[4] defines the state of our
//		unit. Whereas, the implementation of the methods set, reset and get
//		defines its behavior. By marking the member variables as private, we
//		are in effect cutting the access to these memory addresses from the
//		outside world. The only way change the inputs is to use the set and
//		reset methods. And the only way to read the outputs is to use the get
//		method.
// 
// 
/////////////////////////////////////////////////////////////////////////////////


#define																				\
_REQ( class, name, self, ... )			(	self			=	method				\
															(	class,	name	)	\
															(	self,	__VA_ARGS__	\
															)						\
										)	


#define																				\
REQ( class, name, self, ... )			do											\
										{											\
											assert			(	self	);			\
																					\
											_REQ			(	class,				\
																name,				\
																self,				\
															__VA_ARGS__				\
															);						\
																					\
										}	while			(	0	)




HOWTO_INIT								(	bool,
											self,
											bool	b
										);

HOWTO_INIT								(	char,
											self,
											char	c
										);

HOWTO_INIT								(	int,
											self,
											int		i
										);

HOWTO_INIT								(	long,
											self,
											long	l
										);

HOWTO_INIT								(	float,
											self,
											float	f
										);

HOWTO_INIT								(	double,
											self,
											double	d
										);


HOWTO_FINI								(	bool,
											self
										);

HOWTO_FINI								(	char,
											self
										);

HOWTO_FINI								(	int,
											self
										);

HOWTO_FINI								(	long,
											self
										);

HOWTO_FINI								(	float,
											self
										);

HOWTO_FINI								(	double,
											self
										);


