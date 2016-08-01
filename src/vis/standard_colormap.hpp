#include "colormap.hpp"
#include <vector>
#include <memory>

namespace vis
{
    typedef struct {
        double location;
        color c;
    } locationizedColor;

    class StandardColormap: public Colormap
    {
        public:
            StandardColormap(std::vector<locationizedColor> const& locCol)
                : colors(locCol)
            {}
            ~StandardColormap() = default;

            void addColor(double const&, color const&);
            void getColor(double const&, color&) const override;
        protected:
            StandardColormap() = delete;
            StandardColormap(StandardColormap const&) = delete;
            StandardColormap& operator= (StandardColormap const&) = delete;
        private:
            std::vector<locationizedColor> colors;
    };
}
