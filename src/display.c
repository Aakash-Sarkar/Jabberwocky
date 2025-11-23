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
	SDL_DisplayMode					mode = { 0 };

	int								ret = -1;

	// This is a way to query from the OS what are the dimensions of the
	// screen

	CALL						(	SDL,
									GetCurrentDisplayMode,
									0,
									&mode
								);


	// Setup x,y co-ordinates of the Window

	// This tells SDL to show the window at the centre of the screen when the
	// program launches.



	self->posX					=	SDL_WINDOWPOS_CENTERED;
	self->posY					=	SDL_WINDOWPOS_CENTERED;

	// Setup Dimensions of the Window

	self->width					=	mode.w;
	self->height				=	mode.h;

	self->format_type			=	format_type;

	// This tells SDL not to add any visible border to our window

	self->flags					=	SDL_WINDOW_BORDERLESS;

	// Call SDL to create our window

	self->sdl					=	__CALL	(	SDL,
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
									SDL_Renderer *		sdl_renderer,
									int					width,
									int					height,
									Format_type_t		format_type
								)
{
	Format_t						*format	=	NULL;

	int								sdl_type	= 0,
									pitch		= 0;

	format						=	lookup_format (	format_type	);

	ASSERT						(	format,
									"Unsupported format!\n"
								);

	self->width					=	width;
	self->height				=	height;
	self->format_type			=	format_type;

    MSG							(   Format_t,
                                    get_pitch,
                                    format,
                                    width,
                                    &pitch
                                );

	self->pitch					=	pitch;

	MSG							(	Format_t,
									get_sdl_type,
									format,
									&sdl_type
								);

	self->sdl					=	__CALL	(	SDL,
												CreateTexture,
												sdl_renderer,
												sdl_type,
												SDL_TEXTUREACCESS_STREAMING,
												self->width,
												self->height
											);

	ASSERT						(	self->sdl != EMPTY,
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
	self->previous_ticks_ms		=	0;

	self->current_ticks			=	__CALL	(	SDL,
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

	ret							=	__CALL	(	SDL,
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
    ASSERT                          (   self  and  out_w  and  out_h,
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
    ASSERT                          (   self  and  out,
                                        "Invalid args\n"
                                    );

    *out                            =   self->sdl;
}

