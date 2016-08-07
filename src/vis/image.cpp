#include "image.hpp"

vis::Image::Image(size_t const& widthHeight)
throw(std::length_error)
:   width(widthHeight),
    height(widthHeight)
{
    if (width == 0 || height == 0)
    {
        throw std::length_error("Width and height of image must be greater than zero.");
    }
    this->pixels = new color [ this->width * this->height ];
}

vis::Image::Image(size_t const& w, size_t const& h)
throw(std::length_error)
:   width(w),
    height(h)
{
    if (width == 0 || height == 0)
    {
        throw std::length_error("Width and height of image must be greater than zero.");
    }
    this->pixels = new color [ this->width * this->height ];
}

vis::Image::~Image()
{
    if (this->pixels != nullptr)
    {
        delete [] this->pixels;
    }
}

vis::color&
vis::Image::operator() (size_t const& x, size_t const& y)
throw (std::out_of_range, std::logic_error)
{
    if (this->pixels == nullptr)
    {
        throw std::logic_error("Pixel array not initialized.");
    }
    if (this->width <= x || this->height <= y)
    {
        char buf [256];
        sprintf(buf, "Pixel coordinate (%lu, %lu) not in range (%lu, %lu).", x, y, this->width, this->height);
        throw std::out_of_range(buf);
    }

    return this->pixels[x + this->width*y];
}

vis::color const&
vis::Image::operator() (size_t const& x, size_t const& y) const
throw (std::out_of_range, std::logic_error)
{
    if (this->pixels == nullptr)
    {
        throw std::logic_error("Pixel array not initialized.");
    }
    if (this->width <= x || this->height <= y)
    {
        char buf [256];
        sprintf(buf, "Pixel coordinate (%lu, %lu) not in range (%lu, %lu).", x, y, this->width, this->height);
        throw std::out_of_range(buf);
    }

    return this->pixels[x + this->width*y];
}
