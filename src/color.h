/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "object.h"




////////////////////////////////////////////////////////////////////////////////////
//                          COLORS:
////////////////////////////////////////////////////////////////////////////////////
//
//  Computer Graphics is primarily about three things: Images, Colors and Light!
//  If you're working on Graphics, then you should have a more concrete
//  understanding of these three concepts than a lay person (Think of an Artist
//  who has the same understanding of paints as you!). Here we cover the concept
//  of colors in some detail.
//
//  Colors are a manifestation of light interacting with a material surface. We 
//  see different types of colors because each material surface interacts with  
//  light in a different way (depending on the intrinsic properties of the      
//  material). The white light coming from a light source can be thought of as a
//  composition of Red, Green and Blue lights with different intensities (or    
//  energy). When this light hits the surface of a material object; some portion
//  of the light gets abosrbed by the surface and converted to heat; while the  
//  remaining portion gets reflected back. When this reflected light enters into
//  our eyes we percieve it as the color of that material.
//
//  Okay, but what does it have to do with Red, Green and Blue? The decomposition
//  of light into Red, Green and Blue channels has more to do with how our eyes
//  work than light itself. Our retina is coated with tissues that can sense the
//  intensity of Red, Green and Blue lights that fall on it. When a light ray
//  reflected from a material surface enters our eye, these tissues become active
//  and send signal to our brain. Our brain then determines the color of the
//  object based on the intensity of each of these components (Red, Green and
//  Blue).
//
//  One can think of the Red, Green and Blue color channels as the X, Y and Z
//  co-ordinate axes of a 3D space and each color as a point in this color space.
//  Thus, instead of thinking of a color value as one integer value, it is much
//  more convenient to think of it as a point (or vector) with X, Y and Z (or R,
//  G and B) components.
//
//  A large portion of Computer Graphics require us to deal with determining the 
//  color of an object. In order to do this one has to take into account what are
//  the light sources in the scene, at what angle is the light source from our
//  object, what is the intrinsic color of the object, how shiny is the surface
//  of the object etc. This is very similar to how an Artist paints a scene based
//  on where the sun is, how it's reflected by water or a mirror like surface and
//  so on.
//
////////////////////////////////////////////////////////////////////////////////////





typedef                     enum Format_type  {
                                                PIXELFORMAT_ARGB8888 = 0,
                                                PIXELFORMAT_RGBA8888,
                                                PIXELFORMAT_XRGB4444,
                                                PIXELFORMAT_MAX       } Format_type_t;




////////////////////////////////////////////////////////////////////////////////
//
//  On modern day systems we always represent a color value as a 32-bit integer.
//  Each color component (R, G and B) is packed into the successive 8-bits of
//  the 32-bit integar value (with the last 8-bits reserved for other purposes).
//  Thus each color component can take a value between 0 and 255 representing
//  the intensity of that component. This provides us with a wide range of
//  colors (256 * 256 * 256).
//
//  On older 8-bit and 16-bit systems this was not the case. We had a very
//  limited number of colors that we could use to paint our scene (256 for
//  8-bit systems). So, these systems would use a color pallete (lookup table)
//  of the available colors. The color value was used as an index into this
//  color palette to determine the final color.
//
//  Having each of the color component packed into the successive 8-bits of a
//  32-bit integer makes sense from a performace perspective since all three
//  color channels are needed together to determine the the pixel color. Thus
//  having them in a single cache line reduces the number of cache misses.
// 
//  However, there are situations where having the individual components into
//  separate integers make more sense. For eg. if you're doing some image
//  processing work where you want to amplify one of the component (Red for
//  example), but not touch the other components. In this case having the Red
//  component into a separate buffer makes more sense since we want only the
//  Red values in our cache. This also allows us to pack more bits for the Red
//  component. With this we can now do more fine grained operations on the Red
//  component while keeping the number of bits for Green and Blue same as before
//
////////////////////////////////////////////////////////////////////////////////


typedef                     struct Color {
                                    union {
                                        struct   {
                                            uint8_t    r;
                                            uint8_t    g;
                                            uint8_t    b;
                                            uint8_t    a;
                                        }   rgba;
                                        // TODO: Support YUV formats
                                        uint32_t       yuv;
                                    };
                            }  Color_t;




typedef                     struct Format   {
                                    SDL_PixelFormatEnum   sdl_type;
                                    int        r_shft;
                                    int        g_shft;
                                    int        b_shft;
                                    int        a_shft;
                                    int        bpp;
                                    int        planes;
                                    struct {
                                        bool   has_alpha;
                                        bool   has_modifiers;
                                    }   flags;                 }    Format_t;




typedef                     struct color_buffer   {
                                    int        width;
                                    int        height;
                                    int        pitch;
                                    int        num_buffers;
                                    uint32_t*  buffer[4];      }    Color_buffer_t;





HOWTO_MAKE                      (   Color_t,
                                    color,
                                    uint8_t         r,
                                    uint8_t         g,
                                    uint8_t         b,
                                    uint8_t         a    );



CONSTRUCTOR                     (   Color_buffer_t,
                                    int                 width,
                                    int                 height,
                                    Format_type_t       format_type   );


DESTRUCTOR                      (   Color_buffer_t  );



bool
paint_color                     (   Color_t*            color,
                                    Color_buffer_t*     color_buffer,
                                    Format_type_t       format_type,
                                    int                 posX,
                                    int                 posY,
                                    int                 plane       );

Format_t*
lookup_format                   (   Format_type_t       format_type );

bool
clear_color_buffer              (   Color_buffer_t*     buffer      );

