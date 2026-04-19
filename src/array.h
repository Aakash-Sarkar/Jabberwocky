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
                                        }


#define                                                                             \
LIST_INIT( class, self )                do  {                                       \
                                                ;                                   \
                                            }   while               (   0   )


#define                                                                             \
array_reset( class )                    concat3( array_reset, _, class )

#define                                                                             \
HOWTO_ARRAY_RESET( class, name )        void                                        \
                                        array_reset ( class ) ( arr( class ) *name )

#define                                                                             \
ARRAY_RESET( class, name )              array_reset ( class ) ( name )



#define                                                                             \
_LD( class, _ptr, _arr, _idx )          do                                          \
                                        {                                           \
                                            class           *loc    =   NULL;       \
                                                                                    \
                                            GET         (   loc,                    \
                                                            ( _arr )->data  + _idx; \
                                                        );                          \
                                                                                    \
                                            CPY         (   class,                  \
                                                          ( _ptr ),                 \
                                                          ( loc )                   \
                                                        );                          \
                                                                                    \
                                            PUT         (   loc );                  \
                                                                                    \
                                        }   while       (   0   )




#define                                                                             \
LD( class, _ptr, _arr, _idx )           do                                          \
                                        {                                           \
                                            assert      (   _ptr );                 \
                                                                                    \
                                            _LD         (   class,                  \
                                                           ( _ptr ),                \
                                                           ( _arr ),                \
                                                           ( _idx )                 \
                                                        );                          \
                                                                                    \
                                        }   while       (   0   )



#define                                                                             \
_STR( class, _ptr, _arr, _idx )         do                                          \
                                        {                                           \
                                            class           *loc    =   NULL;       \
                                                                                    \
                                            loc         =   ( _arr )->data + _idx;  \
                                                                                    \
                                            CPY         (   class,                  \
                                                            loc,                    \
                                                            _ptr                    \
                                                        );                          \
                                                                                    \
                                        }   while       (   0   )


#define                                                                             \
STR( class, _ptr, _arr, _idx )          do                                          \
                                        {                                           \
                                            assert      (   _ptr   );               \
                                                                                    \
                                            _STR        (   class,                  \
                                                            ( _ptr ),               \
                                                            ( _arr ),               \
                                                            ( _idx )                \
                                                        );                          \
                                        }   while       (   0   )





#define                                                                                 \
PUSH_FIRST( class, _ptr, _arr )         do                                              \
                                        {                                               \
                                                                                        \
                                            MCPY            (   class,                  \
                                                              ( _arr )->data,           \
                                                              ( _ptr )                  \
                                                            );                          \
                                                                                        \
                                            ( _arr )->size   =   1;                     \
                                            ( _arr )->cap    =   1;                     \
                                                                                        \
                                            NEW             (    itr ( class ),         \
                                                               ( _arr )->begin,         \
                                                               ( _arr )->data,          \
                                                               ( 0 ),                   \
                                                               ( ARR_ITER )             \
                                                            );                          \
                                                                                        \
                                            NEW             (    itr ( class ),         \
                                                               ( _arr )->end,           \
                                                               ( _arr )->data  +        \
                                                               ( _arr )->size,          \
                                                               ( _arr )->size,          \
                                                                ARR_ITER                \
                                                            );                          \
                                                                                        \
                                        }   while           (   0    )



#define                                                                                 \
PUSH_FIXED( class, _ptr, _arr )         do                                              \
                                        {                                               \
                                            itr ( class )       *begin  =   NULL,       \
                                                                *end    =   NULL;       \
                                                                                        \
                                            GET             (   ( begin ),              \
                                                                ( _arr )->begin         \
                                                            );                          \
                                                                                        \
                                            GET             (   ( end ),                \
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
                                                                end                     \
                                                            );                          \
                                                                                        \
                                            PUT             (   begin   );              \
                                            PUT             (   end     );              \
                                                                                        \
                                        }   while           (   0    )


#define                                                                                 \
PUSH_RSZED( class, _ptr, _arr )         do                                              \
                                        {                                               \
                                            itr ( class )       *begin  =   NULL,       \
                                                                *end    =   NULL;       \
                                                                                        \
                                            GET             (   ( begin ),              \
                                                                ( _arr  )->begin        \
                                                            );                          \
                                                                                        \
                                            GET             (   ( end  ),               \
                                                                ( _arr )->end           \
                                                            );                          \
                                                                                        \
                                                                                        \
                                            RSZ             (   class,                  \
                                                              ( _arr )->data,           \
                                                              ( _arr )->cap,            \
                                                              ( _arr )->cap * 2         \
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
                                                                ( _arr )->data  +       \
                                                                ( _arr )->size,         \
                                                                ( _arr )->size,         \
                                                                ( ARR_ITER )            \
                                                            );                          \
                                                                                        \
                                            PUSH_FIXED      (   class,                  \
                                                                ( _ptr ),               \
                                                                ( _arr )                \
                                                            );                          \
                                                                                        \
                                            PUT             (   begin   );              \
                                            PUT             (   end     );              \
                                                                                        \
                                        }   while           (   0    )



#define                                                                                 \
_PUSH( class, _ptr, _arr )              do                                              \
                                        {                                               \
                                            if              (   !( _arr )->data  )      \
                                            {                                           \
                                                PUSH_FIRST  (   class,                  \
                                                                ( _ptr ),               \
                                                                ( _arr )                \
                                                            );                          \
                                            }                                           \
                                            else if         (   ( _arr )->size   <      \
                                                                ( _arr )->cap           \
                                                            )                           \
                                            {                                           \
                                                PUSH_FIXED  (   class,                  \
                                                                ( _ptr ),               \
                                                                ( _arr )                \
                                                            );                          \
                                            }                                           \
                                            else                                        \
                                            {                                           \
                                                PUSH_RSZED  (   class,                  \
                                                                ( _ptr ),               \
                                                                ( _arr )                \
                                                            );                          \
                                            }                                           \
                                                                                        \
                                        }   while           (   0   )


#define                                                                             \
PUSH( class, _ptr, _arr )               do                                          \
                                        {                                           \
                                            assert          (   _ptr   );           \
                                                                                    \
                                            _PUSH           (   class,              \
                                                                ( _ptr ),           \
                                                                ( _arr )            \
                                                            );                      \
                                                                                    \
                                        }   while       (   0   )


#define                                                                                     \
INITARR( class, _self, _init_list, _count )                                                 \
                                        do                                                  \
                                        {                                                   \
                                            ( _self )->size     =	0;                      \
                                            ( _self )->cap	    =	0;                      \
                                                                                            \
                                            ( _self )->data	    =	NULL;                   \
                                                                                            \
                                            if			        (	_init_list && _count )  \
                                            {                                               \
                                                                                            \
                                            	const class	        *it		=	_init_list; \
                                                                                            \
                                                ( _self )->cap  =   _count;                 \
                                                                                            \
                                            	while		    (	( _self )->size !=      \
                                                                    ( _self )->cap	)       \
                                            	{                                           \
                                            		PUSH	    (	class,                  \
                                            					    ( it ),                 \
                                            					    ( _self )               \
                                            			        );                          \
                                                                                            \
                                            		( _self )->size++;                      \
                                                	it++;                                   \
                                            	}                                           \
                                            }                                               \
                                        }   while           (   0   )


#define                                                                                     \
FINIARR( class, _self )                 do                                                  \
                                        {                                                   \
                                            ( _self )->size     =	0;                      \
                                            ( _self )->cap	    =	0;                      \
                                                                                            \
                                            DEL                 (   itr ( class ),          \
                                                                    ( _self )->begin        \
                                                                );                          \
                                                                                            \
                                            DEL                 (   itr ( class ),          \
                                                                    ( _self )->end          \
                                                                );                          \
                                                                                            \
                                            DEALLOC             (   ( _self )->data         \
                                                                );                          \
                                                                                            \
                                        }   while               (   0   )

//#define                                                                             \
//for_each_item_in_array( class, item, arr, idx )                                     \
//                                        for (                                       \
//                                                idx     =   0,                      \
//                                                                                    \
//                                                __LD    (   class,                  \
//                                                            item,                   \
//                                                            arr,                    \
//                                                            idx                     \
//                                                        );                          \
//                                                                                    \
//                                                idx     <   ( arr )->count;         \
//                                                                                    \
//                                                idx++,                              \
//                                                __LD    (   class,                  \
//                                                            item,                   \
//                                                            arr,                    \
//                                                            idx                     \
//                                                        )                           \
//                                            )


#define                                                                                     \
for_each_item_in_array( class, _iter, _arr )                                                \
                                        for (   (   CP          (   itr ( class ),          \
                                                                    _iter,                  \
                                                                    ( _arr )->begin         \
                                                                )                           \
                                                );                                          \
                                                                                            \
                                                (   !CMP        (   itr ( class ),          \
                                                                    _iter,                  \
                                                                  ( _arr )->end             \
                                                                )                           \
                                                );                                          \
                                                                                            \
                                                (   INC         (   itr ( class ),          \
                                                                    _iter                   \
                                                                )                           \
                                                )                                           \
                                            )



DECL_ARRAY                              (   bool    );

DECL_ARRAY                              (   char    );

DECL_ARRAY                              (   int     );

DECL_ARRAY                              (   long    );

DECL_ARRAY                              (   float   );

DECL_ARRAY                              (   double  );



HOWTO_INIT				                (	arr ( bool ),
							            	self,
							            	const bool		*init_list,
							            	unsigned int	count
							            );

HOWTO_INIT				                (	arr ( char ),
							            	self,
							            	const char		*init_list,
							            	unsigned int	count
							            );

HOWTO_INIT				                (	arr ( int ),
							            	self,
							            	const int		*init_list,
							            	unsigned int	count
							            );

HOWTO_INIT					            (	arr ( long ),
								            self,
								            const long		*init_list,
								            unsigned int	count
							            );

HOWTO_INIT				                (	arr ( float ),
							            	self,
							            	const float		*init_list,
							            	unsigned int	count
							            );

HOWTO_INIT				                (	arr ( double ),
							            	self,
							            	const double	*init_list,
							            	unsigned int	count
							            );


HOWTO_DEF					            (	arr ( bool ),	self	);

HOWTO_DEF					            (	arr ( char ),	self	);

HOWTO_DEF					            (	arr ( int ),	self	);

HOWTO_DEF					            (	arr ( long ),	self	);

HOWTO_DEF					            (	arr ( float ),	self	);

HOWTO_DEF					            (	arr( double ),	self	);


HOWTO_FINI  				            (	arr ( bool ),	self	);

HOWTO_FINI				                (	arr ( char ),	self	);

HOWTO_FINI				                (	arr ( int ),	self	);

HOWTO_FINI				                (	arr ( long ),	self	);

HOWTO_FINI				                (	arr ( float ),	self	);

HOWTO_FINI				                (	arr ( double ),	self	);

