#include "image_builder.hpp"

std::shared_ptr<vis::Image>
vis::ImageBuilder::buildImageFromData(vis::ImageProperties const& properties,
                                      std::shared_ptr<std::vector<double>> const& normalizedValues,
                                      std::shared_ptr<vis::Colormap const> const& colormap)
{
    size_t const width = properties.width;
    size_t const height = properties.height;
    if (normalizedValues->size() != width*height)
    {
        char buf [1024];
        sprintf(buf, "%s: Method expects %lu x %lu = %lu values, but %lu given.", __func__, width, height, width*height, normalizedValues->size());
        throw except::illegal_size(buf);
    }

    size_t const imgWidth = properties.scale * width + properties.marginLeft + properties.marginRight;
    size_t const imgHeight= properties.scale * height + properties.marginTop + properties.marginBottom;

    std::shared_ptr<vis::Image> img = std::make_shared<vis::Image>(imgWidth, imgHeight);

    for (size_t x = 0; x < imgWidth; ++x)
    {
        for (size_t y = 0; y < imgHeight; ++y)
        {
            if (        (x > properties.marginLeft)
                    &&  (x < imgWidth - properties.marginRight)
                    &&  (y > properties.marginTop)
                    &&  (y < imgHeight - properties.marginBottom))
            {
                size_t const dataX = (x - properties.marginLeft) / properties.scale;
                size_t const dataY = (y - properties.marginTop) / properties.scale;

                (*img)(x, y) = colormap->getColor(normalizedValues->at(dataX+width*dataY));
            }
            else
            {
                (*img)(x, y) = properties.marginColor;
            }
        }
    }

    return img;
}
