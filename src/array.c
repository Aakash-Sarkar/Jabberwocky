#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "object.h"
#include "operation.h"

#define ARRAY_RAW_DATA(array) ((int*)(array) - 2)
#define ARRAY_CAPACITY(array) (ARRAY_RAW_DATA(array)[0])
#define ARRAY_OCCUPIED(array) (ARRAY_RAW_DATA(array)[1])

void* array_hold(void* array, int count, int item_size) {
    if (array == EMPTY) {
        int raw_size = (sizeof(int) * 2) + (item_size * count);
        int* base = (int*)malloc(raw_size);
        base[0] = count;  // capacity
        base[1] = count;  // occupied
        return base + 2;
    } else if (ARRAY_OCCUPIED(array) + count <= ARRAY_CAPACITY(array)) {
        ARRAY_OCCUPIED(array) += count;
        return array;
    } else {
        int needed_size = ARRAY_OCCUPIED(array) + count;
        int double_curr = ARRAY_CAPACITY(array) * 2;
        int capacity = needed_size > double_curr ? needed_size : double_curr;
        int occupied = needed_size;
        int raw_size = sizeof(int) * 2 + item_size * capacity;
        int* base = (int*)realloc(ARRAY_RAW_DATA(array), raw_size);
        base[0] = capacity;
        base[1] = occupied;
        return base + 2;
    }
}

int array_length(void* array) {
    return (array != EMPTY) ? ARRAY_OCCUPIED(array) : 0;
}

void array_free(void* array) {
    if (array != EMPTY) {
        free(ARRAY_RAW_DATA(array));
    }
}

struct ArrayObj
{
    void                    **rawptr;
    int                     count;
    int                     capacity;
};

HOWTO_CONSTRUCT         (   ArrayObj_t,
                            self,
                            TypeCode_t      type,
                            int             capacity
                        )
{
    Unit_t                  *array      =   lookup_unit (    self->type    );
    Unit_t                  *unit       =   lookup_unit (    type    );

    ArrayObj_t              *instance   =   EMPTY;

    char                    *rawptr     =   EMPTY;

    CALLM               (   Unit_t,
                            create_instance,
                            array,
                            instance
                        );

    instance->count     =   0;
    instance->capacity  =   0;
    instance->rawptr    =   EMPTY;

    if                  (   capacity    >   0    )
    {
        ALLOC_ZEROED    (   char *,
                            instance->rawptr,
                            capacity
                        );

        rawptr          =   instance->rawptr;

        while           (   capacity--   >   0    )
        {

            MSG         (   Unit_t,
                            create_instance,
                            unit,
                            *rawptr++
                        );

            instance->capacity++;
        }
    }

    self->priv          =   instance;

    RETURN              (   self    );
}
