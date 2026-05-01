/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "memory.h"
#include "iterator.h"
#include "arithmetic.h"



#define                                                                             \
DECL_ARRAY( class )                     typedef                                     \
                                        struct arr ( class )                        \
                                        {                                           \
                                            int                       size;         \
                                            int                       cap;          \
                                            class                     *data;        \
                                            itr ( class )             *begin;       \
                                            itr ( class )             *end;         \
                                        }   arr ( class )


#define                                                                             \
DECL_LIST( class )                      typedef                                     \
                                        struct lst ( class )                        \
                                        {                                           \
                                            class                     *data;        \
                                            lst ( class )             *next;        \
                                            lst ( class )             *prev;        \
                                            itr ( class )             *begin;       \
                                            itr ( class )             *end;         \
                                        }   lst ( class )


#define                                                                             \
LIST_INIT( class, self )                do  {                                       \
                                                ;                                   \
                                            }   while               (   0   )


#define                                                                             \
for_each_item_in_arr( class, _itr, _this )                                          \
for_each_item_in_cont( class, _itr, _this )


#define                                                                             \
_LD( class, _ptr, _arr, _idx )          do                                          \
                                        {                                           \
                                            class           *_loc    =   NULL;      \
                                                                                    \
                                            GET         (   ( _loc ),               \
                                                            ( _arr )->data          \
                                                        +   ( _idx );               \
                                                        );                          \
                                                                                    \
                                            CPY         (   class,                  \
                                                            ( _ptr ),               \
                                                            ( _loc )                \
                                                        );                          \
                                                                                    \
                                            PUT         (   _loc );                 \
                                                                                    \
                                        }   while       (   0   )




#define                                                                         \
LD( class, _ptr, _arr, _idx )           do                                      \
                                        {                                       \
                                            assert      (   _ptr );             \
                                                                                \
                                            _LD         (   class,              \
                                                            ( _ptr ),           \
                                                            ( _arr ),           \
                                                            ( _idx )            \
                                                        );                      \
                                                                                \
                                        }   while       (   0   )

#define                                                                         \
_STR( class, _ptr, _arr, _idx )         do                                      \
                                        {                                       \
                                            class           *_loc    =   NULL;  \
                                                                                \
                                            _loc        =   ( _arr )->data      \
                                                        +   ( _idx );           \
                                                                                \
                                            CPY         (   class,              \
                                                            ( _loc ),           \
                                                            ( _ptr )            \
                                                        );                      \
                                                                                \
                                        }   while       (   0   )


#define                                                                         \
STR( class, _ptr, _arr, _idx )          do                                      \
                                        {   assert      (   _ptr   );           \
                                                                                \
                                            _STR        (   class,              \
                                                            ( _ptr ),           \
                                                            ( _arr ),           \
                                                            ( _idx )            \
                                                        );                      \
                                                                                \
                                        }   while       (   0   )





#define                                                                         \
PUSH_FIRST( class, _arr, _ptr )         do                                      \
                                        {                                       \
                                            MCPY        (   class,              \
                                                            ( _arr )->data,     \
                                                            ( _ptr )            \
                                                        );                      \
                                                                                \
                                            ( _arr )->size  =   1;              \
                                            ( _arr )->cap   =   1;              \
                                                                                \
                                            NEW         (  itr ( class ),       \
                                                           ( _arr )->begin,     \
                                                           ( _arr )->data,      \
                                                           ( 0 ),               \
                                                           ( ARR_ITER )         \
                                                        );                      \
                                                                                \
                                            NEW         (  itr ( class ),       \
                                                           ( _arr )->end,       \
                                                           ( _arr )->data,      \
                                                           ( _arr )->size,      \
                                                           ( ARR_ITER )         \
                                                        );                      \
                                                                                \
                                        }   while           (   0    )



#define                                                                                 \
PUSH_FIXED( class, _arr, _ptr )         do                                              \
                                        {                                               \
                                            itr ( class )       *_begin  =   NULL,      \
                                                                *_end    =   NULL;      \
                                                                                        \
                                            GET             (   ( _begin ),             \
                                                                ( _arr )->begin         \
                                                            );                          \
                                                                                        \
                                            GET             (   ( _end ),               \
                                                                ( _arr )->end           \
                                                            );                          \
                                                                                        \
                                            STR             (   class,                  \
                                                               ( _ptr ),                \
                                                               ( _arr ),                \
                                                               ( _arr )->size           \
                                                            );                          \
                                                                                        \
                                            ( _arr )->size++;                           \
                                                                                        \
                                            INC             (   itr ( class ),          \
                                                                ( _end )                \
                                                            );                          \
                                                                                        \
                                            PUT             (   _begin   );             \
                                            PUT             (   _end     );             \
                                                                                        \
                                        }   while           (   0    )


#define                                                                                 \
PUSH_RSZED( class, _arr, _ptr )         do                                              \
                                        {                                               \
                                            itr ( class )       *_begin  =   NULL,      \
                                                                *_end    =   NULL;      \
                                                                                        \
                                            GET             (   ( _begin ),             \
                                                                ( _arr  )->begin        \
                                                            );                          \
                                                                                        \
                                            GET             (   ( _end ),               \
                                                                ( _arr )->end           \
                                                            );                          \
                                                                                        \
                                            RSZ             (   class,                  \
                                                                ( _arr )->data,         \
                                                                ( _arr )->cap,          \
                                                                ( _arr )->cap           \
                                                            *   ( 2 )                   \
                                                            );                          \
                                                                                        \
                                            ( _arr )->cap   *=  2;                      \
                                                                                        \
                                            INIT            (   itr ( class ),          \
                                                                ( _arr )->begin,        \
                                                                ( _arr )->data,         \
                                                                ( 0 ),                  \
                                                                ( ARR_ITER )            \
                                                            );                          \
                                                                                        \
                                            INIT            (   itr ( class ),          \
                                                                ( _arr )->end,          \
                                                                ( _arr )->data,         \
                                                                ( _arr )->size,         \
                                                                ( ARR_ITER )            \
                                                            );                          \
                                                                                        \
                                            PUSH_FIXED      (   class,                  \
                                                                ( _arr ),               \
                                                                ( _ptr )                \
                                                            );                          \
                                                                                        \
                                            PUT             (   _begin   );             \
                                            PUT             (   _end     );             \
                                                                                        \
                                        }   while           (   0    )



#define                                                                                 \
_PUSH( class, _arr, _ptr )              do                                              \
                                        {                                               \
                                            if              (   !( _arr )->data  )      \
                                            {                                           \
                                                                                        \
                                                PUSH_FIRST  (   class,                  \
                                                                ( _arr ),               \
                                                                ( _ptr )                \
                                                            );                          \
                                            }                                           \
                                            else if         (   ( _arr )->size          \
                                                            <   ( _arr )->cap           \
                                                            )                           \
                                            {                                           \
                                                                                        \
                                                PUSH_FIXED  (   class,                  \
                                                                ( _arr ),               \
                                                                ( _ptr )                \
                                                            );                          \
                                            }                                           \
                                            else                                        \
                                            {                                           \
                                                                                        \
                                                PUSH_RSZED  (   class,                  \
                                                                ( _arr ),               \
                                                                ( _ptr )                \
                                                            );                          \
                                            }                                           \
                                                                                        \
                                        }   while           (   0   )


#define                                                                                 \
PUSH( class, _arr, _ptr )               do                                              \
                                        {                                               \
                                            assert          (   _arr   );               \
                                            assert          (   _ptr   );               \
                                                                                        \
                                            _PUSH           (   class,                  \
                                                                ( _arr ),               \
                                                                ( _ptr )                \
                                                            );                          \
                                                                                        \
                                        }   while           (   0   )


#define                                                                                 \
POP( class, _arr, _ptr )               do                                               \
                                        {   LD              (   class,                  \
                                                                ( _ptr ),               \
                                                                ( _arr ),               \
                                                                ( _arr )->size - 1      \
                                                            );                          \
                                                                                        \
                                            ( _arr )->size--;                           \
                                                                                        \
                                        }   while           (   0   )


#define                                                                                 \
INITARR( class, _arr, _init_list, _count )                                              \
                                        do                                              \
                                        {                                               \
                                            ( _arr )->size  =	0;                      \
                                            ( _arr )->cap	=	0;                      \
                                                                                        \
                                            ( _arr )->data	=	NULL;                   \
                                                                                        \
                                            if			    (	_init_list && _count )  \
                                            {                                           \
                                            	const class	    *_it	=	_init_list; \
                                                                                        \
                                                ( _arr )->cap   =   _count;             \
                                                                                        \
                                            	while		(	( _arr )->size          \
                                                            !=  ( _arr )->cap	)       \
                                            	{                                       \
                                            		PUSH	(	class,                  \
                                            		    	    ( _arr ),               \
                                            				    ( _it )                 \
                                            		        );                          \
                                                                                        \
                                            		( _arr )->size++;                   \
                                                	( _it )++;                          \
                                            	}                                       \
                                            }                                           \
                                        }   while           (   0   )


#define                                                                                 \
FINIARR( class, _self )                 do                                              \
                                        {                                               \
                                            ( _self )->size =	0;                      \
                                            ( _self )->cap	=	0;                      \
                                                                                        \
                                            DEL             (   itr ( class ),          \
                                                                ( _self )->begin        \
                                                            );                          \
                                                                                        \
                                            DEL             (   itr ( class ),          \
                                                                ( _self )->end          \
                                                            );                          \
                                                                                        \
                                            DEALLOC         (   ( _self )->data         \
                                                            );                          \
                                                                                        \
                                        }   while               (   0   )


#define                                                                                 \
CPYARR( class, _to, _frm )              do                                              \
                                        {                                               \
	                                        ( _to )->size	=	( _frm )->size;         \
	                                        ( _to )->cap	=	( _frm )->cap;          \
                                                                                        \
	                                        ALLOC_ZEROED	(	class,                  \
									                            ( _to )->data,          \
									                            ( _to )->cap            \
								                            );                          \
                                                                                        \
	                                        itr ( class )		_it	=	{ 0 };          \
                                                                                        \
	                                        for_each_item_in_arr(	class,	            \
                                                                   &( _it  ),           \
                                                                    ( _frm )            \
                                                                )                       \
	                                        {                                           \
		                                        CPY			(	class,                  \
									                            ( _to  )->data	        \
                                                            +	( _it  ).pos,           \
									                            ( _frm )->data	        \
                                                            +	( _it  ).pos            \
								                            );                          \
	                                        }                                           \
                                                                                        \
	                                        NEW				(	itr ( class ),          \
									                            ( _to )->begin,         \
									                            ( _to )->data,          \
									                            ( 0 ),                  \
									                            ( ARR_ITER )            \
								                            );                          \
                                                                                        \
	                                        NEW				(	itr ( class ),          \
									                            ( _to )->end,           \
									                            ( _to )->data,          \
									                            ( _to )->size,          \
									                            ( ARR_ITER )            \
								                            );                          \
                                                                                        \
                                        }   while               (   0   )





DECL_ARRAY                              (   bool    );

DECL_ARRAY                              (   char    );

DECL_ARRAY                              (   int     );

DECL_ARRAY                              (   long    );

DECL_ARRAY                              (   float   );

DECL_ARRAY                              (   double  );



HOWTO_INIT				                (	arr ( bool ),
							            	self,
							            	const bool		    *init_list,
							            	unsigned int	    count
							            );

HOWTO_INIT				                (	arr ( char ),
							            	self,
							            	const char		    *init_list,
							            	unsigned int	    count
							            );

HOWTO_INIT				                (	arr ( int ),
							            	self,
							            	const int		    *init_list,
							            	unsigned int	    count
							            );

HOWTO_INIT					            (	arr ( long ),
								            self,
								            const long		    *init_list,
								            unsigned int	    count
							            );

HOWTO_INIT				                (	arr ( float ),
							            	self,
							            	const float		    *init_list,
							            	unsigned int	    count
							            );

HOWTO_INIT				                (	arr ( double ),
							            	self,
							            	const double	    *init_list,
							            	unsigned int	    count
							            );


HOWTO_DEF					            (	arr ( bool ),	    self	);

HOWTO_DEF					            (	arr ( char ),	    self	);

HOWTO_DEF					            (	arr ( int ),	    self	);

HOWTO_DEF					            (	arr ( long ),	    self	);

HOWTO_DEF					            (	arr ( float ),	    self	);

HOWTO_DEF					            (	arr( double ),	    self	);


HOWTO_FINI  				            (	arr ( bool ),	    self	);

HOWTO_FINI				                (	arr ( char ),	    self	);

HOWTO_FINI				                (	arr ( int ),	    self	);

HOWTO_FINI				                (	arr ( long ),	    self	);

HOWTO_FINI				                (	arr ( float ),	    self	);

HOWTO_FINI				                (	arr ( double ),	    self	);

