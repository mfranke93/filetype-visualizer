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
    // log maximum
    double lMax = log(double(maximum)) + 1.0;
    Grid<double> normalized (this->numBins);
    size_t v;
    if (maximum > 0)
    {
        for (size_t x = 0; x < this->numBins; ++x)
        {
            for (size_t y = 0; y < this->numBins; ++y)
            {
                v = this->bins(x,y);
                if (v == 0) normalized(x,y) = 0.0;
                else normalized(x,y) = (log(double(v))+1)/lMax;
            }
        }
    }
    
    return normalized;
}

size_t const& 
data::Histogram::at(size_t const& x, size_t const&y) const
{
    return this->bins(x,y);
}

