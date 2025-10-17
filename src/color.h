/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "object.h"




////////////////////////////////////////////////////////////////////////////////////
//                                  COLORS:
////////////////////////////////////////////////////////////////////////////////////
//
//
//      Computer Graphics is primarily about three things: Images, Colors and
//      Light! If you're working on Graphics, you should have a more concrete
//      understanding of these three concepts than a lay person  (Think of an
//      Artist who has the same understanding of paints as you!). Here we are
//      cover the concept of colors in some detail.
//
//
//      Color is a manifestation of light interacting with a material surface.
//      We can see different kinds of colors because each material surface
//      interacts with light in a different way ( depending on the intrinsic
//      properties of that material ). White light coming from a light source
//      can be thought of as a composition of Red, Green and Blue lights with
//      different intensities ( or energy ). When this white light hits the
//      surface of an object; some portion of the light gets abosrbed by the
//      material surface and converted into heat; while the remaining portion
//      gets reflected back. When this reflected light enters into our eyes,
//      we percieve it as the color of that object.
//
//
//      Okay but what does it have to do with the colors Red, Green and Blue?
//      The decomposition of white light into the Red, Green and Blue color
//      channels has more to do with how our eyes work than the light itself.
//      Our retina is coated with cells that can sense the intensity of the
//      individual Red, Green and Blue lights that fall on it. When a light
//      ray reflected from a material surface enters into our eyes, these
//      cells become active and start sending signals to our brain. Our brain
//      then determines the final color of the object based on the intensity
//      of each of these individual color components (Red, Green and Blue).
//
//
//      One can think of the Red, Green and Blue color channels as the X, Y
//      and Z co-ordinate axes of a 3D space and each color as a point in
//      this color space. Thus, instead of thinking of a color value as one
//      integer value, it is much more convenient to think of it as a point
//      (or vector) with X, Y and Z (or R, G and B) components.
//
//
//                              B           
//                              ^
//                              |       G
//                              |     /               
//                              |   /     *                   --> Purple
//                              | /
//                              +------------- > R
//
//
//      A large portion of Computer Graphics requires us to deal with finding
//      the final color of an object. In order to do this, one has to take
//      into account what are the light sources in the scene, at what angle
//      are the light sources from our object model, what are the material
//      properties of the object, how shiny is the surface of the object etc.
//      This is very similar to how an Artist paints a scene based on where
//      the sun is, how it's reflected by water or a mirror like surface and
//      so on.
//
//
////////////////////////////////////////////////////////////////////////////////////





enum Format_type {
    PIXELFORMAT_ARGB8888 = 0,
    PIXELFORMAT_RGBA8888,
    PIXELFORMAT_XRGB4444,
    PIXELFORMAT_MAX
};


typedef                         enum Format_type              Format_type_t;

typedef                         struct Color                   Color_t;

typedef                         struct Format                  Format_t;

typedef                         struct color_buffer            Color_buffer_t;





HOWTO_COMPOSE                   (   Color_t,
                                    self,
                                    uint8_t         r,
                                    uint8_t         g,
                                    uint8_t         b,
                                    uint8_t         a
                                );



HOWTO_CONSTRUCT                 (   Color_buffer_t,
                                    self,
                                    int             width,
                                    int             height,
                                    Format_type_t   format_type
                                );


HOWTO_DESTRUCT                  (   Color_buffer_t,
                                     self
                                );



Format_t*
lookup_format                   (   Format_type_t       format_type );


METHOD                          (   Format_t,
                                    get_pitch,
                                    self,
                                    int         width,
                                    int*        out
                                );


METHOD                          (   Format_t,
                                    get_sdl_type,
                                    self,
                                    int*        out
                                );


METHOD                          (   Color_buffer_t,
                                    get_buffer_dimensions,
                                    self,
                                    int*        out_w,
                                    int*        out_h
                                );


METHOD                          (    Color_buffer_t,
                                    paint_color,
                                    self,
							        Color_t*	color,
                                    int			posX,
                                    int			posY,
                                    int			plane
                                );


METHOD						    (	Color_buffer_t,
									get_pixel_offset,
									self,
									int		    posX,
									int		    posY,
									int*	    out
								)



