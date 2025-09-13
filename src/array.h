#ifndef ARRAY_H
#define ARRAY_H

#include "util.h"




#define array(class)                            concat(class, _, array)

#define DECL_ARRAY(class, ...)                  struct {    int count;                      \
                                                            __VA_ARGS__    }   array(class)

#define ARRAY(class, name)                      array(class) name




#define array_init(class)                       concat(array_init, _, class)

#define HOWTO_INIT_ARRAY(class, name)           void                                        \
                                                array_init(class) ( array(class)* name )

#define INIT_ARRAY(class, name)                 array_init(class) ( name )




#define array_reset(class)                      concat(array_reset, _, class)

#define HOWTO_RESET_ARRAY(class, name)          void                                        \
                                                array_reset(class) ( array(class)* name )

#define RESET_ARRAY(class, name)                array_reset(class) ( name )




#define loader(class)                           concat(load, _, class)

#define HOWTO_LOAD(class, ptr, array, idx)      void                                        \
                                                loader(class) (class* ptr,                  \
                                                               array(class)* array, int idx)

#define LOAD(class, ptr, array, idx)            loader(class) (ptr, array, idx)




#define storer(class)                           concat(store, _, class)

#define HOWTO_STORE(class, ptr, array)          void                                        \
                                                storer(class) (class* ptr,                  \
                                                               array(class)* array)

#define STORE(class, ptr, array)                storer(class) (ptr, array)




#define for_each_item_in_array(array, idx)      for (idx = 0; idx < (array)->count; idx++)




#define array_push(array, value)                                                \
    do {                                                                        \
        (array) = array_hold((array), 1, sizeof(*(array)));                     \
        (array)[array_length(array) - 1] = (value);                             \
    } while (0);


void* array_hold(void* array, int count, int item_size);

int array_length(void* array);

void array_free(void* array);

#endif
