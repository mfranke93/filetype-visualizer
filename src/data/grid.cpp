#include "grid.hpp"

template <typename _T>
data::Grid<_T>::Grid(Grid<_T> const& other)
:   x_size(other.x_size), y_size(other.y_size)
{
    this->data = new _T [x_size * y_size];
    for (size_t i = 0; i < x_size * y_size; ++i) this->data[i] = other.data[i];
}

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

template <typename _T>
_T const& data::Grid<_T>::operator() (size_t const& x, size_t const& y) const
{ 
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

/* instantiations */
template class data::Grid<float>;
template class data::Grid<double>;
template class data::Grid<size_t>;

