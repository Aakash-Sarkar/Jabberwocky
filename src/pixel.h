/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

#include "array.h"
#include "util.h"
#include "object.h"
#include "rect.h"




//////////////////////////////////////////////////////////////////////////////////
//									PIXELS:
//////////////////////////////////////////////////////////////////////////////////
//
//
//		Pixels are the final output of any graphics program.  Any shader
//		program running on a GPU will finally output a pixel color value.
//		Pixels are like the atoms of an image. If we keep on dividing an
//		image into smaller and smaller pieces, what we eventually end up
//		with is a pixel.
//
//
//		A pixel can be described using its row and column index within the
//		image along with its color value. If we put together all the pixel
//		values and display them on an LED screen,  what we see is a Raster
//		Image. In other words, the individual pixel colors displayed on an
//		LED screen collectively form the impression of an image inside our
//		brains.
//
//
//		Pixels are not unique to computers. 3D printers works on the same
//		principle of a Raster Image. A dot matrix printer will punch a 2D
//		matrix of tiny dots of Red, Green and Blue paints on a sheet. All
//		the colored dots together give the imprerssion of an image in our
//		head. A digital camera works over the principle of converging all
//		the incoming light on a 2D matrix of light sensors and recording
//		the intensity of each of the individual Red, Green and Blue light
//		components that falls on top of it through the use of colored
//		lenses etc.
//
//
//		In other words, a pixel can be a paint dot, a light sensor, an LED
//		on a screen etc., but all them have a common property: all of them
//		have a row and a column address on a 2D grid; and all of them have
//		a color value represented by the encoded Red, Green and Blue light
//		intensities.
//
//
//						0			 1			  2
//				+-------------+-------------+-------------+
//				|			  |				|			  |
//			0	|	[ RGB ]	  |	  [ RGB ]	|	[ RGB ]	  |
//				|			  |				|			  |
//				+-------------+-------------+-------------+
//				|			  |				|			  |
//			1	|	[ RGB ]	  |	  [ RGB ]	|	[ RGB ]	  |
//				|			  |				|			  |
//				+-------------+-------------+-------------+
//				|			  |				|			  |
//			2	|	[ RGB ]	  |	  [ RGB ]	|	[ RGB ]	  |
//				|			  |				|			  |
//				+-------------+-------------+-------------+
//				|			  |				|			  |
//			3	|	[ RGB ]	  |	  [ RGB ]	|	[ RGB ]	  |
//				|			  |				|			  |
//				+-------------+-------------+-------------+
//
//
//		Computing the value of a pixel from the given inputs is not a very
//		complex function and can be done on the CPU as well. The reason we
//		need special accelerators like GPUs in graphics is because we have
//		too many pixels to compute within a small time frame for real time
//		rendering. That means having many more ALUs inside our chip ( aka.
//		higher compute density), so that we can process as many pixels as
//		we can within a single clock cycle.
//
//
//		One interesting property in graphics is that each pixel value can
//		be computed without any dependence on any other pixel. This means
//		that we can compute the value of a pixel in any order we want; we
//		only need to focus on processing in parallel as many pixels as we
//		can at a given time. GPUs are very good at leveraging this kind
//		of parallelism because of their SIMD architecture.
//
//
//		CPUs on the other hand, are designed with the goal of processing
//		as many instructions as it can within a single clock cycle (aka.
//		Instructions Per Cycle or IPC). In other words, CPUs are good at
//		leveraging instruction level parallelism of a program while GPUs
//		are good at leveraging the data level parallelism of a program.
//
//
//////////////////////////////////////////////////////////////////////////////////




typedef							struct Pixel						Pixel_t;




typedef							DECL_ARRAY						(	Pixel_t	);


typedef							struct Image						Image_t;




//////////////////////////////////////////////////////////////////////////////////
//
//
//		Our definition of an Image Patch is the following:
//
//		Whenever we draw a primitive (points, lines, triangles e.t.c.), the
//		corresponding DRAW call will eventually generate an image patch that
//		we can simply overlay on top of our base image.
//
//
//		In this regard, an image patch is an array of pixels that
//		describes how to paint a primitive on our color buffer. This
//		allows our primitives to fly around on different processors
//		for the patch to be generated. Finally the main thread would
//		collect all the patches and draw our full image on the color
//		buffer.
//
//
//////////////////////////////////////////////////////////////////////////////////


typedef							struct Patch						Patch_t;




HOWTO_COMPOSE			(	Pixel_t,
							self,
							uint32_t	color,
							int			posX,
							int			posY
						);

HOWTO_COPY				(	Pixel_t,	to,	from	);

HOWTO_ARRAY_INIT		(	Pixel_t,	pixels	);

HOWTO_ARRAY_RESET		(	Pixel_t,	pixels	);

HOWTO_PUSH				(	Pixel_t,	ptr,	array	);

HOWTO_LOAD				(	Pixel_t,	ptr,	array,	idx	);

HOWTO_STORE				(	Pixel_t,	ptr,	array,	idx	);


HOWTO_CONSTRUCT			(	Image_t,
							self,
							int				posX,
							int				posY,
							int				width,
							int				height,
							Format_type_t	format_type
						);

HOWTO_COPY				(	Image_t,	to,	from	);



