#include <memory>
#include <vector>
#include "colormap.hpp"
#include "image.hpp"

#pragma once

namespace vis
{
    class ImageBuilder
    {
        public:
            static std::shared_ptr<Image> buildImageFromData(size_t const& width,
                                                             size_t const& height,
                                                             std::shared_ptr<std::vector<double>> const& normalizedValues,
                                                             std::shared_ptr<Colormap const> const& colormap);
    };
}
