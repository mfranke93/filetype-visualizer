#include "hist_text.hpp"

vis::TextHistogram::TextHistogram(std::shared_ptr<data::Histogram> const& hist)
: histogram(hist)
{
    // nothing more to do here
}

std::vector<std::string> vis::TextHistogram::getHistogram() const
{
    std::vector<std::string> vec;

    // TODO: replace by transfer function
    char symbols [] = { ' ', '.', '-', '+',  '=', '#' };

    size_t size = this->histogram->getNumBins();
    auto norm = this->histogram->getNormalized();

    for (size_t y = 0; y < size; ++y)
    {
        std::string s = "";
        for (size_t x = 0; x < size; ++x)
        {
            size_t idx = size_t(floor(norm(x,y)*5));
            s += symbols[idx];
        }
        vec.push_back(s);
    }

    return vec;
}
