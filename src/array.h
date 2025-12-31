#ifndef ARRAY_H
#define ARRAY_H

#include "util.h"
#include "object.h"




#define array_push(array, value)                                                            \
    do {                                                                                    \
        (array) = array_hold((array), 1, sizeof(*(array)));                                 \
        (array)[array_length(array) - 1] = (value);                                         \
    } while (0);


void* array_hold(void* array, int count, int item_size);

int array_length(void* array);

void array_free(void* array);

#define                                                                             \
array( class )                          concat3( class, _, array )

#define                                                                             \
DECL_ARRAY( class, ... )                typedef                                     \
                                        struct array( class )                       \
                                        {    int count;                             \
                                             __VA_ARGS__                            \
                                        }   array( class )

#define                                                                             \
ARRAY( class )                          array  ( class )




#define                                                                             \
array_init( class )                     concat3( array_init, _, class )

#define                                                                             \
HOWTO_ARRAY_INIT( class, name )         void                                        \
                                        array_init ( class ) ( array(class)* name )

#define                                                                             \
ARRAY_INIT( class, name )               array_init( class ) ( name )




#define                                                                             \
array_reset( class )                    concat3( array_reset, _, class )

#define                                                                             \
HOWTO_ARRAY_RESET( class, name )        void                                        \
                                        array_reset ( class ) ( array(class) *name )

#define                                                                             \
ARRAY_RESET( class, name )              array_reset ( class ) ( name )




#define                                                                             \
loader( class )                         concat3         (   load, _, class  )

#define                                                                             \
HOWTO_LD( class, ptr, arr, idx )        void                                        \
                                        loader          (   class   )               \
                                                        (   class           *ptr,   \
                                                            array(class)    *arr,   \
                                                            int             idx     \
                                                         )

#define                                                                             \
_LD( class, ptr, arr, idx )             do                                          \
                                        {                                           \
                                            assert      (   ptr );                  \
                                                                                    \
                                            assert      (   arr );                  \
                                                                                    \
                                            loader      (   class   )               \
                                                        (   ptr,                    \
                                                            arr,                    \
                                                            idx                     \
                                                        );                          \
                                        }   while       (   0   )

#define                                                                             \
LD( class, ptr, arr, idx )              do                                          \
                                        {                                           \
                                            if          (   !ptr  )                 \
                                                DEF     (   class,                  \
                                                            ptr                     \
                                                        );                          \
                                                                                    \
                                            _LD          (  class,                  \
                                                            ptr,                    \
                                                            arr,                    \
                                                            idx                     \
                                                         );                         \
                                        }   while        (   0   )




#define                                                                             \
store( class )                          concat3         (   store,  _,  class   )

#define                                                                             \
HOWTO_STR( class, ptr, arr, idx )       void                                        \
                                        store           (   class   )               \
                                                        (   class           *ptr,   \
                                                            ARRAY ( class ) *arr,   \
                                                            int             idx     \
                                                        )

#define                                                                             \
_STR( class, ptr, arr, idx )            do                                          \
                                        {                                           \
                                            assert      (   ptr   );                \
                                            assert      (   arr   );                \
                                                                                    \
                                            store       (   class   )               \
                                                        (   ptr,                    \
                                                            arr,                    \
                                                            idx                     \
                                                        );                          \
                                        }   while       (   0   )


#define                                                                             \
STR( class, ptr, arr, idx )             do                                          \
                                        {                                           \
                                            _STR        (   class,                  \
                                                            ptr,                    \
                                                            arr,                    \
                                                            idx                     \
                                                        );                          \
                                                                                    \
                                        }   while       (   0   )




#define                                                                             \
push( class )                           concat3         (   push,   _,  class   )

#define                                                                             \
HOWTO_PUSH( class, ptr, arr )           void                                        \
                                        push            (   class   )               \
                                                        (   class           *ptr,   \
                                                            ARRAY ( class ) *arr    \
                                                        )

#define                                                                             \
_PUSH( class, ptr, arr )                do                                          \
                                        {                                           \
                                            assert      (   ptr   );                \
                                                                                    \
                                            assert      (   arr   );                \
                                                                                    \
                                            push        (   class   )               \
                                                        (   ptr,                    \
                                                            arr                     \
                                                        );                          \
                                                                                    \
                                        }   while       (   0   )


#define                                                                             \
PUSH( class, ptr, arr )                 do                                          \
                                        {                                           \
                                            _PUSH       (   class,                  \
                                                            ptr,                    \
                                                            arr                     \
                                                        );                          \
                                                                                    \
                                        }   while       (   0   )



#define                                                                             \
for_each_item_in_array( arr, idx )      for (   idx =   0;                          \
                                                idx <   ( arr )->count;             \
                                                idx++                               \
                                            )




DECL_ARRAY                              (   char,
                                            char                *ptr;
                                        );

DECL_ARRAY                              (   int,
                                            int                 *ptr;
                                        );

DECL_ARRAY                              (   long,
                                            long                *ptr;
                                        );

DECL_ARRAY                              (   float,
                                            float               *ptr;
                                        );


DECL_ARRAY                              (   double,
                                            double              *ptr;
                                        );


HOWTO_DEF                               (   ARRAY   ( char ),   self    );

HOWTO_DEF                               (   ARRAY   ( int ),    self    );

HOWTO_DEF                               (   ARRAY   ( long ),   self    );

HOWTO_DEF                               (   ARRAY   ( float ),  self    );

HOWTO_DEF                               (   ARRAY   ( double ), self    );


HOWTO_DESTRUCT                          (   ARRAY   ( char ),   self    );

HOWTO_DESTRUCT                          (   ARRAY   ( int ),    self    );

HOWTO_DESTRUCT                          (   ARRAY   ( long ),   self    );

HOWTO_DESTRUCT                          (   ARRAY   ( float ),  self    );

HOWTO_DESTRUCT                          (   ARRAY   ( double ), self    );


HOWTO_LD					            (	char,	item,	arr,	idx	);

HOWTO_LD					            (	int,	item,	arr,	idx	);

HOWTO_LD		            			(	long,	item,	arr,	idx	);

HOWTO_LD					            (	float,	item,	arr,	idx	);

HOWTO_LD					            (	double,	item,	arr,	idx	);


HOWTO_STR					            (	char,	item,	arr,	idx	);

HOWTO_STR					            (	int,	item,	arr,	idx	);

HOWTO_STR		            			(	long,	item,	arr,	idx	);

HOWTO_STR					            (	float,	item,	arr,	idx	);

HOWTO_STR					            (	double,	item,	arr,	idx	);


HOWTO_PUSH					            (	char,	item,	arr     );

HOWTO_PUSH					            (	int,	item,	arr	    );

HOWTO_PUSH		            			(	long,	item,	arr	    );

HOWTO_PUSH					            (	float,	item,	arr	    );

HOWTO_PUSH					            (	double,	item,	arr	    );


#endif

