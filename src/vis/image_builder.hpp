#include <memory>
#include <vector>
#include "colormap.hpp"
#include "image.hpp"
#include "../except/illegal_size_exception.hpp"

#pragma once

namespace vis
{
    struct ImageProperties 
    {
        ImageProperties() : ImageProperties(0) {};
        ImageProperties(size_t const& widthHeight) : ImageProperties(widthHeight, widthHeight) {};
        ImageProperties(size_t const& width, size_t const& height) : ImageProperties(width, height, 0,0,0,0) {};
        ImageProperties(size_t const width, size_t const height, size_t const marginTop, size_t const marginBottom, size_t const marginLeft, size_t const marginRight)
            :   width(width),
                height(height),
                marginTop(marginTop),
                marginBottom(marginBottom),
                marginLeft(marginLeft),
                marginRight(marginRight),
                scale(1),
                marginColor(0,0,0)
        {};

        size_t width;
        size_t height;
        size_t marginTop;
        size_t marginBottom;
        size_t marginLeft;
        size_t marginRight;
        size_t scale;
        vis::color marginColor;
    };

    /**
     * Class to handle building images from data.
     */
    class ImageBuilder
    {
        public:
            /**
             * Build image from normalized data.
             *
             * \param width Width of the resulting image
             * \param height Height of the resulting image
             * \param normalizedValues A shared pointer to a vector of doubles.
             *        Those are expected to be in range [0;1] and the length of the
             *        vector is expected to be at least width x height.
             * \param colormap A shared pointer to a colormap.
             * \return A shared pointer to an image object.
             */
            static std::shared_ptr<Image> buildImageFromData(ImageProperties const& properties,
                    std::shared_ptr<std::vector<double>> const& normalizedValues,
                    std::shared_ptr<Colormap const> const& colormap);
    };
}
