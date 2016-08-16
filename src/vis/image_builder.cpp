#include "image_builder.hpp"

std::shared_ptr<vis::Image>
vis::ImageBuilder::buildImageFromData(size_t const& width,
                                      size_t const& height,
                                      std::shared_ptr<std::vector<double>> const& normalizedValues,
                                      std::shared_ptr<vis::Colormap const> const& colormap)
throw(std::length_error, except::illegal_size, except::normalizer_exception)
{
    if (normalizedValues->size() != width*height)
    {
        char buf [1024];
        sprintf(buf, "%s: Method expects %lu x %lu = %lu values, but %lu given.", __func__, width, height, width*height, normalizedValues->size());
        throw except::illegal_size(buf);
    }

    std::shared_ptr<vis::Image> img = std::make_shared<vis::Image>(width, height);
    for (size_t x = 0; x < width; ++x)
    {
        for (size_t y = 0; y < height; ++y)
        {
            (*img)(x, y) = colormap->getColor(normalizedValues->at(x+width*y));
        }
    }

    return img;
}
