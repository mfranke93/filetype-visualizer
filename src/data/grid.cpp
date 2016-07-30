#include "grid.hpp"

template <typename _T>
data::Grid<_T>::Grid(size_t const& x_size)
:   x_size(x_size), y_size(x_size)
{
    this->data = new _T [x_size * x_size];
}

template <typename _T>
data::Grid<_T>::Grid(size_t const& x_size, size_t const& y_size)
:   x_size(x_size), y_size(y_size)
{
    this->data = new _T [x_size * y_size];
}

template <typename _T>
_T& data::Grid<_T>::operator() (size_t const& x, size_t const& y)
{ 
    return *(this->data + x + this->x_size*y);
}

/* instantiations */
template class data::Grid<float>;

