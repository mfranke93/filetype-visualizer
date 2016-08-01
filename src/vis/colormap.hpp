/**
 * typedef for one channel of an RGB pixel value.
 */
typedef unsigned char channel;

namespace vis 
{
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
             * \param   Red channel value
             * \param   Green channel value
             * \param   Blue channel value
             */
            void getColor(double const&, channel&, channel&, channel&) const;
    };
}
