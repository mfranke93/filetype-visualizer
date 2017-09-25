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
            if (location < 0.0 || location > 1.0)
            {
                throw std::out_of_range("location must be in range [0;1]");
            }
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
            explicit StandardColormap(std::vector<locationizedColor> const& locCol)
                : colors(locCol)
            {
                if (locCol.empty()) throw std::invalid_argument("Location col array may not be empty!");
                if (locCol.front().location != 0.0) throw std::invalid_argument("Location col array's first entry must have location 0.0!");
                if (locCol.back().location != 1.0) throw std::invalid_argument("Location col array's last entry must have location 1.0!");
                for (auto it = locCol.begin(); it < locCol.end()-1; ++it)
                {
                    if (it->location >= (it+1)->location) throw std::invalid_argument("Location col array must be sorted!");
                }
            }
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
             * \return color
             * \throw normalizer exception if location not in range [0;1]
             */
            color getColor(double const&) const;

            /**
             * Build and get a predefined color map.
             *
             * \param color map type
             * \return color map
             */
            static std::shared_ptr<StandardColormap const> getPredefinedColormap(PredefinedColormaps const&);
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
