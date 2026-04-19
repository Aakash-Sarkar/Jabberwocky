/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#pragma once

#include "generics.h"
#include "arithmetic.h"



typedef
enum IterType {
    ARR_ITER      =   0,
    LST_ITER,
    MAX_ITER
}   IterType_t;



#define                                                                             \
DECL_ITER( class )                      typedef                                     \
                                        struct itr ( class )                        \
                                        {                                           \
                                            class                   *ptr;           \
                                            int                     pos;            \
                                            IterType_t              type;           \
                                        }   itr ( class )


#define                                                                             \
isarriter( _iter )                      (	_iter->type == ARR_ITER     )

#define                                                                             \
islstiter( _iter )                      (	_iter->type == LST_ITER     )


//#define                                                                             \
//DECL_CONT( class )                      typedef                                     \
//                                        struct cont ( class )                       \
//                                        {                                           \
//                                            itr ( class )           begin;          \
//                                            itr ( class )           end;            \
//                                                                                    \
//                                            union {                                 \
//                                                arr ( class )       _arr;           \
//                                                lst ( class )       _lst;           \
//                                            }                       _c;             \
//                                        }


#define                                                                                     \
INITITR( class, _self, _ptr, _pos,_typ )    do                                              \
                                            {                                               \
                                                assert          (   _self    );             \
                                                assert          (   _pos >= 0    );         \
                                                assert          (   _typ < MAX_ITER         \
                                                                );                          \
                                                                                            \
                                                GET             (   ( _self )->ptr,         \
                                                                    _ptr                    \
                                                                );                          \
                                                                                            \
                                                ( _self )->pos  =   _pos;                   \
                                                ( _self )->type =   _typ;                   \
                                                                                            \
                                            }   while               (   0   )


#define                                                                                     \
FINIITR( class, _self )                 do                                                  \
                                        {                                                   \
                                            PUT				 (	( _self )->ptr	);          \
                                                                                            \
                                            ( _self )->pos   =   0;                         \
                                                                                            \
                                        }   while           (   0   )



#define                                                                                    \
HOWTO_ITR( class, _it, _arr )           void                                               \
                                        iterate( class )        (   itr ( class )   *_it,  \
                                                                    arr ( class )   *_arr  \
                                                                )


#define                                                                                    \
INCITRARR( class, _iter )               do                                                 \
                                        {                                                  \
                                            ( _iter )->ptr++;                              \
                                            ( _iter )->pos++;                              \
                                        }   while               (   0   );

#define                                                                                    \
DECITRARR( class, _iter )               do                                                 \
                                        {                                                  \
                                            ( _iter )->ptr--;                              \
                                            ( _iter )->pos--;                              \
                                        }   while               (   0   );


#define                                                                                    \
CMPITR( class, _iter1, _iter2 )         return                                             \
                                        (   ( _iter1 )->ptr == ( _iter2 )->ptr  )   &&     \
                                        (   ( _iter1 )->pos == ( _iter2 )->pos  )


#define                                                                                    \
INCITRLST( class, _iter )               do                                                 \
                                        {                                                  \
                                            ( _iter )->ptr      =   ( _iter )->ptr;        \
                                            ( _iter )->pos++;                              \
                                        }   while               (   0   )


#define                                                                                    \
DECITRLST( class, _iter )               do                                                 \
                                        {                                                  \
                                            ( _iter )->ptr       =   ( _iter )->ptr;       \
                                            ( _iter )->pos--;                              \
                                        }   while               (   0   )


#define                                                                                    \
INCITR( class, _iter )                  if                      (   isarriter( _iter ) )   \
                                        {                                                  \
                                            INCITRARR           (   class,                 \
                                                                    _iter                  \
                                                                );                         \
                                        }                                                  \
                                        else if                 (   islstiter( _iter ) )   \
                                        {                                                  \
                                            INCITRLST           (   class,                 \
                                                                    _iter                  \
                                                                );                         \
                                        }                                                  \
                                        else                                               \
                                        {                                                  \
                                            /* Do Nothing */                               \
                                        }


#define                                                                                    \
DECITR( class, _iter )                  if                      (   isarriter( _iter ) )   \
                                        {                                                  \
                                            DECITRARR           (   class,                 \
                                                                    _iter                  \
                                                                );                         \
                                        }                                                  \
                                        else if                 (   islstiter( _iter ) )   \
                                        {                                                  \
                                            DECITRLST           (   class,                 \
                                                                    _iter                  \
                                                                );                         \
                                        }                                                  \
                                        else                                               \
                                        {                                                  \
                                            /* Do Nothing */                               \
                                        }


DECL_ITER                               (   bool    );

DECL_ITER                               (   char    );

DECL_ITER                               (   int     );

DECL_ITER                               (   long    );

DECL_ITER                               (   float   );

DECL_ITER                               (   double  );


HOWTO_INIT  				            (	itr ( bool ),
							            	self,
							            	const bool		*ptr,
                                            unsigned int    pos,
                                            IterType_t      typ
							            );

HOWTO_INIT	    			            (	itr ( char ),
							            	self,
							            	const char		*ptr,
                                            unsigned int    pos,
                                            IterType_t      typ
							            );


HOWTO_INIT  				            (	itr ( int ),
							            	self,
							            	const int		*ptr,
                                            unsigned int    pos,
                                            IterType_t      typ
							            );

HOWTO_INIT				                (	itr ( float ),
							            	self,
							            	const float		*ptr,
                                            unsigned int    pos,
                                            IterType_t      typ
							            );

HOWTO_INIT				                (	itr ( double ),
							            	self,
							            	const double	*ptr,
                                            unsigned int    pos,
                                            IterType_t      typ
							            );


HOWTO_FINI                              (   itr ( bool ),   self    );

HOWTO_FINI                              (   itr ( char ),   self    );

HOWTO_FINI                              (   itr ( int ),    self    );

HOWTO_FINI                              (   itr ( long ),   self    );

HOWTO_FINI                              (   itr ( float ),  self    );

HOWTO_FINI                              (   itr ( double ), self    );


HOWTO_DEF                               (   itr ( bool ),   self    );

HOWTO_DEF                               (   itr ( char ),   self    );

HOWTO_DEF                               (   itr ( int ),    self    );

HOWTO_DEF                               (   itr ( long ),   self   );

HOWTO_DEF                               (   itr ( float ),  self    );

HOWTO_DEF                               (   itr ( double ), self    );


HOWTO_CMP                               (   itr ( bool ),   it1,    it2    );

HOWTO_CMP                               (   itr ( char ),   it1,    it2    );

HOWTO_CMP                               (   itr ( int ),    it1,    it2    );

HOWTO_CMP                               (   itr ( long ),   it1,    it2    );

HOWTO_CMP                               (   itr ( float ),  it1,    it2    );

HOWTO_CMP                               (   itr ( double ), it1,    it2    );


HOWTO_INC                               (   itr ( bool ),   self    );

HOWTO_INC                               (   itr ( char ),   self    );

HOWTO_INC                               (   itr ( int ),    self    );

HOWTO_INC                               (   itr ( long ),   self    );

HOWTO_INC                               (   itr ( float ),  self    );

HOWTO_INC                               (   itr ( double ), self    );


HOWTO_DEC                               (   itr ( bool ),   self    );

HOWTO_DEC                               (   itr ( char ),   self    );

HOWTO_DEC                               (   itr ( int ),    self    );

HOWTO_DEC                               (   itr ( long ),   self    );

HOWTO_DEC                               (   itr ( float ),  self    );

HOWTO_DEC                               (   itr ( double ), self    );

