/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <SDL.h>

#include "object.h"
#include "color.h"
#include "mesh.h"
#include "triangle.h"




typedef					struct	Choreographer	{
									uint32_t		previous_ticks_ms;
									uint32_t		current_ticks;
												}					Choreographer_t;




//////////////////////////////////////////////////////////////////////////////////
//								WINDOW:											//
//////////////////////////////////////////////////////////////////////////////////

typedef					INHERIT	(	SDL,
									Window,
									int				posX;
									int				posY;
									int				width;
									int				height;
									long			flags;	)			Window_t;


//////////////////////////////////////////////////////////////////////////////////
//								TEXTURE:										//
//////////////////////////////////////////////////////////////////////////////////

typedef					INHERIT (	SDL,
									Texture,
									int				width;
									int				height;
									int				pitch;
									Format_type_t	format_type;	)	Texture_t;



typedef					INHERIT (	SDL,
									Renderer,
									Color_buffer_t*			buffer;
									Texture_t*				texture;
									Window_t*				window;
									Choreographer_t*		c_grapher;
									ARRAY ( Triangle2d_t )	triangles_to_draw;
									Mesh_t*					mesh;
									Point2d_t				origin;		)	Renderer_t;




/* Beginning of function declarations */


CONSTRUCTOR				(	Window_t	);


DESTRUCTOR				(	Window_t	);


CONSTRUCTOR				(	Renderer_t,
							Window_t*	w	);


DESTRUCTOR				(	Renderer_t	);



CONSTRUCTOR				(	Texture_t,
							Renderer_t*		r,
							int				w,
							int				h,
							Format_type_t	f_t	);

DESTRUCTOR				(	Texture_t	);

CONSTRUCTOR				(	Choreographer_t	);

bool
render_color_buffer		(	Renderer_t*	renderer	);

