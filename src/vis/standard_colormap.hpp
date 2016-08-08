#include "colormap.hpp"
#include <vector>
#include <memory>

namespace vis
{
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

    enum class PredefinedColormaps
    {
        RED_BLUE,
        BLACK_BODY_HEAT,
        DEEP_SEA,
        dummy
    };

    class StandardColormap: public Colormap
    {
        public:
            StandardColormap(std::vector<locationizedColor> const& locCol)
                : colors(locCol)
            {}
            ~StandardColormap() = default;

            void addColor(double const&, color const&);
            void getColor(double const&, color&) const override;

            static std::shared_ptr<StandardColormap const> getPredefinedColormap(PredefinedColormaps const&);
        protected:
            StandardColormap() = delete;
            StandardColormap(StandardColormap const&) = delete;
            StandardColormap& operator= (StandardColormap const&) = delete;
        private:
            std::vector<locationizedColor> colors;
    };


}
