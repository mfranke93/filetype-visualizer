#include "../except/normalizer_exception.hpp"

#pragma once

namespace vis 
{
    /**
     * typedef for one channel of an RGB pixel value.
     */
    typedef unsigned char channel;
    struct color {
        color()
        :   color(0, 0, 0)
        {
            // ctor
        }

        color(channel const& r, channel const& g, channel const& b)
        :   R(r), G(g), B(b)
        {
            // ctor
        }

        channel R;
        channel G;
        channel B;
    };

    /**
     * Class for colormaps.
     *
     * Generally just gives a unsigned char triplet (RGB) for each double in
     * range [0; 1].
     */
    class Colormap
    {
        public:
            virtual ~Colormap() = default;
            /**
             * Get color for one value.
             *
             * \param   Value between 0 and 1 to be mapped to color
             * \param   Red, green, blue channel values as color struct
             * \throw   except::normalizer_exception if value not in range [0;1]
             */
            virtual color getColor(double const&) const throw(except::normalizer_exception) = 0;
    };
}
