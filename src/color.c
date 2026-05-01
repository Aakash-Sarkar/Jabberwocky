/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "color.h"
#include "memory.h"




Format_t
formats_lut[]                       =   {

    [ PIXELFORMAT_ARGB8888 ]        =   {

        .sdl_type                   =   SDL_PIXELFORMAT_ARGB8888,
        .b_shft                     =   0,
        .g_shft                     =   8,
        .r_shft                     =   16,
        .a_shft                     =   24,
        .bpp                        =   32,
        .planes                     =   1,
        .flags                      =   {
            .has_alpha              =       true,
        },
    },

    [ PIXELFORMAT_XRGB4444 ]        =   {

        .sdl_type                   =   SDL_PIXELFORMAT_XRGB4444,
        .a_shft                     =   12,
        .r_shft                     =   8,
        .g_shft                     =   4,
        .b_shft                     =   0,
        .bpp                        =   16,
        .planes                     =   1,
        .flags                      =   {
            .has_alpha              =       false,
        },
    },

    [ PIXELFORMAT_RGBA8888 ]        =   {

        .sdl_type                   =   SDL_PIXELFORMAT_RGBA8888,
        .a_shft                     =   0,
        .b_shft                     =   8,
        .g_shft                     =   16,
        .r_shft                     =   24,
        .bpp                        =   32,
        .planes                     =   1,
        .flags                      =   {
            .has_alpha              =       false,
        },
    },
};




Format_t*
lookup_format                       (   Format_type_t format_type   )
{
    switch                          (   format_type   )
    {
        case                        (   PIXELFORMAT_ARGB8888    ):
        case                        (   PIXELFORMAT_XRGB4444    ):
        case                        (   PIXELFORMAT_RGBA8888    ):
            RET                     (   &formats_lut [ format_type ]  );
        default:
            RET                     (   NULL    );
    }
}




HOWTO_INIT                          (   Color_t,
                                        self,
                                        uint8_t         red,
                                        uint8_t         green,
                                        uint8_t         blue,
                                        uint8_t         alpha
                                    )
{
    ( self )->rgba.r                =   red;
    ( self )->rgba.g                =   green;
    ( self )->rgba.b                =   blue;
    ( self )->rgba.a                =   alpha;
}

HOWTO_FINI                          (   Color_t,
                                        self
                                    )
{
}


static
bool
get_color_val                       (   Color_t         *color,
                                        uint32_t        *val,
                                        Format_type_t   format_type    )
{
    PTR                             (    Format_t,   format,    NULL   );

    format                          =   lookup_format   (   format_type   );
    if                              (   !format   )
    {
        LOG                         (   "Unsupported Format type %d\n",
                                        format_type   );
        *val                        =   0x00;
        RET                         (   FAIL   );
    }

    *val                        =   (   color->rgba.r << format->r_shft
                                      | color->rgba.g << format->g_shft
                                      | color->rgba.b << format->b_shft   );

    //  Some formats like XRGB8888 doesn't use or discard the alpha
    //  component of the color. |X| stands for `don't care`

    if                              (   format->flags.has_alpha   )
        *val                        |=  (   color->rgba.a << format->a_shft   );

    // Use the force Luke!
    return SUCCESS;
}




HOWTO_INIT                          (   Color_buffer_t,
                                        self,
                                        int             width,
                                        int             height,
                                        Format_type_t   format_type
                                    )
{
    Format_t                            *format =   NULL;

    uint32_t                            *buf  =     NULL,
                                        *prev =     NULL;

    format                          =   lookup_format   (   format_type   );

    assert                          (   format   );

    ( self )->width                 =   width;
    ( self )->height                =   height;

    ( self )->pitch                 =   width
                                    *   BITS_TO_BYTES   (   format->bpp     );

    ( self )->num_buffers           =   ( format )->planes;

    buf                             =   ALLOC_NONZEROED (   width * height,   uint32_t   );

    assert                          (   buf   );

    ( self )->buffer[0]             =   buf;
    buf                             =   NULL;

    for                             (   int i = 1;
                                        i < format->planes;
                                        i++
                                    )
    {

        buf                         =   ALLOC_NONZEROED (   width * height,   uint32_t   );

        assert                      (   buf   );
        ( self )->buffer[i]         =   buf;
        buf                         =   NULL;
    }
}

HOWTO_FINI                     (   Color_buffer_t,   self   )
{
    if                              (   !self   )
        return;
 
    //  Free up memory for all the plane buffers

    for                             (   int i = 0;
                                        i < self->num_buffers;
                                        i++
                                    )
    {
        uint32_t                    *buf = self->buffer [ i ];
        DEALLOC                     (   buf   );
    }

    //  Free the color buffer

    DEALLOC                         (   self    );
}

static
inline
int
get_pixel_offset                    (   int     width,
                                        int     posX,
                                        int     posY
                                    )
{
    RET                             (   width * posY   +   posX   );
}

bool
paint_color                         (   Color_t            *color,
                                        Color_buffer_t     *colorbuf,
                                        Format_type_t      format_type,
                                        int                posX,
                                        int                posY,
                                        int                plane
                                    )
{

    uint32_t                            *buf        =      NULL,
                                        val         =      0;

    int                                 offset      =      0;
    bool                                ret         =      FAIL;

    assert                          (   color   &&  colorbuf   );

    if                              (   posX    <   0
                                    ||  posX    >   colorbuf->width
                                    ||  posY    <   0
                                    ||  posY    >   colorbuf->height
                                    )
    {
        LOG                         (   "Invalid args: posX: %d, posY: %d\n",
                                        posX,   posY
                                    );

        RET                         (   FAIL   );
    }

    assert                          (   plane   <   colorbuf->num_buffers   );

    //  Get the buffer address for this image plane

    buf                             =   colorbuf->buffer[plane];

    if                              (   !buf    )
    {
        LOG                         (   "colorbuf->buffer[%d] is NULL\n",
                                        plane   );
        RET                         (   FAIL    );
    }

    //  Get the offset in buffer for pixel co-ordinate ( posX, posY )

    offset                          =   get_pixel_offset  (   colorbuf->width,
                                                              posX,
                                                              posY
                                                          );

    //  Get the color value

    ret                             =   get_color_val     (   color,
                                                              &val,
                                                              format_type
                                                          );
    if                              (   ret != SUCCESS   )
    {
        LOG                         (   "get_color failed\n"    );
        RET                         (   FAIL    );
    }

    // Write the color value at this buffer offset
    buf [ offset ]                  =   val;

    // Use the force Luke!
    return SUCCESS;
}




static
bool
fill_color_buffer                   (   Color_buffer_t*   buffer,
                                        Color_t*          color,
                                        Format_type_t     format_type,
                                        int               width,
                                        int               height
                                    )
{

    bool                                ret     =   FAIL;

    for                             (   int y   =   0;   y  <   height;   y++   )
        for                         (   int x   =   0;   x  <   width;    x++   )
        {
            ret                     =   paint_color  (    color,
                                                          buffer,
                                                          format_type,
                                                          x,        y,
                                                          0
                                                    );

            if                      (   ret != SUCCESS   )
            {
                LOG                 (   "paint color failed at x:%d y: %d\n",
                                        x, y
                                    );
                RET                 (   FAIL    );
            }
        }

    // Use the force, Luke!
    return  SUCCESS;
}




bool
clear_color_buffer                  (   Color_buffer_t*   buffer   )
{

    bool                                ret     =   FAIL;

    Color_t                             *black  =   NULL;

    //  Make a Black color

    NEW                             (   Color_t,
                                        black,
                                        0x00,      //   no red
                                        0x00,      //   no green
                                        0x00,      //   no blue
                                        0xFF       //   opaque alpha
                                    );

    if                              (   !black   )
    {
        LOG                         (   "failed to create color\n"   );
        RET                         (   FAIL   );
    }

    /*
     *  Fill the color buffer with our color to the full width and height of the
     *  buffer
     */

    ret                             =   fill_color_buffer   (   buffer,
                                                                black,
                                                                PIXELFORMAT_ARGB8888,
                                                                buffer->width,
                                                                buffer->height
                                                            );

    if                              (   ret != SUCCESS   )
    {
        LOG                         (   "failed to fill color buffer\n"   );
        RET                         (   FAIL   );
    }

    // Use the force Luke!
    return SUCCESS;
}

