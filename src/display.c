/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "display.h"

/**
 * The purpose of this function is as follows:
 * 1. Initialize SDL
 * 2. Allocate a New Window
 * 3. Setup dimensions of the window
 *	4. Setup the position of the window on screen
 *	5. Create an SDL_Window
 *	6. Set SDL Window to Fullscreen
 */

CONSTRUCTOR								(	Window_t	)
{
	DECL_PTR							(	window,		Window_t,	NULL	);

	SDL_DisplayMode							mode;
	int										ret = -1;

	// Allocate our window
	ALLOC_ZEROED						(	1,			Window_t,	window	);

	if									(	!window		)
		RETURN							(	NULL	);

	/* This is a way to query from the OS what are the dimensions of the
	 * screen */
	CALL								(	ret,
											SDL,
											GetCurrentDisplayMode,
											0,
											&mode
										);

	if									(	ret		)
		RETURN							(	NULL	);

	// Setup x,y co-ordinates of the Window
	/**
	 * This tells SDL to show the window at the centre of the screen when the
	 * program launches. The user may move the window around later using her
	 * mouse. But that is not in the scope of this function.
	 */
	window->posX						=	SDL_WINDOWPOS_CENTERED;
	window->posY						=	SDL_WINDOWPOS_CENTERED;

	// Setup Dimensions of the Window
	window->width						=	mode.w;
	window->height						=	mode.h;

	/* This tells SDL not to add any visible border to our window */
	window->flags						=	SDL_WINDOW_BORDERLESS;

	// Call SDL to create our window
	CALL								(	window->sdl,
											SDL,
											CreateWindow,
											NULL,			// window name
											window->posX,
											window->posY,
											window->width,
											window->height,
											window->flags	);

	// Something went wrong
	if									(	!window->sdl	)
	{
		DEALLOC							(	window	);
		RETURN							(	NULL	);
	}

	// Set window to fullscreen
	CALL								(	ret,
											SDL,
											SetWindowFullscreen,
											window->sdl,
											SDL_WINDOW_FULLSCREEN	);

	RETURN								(	window	);
}

DESTRUCTOR								(	Window_t	)
{
}

/**
 * The purpose of this function is as follows:
 * 	1. Allocate the renderer
 * 	2. attach the renderer to the window
 */
CONSTRUCTOR								(	Renderer_t,
											Window_t*		window		)
{
	DECL_PTR							(	renderer,		Renderer_t,		NULL	);

	if									(	!window		)
	{
		LOG								(	"Invalid argument\n"	);
		RETURN							(	NULL	);
	}

	// Allocate memory
	ALLOC_ZEROED						(	1,				Renderer_t,		renderer	);

	if									(	!renderer	)
	{
		LOG								(	"Couldn't allocate memory\n"	);
		RETURN							(	NULL	);
	}

	// This creates our renderer
	CALL								(	renderer->sdl,
											SDL,
											CreateRenderer,
											window->sdl,
											-1,
											0
										);

	if									(	!renderer->sdl	)
	{
		DEALLOC							(	renderer	);
		RETURN							(	NULL	);
	}

	INIT_ARRAY							(	Triangle2d_t,	&renderer->triangles_to_draw	);

	renderer->window					=	window;

	RETURN								(	renderer	);
}

//TODO: Implement this
DESTRUCTOR								(	Renderer_t	)
{
}

CONSTRUCTOR								(	Texture_t,
											Renderer_t*				renderer,
											int						width,
											int						height,
											format_type_t			format_type		)
{

	DECL_PTR							(	texture,	Texture_t,	NULL	);
	DECL_PTR							(	format,		Format_t,	NULL	);

	format								=	lookup_format (	format_type	);
	if									(	!format	)
	{
		LOG								(	"Unsupported format!"	);
		RETURN							(	NULL	);
	}

	ALLOC_ZEROED						(	1,			Texture_t,	texture		);

	if									(	!texture	)
	{
		LOG								(	"failed to allocate texture\n"	);
		RETURN							(	NULL	);
	}

	texture->width						=	width;
	texture->height						=	height;
	texture->format_type				=	format_type;

	texture->pitch						=	(	width	*	BITS_TO_BYTES ( format->bpp )	);

	CALL								(	texture->sdl,
											SDL,
											CreateTexture,
											renderer->sdl,
											format->sdl_type,
											SDL_TEXTUREACCESS_STREAMING,
											texture->width,
											texture->height
										);

	if									(	!texture->sdl	)
	{
		LOG								(	"SDL_CreateTexture failed\n"	);
		DEALLOC							(	texture	);
		RETURN							(	NULL	);
	}
	RETURN								(	texture	);
}

DESTRUCTOR								(	Texture_t	)
{

}

CONSTRUCTOR								(	Choreographer_t	)
{
	DECL_PTR							(	c,	Choreographer_t,	NULL	);

	ALLOC_ZEROED						(	1, Choreographer_t, c	);
	if									(	!c	)
	{
		RETURN							(	NULL	);
	}

	c->previous_ticks_ms				=	0;

	CALL								(	c->current_ticks,
											SDL,
											GetTicks  );
	RETURN								(	c	);
}

bool
render_color_buffer						(	Renderer_t* renderer	)
{

	DECL_PTR							(	texture,	Texture_t,		renderer->texture	);
	DECL_PTR							(	bo,			Color_buffer_t,	renderer->buffer	);

	int										ret	= -1;

	// copy color buffer into texture
	CALL								(	ret,
											SDL,
											UpdateTexture,
											texture->sdl,
											NULL,
											bo->buffer[0],
											texture->pitch	);

	if									(	ret	)
	{
		LOG								(	"SDL_UpdateTexture Failed!\n"	);
		RETURN							(	FAIL	);
	}

	// Ask SDL to display the texture
	CALL								(	ret,
											SDL,
											RenderCopy,
											renderer->sdl,
											texture->sdl,
											NULL,
											NULL	);

	if									(	ret	)
	{
		LOG								(	"SDL_RenderCopy Failed!\n"	);
		RETURN							(	FAIL	);
	}

	// Use the force Luke!
	return SUCCESS;
}
