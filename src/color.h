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
//      We see different types of color on different material objects because
//      every material surface interacts with the incoming light a little bit
//      differently ( depending on the intrinsic properties of that material).
//
//
//      White light coming from a light source (like the sun ) can be thought
//      of as a composition of Red , Green and Blue colored lights with equal
//      intensity ( or energy ). When this white light hits the surface of an
//      object; some portion of the light gets abosrbed by the object surface
//      and converted into heat; while the remaining portion of the light get
//      reflected back. During this process, the matrial surface distorts the
//      intensity of the Red, Green and Blue color channels in this reflected
//      light. When this reflected light enters into our eyes, we percieve it
//      as the color of the object. The amount of distortion in the Red, Blue
//      and Green color components defines the final color of the object.
//
//
//      Okay but what does it have to do with the colors Red, Green and Blue?
//      The decomposition of white light into Red , Green and Blue colors has
//      more to do with how our eyes work than the light itself.The retina of
//      our eyes is coated with special cells that can sense the intensity of
//      the individual Red, Green and Blue colored lights that fall on top of
//      it. When a light ray reflected from a material surface enter into our
//      eyes, these special cells become active and starts to send signals to
//      our brain. Our brain then interprets these signals and determines the
//      final color of the object based on the intensity of each one of these
//      individual color components (Red, Green and Blue).
//
//
//      One can think of these Red, Green and Blue color channels as the X, Y
//      and Z co-ordinate axes of a 3D space and every color that we are able
//      to see as a point in this color space. Thus, instead of thinking of a
//      color value as one integer value, it is much more convenient to think
//      of it as a point ( or as a vector ) with X, Y and Z ( or R, G and B )
//      components.
//
//
//                              B          
//                              ^
//                              |
//                              |       G
//                              |     /               
//                              |   /     *                   -->   Purple
//                              | /
//                              + - - - - - - - > R
//
//
//      A large portion of Computer Graphics require us to deal with finding
//      the final color of an object. In order to do this, one needs to take
//      into account what are the light sources in the scene, at what angles
//      are these light sources from our object model, what are the material
//      properties of our object, how shiny is the surface of the object etc.
//      This is very similar to how an Artist paints a scene: based on where
//      the sun is, how it's reflected by water or a mirror like surface and
//      so on.
//
//
////////////////////////////////////////////////////////////////////////////////////





enum Format_type
{
    PIXELFORMAT_ARGB8888        =       0,
    PIXELFORMAT_RGBA8888,
    PIXELFORMAT_XRGB4444,
    PIXELFORMAT_MAX
};


typedef                         enum    Format_type             Format_type_t ;


typedef                         struct  Color                   Color_t ;


typedef                         struct  Format                  Format_t ;


typedef                         struct  color_buffer            Color_buffer_t ;





HOWTO_CONSTRUCT                 (   Color_t,
                                    self,
                                    uint8_t             r,
                                    uint8_t             g,
                                    uint8_t             b,
                                    uint8_t             a
                                );



HOWTO_CONSTRUCT                 (   Color_buffer_t,
                                    self,
                                    int                 width,
                                    int                 height,
                                    Format_type_t       format_type
                                );


HOWTO_DESTRUCT                  (   Color_buffer_t,
                                     self
                                );



Format_t*
lookup_format                   (   Format_type_t       format_type );


METHOD                          (   Format_t,
                                    get_pitch,
                                    self,
                                    int                 width,
                                    int*                out
                                );


METHOD                          (   Format_t,
                                    get_sdl_type,
                                    self,
                                    int*                out
                                );


METHOD                          (   Color_buffer_t,
                                    get_buffer_dimensions,
                                    self,
                                    int*                out_w,
                                    int*                out_h
                                );


METHOD                          (    Color_buffer_t,
                                    paint_color,
                                    self,
							        Color_t*	        color,
                                    int			        posX,
                                    int			        posY,
                                    int			        plane
                                );


METHOD						    (	Color_buffer_t,
									get_pixel_offset,
									self,
									int		            posX,
									int		            posY,
									int*	            out
								);


METHOD							(	Color_buffer_t,
									get_raw_buffer,
									self,
									int	idx,
									uint32_t            **out
								);



