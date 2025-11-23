/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "object.h"


static
void
create_object						(	Object_t		*self,
										Type_t			*type,
										size_t			self_idx
									)
{
	Object_t							*parent		=	NULL;
	Type_t								*parent_t	=	NULL;
	size_t								idx			=	-1;

	MSG								(	Type_t,
										get_parent,
										type,
										parent_t
									);

	if								(	parent_t	)
	{
		MSG							(	Type_t,
										create_instance,
										parent_t,
										parent,
										&idx
									);

		create_object				(	parent,
										parent_t,
										idx
									);
		idx							=	-1;
	}

	self->parent					=	parent;
	self->type						=	type;
	self->self_idx					=	self_idx;

	void								*instance	=	NULL;

	MSG								(	Type_t,
										create_instance,
										type,
										instance,
										&idx
									);

	if								(	idx >= 0	)
	{
		self->priv					=	instance;
		self->idx					=	idx;
		self->refcount				=	0;
	}
}


void
destroy_object						(	Object_t		*self	)
{
	DEALLOC							(	self	);
}


METHOD								(	Object_t,
										create_object,
										self,
										Type_t			*type,
										size_t			idx
									)
{
	ASSERT							(	self, ""	);
	ASSERT							(	type, ""	);

	create_object					(	self,
										type,
										idx
									);
	return							(	self	);
}


METHOD								(	Object_t,
										get_instance,
										self,
										void*			ptr
									)
{
	ASSERT							(	self,
										"Invalid object\n"
									);

	ASSERT							(	!ptr,
										"ptr already holds a valid reference\n"
									);

	ptr								=	self->priv;
	self->refcount++;

	RETURN							(	self	);
}


METHOD								(	Object_t,
										put_instance,
										self,
										void			*null
									)
{
	if								(	--self->refcount == 0	)
	{
		MSG							(	Type_t,
										remove_instance,
										self->type,
										self->idx
									);

		destroy_object				(	self	);
	}

	RETURN							(	self	);
}