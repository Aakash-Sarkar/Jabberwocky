/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "rect.h"


/*
 * This function checks whether the pixel falls within the rectangle border
 */
bool
pixel_at_border			(	Rect_t*		rect,
							int			posX,
							int			posY,
							int			border_len	)
{

	bool					is_border = (( (	posX - rect->posX	) < border_len )
									||   ( (	posY - rect->posY	) < border_len )
									||   ( (	rect->posX + rect->width  - 1	)
												- posX )  < border_len
									||   ( (	rect->posY + rect->height - 1	)
												- posY	) < border_len
										);

	RETURN				(	is_border	);
}

static
void
normalize_rect					(	Rect_t*			rect,
									Color_buffer_t*	colorbuf	)
{

	if							((	rect->posX + rect->width	) > colorbuf->width	)
	{
		int							del	= ((	rect->posX	+	rect->width		)
												- colorbuf->width + 1	);
		rect->width				-=	del;
	}

	if							(	rect->posY + rect->height > colorbuf->height	)
	{
		int							del = (	rect->posY + rect->height
											- colorbuf->height + 1	);
		rect->height			-=	del;
	}
	return;
}

static
bool
paint_rect						(	Rect_t*			rect,
									Color_t*		interior_color,
									Color_t*		border_color,
									Color_buffer_t*	colorbuf,
									int				border_len	)
{
	PTR							(	Color_t,		color,	NULL	);

	bool							ret	= FAIL;

	if							(	!rect	||	!border_color
											||	!interior_color	)
	{
		LOG						(	"Invalid args\n"	);
		RETURN					(	FAIL	);
	}

	if							(	border_len < 0	)
		border_len				=	0;

	normalize_rect				(	rect,	colorbuf	);

	int								posX = 0,
									posY = 0;

	for_each_posY_in_rect		(	rect,	posY	)
		for_each_posX_in_rect	(	rect,	posX	)
		{
			// Are we at the border, Sergeant?
			color				= (	pixel_at_border (	rect,
														posX, posY,
														border_len	))
									? border_color : interior_color;

			ret					=	paint_color		(	color,
														colorbuf,
														PIXELFORMAT_ARGB8888,
														posX, posY,
														0
													);

			if					(	ret != SUCCESS	)
			{
				LOG				(	"Failed to paint color at posX : %d, posY : %d\n",
									posX, posY
								);
				RETURN			(	FAIL	);
			}
		}

	// Use the force, Luke!
	return SUCCESS;
}



HOWTO_DRAW						(	Rect_t,
									rect,
									Color_t*			color,
									Color_buffer_t*		colorbuf	)
{
	paint_rect					(	rect,	color,	color,	colorbuf,	1	);
}


HOWTO_DRAW						(	Grid_t,
									grid,
									Color_t*			color,
									Color_buffer_t*		colorbuf	)
{
	MEM							(	Rect_t,		rect,	1	);

	int								posX		= 0,
									posY		= 0,
									n			= 0;

	rect->posX					=	posX;
	rect->posY					=	posY;
	rect->width					=	grid->width;
	rect->height				=	grid->height;

	for_each_rect_in_buffer		(	n,		rect,	colorbuf	)
		DRAW					(	Rect_t,
									rect,	color,	colorbuf	);

}

