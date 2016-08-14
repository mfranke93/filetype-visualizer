#include "colormap.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#pragma once

namespace vis
{
    /**
     * Struct for a combination of a color and a double between 0 and 1.
     */
    struct locationizedColor {
        locationizedColor(double const& location, color color)
        :   location(location), c(color)
        {
            // ctor
        }

        locationizedColor()
        :   location(0.0), c()
        {
            // ctor
        }

        double location;
        color c;
    };

    /**
     * Enum for predefined color maps.
     */
    enum class PredefinedColormaps
    {
        RED_BLUE,
        BLACK_BODY_HEAT,
        DEEP_SEA,
        GRAYSCALE
    };

    /**
     * Class for linear colormaps.
     */
    class StandardColormap: public Colormap
    {
        public:
            /**
             * Constructor.
             *
             * \param locCol Vector of locationizedColor:s
             */
            StandardColormap(std::vector<locationizedColor> const& locCol)
                : colors(locCol)
            {}
            /**
             * Destructor.
             */
            ~StandardColormap() = default;

            /**
             * Add color at location.
             *
             * \param location
             * \param color
             */
            void addColor(double const&, color const&);

            /**
             * Get color at location.
             *
             * \param location
             * \param color as reference
             * \throw normalizer exception if location not in range [0;1]
             */
            void getColor(double const&, color&) const throw(except::normalizer_exception) override;

            /**
             * Build and get a predefined color map.
             *
             * \param color map type
             * \return color map
             */
            static std::shared_ptr<StandardColormap const> getPredefinedColormap(PredefinedColormaps const&) throw(std::out_of_range);
        protected:
            StandardColormap() = delete;
            StandardColormap(StandardColormap const&) = delete;
            StandardColormap& operator= (StandardColormap const&) = delete;
        private:
            /**
             * Vector of location, color tuples.
             */
            std::vector<locationizedColor> colors;
    };
}
