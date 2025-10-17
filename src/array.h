#ifndef ARRAY_H
#define ARRAY_H

#include "util.h"




#define array(class)                            concat3(class, _, array)

#define DECL_ARRAY(class, ...)                  struct array(class)

#define ARRAY(class)                            concat5(class, _, array, _, t)




#define array_init(class)                       concat3(array_init, _, class)

#define HOWTO_ARRAY_INIT(class, self)           void                                        \
                                                array_init(class) ( ARRAY(class)* self )

#define ARRAY_INIT(class, self)                 array_init(class) ( self )




#define array_reset(class)                      concat3(array_reset, _, class)

#define HOWTO_ARRAY_RESET(class, self)          void                                        \
                                                array_reset(class) ( ARRAY(class)* self )

#define ARRAY_RESET(class, self)                array_reset(class) ( self )




#define loader(class)                           concat3(load, _, class)

#define HOWTO_LOAD(class, self, array, idx)     void                                         \
                                                loader(class) (class* self,                  \
                                                               ARRAY(class)* array, int idx)

#define LOAD(class, self, array, idx)            loader(class) (self, array, idx)




#define storer(class)                           concat3(store, _, class)

#define HOWTO_STORE(class, self, array, idx)    void                                         \
                                                storer(class) (class* self,                  \
                                                               ARRAY(class)* array,          \
                                                               int idx)

#define STORE(class, self, array, idx)          storer(class) (self, array, idx)




#define pusher(class)                           concat3(push, _, class)

#define HOWTO_PUSH(class, self, array)          void                                         \
                                                pusher(class) (class* self,                  \
                                                               ARRAY(class)* array)

#define PUSH(class, self, array)                pusher(class) (self, array)




#define for_each_item_in_array(array, idx)      for (idx = 0; idx < (array)->count; idx++)




#define array_push(array, value)                                                            \
    do {                                                                                    \
        (array) = array_hold((array), 1, sizeof(*(array)));                                 \
        (array)[array_length(array) - 1] = (value);                                         \
    } while (0);


void* array_hold(void* array, int count, int item_size);

int array_length(void* array);

void array_free(void* array);

#endif
