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
isarriter( _itr )                      (	_itr->type == ARR_ITER     )

#define                                                                             \
islstiter( _itr )                      (	_itr->type == LST_ITER     )

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
                                                assert          (   _pos    >=  0  );       \
                                                assert          (   _typ < MAX_ITER         \
                                                                );                          \
                                                                                            \
                                                GET             (   ( _self )->ptr,         \
                                                                    ( _ptr )                \
                                                                +   ( _pos )                \
                                                                );                          \
                                                                                            \
                                                ( _self )->pos  =   _pos;                   \
                                                ( _self )->type =   _typ;                   \
                                                                                            \
                                            }   while               (   0   )


#define                                                                                     \
FINIITR( class, _self )                 do                                                  \
                                        {                                                   \
                                            PUT				    (	( _self )->ptr	);      \
                                                                                            \
                                            ( _self )->pos      =   0;                      \
                                                                                            \
                                        }   while               (   0   )


#define                                                                                    \
INCITRARR( class, _itr )               do                                                  \
                                        {                                                  \
                                            ( _itr )->ptr++;                               \
                                            ( _itr )->pos++;                               \
                                        }   while               (   0   );

#define                                                                                    \
DECITRARR( class, _itr )                do                                                 \
                                        {                                                  \
                                            ( _itr )->ptr--;                               \
                                            ( _itr )->pos--;                               \
                                        }   while               (   0   );


#define                                                                                    \
CMPITR( class, _itr1, _itr2 )           do                                                 \
                                        {                                                  \
                                            bool                    res =  false;          \
                                                                                           \
                                            res                 =   (   ( _itr1 )->ptr     \
                                                                ==      ( _itr2 )->ptr     \
                                                                    )                      \
                                                                &&  (   ( _itr1 )->pos     \
                                                                ==      ( _itr2 )->pos     \
                                                                    );                     \
                                                                                           \
                                            RET                 (   res );                 \
                                                                                           \
                                        }   while               (   0   )


#define                                                                                    \
INCITRLST( class, _itr )                do                                                 \
                                        {                                                  \
                                            ( _itr )->ptr       =   ( _itr )->ptr;         \
                                            ( _itr )->pos++;                               \
                                        }   while               (   0   )


#define                                                                                    \
DECITRLST( class, _itr )                do                                                 \
                                        {                                                  \
                                            ( _itr )->ptr       =   ( _itr )->ptr;         \
                                            ( _itr )->pos--;                               \
                                        }   while               (   0   )


#define                                                                                    \
INCITR( class, _itr )                   if                      (   isarriter( _itr ) )    \
                                        {                                                  \
                                            INCITRARR           (   class,                 \
                                                                    _itr                   \
                                                                );                         \
                                        }                                                  \
                                        else if                 (   islstiter( _itr ) )    \
                                        {                                                  \
                                            INCITRLST           (   class,                 \
                                                                    _itr                   \
                                                                );                         \
                                        }                                                  \
                                        else                                               \
                                        {                                                  \
                                            /* Do Nothing */                               \
                                        }


#define                                                                                    \
DECITR( class, _itr )                   if                      (   isarriter( _itr ) )    \
                                        {                                                  \
                                            DECITRARR           (   class,                 \
                                                                    _itr                   \
                                                                );                         \
                                        }                                                  \
                                        else if                 (   islstiter( _itr ) )    \
                                        {                                                  \
                                            DECITRLST           (   class,                 \
                                                                    _itr                   \
                                                                );                         \
                                        }                                                  \
                                        else                                               \
                                        {                                                  \
                                            /* Do Nothing */                               \
                                        }


#define                                                                                     \
for_each_item_in_cont( class, _itr, _this )                                                 \
                                        for (   (   CP          (   itr ( class ),          \
                                                                    ( _itr ),               \
                                                                    ( _this )->begin        \
                                                                )                           \
                                                );                                          \
                                                                                            \
                                                (   !CMP        (   itr ( class ),          \
                                                                    ( _itr ),               \
                                                                    ( _this )->end          \
                                                                )                           \
                                                );                                          \
                                                                                            \
                                                (   INC         (   itr ( class ),          \
                                                                    ( _itr )                \
                                                                )                           \
                                                )                                           \
                                            )

#define                                                                                     \
ITR( class, _itr, _this )                   itr ( class )           _itr = { 0 };           \
                                                                                            \
                                            for_each_item_in_cont( class, &(_itr), _this )


DECL_ITER                               (   bool    );

DECL_ITER                               (   char    );

DECL_ITER                               (   int     );

DECL_ITER                               (   long    );

DECL_ITER                               (   float   );

DECL_ITER                               (   double  );


HOWTO_INIT  				            (	itr ( bool ),
							            	self,
							            	const bool		        *ptr,
                                            unsigned int            pos,
                                            IterType_t              typ
							            );

HOWTO_INIT	    			            (	itr ( char ),
							            	self,
							            	const char		        *ptr,
                                            unsigned int            pos,
                                            IterType_t              typ
							            );


HOWTO_INIT  				            (	itr ( int ),
							            	self,
							            	const int		        *ptr,
                                            unsigned int            pos,
                                            IterType_t              typ
							            );

HOWTO_INIT				                (	itr ( float ),
							            	self,
							            	const float		        *ptr,
                                            unsigned int            pos,
                                            IterType_t              typ
							            );

HOWTO_INIT				                (	itr ( double ),
							            	self,
							            	const double	        *ptr,
                                            unsigned int            pos,
                                            IterType_t              typ
							            );


HOWTO_FINI                              (   itr ( bool ),           self    );

HOWTO_FINI                              (   itr ( char ),           self    );

HOWTO_FINI                              (   itr ( int ),            self    );

HOWTO_FINI                              (   itr ( long ),           self    );

HOWTO_FINI                              (   itr ( float ),          self    );

HOWTO_FINI                              (   itr ( double ),         self    );


HOWTO_DEF                               (   itr ( bool ),           self    );

HOWTO_DEF                               (   itr ( char ),           self    );

HOWTO_DEF                               (   itr ( int ),            self    );

HOWTO_DEF                               (   itr ( long ),           self   );

HOWTO_DEF                               (   itr ( float ),          self    );

HOWTO_DEF                               (   itr ( double ),         self    );


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

