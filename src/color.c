/* Copyright © 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */

#include "color.h"
#include "util.h"




 ////////////////////////////////////////////////////////////////////////////////////
 //
 //
 //      On modern day systems, we always represent a color value as a 32-
 //      bit integer. Each of the color components (R, G and B) are packed
 //      into the successive 8-bits of a 32-bit integer ( with last 8-bits
 //      reserved for other purposes). Thus, each color component can take
 //      up a value between 0 and 255 representing the intensity of that
 //      individual component. This provides us with a wide range of colors
 //      (256 * 256 * 256).
 //
 //
 //       |<--------------  32-bit integer  ------------->|
 //       +-----------------------------------------------+
 //       |   8-bit   |   8-bit   |   8-bit   |   8-bit   |
 //       +------+----------+-----------+-----------+-----+
 //              |          |           |           |
 //              |          |           |           |
 //              |          |           |           +--------> B  channel
 //              |          |           +--------------------> G  channel
 //              |          +--------------------------------> R  channel
 //              +-------------------------------------------> A  channel
 //
 //
 //      On older 8-bit and 16-bit systems this was not the case. We had
 //      a very limited number of colors that we could use to paint our
 //      scenes (256 for 8-bit systems). Therefore, these systems would
 //      instead use a color pallete (or lookup table) of the available
 //      colors. The color value was then used as an index into the color
 //      pallete in order to determine the final color of the pixel.
 //
 //
 //      Having each of the color components packed into the successive
 //      8-bits of a 32-bit integer value makes sense from a performace
 //      perspective, since all three color channels are needed together
 //      in order to determine the final pixel color. Therefore, having
 //      them in a single cache line reduces the number of cache misses.
 //
 //
 //      However, there are situations where having the individual color
 //      components inside separate integers is more useful. For e.g. if
 //      you are doing some kind of image processing work where you wish
 //      to amplify only one of the components ( Red for e.g. ), but not
 //      want to touch any of the other color components. In this case,
 //      having all the Red values in a separate buffer makes more sense
 //      since we want to have only the Red values inside our cache line.
 //      This also allows us to pack more bits for our Red component, so
 //      that we can now have a more fine grained control over it, while
 //      keeping the number of bits for the Green and Blue color values
 //      the same as before.
 //
 //
 ////////////////////////////////////////////////////////////////////////////////////

struct Color
{
    union
    {
        struct
        {
            uint8_t                     r;
            uint8_t                     g;
            uint8_t                     b;
            uint8_t                     a;
        }   rgba;

        // TODO: Support YUV formats
        uint32_t                        yuv;
    };
};


struct Format
{
    SDL_PixelFormatEnum                 sdl_type;
    int                                 r_shft;
    int                                 g_shft;
    int                                 b_shft;
    int                                 a_shft;
    int                                 bpp;
    int                                 planes;
    struct
    {
        bool                            has_alpha;
        bool                            has_modifiers;
    }   flags;
};


struct color_buffer
{
    int                                 width;
    int                                 height;
    int                                 pitch;
    int                                 num_buffers;
    Format_type_t                       format_type;
    uint32_t*                           buffer[4];
};

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



HOWTO_COMPOSE                       (   Color_t,
                                        self,
                                        uint8_t     red,
                                        uint8_t     green,
                                        uint8_t     blue,
                                        uint8_t     alpha
                                    )
{
    self->rgba.r                    =   red;
    self->rgba.g                    =   green;
    self->rgba.b                    =   blue;
    self->rgba.a                    =   alpha;
}

static
METHOD                              (   Color_t,
                                        get_color_val,
                                        self,
                                        Format_type_t   format_type,
                                        uint32_t*       out
                                    )
{
    PTR                             (   Format_t,
                                        format,
                                        NULL
                                    );

    format                          =   lookup_format   (   format_type   );
    ASSERT                          (   format != NULL,
                                        "Unsupported Format type %d\n",
                                        format_type
                                    );

    *out                            =   (   self->rgba.r << format->r_shft   |
                                            self->rgba.g << format->g_shft   |
                                            self->rgba.b << format->b_shft
                                        );

     // Some formats like XRGB8888 doesn't use or discard the alpha
     // component of the color. |X| stands for `don't care`

    if                              (   format->flags.has_alpha   )
        *out                        |=  self->rgba.a << format->a_shft;
}




HOWTO_CONSTRUCT                     (   Color_buffer_t,
                                        self,
                                        int                 width,
                                        int                 height,
                                        Format_type_t       format_type
                                    )
{

    PTR                             (   Format_t,
                                        format,
                                        NULL
                                    );

    uint32_t                            *buf  = NULL,
                                        *prev = NULL;

    int                                 pitch = 0;

    format                          =   lookup_format   (   format_type   );

    ASSERT                          (   format != NULL,
                                        "Unsupported Format type %d\n",
                                        format_type
                                    );

    ALLOC_ZEROED                    (   Color_buffer_t,
                                        self,
                                        1
                                    );

    if                              (   !self   )
        RETURN                      (   NULL   );

    self->width                     =   width;
    self->height                    =   height;

    CALLM                           (   Format_t,
                                        get_pitch,
                                        format,
                                        width,
                                        &pitch
                                    );

    self->pitch                     =   pitch;

    self->num_buffers               =   format->planes;
    self->format_type               =   format_type;

    buf                             =   ALLOC_NONZEROED (   width * height,   uint32_t   );

    ASSERT                          (   buf != NULL,
                                        "Couldn't allocate memory\n"
                                    );

    self->buffer[0]                 =   buf;
    buf                             =   NULL;

    for                             (   int i = 1;
                                        i < format->planes;
                                        i++   )
    {

        buf                         =   ALLOC_NONZEROED (   width * height,   uint32_t   );

        ASSERT                      (   buf != NULL, "" );

        self->buffer[i]             =   buf;
            buf                     =   NULL;
    }

    RETURN                          (   self    );
}

HOWTO_DESTRUCT                      (   Color_buffer_t,
                                        self
                                    )
{
}


METHOD                              (   Format_t,
                                        get_pitch,
                                        self,
                                        int     width,
                                        int*    out
                                    )
{
    ASSERT                          (   self != NULL && out != NULL,
                                        "Invalid args\n"
                                    );

    *out                            =   width * BITS_TO_BYTES ( self->bpp );
}


METHOD                              (   Format_t,
                                        get_sdl_type,
                                        self,
                                        int*    out
                                    )
{
    ASSERT                          (   self != NULL && out != NULL,
                                        "Invalid args\n"
                                    );

    *out                            =   self->sdl_type;
}


METHOD                              (   Color_buffer_t,
                                        get_buffer_dimensions,
                                        self,
                                        int*    out_w,
                                        int*    out_h
                                    )
{
    ASSERT                          (   self != NULL && out_w != NULL && out_h != NULL,
                                        "Invalid args\n"
                                    );

    *out_w                          =   self->width;
    *out_h                          =   self->height;
}

METHOD                              (   Color_buffer_t,
                                        paint_color,
                                        self,
								    	Color_t*		color,
                                        int				posX,
                                        int				posY,
                                        int				plane
                                    )
{

    uint32_t                            *buf = NULL,
                                        val  = 0;

    int                                 offset = 0;
    bool                                ret    = FAIL;

    ASSERT                          (   color != NULL,
					    			    "Invalid args: color\n"
						    		);

    ASSERT                          (   ( posX => 0 )            &&
                                        ( posX <= self->width )  &&
                                        ( posY => 0 )            &&
                                        ( posY <= self->height ),
								    	"Invalid args: posX: %d, posY: %d\n",
                                        posX, posY
                                    );

    ASSERT                          (   ( plane < self->num_buffers ),
								    	"Invalid arg: plane: %d\n",
                                        plane
								    );


    // Get the buffer address for this image plane

    buf                             =   self->buffer [ plane ];

    ASSERT                          (   ( buf != NULL ), " colorbuf: buffer[%d] is NULL\n", plane    );


    // Get the offset in buffer for pixel co-ordinate ( posX, posY )

	CALLM						    (	Color_buffer_t,
								    	get_pixel_offset,
								    	self,
								    	posX,
								    	posY,
								    	&offset
								    );

    // Get the color value
	CALLM						    (	Color_t,
								    	get_color_val,
								    	color,
								    	self->format_type,
								    	&val
								    );


    // Write the color value at this buffer offset

    buf [ offset ]                  =   val;
}


METHOD							    (	Color_buffer_t,
								    	get_pixel_offset,
								    	self,
								    	int		posX,
								    	int		posY,
								    	int*	out
								    )
{
	*out						    =	self->width * posY  +  posX;
}