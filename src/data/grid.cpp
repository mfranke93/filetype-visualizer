#include "grid.hpp"

template <typename _T>
data::Grid<_T>::~Grid()
{
    if (this->data == nullptr) delete [] data;
}

template <typename _T>
data::Grid<_T>::Grid(Grid<_T> const& other)
:   x_size(other.x_size), y_size(other.y_size)
{
    this->data = new _T [x_size * y_size];
    for (size_t i = 0; i < x_size * y_size; ++i) this->data[i] = other.data[i];
}

template <typename _T>
data::Grid<_T>::Grid(size_t const& x_size)
:   data::Grid<_T>::Grid(x_size, x_size) 
{
    // ctor
}

template <typename _T>
data::Grid<_T>::Grid(size_t const& x_size, size_t const& y_size)
:   x_size(x_size), y_size(y_size)
{
    if (x_size == 0 || y_size == 0)
    {
        char buf [256];
        sprintf(buf, "Cannot construct grid of size %lux%lu.", x_size, y_size);
        throw except::illegal_size(buf);
    }
    this->data = new _T [x_size * y_size];
    for (size_t i = 0; i < x_size * y_size; ++i) this->data[i] = _T(0);
}

template <typename _T>
_T& data::Grid<_T>::operator() (size_t const& x, size_t const& y)
{ 
    if (x >= this->x_size || y >= this->y_size)
    {
        char buf [256];
        sprintf(buf, "Cannot access value at position (%lu, %lu) for grid of dimension (%lu, %lu).",
                x, y, this->x_size, this->y_size);
        throw std::out_of_range(buf);
    }
    return *(this->data + x + this->x_size*y);
}

template <typename _T>
_T const& data::Grid<_T>::operator() (size_t const& x, size_t const& y) const
{ 
    if (x >= this->x_size || y >= this->y_size)
    {
        char buf [256];
        sprintf(buf, "Cannot access value at position (%lu, %lu) for grid of dimension (%lu, %lu).",
                x, y, this->x_size, this->y_size);
        throw std::out_of_range(buf);
    }
    return *(this->data + x + this->x_size*y);
}

template <typename _T>
_T data::Grid<_T>::getMaximum() const
{
    _T a = this->data[0];
    for (size_t i = 0; i < this->x_size * this->y_size; ++i)
    {
        if (this->data[i] > a)
        {
            a = this->data[i];
        }
    }

    return a;
}

template <typename _T>
std::shared_ptr<std::vector<_T>> 
data::Grid<_T>::asVector() const
{
    std::shared_ptr<std::vector<_T>> vec = std::make_shared<std::vector<_T>>();
    for (size_t y = 0; y < this->y_size; ++y)
    {
        for (size_t x = 0; x < this->x_size; ++x)
        {
            vec->push_back((*this)(x,y));
        }
    }

    return vec;
}

/* instantiations */
template class data::Grid<float>;
template class data::Grid<double>;
template class data::Grid<size_t>;
template class data::Grid<int>;

