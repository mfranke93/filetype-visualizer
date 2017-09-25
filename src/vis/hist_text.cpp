#include "hist_text.hpp"
#include "../data/linear_normalizer.hpp"

vis::TextHistogram::TextHistogram(std::shared_ptr<data::Histogram> const& hist)
: histogram(hist)
{
    if (!hist)
    {
        throw std::invalid_argument("Histogram pointer must not be null.");
    }
    hist->setNormalizer(std::make_shared<data::LinearNormalizer<size_t>>());
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
            size_t idx;

            if (norm(x, y) < 0.1) idx = 0;
            else if (norm(x, y) < 0.3) idx = 1;
            else if (norm(x, y) < 0.5) idx = 2;
            else if (norm(x, y) < 0.7) idx = 3;
            else if (norm(x, y) < 0.9) idx = 4;
            else idx = 5;

            s += symbols[idx];
        }
        vec.push_back(s);
    }

    return vec;
}
