#include "linear_normalizer.hpp"

template<typename _T>
data::LinearNormalizer<_T>::LinearNormalizer()
{
    // ctor
}

template<typename _T>
data::LinearNormalizer<_T>::LinearNormalizer(_T const& minimum, _T const& maximum)
: minimumValue(minimum<maximum?minimum:maximum), maximumValue(minimum>maximum?minimum:maximum)
{
    // ctor
}

template<typename _T>
void
data::LinearNormalizer<_T>::seed(_T const& value)
{
    if (!this->initialized)
    {
        this->initialized = true;
        this->minimumValue = value;
        this->maximumValue = value;
    }
    else if (value > this->maximumValue)
    {
        this->maximumValue = value;
    }
    else if (value < this->minimumValue)
    {
        this->minimumValue = value;
    }
    else
    {
        return;
    }

    this->calculateNewLinearParameters();
}

template<typename _T>
void
data::LinearNormalizer<_T>::calculateNewLinearParameters()
{
    // TODO
    // if min=max, every return value should be 0
    if (this->minimumValue == this->maximumValue)
    {
        this->scalingFactor = 0.0;
        this->offset = 0.0;
    }
    else
    {
        this->scalingFactor = 1.0/double(this->maximumValue - this->minimumValue);
        this->offset = double(this->minimumValue);
    }
}

template<typename _T>
double
data::LinearNormalizer<_T>::normalize(_T const& value) const throw(std::out_of_range)
{
    if (!this->initialized)
    {
        throw std::out_of_range("This data::LinearNormalizer was not yet initialized.");
    }
    if (value > this->maximumValue || value < this->minimumValue)
    {
        char buf [256];
        sprintf(buf, "Value %d is not in range [%d; %d].", int(value), int(this->minimumValue), int(this->maximumValue));
        throw std::out_of_range(buf);
    }

    return scalingFactor*(double(value) - this->offset);
}
