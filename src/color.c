/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "color.h"
#include "util.h"




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

            RETURN                  (   &formats_lut [ format_type ]  );
        default:
            RETURN                  (   NULL    );
    }
}




static
bool
set_color_rgb                       (   Color_t*    color,
                                        uint8_t     red,
                                        uint8_t     green,
                                        uint8_t     blue,
                                        uint8_t     alpha   )
{
    if                              (   !color   )
    {
        LOG                         (   "Invalid args\n"   );
        RETURN                      (   FAIL   );
    }

    color->rgba.r                   =   red;
    color->rgba.g                   =   green;
    color->rgba.b                   =   blue;
    color->rgba.a                   =   alpha;

    // Use the force Luke!
    return SUCCESS;
}




/**
 * Constructor for creating a color
 */
HOWTO_MAKE                          (   Color_t,
                                        color,
                                        uint8_t     r,
                                        uint8_t     g,
                                        uint8_t     b,
                                        uint8_t     a   )
{
    set_color_rgb                   (   color,      r,  g,
                                                    b,  a   );
}




static
bool
get_color_val                       (   Color_t*        color,
                                        uint32_t*       val,
                                        Format_type_t   format_type    )
{
    PTR                             (    Format_t,   format,    NULL   );

    format                          =   lookup_format   (   format_type   );
    if                              (   !format   )
    {
        LOG                         (   "Unsupported Format type %d\n",
                                        format_type   );
        *val                        =   0x00;
        RETURN                      (   FAIL   );
    }

    *val                        =   (   color->rgba.r << format->r_shft
                                      | color->rgba.g << format->g_shft
                                      | color->rgba.b << format->b_shft   );

    /**
     * Some formats like XRGB8888 doesn't use or discard the alpha
     * component of the color. |X| stands for `don't care`
     */
    if                              (   format->flags.has_alpha   )
        *val                        |=  (   color->rgba.a << format->a_shft   );

    // Use the force Luke!
    return SUCCESS;
}




CONSTRUCTOR                         (   Color_buffer_t,
                                        int             width,
                                        int             height,
                                        Format_type_t   format_type   )
{
    PTR                             (   Color_buffer_t,
                                        colorbuf,       NULL   );
    PTR                             (   Format_t,
                                        format,         NULL    );

    uint32_t                            *buf  = NULL,
                                        *prev = NULL;

    format                          =   lookup_format   (   format_type   );

    if                              (   !format   )
    {
        LOG                         (   "Invalid format: %d\n",
                                        (int) format_type
                                    );
        RETURN                      (   NULL   );
    }

    ALLOC_ZEROED                    (   Color_buffer_t,
                                        colorbuf,       1   );

    if                              (   !colorbuf   )
        RETURN                      (   NULL   );

    colorbuf->width                 =   width;
    colorbuf->height                =   height;
    colorbuf->pitch                 = ( width
                                        *  BITS_TO_BYTES ( format->bpp ) );
    colorbuf->num_buffers           =   format->planes;

    buf                             =   ALLOC_NONZEROED (   width * height,   uint32_t   );

    if                              (   !buf   )
    {
        LOG                         (   "Couldn't allocate memory\n"    );
        DEALLOC                     (   colorbuf    );
        RETURN                      (   NULL    );
    }
    colorbuf->buffer[0]             =   buf;
    buf                             =   NULL;

    for                             (   int i = 1;
                                        i < format->planes;
                                        i++   )
    {

        buf                         =   ALLOC_NONZEROED (   width * height,   uint32_t   );

        if                          (   !buf   )
        {
            // free up all the previous plane buffers
            for                     (   int j = 0; j < i; j++   )
            {
                prev                =   colorbuf->buffer[ j ];
                DEALLOC             (   prev   );
            }

            // Free the color buffer
            DEALLOC                 (   colorbuf    );
            RETURN                  (   NULL    );
        }
            colorbuf->buffer[i]     =   buf;
            buf                     =   NULL;
    }

    RETURN                          (   colorbuf    );
}

DESTRUCTOR                          (   Color_buffer_t  )
{
    if                              (   !object   )
        return;
 
    // Free up memory for all the plane buffers
    for                             (   int i = 0;
                                        i < object->num_buffers;
                                        i++
                                    )
    {
        uint32_t                    *buf = object->buffer [ i ];
        DEALLOC                     (   buf   );
    }

    // Free the color buffer
    DEALLOC                         (   object    );
}

static
inline
int
get_pixel_offset                    (   int width,
                                        int posX,
                                        int posY    )
{
    RETURN                          (   width * posY   +   posX   );
}

bool
paint_color                         (   Color_t*           color,
                                        Color_buffer_t*    colorbuf,
                                        Format_type_t      format_type,
                                        int                posX,
                                        int                posY,
                                        int                plane   )
{

    uint32_t                            *buf   = NULL,
                                        val    = 0;

    int                                 offset = 0;
    bool                                ret    = FAIL;

    if                              (   !color || !colorbuf   )
    {
        LOG                         (   "Invalid args\n"    );
        RETURN                      (   FAIL    );
    }

    if                              (      posX < 0
                                        || posX > colorbuf->width
                                        || posY < 0
                                        || posY > colorbuf->height   )
    {
        LOG                         (   "Invalid args: posX: %d, posY: %d\n",
                                        posX, posY  );
        RETURN                      (   FAIL   );
    }

    if                              (   plane >= colorbuf->num_buffers   )
    {
        LOG                         (   "Invalid arg: plane: %d\n",
                                        plane   );
        RETURN                      (   FAIL    );
    }

    // Get the buffer address for this image plane
    buf                             =   colorbuf->buffer[plane];

    if                              (   !buf    )
    {
        LOG                         (   "colorbuf->buffer[%d] is NULL\n",
                                        plane   );
        RETURN                      (   FAIL    );
    }

    // Get the offset in buffer for pixel co-ordinate ( posX, posY )
    offset                          =   get_pixel_offset  (   colorbuf->width,
                                                              posX,
                                                              posY
                                                          );

    // Get the color value
    ret                             =   get_color_val     (   color,
                                                              &val,
                                                              format_type
                                                          );
    if                              (   ret != SUCCESS   )
    {
        LOG                         (   "get_color failed\n"    );
        RETURN                      (   FAIL    );
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
                                        int               height          )
{

    bool                                ret = FAIL;

    for                             (   int y = 0;   y <  height;   y++   )
        for                         (   int x = 0;   x <  width;    x++   )
        {
            ret                     =   paint_color  (    color,
                                                          buffer,
                                                          format_type,
                                                          x,
                                                          y,
                                                          0
                                                    );

            if                      (   ret != SUCCESS   )
            {
                LOG                 (   "paint color failed at x:%d y: %d\n",
                                        x, y
                                    );
                RETURN              (   FAIL    );
            }
        }

    // Use the force, Luke!
    return SUCCESS;
}




bool
clear_color_buffer                  (   Color_buffer_t*   buffer   )
{

    bool                                ret = FAIL;

    MEM                             (   Color_t,   black,   1   );

    // Make a Black color
    MAKE                            (   Color_t,
                                        black,
                                        0x00,      // no red
                                        0x00,      // no green
                                        0x00,      // no blue
                                        0xFF       // opaque alpha
                                    );

    if                              (   !black   )
    {
        LOG                         (   "failed to create color\n"   );
        RETURN                      (   FAIL   );
    }

    /**
     * Fill the color buffer with our color to the full width and height of the
     * buffer
     */

    ret                             =   fill_color_buffer (   buffer,
                                                              black,
                                                              PIXELFORMAT_ARGB8888,
                                                              buffer->width,
                                                              buffer->height
                                                          );

    if                              (   ret != SUCCESS   )
    {
        LOG                         (   "failed to fill color buffer\n"   );
        RETURN                      (   FAIL   );
    }

    // Use the force Luke!
    return SUCCESS;
}

