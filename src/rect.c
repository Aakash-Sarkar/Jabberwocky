/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include <stdbool.h>

#include "rect.h"
#include "util.h"


/*
 * This function checks whether the pixel falls within the rectangle border
 */
bool
pixel_at_border				(	Rect_t*		rect,
								int			posX,
								int			posY,
								int			border_len	)
{

	bool						is_border = (((	posX - rect->posX	)
											< border_len	)
										||	((	posY - rect->posY	)
											< border_len	)
										||	(( rect->posX + rect->width		- 1) - posX	)
											< border_len
										||	(( rect->posY + rect->height	- 1) - posY	)
											< border_len	);

	RETURN					(	is_border	);
}

static
void
normalize_rect				(	Rect_t*			rect,
								Color_buffer_t*	colorbuf	)
{

	if						((	rect->posX + rect->width	) > colorbuf->width	)
	{
		int						del	= ((	rect->posX + rect->width	)
											- colorbuf->width + 1	);
		rect->width			-=	del;
	}

	if						(	rect->posY + rect->height > colorbuf->height	)
	{
		int						del = (	rect->posY + rect->height
										- colorbuf->height + 1	);
		rect->height		-=	del;
	}
	return;
}

bool
paint_rect					(	Rect_t*			rect,
								Color_t*		interior_color,
								Color_t*		border_color,
								Color_buffer_t*	colorbuf,
								int				border_len	)
{
	DECLARE_PTR				(	color,	Color_t,	NULL	);

	bool						ret	= FAIL;

	if						(	!rect	||	!border_color
										||	!interior_color	)
	{
		LOG					(	"Invalid args\n"	);
		RETURN				(	FAIL	);
	}

	if						(	border_len < 0	)
		border_len			=	0;

	normalize_rect			(	rect, colorbuf	);

	int							posX = 0,
								posY = 0;

	for_each_posY_in_rect	(	rect, posY	)
		for_each_posX_in_rect	(	rect, posX	)
		{
			// Are we at the border, Sergeant?
			color			=	(	pixel_at_border (	rect,
														posX, posY,
														border_len	))
								? border_color : interior_color;

			ret				=	paint_color (	color,
												colorbuf,
												posX, posY,
												0	);

			if				(	ret != SUCCESS	)
			{
				LOG			(	"Failed to paint color at posX : %d, posY : %d",
								posX, posY	);
				RETURN		(	FAIL	);
			}
		}

	// Use the force, Luke!
	return SUCCESS;
}

bool
draw_rectangle				(	Color_buffer_t*		colorbuf,
								Rect_t*				rect	)
{

	DECLARE_PTR				(	border,		Color_t,	NULL	);
	DECLARE_PTR				(	interior,	Color_t,	NULL	);

	bool						ret = FAIL;

	// Construct border color
	CONSTRUCT				(	border,
								Color_t,
								0xFF,
								0xFF,
								0x00,
								0xFF,
								PIXELFORMAT_ARGB8888	);

	if						(	!border	)
	{
		LOG					(	"Failed to create border color"	);
		RETURN				(	FAIL	);
	}

	// Construct interior color
	CONSTRUCT				(	interior,
								Color_t,
								0xFF,
								0xFF,
								0x00,
								0xFF,
								PIXELFORMAT_ARGB8888	);

	if						(	!interior	)
	{
		LOG					(	"Failed to create border color"	);
		RETURN				(	FAIL	);
	}

	ret						=	paint_rect (	rect,
												interior, border,
												colorbuf, 1	);

	if						(	ret != SUCCESS	)
	{
		LOG					(	"Failed to draw rectangle\n"	);
		RETURN				(	FAIL	);
	}

	// Destroy border color
	DESTRUCT				(	border, Color_t	);

	// Destroy interior color
	DESTRUCT				(	interior , Color_t	);

	// Use the force, Luke!
	return SUCCESS;
}

bool
draw_grid					(	Color_buffer_t* colorbuf	)
{
	Rect_t						rect		= { 0 };

	int							posX		= 0,
								posY		= 0,
								n			= 0,
								border_len	= 1;

	bool						ret			= FAIL;

	Color_t						*border		= NULL,
								*interior	= NULL;

	// Create border color
	CONSTRUCT				(	border,
								Color_t,
								0xF0,
								0xF0,
								0xF0,
								0xFF,
								PIXELFORMAT_ARGB8888	);

	if						(	!border	)
	{
		LOG					(	"Failed to create border color\n"	);
		RETURN				(	FAIL	);
	}

	// Create interior color
	CONSTRUCT				(	interior,
								Color_t,
								0x20,
								0x20,
								0x20,
								0xFF,
								PIXELFORMAT_ARGB8888	);

	if						(	!interior	)
	{
		LOG					(	"Failed to create interior color\n"	);
		RETURN				(	FAIL	);
	}

	rect.posX				=	posX;
	rect.posY				=	posY;
	rect.width				=	50;
	rect.height				=	50;

	for_each_rect_in_buffer	(	n, &rect, colorbuf	)
	{
		ret					=	paint_rect(	&rect,
											interior, border,
											colorbuf, 1	);

		if					(	ret != SUCCESS	)
		{
			LOG				(	"Failed to draw rectangle\n"	);
			RETURN			(	FAIL	);
		}
	}

	// Destroy colors
	DESTRUCT				(	border,		Color_t	);
	DESTRUCT				(	interior,	Color_t	);

	// Use the force, Luke!
	return SUCCESS;
}
