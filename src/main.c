/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include <SDL.h>

#include "array.h"
#include "color.h"
#include "display.h"
#include "geometry.h"
#include "mesh.h"
#include "point.h"
#include "rect.h"
#include "triangle.h"
#include "util.h"










//////////////////////////////////////////////////////////////////////////////
//								GAME LOOP:
//////////////////////////////////////////////////////////////////////////////
//
//
//
//		A Game loop is perhaps one of the most common concept you'll find
//		in Interactive Computer Graphics. It is found in most rendering
//		apis and game engines in one form or another. You can also call it
//		as Render Loop etc but the core idea remain the same:
//
//
//		At every screen refresh (vblank) do the following:
//
//
//		1.	Collect and process the inputs given by the user.
//
//		2.	Because of the inputs, the state of your world (in the video
//			game) has somehow now changed. So update your data structures
//			to reflect the new state.
//
//		3.	Draw the next frame using the updated state into a image
//			buffer.
//
//		4.	Show the new image to the user at next screen refresh and
//			repeat the cycle.
//
//
//		Most video games aim for a 60 FPS rate. That means you should show
//		at least 60 image frames to the user in a second. If your GPU is
//		slow and is not able to draw the frame within the next refresh cycle,
//		then your frames will start to drop (figuratively!). If the frame
//		rate drops too low then the user will start to notice a visible lag.
//
//
//		In a C style representation this will look something like this:
//
//
//		int main ( void ) {
//			setup();
//
//			while (true) {
//				Process_inputs();
//				...
//				Update();
//				...
//				Render();
//			}
//		}
//
//
//
//////////////////////////////////////////////////////////////////////////////




DECLARE_LOOP					(	GAME	);




// This inits everythign
static
bool
yo_sdl_init_everything			(	void	)
{

	int								ret = -1;

	ret							=	__CALL	(	SDL,
												Init,
												SDL_INIT_EVERYTHING
											);

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
	Window_t						*window		=	NULL;
	Renderer_t						*renderer	=	NULL;

	int								numbufs		=	1;

	// Initialze SDL

	if							(	yo_sdl_init_everything ( )
									!=	SUCCESS		)
	{
		RETURN					(	NULL	);
	}

	/*
	 * Ask SDL to create a window for us where we can render (show) our images.
	 */

	DEF							(	Window_t,
									window
								);

	if							(	!window		)
	{
		LOG						(	"Couldn't create window\n"	);
		RETURN					(	NULL	);
	}

	/*
	 * Create a renderer so that we can talk to the SDL layer.
	 */

	NEW							(	Renderer_t,
									renderer,
									window
								);

	if							(	!renderer	)
	{
		LOG						(	"Couldn't create renderer\n"	);
		DEL						(	Window_t,	window	);
		RETURN					(	EMPTY	);
	}

	RETURN						(	renderer	);
}

static
void
process_input					(	void	)
{

	int								ret	=	-1;

	TMP							(	SDL_Event,
									event,
									1
								);

	/*
	 * Check for Keyboard inputs from the user
	 */
	ret							=	__CALL	(	SDL,
												PollEvent,
												event
											);

	switch						(	event->type		)
	{
		// Window close
		case					(	SDL_QUIT	):
			LOOP_BREAK			(	GAME	);
			break;

		// Escape key
		case					(	SDL_KEYDOWN		):
			if					(	event->key.keysym.sym == SDLK_ESCAPE	)
				LOOP_BREAK		(	GAME	);
			break;
		default:
			break;
	}
}


static
bool
cull							(	Triangle3d_t*	triangle	)
{

	Vec3_t							camera_ray	[ 1 ]	=	{ 0 };
	Vec3_t							camera		[ 1 ]	=	{ 0, 0, 0 };


	float							dotp	=	0;
	bool							cull	=	false;


	SUB							(	vec3_t,
									camera_ray,
									camera,
									&triangle->p1.v
								);


	cull						=	(	dotp	<	0	);

	RETURN						(	cull	);
}


static
bool
update							(	Renderer_t*		renderer	)
{

	int								ret		=	-1,
									idx		=	0;

	Mesh_t							*mesh	=	NULL;

	MSG							(	Renderer_t,
									get_mesh,
									renderer,
									mesh
								);


	Triangle3d_t					*triangle	=	NULL;
	Vec3_t							*rotation	=	NULL;
	Color_t							*color		=	NULL;

	DEF							(	Triangle3d_t,
									triangle
								);

	NEW							(	Vec3_t,
									rotation,
									0.1f,	0.00f,	0.00f
								);

	NEW							(	Color_t,
									color,
									0x00,
									0xFF,
									0x00,
									0xFF
								);


	ROT							(	Mesh_t,
									mesh,
									rotation
								);


	for_each_triangle_in_mesh	(	triangle,	mesh,	idx		)
	{
		Triangle2d_t				*proj	=	NULL;

		if						(	cull	(	triangle	)	)
		{
			continue;
		}

		//triangle->p1.v.z += 5;
		//triangle->p2.v.z += 5;
		//triangle->p3.v.z += 5;


		PROJ					(	Triangle2d_t,		Triangle3d_t,
									proj,				triangle,
									ORTHOGRAPHIC
								);


		PUSH					(	Triangle2d_t,
									proj,
									&renderer->triangles_to_draw
								);
	}

	// Use the force, Luke!
	return SUCCESS;
}


/**
 * This is the part of game loop that does the actual drawing on the screen. 
 */
static
bool
render							(	Renderer_t*		renderer	)
{

	int								ret		=	-1,
									idx		=	0;

	Color_t							*green	=	NULL;

	NEW							(	Color_t,
									green,
									0x00,
									0xFF,
									0x00,
									0xFF
								);


	for_each_item_in_array		(	ARRAY ( Triangle2d_t ), renderer->triangles_to_draw, idx	)
	{
		Triangle2d_t				*triangle	=	NULL;

		LD						(	Triangle2d_t,
									triangle,
									&renderer->triangles_to_draw,
									idx
								);


		DRAW					(	Triangle2d_t,
									triangle,
									&renderer->origin,
									green,
									renderer->buffer
								);
	}


	ARRAY_RESET					(	Triangle2d_t,
									&renderer->triangles_to_draw
								);


	ret							=	render_color_buffer		(	renderer	);

	if							(	(	!!ret	)	!=	SUCCESS		)
	{
		LOG						(	"Failed to render color buffer\n"	);
		RETURN					(	FAIL	);
	}

	ret							=	clear_color_buffer		(	renderer->buffer	);

	if							(	(	!!ret	)	!=	SUCCESS	)
	{
		LOG						(	"Failed to clear buffer\n"	);
		RETURN					(	FAIL	);
	}

	SDL_RenderPresent			(	renderer->sdl	);

	// Use the force, Luke!
	return SUCCESS;
}



int
main							(	int argc,	char** argv	)
{
	Renderer_t						*renderer	=	NULL;

	renderer					=	setup	(	);
	if							(	!renderer	)
	{
		LOG						(	"Setup failed\n"	);
		RETURN					(	1	);
	}

	LOOP						(	GAME	)
	{
		process_input			(	);
		update					(	renderer	);
		render					(	renderer	);
	}
	RETURN						(	0	);
}
