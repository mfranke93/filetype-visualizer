#include "logarithmic_plus_one_normalizer.hpp"

data::LogarithmicPlusOneNormalizer::LogarithmicPlusOneNormalizer()
:   initialized(false),
    minimumValue(0),
    maximumValue(0),
    scalingFactor(1.0)
{
    // ctor
}

data::LogarithmicPlusOneNormalizer::LogarithmicPlusOneNormalizer(size_t const& min, size_t const& max)
:   initialized(true),
    minimumValue(min<max?min:max),
    maximumValue(max>min?max:min)
{
    this->calculateNewLogarithmicPlusOneParameters();
}
    
void
data::LogarithmicPlusOneNormalizer::seed(size_t const& value)
noexcept
{
    if (!this->initialized)
    {
        this->initialized = true;
        this->minimumValue = value;
        this->maximumValue = value;
    }
    else if (this->minimumValue <= value && this->maximumValue >= value)
    {
        return;
    }
    else if (this->minimumValue > value)
    {
        this->minimumValue = value;
    }
    else if (this->maximumValue < value)
    {
        this->maximumValue = value;
    }
    else
    {
        throw std::logic_error("Illegal state reached.");
    }

    this->calculateNewLogarithmicPlusOneParameters();
}

double
data::LogarithmicPlusOneNormalizer::normalize(size_t const& value) const
throw(except::normalizer_exception, except::uninitialized)
{
    if (!this->initialized)
    {
        throw except::uninitialized("Object not yet initialized!");
    }
    if (value > this->maximumValue || value < this->minimumValue)
    {
        char buf [256];
        sprintf(buf, "Value %lu not in range [%lu;%lu].", value, this->minimumValue, this->maximumValue);
        throw except::normalizer_exception(buf);
    }

    double a = log(double(value) + 1.0) - this->offset;
    double b = this->scalingFactor;
    if (b == 0.0)
    {
        b = 1.0;
    }

    return a/b;
}

void
data::LogarithmicPlusOneNormalizer::calculateNewLogarithmicPlusOneParameters()
{
    this->offset = log(double(this->minimumValue) + 1.0);
    this->scalingFactor = log(double(this->maximumValue) + 1.0) - log(double(this->minimumValue) + 1.0);
}
