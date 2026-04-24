/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include <SDL.h>

#include "array.h"
#include "color.h"
#include "cube.h"
#include "display.h"
#include "geometry.h"
#include "mesh.h"
#include "point.h"
#include "triangle.h"
#include "util.h"









//////////////////////////////////////////////////////////////////////////////
//								GAME LOOP:
//////////////////////////////////////////////////////////////////////////////
//
//
//		A Game loop is perhaps one of the most common concept you'll
//		find in Interactive Computer Graphics. It's found in many of
//		the rendering apis and game engines in one form or another.
//		You can also call it as Render Loop e.t.c. but the core idea
//		remain the same:
//
//		At every screen refresh (vblank) do the following:
//
//		1.	Collect and process the inputs given by the user.
//
//		2.	Because of the inputs, the state of your world ( in the
//			video game) has somehow now changed. So update your data
//			structures to reflect the new state.
//
//		3.	Draw the next frame using the updated state into a image
//			buffer.
//
//		4.	Show the new image to the user at next screen refresh and
//			repeat the cycle.
//
//
//		Most video games aim for a 60 FPS rate. That means you should
//		show at least 60 image frames to the user in a second. If your
//		GPU is slow and is not able to draw the frame within the next
//		refresh cycle then your frames will start to drop. If the frame
//		rate drops too low then the user will start to notice a visible
//		lag.
//
//
//		In a C style representation this will look something like this:
//
//		int main ( void ) {
//
//			setup();
//
//			while (true) {
//
//				Process_inputs();
//
//				...
//
//				Update();
//
//				...
//
//				Render();
//			}
//		}
//
//
//////////////////////////////////////////////////////////////////////////////


DECLARE_LOOP					(	GAME	);





// This inits everythign
static
bool
yo_sdl_init_everything			(	void	)
{
	int								ret	=	-1;

	CALL						(	ret,
									SDL,
									Init,
									SDL_INIT_EVERYTHING
								);

	if							(	ret != 0	)
	{
		LOG						(	"BITCH!\n"	);
		RET						(	FAIL	);
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

	//	Initialze SDL

	if							(	yo_sdl_init_everything ( )
								!=	SUCCESS		)
		RET						(	NULL	);

	//	Create a new window

	NEW							(	Window_t,
									window,
									NULL
								);


	//	Create a renderer so that we can talk to the SDL layer.

	NEW							(	Renderer_t,
									renderer,
									window
								);

	RET							(	renderer	);
}

static
void
process_input					(	void	)
{

	SDL_Event						event	=	{ 0 };

	int								ret		=	-1;

	/*
	 * Check for Keyboard inputs from the user
	 */
	CALL						(	ret,
									SDL,
									PollEvent,
									&event
								);

	switch						(	event.type	)
	{
		// Window close
		case					(	SDL_QUIT	):
			LOOP_BREAK			(	GAME	);
			break;

		// Escape key
		case					(	SDL_KEYDOWN	):
			if					(	event.key.keysym.sym
								==	SDLK_ESCAPE
								)
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
	Mesh_t							*mesh	=	NULL;

	Triangle2d_t					*prj	=	NULL,
									*top	=	NULL,
									*bot	=	NULL;

	Vec3_t							*rot	=	NULL;


	DEF							(	Triangle2d_t,
									prj
								);

	DEF							(	Triangle2d_t,
									top
								);

	DEF							(	Triangle2d_t,
									bot
								);

	DEF							(	arr ( Triangle2d_t ),
									( renderer )->triangles_to_draw
								);

	NEW							(	Vec3_t,
									rot,
									0.01f,
									0.01f,
									0.01f
								);


	GET							(	mesh,
									( renderer )->mesh
								);

	ROT							(	Mesh_t,
									mesh,
									rot
								);

	itr ( Triangle3d_t )			it		=	{ 0 };

	for_each_triangle_in_mesh	(	&( it ),	mesh	)
	{
		bool						cull	=	false;

		LD						(	bool,
									&( cull ),
									( mesh )->cull,
									( it ).pos
								);

		if						(	cull == true	)
		{
			continue;
		}

		PROJ					(	Triangle2d_t,			Triangle3d_t,
									( prj ),				( it ).ptr,
									( PERSPECTIVE )
								);

		REQ						(	Triangle2d_t,
									get_flat_top_bottom,
									prj,
									top,
									bot
								);

		PUSH					(	Triangle2d_t,
									( renderer )->triangles_to_draw,
									( prj )
								);


		assert					(	top	);
		assert					(	bot	);


		//PUSH					(	Triangle2d_t,
		//							top,
		//							renderer->triangles_to_draw
		//						);

		//PUSH					(	Triangle2d_t,
		//							bot,
		//							renderer->triangles_to_draw
		//						);
	}

	DEL							(	Vec3_t,
									rot
								);

	DEL							(	Triangle2d_t,
									top
								);

	DEL							(	Triangle2d_t,
									bot
								);

	PUT							(	mesh	);

	// Use the force, Luke!
	return SUCCESS;
}



//	This is the part of game loop that does the actual drawing on the screen. 

static
bool
render							(	Renderer_t*		renderer	)
{

	int								ret		=	-1,
									idx		=	0;

	Color_t							*green	=	NULL;

	itr ( Triangle2d_t )			tr		=	{ 0 };

	NEW							(	Color_t,
									green,
									0x00,
									0xFF,
									0x00,
									0xFF
								);

	for_each_item_in_arr		(	Triangle2d_t,	&( tr ),	( renderer )->triangles_to_draw	)
	{
		DRAW					(	Triangle2d_t,
									( tr ).ptr,
									( renderer )->origin,
									( green ),
									( renderer )->buffer
								);

		//LOG						(	"idx: %d\n", idx	);
	}


	DEL							(	arr	( Triangle2d_t ),
									( renderer )->triangles_to_draw
								);

	ret							=	render_color_buffer	(	renderer	);

	if							(	( !!ret ) != SUCCESS	)
	{
		LOG						(	"Failed to render color buffer\n"	);
		RET						(	FAIL	);
	}

	ret							=	clear_color_buffer	(	( renderer )->buffer	);

	if							(	( !!ret ) != SUCCESS	)
	{
		LOG						(	"Failed to clear buffer\n"	);
		RET						(	FAIL	);
	}

	SDL_RenderPresent			(	( renderer )->sdl	);

	// Use the force, Luke!
	return SUCCESS;
}



int
main							(	int	argc,		char**	argv	)
{

	Renderer_t						*renderer	=	NULL;

	renderer					=	setup	(	);

	if							(	!renderer	)
	{
		LOG						(	"Setup failed\n"	);
		RET						(	1	);
	}

	LOOP						(	GAME	)
	{
		process_input			(	);

		update					(	renderer	);

		render					(	renderer	);
	}

	RET							(	0	);
}
