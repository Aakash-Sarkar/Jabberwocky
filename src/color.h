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



typedef     enum Format_type    {   PIXELFORMAT_ARGB8888 = 0,
                                    PIXELFORMAT_RGBA8888,
                                    PIXELFORMAT_XRGB4444,
                                    PIXELFORMAT_MAX       } Format_type_t;




////////////////////////////////////////////////////////////////////////////////////
//
//
//      On modern day systems, we always represent a color value as a 32-bit
//      integer. Each of the color components ( R, G and B ) are packed into
//      the successive 8-bits of a 32-bit integer (with last 8-bits reserved
//      for other purposes ). Thus, each color component can take up a value
//      between 0 and 255 representing the intensity of that color component.
//      This provides us with a wide range of colors ( 256 * 256 * 256 ).
//
//
//       |<--------------  32-bit integer  ------------->|
//       +-----------------------------------------------+
//       |   8-bit   |   8-bit   |   8-bit   |   8-bit   |
//       +------+----------+-----------+-----------+-----+
//              |          |           |           |
//              |          |           |           |
//              |          |           |           +-------- > B    channel
//              |          |           +-------------------- > G    channel
//              |          +-------------------------------- > R    channel
//              +------------------------------------------- > A    channel
//
//
//      On older 8-bit and 16-bit systems this was not the case. We had a very
//      limited set of colors that we could use to paint our scenes ( 256 for
//      the 8-bit systems ). Therefore these systems would instead rely upon a
//      color pallete ( or a lookup table ) of the available colors. The color
//      value was then used as an index into this color pallete to figure out
//      the final color of the pixel.
//
//
//      Having each of the color components packed into the successive 8-bits
//      of a 32-bit integer value makes sense from a performace perspective,
//      since all three color channels are needed together in order to paint
//      the final pixel color. Therefore, having them in a single cache line
//      reduces the number of potential cache misses.
//
//
//      However there are situations where having the individual colors inside
//      separate integers is more useful. For e.g. if you are doing some kind
//      of image processing work where you wish to amplify the intensity of a
//      single component ( Red for e.g. ), but do not want to touch any of the
//      other color components. In this case, having all the Red values inside
//      a separate buffer makes more sense, since we want to have only the Red
//      values inside our cache line. This also allow us to pack more bits for
//      our Red component so that we can have a more fine grained control over
//      it, while keeping the number of bits needed for Green and Blue colors
//      the same as before.
//
//
////////////////////////////////////////////////////////////////////////////////////


typedef                             struct Color
                                 {
                                    union
                                    {
                                        struct
                                        {
                                            uint8_t         r;
                                            uint8_t         g;
                                            uint8_t         b;
                                            uint8_t         a;
                                        }                   rgba;

                                        // TODO: Support YUV formats
                                        uint32_t            yuv;
                                     };
                                 }    Color_t;




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




typedef                             struct color_buffer
                                {
                                    int         width;
                                    int         height;
                                    int         pitch;
                                    int         num_buffers;
                                    uint32_t    *buffer[ 4 ];
                                }   Color_buffer_t;





HOWTO_INIT                      (   Color_t,
                                    self,
                                    uint8_t      red,
                                    uint8_t      green,
                                    uint8_t      blue,
                                    uint8_t      alpha
                                );


HOWTO_INIT                      (   Color_buffer_t,
                                    self,
                                    int             width,
                                    int             height,
                                    Format_type_t   format_type    
                                );


HOWTO_FINI                      (   Color_buffer_t,    self    );

bool
paint_color                     (   Color_t             *color,
                                    Color_buffer_t      *color_buffer,
                                    Format_type_t       format_type,
                                    int                 posX,
                                    int                 posY,
                                    int                 plane
                                );

Format_t*
lookup_format                   (   Format_type_t       format_type );

bool
clear_color_buffer              (   Color_buffer_t*     buffer      );

