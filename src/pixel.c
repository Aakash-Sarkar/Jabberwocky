/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "pixel.h"




struct Pixel				{	uint32_t	color;
								int			posX;
								int			posY;
							};


DECL_ARRAY ( Pixel_t )		{	uint32_t *	color;
								int *		posX;
								int *		posY;
								int			count;
							};


struct Image				{	ARRAY ( Pixel_t ) *	pixels;
								Rect_t *			rect;
								Format_type_t		format_type;
								int					size;
							};


struct Patch				{	ARRAY ( Pixel_t ) *	pixels;	};




HOWTO_CONSTRUCT				(	Pixel_t,
								self,
								uint32_t	color,
								int			posX,
								int			posY
							)
{
	self->color				=	color;
	self->posX				=	posX;
	self->posY				=	posY;

	RETURN					(	self	);
}

HOWTO_CPY					(	Pixel_t,	to,	from	)
{
	to->color				=	from->color;
	to->posX				=	from->posX;
	to->posY				=	from->posY;
}

HOWTO_ARRAY_INIT			(	ARRAY ( Pixel_t ),	self	)
{
	self->color				=	EMPTY;
	self->posX				=	EMPTY;
	self->posY				=	EMPTY;

	self->count				=	0;
}

HOWTO_ARRAY_RESET			(	ARRAY( Pixel_t ),	self	)
{
	array_free				(	self->color	);
	array_free				(	self->posX	);
	array_free				(	self->posY	);

	ARRAY_INIT				(	ARRAY ( Pixel_t ),	self	);
}

HOWTO_CONSTRUCT				(	ARRAY ( Pixel_t ),	self,	void* null	)
{
	INIT					(	ARRAY ( Pixel_t ), self	);
}

HOWTO_LD					(	Pixel_t,	self,	array,	idx	)
{
	self->color				=	array->color [ idx ];
	self->posX				=	array->posX  [ idx ];
	self->posY				=	array->posY  [ idx ];
}

HOWTO_STR					(	Pixel_t,	self,	array,	idx	)
{
	array->color[idx]		=	self->color;
	array->posX [idx]		=	self->posX;
	array->posY [idx]		=	self->posY;
}


HOWTO_CONSTRUCT				(	Image_t,
								self,
								int				posX,
								int				posY,
								int				width,
								int				height,
								Format_type_t	format_type
							)
{
}

HOWTO_CPY					(	Image_t,	to,	from	)
{
}