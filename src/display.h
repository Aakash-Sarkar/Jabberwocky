/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <SDL.h>

#include "object.h"
#include "color.h"

/**
 * WINDOW:
 * 
 */

typedef					INHERIT	(	SDL,
									Window,
									int					posX;
									int					posY;
									int					width;
									int					height;
									long				flags;		)	Window_t;


/**
 * TEXTURE:
 *
 */
typedef					INHERIT (	SDL,
									Texture,
									int					width;
									int					height;
									int					pitch;
									format_type_t		format_type;	)	Texture_t;


typedef					struct Choreographer {
									uint32_t			previous_ticks_ms;
									uint32_t			current_ticks;		}	Choreographer_t;

typedef					INHERIT (	SDL,
									Renderer,
									Color_buffer_t*		buffer;
									Texture_t*			texture;
									Window_t*			window;
									Choreographer_t*	c_grapher;	)	Renderer_t;


/* Beginning of function declarations */


/**
 * @brief:  Constructs an object of type window_t
 *
 * @param:  none
 *
 * @return: pointer to window_t on success,
 *          NULL otherwise
 */

CONSTRUCTOR				(	Window_t	);

/**
 * @brief:  Destructs an object of type window_t
 *
 * @param:  window					window to destroy
 *
 * @return: void
 */

DESTRUCTOR				(	Window_t	);


/**
 * @brief:  Constructs an object of type renderer_t
 *
 * @param:  window			window to use
 *
 * @return: pointer to renderer_t on success,
 *          NULL otherwise
 */

CONSTRUCTOR				(	Renderer_t,
							Window_t*	w	);

/**
 * @brief:  Destructs an object of type renderer_t
 *
 * @param:  renderer		renderer to destroy
 *
 * @return: void
 */

DESTRUCTOR				(	Renderer_t	);


/**
 * @brief:  Constructs an object of type texture_t
 *
 * @param:  r						renderer to use 
 * @param:  w						texture width
 * @param:  h						texture height
 * @param:  f_t						pixel format
 *
 * @return: pointer to texture_t on success,
 *          NULL otherwise
 */

CONSTRUCTOR				(	Texture_t,
							Renderer_t*		r,
							int				w,
							int				h,
							format_type_t	f_t	);

DESTRUCTOR				(	Texture_t	);

CONSTRUCTOR				(	Choreographer_t	);

bool
render_color_buffer		(	Renderer_t*	renderer	);

