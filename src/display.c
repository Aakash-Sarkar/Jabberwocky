/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "display.h"
#include "renderer.h"
#include "cube.h"



struct	Choreographer
{
	uint32_t						previous_ticks_ms;
	uint32_t						current_ticks;
};


struct	Window
{
	SDL_Window*						sdl;
	int								posX;
	int								posY;
	int								width;
	int								height;
	Format_type_t					format_type;
	long							flags;
};


struct	Texture
{
	SDL_Texture*					sdl;
	int								width;
	int								height;
	int								pitch;
	Format_type_t					format_type;
};


HOWTO_CONSTRUCT					(	Window_t,
									self,
									Format_type_t	format_type
								)
{

	TMP							(	SDL_DisplayMode,
									mode,
									1
								);

	int								ret = -1;


	// Allocate our window

	ALLOC_ZEROED				(	Window_t,
									self,
									1
								);

	ASSERT						(	self != NULL, "Failed to alloc window\n" );

	// This is a way to query from the OS what are the dimensions of the
	// screen

	CALL						(	ret,
									SDL,
									GetCurrentDisplayMode,
									0,
									mode
								);


	// Setup x,y co-ordinates of the Window

	// This tells SDL to show the window at the centre of the screen when the
	// program launches.



	self->posX					=	SDL_WINDOWPOS_CENTERED;
	self->posY					=	SDL_WINDOWPOS_CENTERED;

	// Setup Dimensions of the Window

	self->width					=	mode->w;
	self->height				=	mode->h;

	self->format_type			=	format_type;

	// This tells SDL not to add any visible border to our window

	self->flags					=	SDL_WINDOW_BORDERLESS;

	// Call SDL to create our window

	CALL						(	self->sdl,
									SDL,
									CreateWindow,
									NULL,			// window name
									self->posX,
									self->posY,
									self->width,
									self->height,
									self->flags
								);

	// Set window to fullscreen

	//CALL						(	ret,
	//								SDL,
	//								SetWindowFullscreen,
	//								self->sdl,
	//								SDL_WINDOW_FULLSCREEN
	//							);

	RETURN						(	self	);
}

HOWTO_DESTRUCT					(	Window_t,
									self
								)
{
}






HOWTO_CONSTRUCT					(	Texture_t,
									self,
									Renderer_t*		renderer,
									int				width,
									int				height,
									Format_type_t	format_type
								)
{

	PTR							(	Format_t,
									format,
									NULL
								);

	int								sdl_type	= 0,
									pitch		= 0;

	format						=	lookup_format (	format_type	);

	ASSERT						(	format != NULL,
									"Unsupported format!\n"
								);

	ALLOC_ZEROED				(	Texture_t,
									self,
									1
								);

	ASSERT						(	self != NULL,
									"failed to allocate texture\n"
								);

	self->width					=	width;
	self->height				=	height;
	self->format_type			=	format_type;

    CALLM                       (   Format_t,
                                    get_pitch,
                                    format,
                                    width,
                                    &pitch
                                );

	self->pitch					=	pitch;

	CALLM						(	Format_t,
									get_sdl_type,
									format,
									&sdl_type
								);

	CALL						(	self->sdl,
									SDL,
									CreateTexture,
									renderer->sdl,
									sdl_type,
									SDL_TEXTUREACCESS_STREAMING,
									self->width,
									self->height
								);

	ASSERT						(	self->sdl != NULL,
									"SDL_CreateTexture failed\n"
								);

	RETURN						(	self	);
}

HOWTO_DESTRUCT					(	Texture_t,
									self
								)
{
}

HOWTO_CONSTRUCT					(	Choreographer_t,
									self,
									void*	null
								)
{

	ALLOC_ZEROED				(	Choreographer_t,
									self,
									1
								);
	if							(	!self	)
	{
		RETURN					(	NULL	);
	}

	self->previous_ticks_ms		=	0;

	CALL						(	self->current_ticks,
									SDL,
									GetTicks
								);
	RETURN						(	self	);
}


METHOD							(	Window_t,
									set_window_fullscreen,
									self,
									void*	null
								)
{
	int								ret = -1;
	// Set window to fullscreen

	CALL						(	ret,
									SDL,
									SetWindowFullscreen,
									self->sdl,
									SDL_WINDOW_FULLSCREEN
								);
}


METHOD                              (   Window_t,
                                        get_window_dimensions,
                                        self,
                                        int*    out_w,
                                        int*    out_h
                                    )
{
    ASSERT                          (   self != NULL && out_w != NULL && out_h != NULL,
                                        "Invalid args\n"
                                    );

    *out_w                          =   self->width;
    *out_h                          =   self->height;
}


METHOD                              (   Window_t,
                                        get_sdl_type,
                                        self,
                                        int*    out
                                    )
{
    ASSERT                          (   self != NULL && out != NULL,
                                        "Invalid args\n"
                                    );

    *out                            =   self->sdl;
}

