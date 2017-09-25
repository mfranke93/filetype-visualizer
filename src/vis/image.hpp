#include <cstddef>
#include <stdexcept>
#include "colormap.hpp"

#pragma once

namespace vis
{
    /**
     * Class for the representation of image data.
     *
     * Objects of this class contain the pixel values for an image of given
     * size. This class is used to store image data internally. This has
     * multiple reasons: For one, we can then write the image multiple times to
     * different files without having to calculate the values of the pixels
     * every time. Also, we decouple the actual IO process from the generation
     * of the color values.
     */
    class Image
    {
        public:
            /**
             * Constructor.
             *
             * Assumes width = height
             *
             * \param Width and height
             */
            explicit Image(size_t const&);

            /**
             * Constructor.
             *
             * \param Width
             * \param Height
             */
            explicit Image(size_t const&, size_t const&);

            /**
             * Destructor.
             * Deallocates pixel array.
             */
            ~Image();

            /**
             * Non-const access operator to one pixel value.
             *
             * \param x coordinate
             * \param y coordinate
             * \throw std::out_of_range if x or y value illegal
             * \throw std::logic_error if image data pointer uninitialized
             * \return reference to pixel color value at coordinates
             */
            color& operator() (size_t const&, size_t const&);

            /**
             * const access operator to one pixel value.
             *
             * \param x coordinate
             * \param y coordinate
             * \throw std::out_of_range if x or y value illegal
             * \throw std::logic_error if image data pointer uninitialized
             * \return const reference to pixel color value at coordinates
             */
            color const& operator() (size_t const&, size_t const&) const;

            /**
             * Get height of image.
             * \return Height
             */
            size_t const& getHeight() const { return this->height; }

            /**
             * Get width of image.
             * \return Width
             */
            size_t const& getWidth() const { return this->width; }
        protected:
            Image() = delete;
            Image(Image const&) = delete;
            Image& operator= (Image const&) = delete;
        private:
            /**
             * Stores width of image.
             */
            size_t const width;
            /**
             * Stores height of image.
             */
            size_t const height;

            /**
             * Image data.
             */
            color * pixels = nullptr;
    };
}
