/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "point.h"
#include "color.h"
#include "geometry.h"




typedef							struct Line						Line_t;


////////////////////////////////////////////////////////////////////////////////
//								Line Operations
////////////////////////////////////////////////////////////////////////////////


HOWTO_COPY						(	Line_t,	to,	from	);


HOWTO_COMPOSE					(	Line_t,
									self,
									Point2d_t*	p1,
									Point2d_t*	p2	);




//////////////////////////////////////////////////////////////////////////////////
//								Geomertic Operations
//////////////////////////////////////////////////////////////////////////////////


HOWTO_DRAW						(	Line_t,
									self,
									Color_t*			color,
									Renderer_t*			renderer
								);


