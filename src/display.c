/*	Copyright © 2025 Intel Corporation
 *	SPDX-License-Identifier: MIT
 */

#include "display.h"




HOWTO_INIT						(	Window_t,
									self,
									void				*null
								)
{

	SDL_DisplayMode					mode	=	{ 0 };
	int								ret		=	-1;

	//	This is a way to query from the OS what are the dimensions of the
	//	screen

	CALL						(	ret,
									SDL,
									GetCurrentDisplayMode,
									0,
									&( mode )
								);

	assert						(	!ret	);

	//	Setup x,y co-ordinates of the Window

	//	This tells SDL to show the window at the centre of the screen when the
	//	program launches. The user may move the window around later using her
	//	mouse. But that is not in the scope of this function.


	( self )->posX				=	SDL_WINDOWPOS_CENTERED;
	( self )->posY				=	SDL_WINDOWPOS_CENTERED;

	//	Setup Dimensions of the Window

	( self )->width				=	( mode ).w;
	( self )->height			=	( mode ).h;

	//	This tells SDL not to add any visible border to our window */

	( self )->flags				=	SDL_WINDOW_BORDERLESS;

	//	Call SDL to create our window

	CALL						(	( self )->sdl,
									SDL,
									CreateWindow,
									( NULL ),			// window name
									( self )->posX,
									( self )->posY,
									( self )->width,	// 800
									( self )->height,	// 600
									( self )->flags
								);

	assert						(	( self )->sdl	);

	//	Set window to fullscreen

	//CALL						(	ret,
	//								SDL,
	//								SetWindowFullscreen,
	//								self->sdl,
	//								SDL_WINDOW_FULLSCREEN
	//							);
}

HOWTO_FINI						(	Window_t,	self	)
{
}


HOWTO_INIT						(	Renderer_t,
									self,
									Window_t		*window
								)
{
	assert						(	window );

	assert						(	( window )->sdl	);

	//	This creates our renderer

	CALL						(	( self )->sdl,
									SDL,
									CreateRenderer,
									( window )->sdl,
									( - 1 ),
									( 0 )
								);

	assert						(	( self )->sdl	);


	//DEF							(	arr ( Triangle2d_t ),
	//								( self )->triangles_to_draw
	//							);

	NEW							(	Mesh_t,
									( self )->mesh,
									"assets/cube.obj"
								);

	assert						(	( self )->mesh	);

	//	Create a color buffer that we'll use to paint our image inside the game
	//	loop.

	NEW							(	Color_buffer_t,
									( self )->buffer,
									( window )->width,
									( window )->height,
									PIXELFORMAT_ARGB8888
								);

	assert						(	( self )->buffer	);

	//	Create a texture for the color buffer

	NEW							(	Texture_t,
									( self )->texture,
									( self ),
									( window )->width,
									( window )->height,
									PIXELFORMAT_ARGB8888
								);

	assert						(	( self )->texture	);

	NEW							(	Choreographer_t,
									( self )->c_grapher,
									NULL
								);

	assert						(	( self )->c_grapher	);

	NEW							(	Point2d_t,
									( self )->origin,
									( window )->width 
								/	( float ) 2,
									( window )->height
								/	( float ) 2
								);

	( self )->window			=	window;
}

//	TODO: Implement this

HOWTO_FINI						(	Renderer_t,		self	)
{
}

HOWTO_INIT						(	Texture_t,
									self,
									Renderer_t			*renderer,
									int					width,
									int					height,
									Format_type_t		format_type
								)
{

	Format_t						*format	=	NULL;

	format						=	lookup_format	(	format_type		);

	assert						(	format	);

	( self )->width				=	width;
	( self )->height			=	height;
	( self )->format_type		=	format_type;

	( self )->pitch				=	width *
									BITS_TO_BYTES	(	format->bpp		);

	CALL						(	( self )->sdl,
									SDL,
									CreateTexture,
									( renderer )->sdl,
									( format )->sdl_type,
									SDL_TEXTUREACCESS_STREAMING,
									( self )->width,
									( self )->height
								);

	assert						(	( self )->sdl	);
}

HOWTO_FINI						(	Texture_t,	self	)
{
}

HOWTO_INIT						(	Choreographer_t,
									self,
									void				*null
								)
{


	( self )->previous_ticks_ms	=	0;

	CALL						(	( self )->current_ticks,
									SDL,
									GetTicks
								);
}


HOWTO_FINI						(	Choreographer_t,	self	)
{
}


bool
render_color_buffer				(	Renderer_t		*renderer	)
{
	Texture_t						*tex	=	NULL;
	Color_buffer_t					*bo		=	NULL;

	GET							(	tex,	renderer->texture	);
	GET							(	bo,		renderer->buffer	);

	int								ret	= -1;

	//	copy color buffer into texture

	CALL						(	ret,
									SDL,
									UpdateTexture,
									tex->sdl,
									NULL,
									bo->buffer[0],
									tex->pitch
								);

	assert						(	!ret	);

	//	Ask SDL to display the texture

	CALL						(	ret,
									SDL,
									RenderCopy,
									renderer->sdl,
									tex->sdl,
									NULL,
									NULL
								);

	assert						(	!ret	);

	PUT							(	tex		);
	PUT							(	bo		);

	//	Use the force Luke!
	return SUCCESS;
}
