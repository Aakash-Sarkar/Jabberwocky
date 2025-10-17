/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "renderer.h"




struct								Renderer
{
	SDL_Renderer *					sdl	;

	Color_buffer_t *				buffer	;

	Texture_t *						texture	;

	Window_t *						window	;

	Choreographer_t *				c_grapher	;

	ARRAY ( Triangle2d_t ) *		triangles_to_draw	;

	Mesh_t *						mesh	;

	Point2d_t *						origin	;
};




HOWTO_CONSTRUCT					(	Renderer_t,
									self,
									Window_t*	window
								)
{
	int								window_w = 0,
									window_h = 0;

	float							origin_x = 0,
									origin_y = 0;

	PTR							(	SDL_Window,
									sdl_window,
									NULL
								);

	ASSERT						(	window != NULL,
									"Invalid arguments\n"
								);

	// Allocate memory
	
	ALLOC_ZEROED				(	Renderer_t,
									self,
									1
								);

	ASSERT						(	self != NULL,	" "	);

	CALLM						(	Window_t,
									get_window_dimensions,
									window,
									&window_w,
									&window_h
								);

	CALLM						(	Window_t,
									get_sdl_type,
									window,
									sdl_window
								);

	// This creates our renderer
	
	CALL						(	self->sdl,
									SDL,
									CreateRenderer,
									sdl_window,
									-1,
									0
								);

	ASSERT						(	self->sdl != NULL, ""	);

	CONSTRUCT					(	ARRAY ( Triangle2d_t ),
									self->triangles_to_draw,
									NULL
								);

	CONSTRUCT					(	Mesh_t,
									self->mesh,
									"assets/cube.obj"
								);


//	Create a color buffer that we'll use to paint our image inside the game
//	loop.

	CONSTRUCT					(	Color_buffer_t,
									self->buffer,
									window_w,
									window_h,
									PIXELFORMAT_ARGB8888
								);

	ASSERT						(	self->buffer != NULL,	" "	)	;

	// Create a texture for the color buffer

	CONSTRUCT					(	Texture_t,
									self->texture,
									self,
									window_w,
									window_h,
									PIXELFORMAT_ARGB8888
								)	;

	ASSERT						(	self->texture != NULL,	" "	)	;

	CONSTRUCT					(	Choreographer_t,
									self->c_grapher,
									NULL
								)	;

	ASSERT						(	self->c_grapher != NULL,	" "	);

	origin_x					=	window_w  / (float) 2;
	origin_y					=	window_h  / (float) 2;

	CONSTRUCT					(	Point2d_t,
									self->origin,
									origin_x,
									origin_y
								);

	self->window				=	window;

	RETURN						(	self	);
}


//TODO: Implement this
HOWTO_DESTRUCT					(	Renderer_t,
									self
								)
{
}




METHOD							(	Renderer_t,
									render_color_buffer,
									self,
									void* null
								)
{

	int								ret	= -1;

	// copy color buffer into texture

	CALL						(	ret,
									SDL,
									UpdateTexture,
									self->texture->sdl,
									NULL,
									self->buffer->buffer[ 0 ],
									self->texture->pitch
								);

	if							(	ret	)
	{
		LOG						(	"SDL_UpdateTexture Failed!\n"	);
	}

	// Ask SDL to display the texture

	CALL						(	ret,
									SDL,
									RenderCopy,
									self->sdl,
									self->texture->sdl,
									NULL,
									NULL
								);

	if							(	ret	)
	{
		LOG						(	"SDL_RenderCopy Failed!\n"	);
	}
}


METHOD                          (   Renderer_t,
                                    fill_color_buffer,
                                    self,
                                    Color_t*          color
                                )
{
	int								width	= 0,
									height	= 0;

	CALLM						(	Color_buffer_t,
									get_buffer_dimensions,
									self->buffer,
									&width,
									&height
								);

    for                         (   int y = 0;   y < height;   y++   )
        for                     (   int x = 0;   x < width;    x++   )
        {

            CALLM               (   Color_buffer_t,
                                    paint_color,
                                    self,
                                    color,
                                    x, y,
                                    0
                                );
        }
}

METHOD							(	Renderer_t,
									clear_color_buffer,
									self,
                                    void*   null
								)
{

	bool							ret = FAIL;

	TMP							(	Color_t,
									black,
									1
								);

    // Compose a Black color

	COMPOSE						(	Color_t,
									black,
									0x00,      // no red
									0x00,      // no green
									0x00,      // no blue
									0xFF       // opaque alpha
								);


     // Fill the color buffer with our color to the full width and height of the
     // buffer

    CALLM                       (   Renderer_t,
                                    fill_color_buffer,
                                    self,
                                    black
                                );
}


METHOD							(	Renderer_t,
									store_triangle,
									self,
									Triangle2d_t*	triangle
								)
{
	PUSH						(	Triangle2d_t,
									triangle,
									&self->triangles_to_draw
								);
}

METHOD							(	Renderer_t,
									draw_triangles,
									self,
									Color_t*	color
								)
{
	int								idx	= 0;

	TMP							(	Triangle2d_t,
									triangle,
									1
								);

	for_each_item_in_array		(	&self->triangles_to_draw, idx	)
	{
		LOAD					(	Triangle2d_t,
									triangle,
									&self->triangles_to_draw,
									idx
								);

		DRAW					(	Triangle2d_t,
									triangle,
									&self->origin,
									color,
									self->buffer
								);
	}
}
