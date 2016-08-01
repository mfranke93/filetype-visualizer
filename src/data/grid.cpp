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
    for (size_t i = 0; i < x_size * y_size; ++i) this->data[i] = _T(0);
}

template <typename _T>
data::Grid<_T>::Grid(size_t const& x_size, size_t const& y_size)
:   x_size(x_size), y_size(y_size)
{
    this->data = new _T [x_size * y_size];
    for (size_t i = 0; i < x_size * y_size; ++i) this->data[i] = _T(0);
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

