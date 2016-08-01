#pragma once

namespace vis 
{
    /**
     * typedef for one channel of an RGB pixel value.
     */
    typedef unsigned char channel;
    typedef struct {
        channel R;
        channel G;
        channel B;
    } color;

    /**
     * Class for colormaps.
     *
     * Generally just gives a unsigned char triplet (RGB) for each double in
     * range [0; 1].
     */
    class Colormap
    {
        public:
            /**
             * Get color for one value.
             *
             * \param   Value between 0 and 1 to be mapped to color
             * \param   Red, green, blue channel values as color struct
             */
            virtual void getColor(double const&, color&) const = 0;
    };
}
