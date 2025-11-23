/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "display.h"
#include "object.h"




typedef								struct Renderer					Renderer_t;





HOWTO_CONSTRUCT					(	Renderer_t,
									self,
									Window_t*	w
								);


HOWTO_DESTRUCT					(	Renderer_t,
									self
								);



METHOD							(	Renderer_t,
									fill_color_buffer,
									self,
									Color_t*	color
								);

METHOD							(	Renderer_t,
									clear_color_buffer,
									self,
                                    void*	EMPTY
								);


METHOD							(	Renderer_t,
									render_color_buffer,
									self,
									void*	EMPTY
								);

METHOD							(	Renderer_t,
									store_triangle,
									self,
									Triangle2d_t *	triangle
								);

METHOD							(	Renderer_t,
									get_origin,
									self,
									Point2d_t *	out
								);

METHOD							(	Renderer_t,
									get_raw_buffer,
									self,
									int	idx,
									uint32_t **	out
								);