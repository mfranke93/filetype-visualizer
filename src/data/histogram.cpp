#include "histogram.hpp"

data::Histogram::Histogram(size_t const& numBins)
: numBins(numBins), bins(numBins)
{
    // nothing to do here
}

void data::Histogram::addEntry(size_t const& x, size_t const& y, size_t const& amount)
{
    this->bins(x, y) += amount;
}

data::Grid<double> data::Histogram::getNormalized() const
{
    size_t maximum = this->bins.getMaximum();
    Grid<double> normalized (this->numBins);
    for (size_t x = 0; x < this->numBins; ++x)
    {
        for (size_t y = 0; y < this->numBins; ++y)
        {
            normalized(x,y) = double(this->bins(x,y))/double(maximum);
        }
    }
    
    return normalized;
}
