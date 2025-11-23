#ifndef ARRAY_H
#define ARRAY_H

#include "util.h"
#include "arithmetic.h"




typedef             struct ArrayObj             Array_t;

#define array(class)                            concat3(class, _, array)

#define DECL_ARRAY(class, ...)                  struct array(class)

#define ARRAY(class)                            concat5(class, _, array, _, t)




#define array_init(class)                       concat3(array_init, _, class)

#define HOWTO_ARRAY_INIT(class, self)           void                                        \
                                                array_init(class) ( class * self )

#define INIT(class, self)                       array_init(class) ( self )




#define array_reset(class)                      concat3(array_reset, _, class)

#define HOWTO_ARRAY_RESET(class, self)          void                                        \
                                                array_reset(class) ( class * self )

#define ARRAY_RESET(class, self)                array_reset(class) ( self )




#define loader(class)                           concat3(load, _, class)

#define                                                                                          \
HOWTO_LD( class, self, array, idx )             void                                             \
                                                loader      ( class ) ( class* self,             \
                                                                        ARRAY ( class )*  array, \
                                                                        int               idx    \
                                                                      )

#define                                                                                      \
_LD( class, self, array, idx )                  loader      ( class ) ( self, array, idx )

#define                                                                                         \
LD( class, self, array, idx )                   do                                              \
                                                {                                               \
                                                    if          (   !self    )                  \
                                                    {                                           \
                                                        DEF     (   class, self     );          \
                                                    }                                           \
                                                                                                \
                                                    assert      (   self    );                  \
                                                                                                \
                                                    _LD         (   class,                      \
                                                                    self,                       \
                                                                    array,                      \
                                                                    idx                         \
                                                                );                              \
                                                }   while       (   0   )




#define storer(class)                           concat3(store, _, class)

#define                                                                                                \
HOWTO_STR(class, self, array, idx)              void                                                   \
                                                storer        ( class ) ( class*               self,   \
                                                                          ARRAY ( class )*     array,  \
                                                                          int                  idx )

#define _STR(class, self, array, idx)           storer        ( class ) ( self, array, idx )

#define                                                                                         \
PUSH( class, item, array )                      do                                              \
                                                {                                               \
                                                    int             idx =   0;                  \
                                                                                                \
                                                    assert      (   item    );                  \
                                                                                                \
                                                    INC         (   Array_t,                    \
                                                                    array,                      \
                                                                    1,                          \
                                                                    &idx                        \
                                                                );                              \
                                                    if          (   idx >= 0    )               \
                                                    {                                           \
                                                        _STR    (   class,                      \
                                                                    item,                       \
                                                                    array,                      \
                                                                    idx                         \
                                                                );                              \
                                                    }                                           \
                                                }   while       (   0   )
#define                                                                                         \
STR( class, item, array, idx )                  do                                              \
                                                {                                               \
                                                    int          count   =   0;                 \
                                                    class        *zero   =   NULL;              \
                                                                                                \
                                                    if        (   array  )                      \
                                                    {                                           \
                                                        MSG   (   Array_t,                      \
                                                                  get_size,                     \
                                                                  array,                        \
                                                                  &count                        \
                                                               );                               \
                                                        while  (   count <= idx )               \
                                                        {                                       \
                                                            DEF     (   class, zero   );        \
                                                                                                \
                                                            PUSH    (   class,                  \
                                                                        zero,                   \
                                                                        array                   \
                                                                    );                          \
                                                            count++;                            \
                                                        }                                       \
                                                        _STR   (   class,                       \
                                                                   item,                        \
                                                                   array,                       \
                                                                   idx                          \
                                                               );                               \
                                                        DEL    (   class, zero  );              \
                                                    }                                           \
                                                }   while     (   0   )






#define counter(class)                         concat3(count, _, class)

#define HOWTO_COUNT(class, self )               int counter(class) (class* self)

#define COUNT(class, self)                      counter(class) (self)


#define for_each_item_in_array(class, item, array, idx )      for (idx = 0; idx < COUNT(class, self); idx++)




#define array_push(array, value)                                                            \
    do {                                                                                    \
        (array) = array_hold((array), 1, sizeof(*(array)));                                 \
        (array)[array_length(array) - 1] = (value);                                         \
    } while (0);


void* array_hold(void* array, int count, int item_size);

int array_length(void* array);

void array_free(void* array);




#endif
