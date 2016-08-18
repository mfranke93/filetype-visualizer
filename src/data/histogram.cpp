#include "histogram.hpp"

data::Histogram::Histogram(size_t const& numBins)
noexcept
: numBins(numBins), bins(numBins)
{
    this->normalizer = std::make_shared<data::LinearNormalizer<size_t>>();
}

void
data::Histogram::addEntry(size_t const& x, size_t const& y, size_t const& amount)
throw (std::out_of_range)
{
    this->bins(x, y) += amount;
}

data::Grid<double>
data::Histogram::getNormalized() const
noexcept
{
    Grid<double> normalized (this->numBins);
    for (size_t x = 0; x < this->numBins; ++x)
    {
        for (size_t y = 0; y < this->numBins; ++y)
        {
            this->normalizer->seed(this->bins(x,y));
        }
    }

    for (size_t x = 0; x < this->numBins; ++x)
    {
        for (size_t y = 0; y < this->numBins; ++y)
        {
            normalized(x,y) = this->normalizer->normalize(this->bins(x,y));
        }
    }
    
    return normalized;
}

size_t const& 
data::Histogram::at(size_t const& x, size_t const&y) const
throw(std::out_of_range)
{
    return this->bins(x,y);
}

void
data::Histogram::setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const& norm)
throw(except::uninitialized)
{
    if (!norm) throw except::uninitialized("Normalizer pointer must not be null!");
    this->normalizer = norm;
}
