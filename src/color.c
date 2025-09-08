/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "color.h"
#include "util.h"

Format_t
formats_lut[]                   = {

    [ PIXELFORMAT_ARGB8888 ]    = {

        .sdl_type               = SDL_PIXELFORMAT_ARGB8888,
        .b_shft                 = 0,
        .g_shft                 = 8,
        .r_shft                 = 16,
        .a_shft                 = 24,
        .bpp                    = 32,
        .planes                 = 1,
        .flags                  = {
            .has_alpha          = true,
        },
    },

    [ PIXELFORMAT_XRGB4444 ]    = {

        .sdl_type               = SDL_PIXELFORMAT_XRGB4444,
        .a_shft                 = 12,
        .r_shft                 = 8,
        .g_shft                 = 4,
        .b_shft                 = 0,
        .bpp                    = 16,
        .planes                 = 1,
        .flags                  = {
            .has_alpha          = false,
        },
    },

    [ PIXELFORMAT_RGBA8888 ]    = {

        .sdl_type               = SDL_PIXELFORMAT_RGBA8888,
        .a_shft                 = 0,
        .b_shft                 = 8,
        .g_shft                 = 16,
        .r_shft                 = 24,
        .bpp                    = 32,
        .planes                 = 1,
        .flags                  = {
            .has_alpha          = false,
        },
    },
};

Format_t*
lookup_format                   (   format_type_t format_type   )
{
    switch                      (   format_type   )
    {
        case                    (   PIXELFORMAT_ARGB8888    ):
        case                    (   PIXELFORMAT_XRGB4444    ):
        case                    (   PIXELFORMAT_RGBA8888    ):
            RETURN              (   &formats_lut[format_type]  );
        default:
            RETURN              (   NULL    );
    }
}

static
bool
update_color_val                (   Color_t* color   )
{
    DECLARE_PTR                 (   format,    Format_t,   NULL   );

    format                      =   lookup_format (   color->format_type   );
    if                          (   !format   )
    {
        LOG                     (   "Unsupported Format type %d\n",
                                    color->format_type   );
        RETURN                  (   FAIL   );
    }
    color->val                  =   ( color->rgb.r << format->r_shft
                                    | color->rgb.g << format->g_shft
                                    | color->rgb.b << format->b_shft    );

    /**
     * Some formats like XRGB8888 doesn't use or discard the alpha
     * component of the color. |X| stands for `don't care`
     */
    if                          (   format->flags.has_alpha   )
        color->val              |=  (   color->rgb.a << format->a_shft   );

    color->dirty                =   false;

    // Use the force Luke!
    return SUCCESS;
}

/**
 * Constructor for creating a color
 */
CONSTRUCTOR                     (   Color_t,
                                    uint8_t         r,
                                    uint8_t         g,
                                    uint8_t         b,
                                    uint8_t         a,
                                    format_type_t   f_t   )
{

    DECLARE_PTR                 (   c,  Color_t,  NULL   );

    if                          (   f_t >= PIXELFORMAT_MAX   )
    {
        LOG                     (   "Unsupported pixel format %d\n", f_t   );
        RETURN                  (   NULL   );
    }

    ALLOC_ZEROED                (   1,  Color_t,  c   );

    if                          (   !c   )
        RETURN                  (   NULL   );

    c->rgb.r                    =   r;
    c->rgb.g                    =   g;
    c->rgb.b                    =   b;
    c->rgb.a                    =   a;

    c->format_type              =   f_t;
    update_color_val            (   c   );
    RETURN                      (   c   );
}

DESTRUCTOR                      (   Color_t  )
{
    DEALLOC                     (   object   );
}

static
bool
get_color                       (   Color_t     *color,
                                    uint32_t    *val   )
{
    if                          (   !color || !val   )
    {
        LOG                     (   "Invalid args\n"   );
        RETURN                  (   FAIL   );
    }

    if                          (   color->dirty    )
    {
        if                      (   update_color_val (  color  )
                                    != SUCCESS   )
            RETURN              (   FAIL   );
    }

    *val                        =   color->val;

    // Use the force Luke!
    return SUCCESS;
}

static
bool
set_color_rgb                   (   Color_t *color,
                                    uint8_t red,
                                    uint8_t green,
                                    uint8_t blue,
                                    uint8_t alpha   )
{
    if                          (   !color   )
    {
        LOG                     (   "Invalid args\n"   );
        RETURN                  (   FAIL   );
    }

    color->rgb.r                =   red;
    color->rgb.g                =   green;
    color->rgb.b                =   blue;
    color->rgb.a                =   alpha;

    color->dirty                =   true;

    // Use the force Luke!
    return SUCCESS;
}

static
bool
set_color_format                (   Color_t *color,
                                    format_type_t format_type   )
{
    if                          (   !color
                                    || format_type >= PIXELFORMAT_MAX   )
    {
        LOG                     (   "Invalid args\n"   );
        RETURN                  (   FAIL   );
    }
    color->format_type          =   format_type;
    color->dirty                =   true;

    // Use the force, Luke!
    return SUCCESS;
}

CONSTRUCTOR                     (   Color_buffer_t,
                                    int                 w,
                                    int                 h,
                                    format_type_t       f_t    )
{

    DECLARE_PTR                 (   colorbuf,   Color_buffer_t,   NULL    );
    DECLARE_PTR                 (   format,     Format_t,         NULL    );

    uint32_t                        *buf  = NULL,
                                    *prev = NULL;

    format                      =   lookup_format ( f_t );

    if                          (   !format   )
    {
        LOG                     (   "Invalid format: %d\n", (int) f_t   );
        RETURN                  (   NULL   );
    }

    ALLOC_ZEROED                (   1, Color_buffer_t, colorbuf   );

    if                          (   !colorbuf   )
        RETURN                  (   NULL   );

    colorbuf->width             =   w;
    colorbuf->height            =   h;
    colorbuf->pitch             =   ( w  *  BITS_TO_BYTES ( format->bpp ) );
    colorbuf->num_buffers       =   format->planes;

    buf                         =   ALLOC_NONZEROED (   w * h, uint32_t   );

    if                          (   !buf   )
    {
        LOG                     (   "Couldn't allocate memory\n"    );
        DEALLOC                 (   colorbuf    );
        RETURN                  (   NULL    );
    }
    colorbuf->buffer[0]         =   buf;
    buf                         =   NULL;

    for                         (   int i = 1;
                                    i < format->planes;
                                    i++   )
    {

        buf                     =   ALLOC_NONZEROED (   w * h, uint32_t   );

        if                      (   !buf   )
        {
            // free up all the previous plane buffers
            for                 (   int j = 0; j < i; j++   )
            {
                prev            =   colorbuf->buffer[ j ];
                DEALLOC         (   prev   );
            }

            // Free the color buffer
            DEALLOC             (   colorbuf    );
            RETURN              (   NULL    );
        }
            colorbuf->buffer[i] =   buf;
            buf                 =   NULL;
    }

    RETURN                      (   colorbuf    );
}

DESTRUCTOR                      (   Color_buffer_t  )
{
    if                          (   !object   )
        return;
 
    // Free up memory for all the plane buffers
    for                         (   int i = 0;
                                    i < object->num_buffers;
                                    i++   )
    {
        uint32_t                    *buf = object->buffer[ i ];
        DEALLOC                 (   buf   );
    }

    // Free the color buffer
    DEALLOC                     (   object   );
}

static
inline
int
get_pixel_offset                (   int width,
                                    int posX,
                                    int posY    )
{
    RETURN                      (   width * posY   +   posX   );
}

bool
paint_color                     (   Color_t*            color,
                                    Color_buffer_t*     colorbuf,
                                    int                 posX,
                                    int                 posY,
                                    int                 plane   )
{
    uint32_t                        *buf   = NULL,
                                    val    = 0;

    int                             offset = 0;
    bool                            ret    = FAIL;

    if                          (   !color || !colorbuf   )
    {
        LOG                     (   "Invalid args\n"    );
        RETURN                  (   FAIL    );
    }

    if                          (   posX < 0
                                 || posX > colorbuf->width
                                 || posY < 0
                                 || posY > colorbuf->height   )
    {
        LOG                     (   "Invalid args: posX: %d, posY: %d\n",
                                    posX, posY  );
        RETURN                  (   FAIL   );
    }

    if                          (   plane >= colorbuf->num_buffers   )
    {
        LOG                     (   "Invalid arg: plane: %d\n",
                                    plane   );
        RETURN                  (   FAIL    );
    }

    // Get the buffer address for this image plane
    buf                         =   colorbuf->buffer[plane];

    if                          (   !buf    )
    {
        LOG                     (   "colorbuf->buffer[%d] is NULL\n",
                                    plane   );
        RETURN                  (   FAIL    );
    }

    // Get the offset in buffer for pixel co-ordinate ( posX, posY )
    offset                      =   get_pixel_offset (    colorbuf->width,
                                                          posX, posY     );

    // Get the color value
    ret                         =   get_color (   color, &val   );
    if                          (   ret != SUCCESS   )
    {
        LOG                     (   "get_color failed\n"    );
        RETURN                  (   FAIL    );
    }

    // Write the color value at this buffer offset
    buf[ offset ]               =   val;

    // Use the force Luke!
    return SUCCESS;
}

static
bool
fill_color_buffer               (   Color_buffer_t* buffer,
                                    int             width,
                                    int             height,
                                    Color_t*        color   )
{
    bool                            ret = FAIL;

    for                         (   int y = 0;  y < height;  y++   )
        for                     (   int x = 0;  x < width;   x++   )
        {
            ret                 =   paint_color (   color,
                                                    buffer,
                                                    x, y,
                                                    0     );

            if                  (   ret != SUCCESS  )
            {
                LOG             (   "paint color failed at x:%d y: %d\n",
                                    x, y    );
                RETURN          (   FAIL    );
            }
        }

    // Use the force, Luke!
    return SUCCESS;
}

bool
clear_color_buffer              (   Color_buffer_t* buffer  )
{

    DECLARE_PTR                 (   black,  Color_t,    NULL   );

    bool                            ret = FAIL;

    // Construct a Black color
    CONSTRUCT                   (   black,
                                    Color_t,
                                    0x00,       // no red
                                    0x00,       // no green
                                    0x00,       // no blue
                                    0xFF,       // opaque alpha
                                    PIXELFORMAT_ARGB8888    );

    if                          (   !black  )
    {
        LOG                     (   "failed to create color\n"   );
        RETURN                  (   FAIL   );
    }

    /**
     * Fill the color buffer with our color to the full width and height of the
     * buffer
     */

    ret                         =   fill_color_buffer (  buffer,
                                                         buffer->width,
                                                         buffer->height,
                                                         black   );
    if                          (   ret != SUCCESS  )
    {
        LOG                     (   "failed to fill color buffer\n"   );
        RETURN                  (   FAIL   );
    }

    // Destroy the color as it's no longer needed
    DESTRUCT                    (   black,  Color_t   );

    // Use the force Luke!
    return SUCCESS;
}

