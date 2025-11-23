/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "rect.h"




HOWTO_DRAW						(	Rect_t,
									self,
									Color_t*		color,
									Renderer_t*		renderer
								)
{
		int							posX = 0,
									posY = 0;

	for_each_posY_in_rect		(	self,	posY	)
		for_each_posX_in_rect	(	self,	posX	)
		{

			MSG					(	Renderer_t,
									paint_color,
									renderer,
									color,
									posX,
									posY,
									0
								);
		}
}


HOWTO_DRAW						(	Grid_t,
									self,
									Color_t*		color,
									Renderer_t*		renderer
								)
{
	TMP							(	Rect_t,
									rect,
									1
								);

	int								posX		= 0,
									posY		= 0,
									n			= 0;

	rect->posX					=	posX;
	rect->posY					=	posY;
	rect->width					=	self->width;
	rect->height				=	self->height;

	//for_each_rect_in_buffer		(	n,		rect,	renderer->buffer	)
	//	DRAW					(	Rect_t,
	//								rect,
	//								color,
	//								renderer
	//							);

}

