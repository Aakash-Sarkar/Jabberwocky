/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */




#include <SDL.h>

#include "color.h"
#include "cube.h"
#include "display.h"
#include "geometry.h"
#include "mesh.h"
#include "point.h"
#include "rect.h"
#include "triangle.h"
#include "util.h"




 
 
 
/**
 * GAME LOOP:
 *
 * A Game loop is perhaps one of the most common concept you'll find in
 * Interactive Computer Graphics (caps are there for a reason!). It is
 * found in most rendering apis and game engines in one form or another.
 * You can also call it as Render Loop etc but the core idea remain the
 * same:
 *
 * At every screen refresh (vblank) do the following:
 *
 *  1. Collect and process the inputs given by the user.
 *
 *  2. Because of the inputs, the state of your world (in the video game)
 *     has somehow now changed. So update your data structures to reflect
 *     the new state.
 *
 *  3. Draw the next frame using the updated state into a image buffer.
 *
 *  4. Show the new image to the user at next screen refresh and repeat
 *     the cycle.
 *
 * Most video games aim for a 60 FPS rate. That means you should show at
 * least 60 image frames to the user in a second. If your GPU is slow and
 * is not able to draw the frame within the next refresh cycle, then your
 * frames will start to drop (figuratively!). If the frame rate drops too
 * low then the user will start to notice a visible lag.
 *
 * In a C style representation this will look something like this:
 *
 * int main(void) {
 *     setup();
 *
 *     while (true) {
 *         Process_inputs();
 *         ...
 *         Update();
 *         ...
 *         Render();
 *     }
 * }
 *
 */


DECLARE_LOOP					(	GAME	);





// This inits everythign
static
bool
yo_sdl_init_everything			(	void	)
{
	int								ret = -1;

	CALL						(	ret,
									SDL,
									Init,
									SDL_INIT_EVERYTHING	);

	if							(	ret != 0	)
	{
		LOG						(	"BITCH!\n"	);
		RETURN					(	FAIL	);
	}

	// Use the force, Luke!
	return SUCCESS;
}

static
Renderer_t*
setup							(	void	)
{

	DECL_PTR					(	w,	Window_t,	NULL	);
	DECL_PTR					(	r,	Renderer_t,	NULL	);

	int								numbufs	= 1;

	// Initialze SDL
	if							(	yo_sdl_init_everything ( )
									!= SUCCESS	)
	{
		RETURN					(	NULL	);
	}

	/**
	 * Ask SDL to create a window for us where we can render (show) our images.
	 */
	CONSTRUCT					(	w, Window_t	);
	if							(	!w	)
	{
		LOG						(	"Couldn't create window\n"	);
		RETURN					(	NULL	);
	}

	/**
	 * Create a renderer so that we can talk to the SDL layer.
	 */
	CONSTRUCT					(	r, Renderer_t, w	);
	if							(	!r	)
	{
		LOG						(	"Couldn't create renderer\n"	);
		DESTRUCT				(	w, Window_t	);
		RETURN					(	NULL	);
	}

	/**
	 * Create a color buffer that we'll use to paint our image inside the game
	 * loop.
	 */
	CONSTRUCT					(	r->buffer,
									Color_buffer_t,
									w->width,
									w->height,
									PIXELFORMAT_ARGB8888	);

	if							(	!r->buffer	)
	{
		LOG						(	"failed to create buffer\n"	);
		DESTRUCT				(	r, Renderer_t	);
		RETURN					(	NULL	);
	}

	/*
	 * Create a texture for the color buffer
	 */
	CONSTRUCT					(	r->texture,
									Texture_t,
									r,					// renderer
									w->width,
									w->height,
									PIXELFORMAT_ARGB8888	);

	if							(	!r->texture	)
	{
		LOG						(	"failed to create texture\n"	);
		DESTRUCT				(	r, Renderer_t	);
		RETURN					(	NULL	);
	}

	CONSTRUCT					(	r->c_grapher, Choreographer_t	);

	if							(	!r->c_grapher	)
	{
		LOG						(	"Failed to create Choreographer\n"	);
		DESTRUCT				(	r, Renderer_t	);
		RETURN					(	NULL	);
	}

	RETURN						(	r	);
}

static
void
process_input					(	void	)
{
	SDL_Event						event	= { 0 };
	int								ret		= -1;

	/*
	 * Check for Keyboard inputs from the user
	 */
	CALL						(	ret,
									SDL,
									PollEvent,
									&event		);

	switch						(	event.type	)
	{
		// Window close
		case					(	SDL_QUIT	):
			LOOP_BREAK			(	GAME	);
			break;

		// Escape key
		case					(	SDL_KEYDOWN	):
			if					(	event.key.keysym.sym == SDLK_ESCAPE	)
				LOOP_BREAK		(	GAME	);
			break;
		default:
			break;
	}
}

static
bool
update							(	Renderer_t	*renderer	)
{
	static
	vec3_t							angle = { 0.0, 0.0, 0.0 };

	int								ret	= -1,
									i	= 0,
									j	= 0;

	DECL_PTR					(	colorbuf,	Color_buffer_t,	renderer->buffer	);
	DECL_PTR					(	point,		Point3d_t,		NULL	);
	DECL_PTR					(	mesh,		Mesh_t,			NULL	);
	DECL_PTR					(	face,		Face_t,			NULL	);
	DECL_PTR					(	yellow,		Color_t,		NULL	);


	Point3d_t						p		= { 0 };
	Point2d_t						origin	= { 0 };

	CONSTRUCT					(	yellow,
									Color_t,
									0xFF,
									0xFF,
									0x00,
									0xFF,
									PIXELFORMAT_ARGB8888	);

	if							(	!yellow	)
	{
		LOG						(	"Failed to create Color\n"	);
		RETURN					(	FAIL	);
	}

	CONSTRUCT					(	mesh,
									Mesh_t,
									mesh_vertices,
									mesh_faces,
									8,
									12		);

	if							(	!mesh	)
	{
		LOG						(	"Failed to create Mesh\n"	);
		RETURN					(	FAIL	);
	}

	origin.v.x					=	(float)	renderer->window->width / 2;
	origin.v.y					=	(float)	renderer->window->height / 2;

	for_each_face_in_mesh		(	face,	i,	mesh	)
	{
		Triangle_t					triangle,
									new_triangle;

		triangle				= create_triangle_from_face	(	face,
																mesh	);

		ROTATE					(	Triangle_t,
									&new_triangle,
									&triangle,
									angle		);

		DRAW					(	Triangle_t,
									&new_triangle,
									&origin,
									yellow,
									colorbuf	);
	}
	angle.x						+=	0.01;
	//angle.y						+= 0.05;
	//angle.z						+= 0.05;

	// Use the force, Luke!
	return SUCCESS;
}


/**
 * This is the part of game loop that does the actual drawing on the screen. 
 */
static
bool
render							(	Renderer_t* renderer	)
{
	int								ret	= -1;
	DECL_PTR					(	color,	Color_t,	NULL	);
	ret							=	render_color_buffer	(	renderer	);

	if							(	( !!ret ) != SUCCESS	)
	{
		LOG						(	"Failed to render color buffer\n"	);
		RETURN					(	FAIL	);
	}

	ret							=	clear_color_buffer	(	renderer->buffer	);

	if							(	( !!ret ) != SUCCESS	)
	{
		LOG						(	"Failed to clear buffer\n"	);
		RETURN					(	FAIL	);
	}

	SDL_RenderPresent			(	renderer->sdl	);

	// Use the force, Luke!
	return SUCCESS;
}



int
main							(	int argc, char** argv	)
{
	DECL_PTR					(	r,	Renderer_t,	NULL	);

	r							=	setup	(	);
	if							(	!r	)
	{
		LOG						(	"Setup failed\n"	);
		RETURN					(	1	);
	}

	LOOP						(	GAME	)
	{
		process_input			(	);
		update					(	r	);
		render					(	r	);
	}
	RETURN						(	0	);
}
