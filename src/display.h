/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <SDL.h>

#include "object.h"
#include "color.h"
#include "mesh.h"
#include "triangle.h"




typedef					struct	Choreographer					Choreographer_t;


//////////////////////////////////////////////////////////////////////////////////
//								WINDOW:
//////////////////////////////////////////////////////////////////////////////////


typedef					struct	Window							Window_t;


//////////////////////////////////////////////////////////////////////////////////
//								TEXTURE:
//////////////////////////////////////////////////////////////////////////////////


typedef					struct	Texture							Texture_t;






/* Beginning of function declarations */


HOWTO_CONSTRUCT					(	Window_t,
									self,
									Format_type_t	format_type
								);


HOWTO_DESTRUCT					(	Window_t,
									self
								);


HOWTO_CONSTRUCT					(	Texture_t,
									self,
									SDL_Renderer*	sdl_renderer,
									int				width,
									int				height,
									Format_type_t	format_type
								);

HOWTO_DESTRUCT					(	Texture_t,
									self
								);

HOWTO_CONSTRUCT					(	Choreographer_t,
									self,
									void*	null
								);


METHOD							(	Window_t,
									set_window_fullscreen,
									self,
									void*	null
								);


METHOD                          (   Window_t,
                                    get_window_dimensions,
                                    self,
                                    int*    out_w,
                                    int*    out_h
                                );


METHOD                          (   Window_t,
                                    get_sdl_type,
                                    self,
                                    int*    out
                                );


