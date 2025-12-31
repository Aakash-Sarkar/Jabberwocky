#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "object.h"




#define ARRAY_RAW_DATA(array) ((int*)(array) - 2)
#define ARRAY_CAPACITY(array) (ARRAY_RAW_DATA(array)[0])
#define ARRAY_OCCUPIED(array) (ARRAY_RAW_DATA(array)[1])



void* array_hold(void* array, int count, int item_size) {
    if (array == NULL) {
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
    return (array != NULL) ? ARRAY_OCCUPIED(array) : 0;
}

void array_free(void* array) {
    if (array != NULL) {
        free(ARRAY_RAW_DATA(array));
    }
}

HOWTO_DEF					(	ARRAY	(	char	),	self	)
{
	self->ptr				=	NULL;
	self->count				=	0;
}

HOWTO_DEF					(	ARRAY	(	int		),	self	)
{
	self->ptr				=	NULL;
    self->count				=	0;
}

HOWTO_DEF					(	ARRAY	(	long	),	self	)
{
	self->ptr				=	NULL;
	self->count				=	0;
}

HOWTO_DEF					(	ARRAY	(	float	),	self	)
{
	self->ptr				=	NULL;
	self->count				=	0;
}

HOWTO_DEF					(	ARRAY	(	double	),	self	)
{
	self->ptr				=	NULL;
	self->count				=	0;
}


HOWTO_DESTRUCT				(	ARRAY	(	char	),	self	)
{
	array_free				(	self->ptr	);

	self->ptr				=	NULL;
	self->count				=	0;
}

HOWTO_DESTRUCT				(	ARRAY	(	int		),	self	)
{
	array_free				(	self->ptr	);

	self->ptr				=	NULL;
	self->count				=	0;
}

HOWTO_DESTRUCT				(	ARRAY	(	long	),	self	)
{
	array_free				(	self->ptr	);

	self->ptr				=	NULL;
	self->count				=	0;
}

HOWTO_DESTRUCT				(	ARRAY	(	float	),	self	)
{
	array_free				(	self->ptr	);

	self->ptr				=	NULL;
	self->count				=	0;
}

HOWTO_DESTRUCT				(	ARRAY	(	double	),	self	)
{
	array_free				(	self->ptr	);

	self->ptr				=	NULL;
	self->count				=	0;
}


HOWTO_LD					(	char,	item,	arr,	idx		)
{

	assert					(	idx <=	arr->count	);

	CPY						(	char,
								item,
								arr->ptr + idx
							);
}

HOWTO_LD					(	int,	item,	arr,	idx		)
{

	assert					(	idx	<=	arr->count	);

	CPY						(	int,
								item,
								arr->ptr + idx
							);
}

HOWTO_LD					(	long,	item,	arr,	idx		)
{

	assert					(	idx <=	arr->count	);

	CPY						(	long,
								item,
								arr->ptr + idx
							);
}

HOWTO_LD					(	float,	item,	arr,	idx		)
{

	assert					(	idx <=	arr->count	);

	CPY						(	float,
								item,
								arr->ptr + idx
							);
}

HOWTO_LD					(	double,	item,	arr,	idx		)
{
	assert					(	idx	<=	arr->count	);

	CPY						(	double,
								item,
								arr->ptr + idx
							);
}


HOWTO_STR					(	char,	item,	arr,	idx		)
{
	assert					(	idx		<=	arr->count	);

	_CPY					(	char,
								arr->ptr +	idx,
								item
							);
}

HOWTO_STR					(	int,	item,	arr,	idx		)
{
	assert					(	idx		<=	arr->count	);

	_CPY					(	int,
								arr->ptr +	idx,
								item
							);
}

HOWTO_STR					(	long,	item,	arr,	idx		)
{
	assert					(	idx		<=	arr->count	);

	_CPY					(	long,
								arr->ptr +	idx,
								item
							);
}

HOWTO_STR					(	float,	item,	arr,	idx		)
{
	assert					(	idx		<=	arr->count	);

	_CPY					(	float,
								arr->ptr +	idx,
								item
							);
}

HOWTO_STR					(	double,	item,	arr,	idx		)
{
	assert					(	idx		<=	arr->count	);

	_CPY					(	double,
								arr->ptr +	idx,
								item
							);
}


HOWTO_PUSH					(	char,	item,	arr		)
{
	array_push				(	arr->ptr,
								*item
							);

	arr->count++;
}

HOWTO_PUSH					(	int,	item,	arr		)
{
	array_push				(	arr->ptr,
								*item
							);

	arr->count++;
}

HOWTO_PUSH					(	long,	item,	arr		)
{
	array_push				(	arr->ptr,
								*item
							);

	arr->count++;
}

HOWTO_PUSH					(	float,	item,	arr		)
{
	array_push				(	arr->ptr,
								*item
							);

	arr->count++;
}

HOWTO_PUSH					(	double,	item,	arr		)
{
	array_push				(	arr->ptr,
								*item
							);

	arr->count++;
}


