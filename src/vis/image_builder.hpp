#include <memory>
#include <vector>
#include "colormap.hpp"
#include "image.hpp"
#include "../except/illegal_size_exception.hpp"

#pragma once

namespace vis
{
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
            static std::shared_ptr<Image> buildImageFromData(size_t const& width,
                                                             size_t const& height,
                                                             std::shared_ptr<std::vector<double>> const& normalizedValues,
                                                             std::shared_ptr<Colormap const> const& colormap)
                throw(std::length_error, except::illegal_size);
    };
}
