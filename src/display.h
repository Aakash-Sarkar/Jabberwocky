/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <SDL.h>

#include "object.h"
#include "color.h"
#include "mesh.h"
#include "triangle.h"




typedef	struct	Choreographer	{	uint32_t	previous_ticks_ms;
									uint32_t	current_ticks;	}	Choreographer_t;




//////////////////////////////////////////////////////////////////////////////////
//								WINDOW:											//
//////////////////////////////////////////////////////////////////////////////////


typedef	INHERIT	(	SDL,	Window,		sdl,	int			posX;
												int			posY;
												int			width;
												int			height;
												long		flags;	)	Window_t;


//////////////////////////////////////////////////////////////////////////////////
//								TEXTURE:										//
//////////////////////////////////////////////////////////////////////////////////


typedef	INHERIT (	SDL,	Texture,	sdl,	int				width;
												int				height;
												int				pitch;
												Format_type_t	format_type;	)	Texture_t;



typedef	INHERIT (	SDL,	Renderer,	sdl,	Color_buffer_t			*buffer;
												Texture_t				*texture;
												Window_t				*window;
												Choreographer_t			*c_grapher;
												arr ( Triangle2d_t )	*triangles_to_draw;
												Mesh_t					*mesh;
												Point2d_t				*origin;	)	Renderer_t;




/* Beginning of function declarations */


HOWTO_INIT									(	Window_t,
												self,
												void			*null
											);


HOWTO_FINI									(	Window_t,		self	);


HOWTO_INIT									(	Renderer_t,
												self,
												Window_t		*window
											);


HOWTO_FINI									(	Renderer_t,		self	);



HOWTO_INIT									(	Texture_t,
												self,
												Renderer_t		*r,
												int				w,
												int				h,
												Format_type_t	f_t
											);

HOWTO_FINI									(	Texture_t,	self	);

HOWTO_INIT									(	Choreographer_t,
												self,
												void			*null
											);

HOWTO_FINI									(	Choreographer_t,	self	);

bool
render_color_buffer							(	Renderer_t*		renderer	);

