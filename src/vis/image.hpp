#include <cstddef>
#include <stdexcept>
#include "colormap.hpp"

#pragma once

namespace vis
{
    class Image
    {
        public:
            explicit Image(size_t const&);
            explicit Image(size_t const&, size_t const&);

            ~Image();

            color& operator() (size_t const&, size_t const&) throw(std::out_of_range, std::logic_error);
            color const& operator() (size_t const&, size_t const&) const throw(std::out_of_range, std::logic_error);

            size_t const& getHeight() { return this->height; }
            size_t const& getWidth() { return this->width; }
        protected:
            Image() = delete;
            Image(Image const&) = delete;
            Image& operator= (Image const&) = delete;
        private:
            size_t const width;
            size_t const height;

            color * pixels = nullptr;
    };
}
