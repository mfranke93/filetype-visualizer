#include "grid.hpp"
#include "normalizer.hpp"
#include <cmath>

#pragma once

namespace data 
{
    class Histogram 
    {
        public:
            Histogram(size_t const&);
            void addEntry(size_t const&, size_t const&, size_t const& amount = 1);
            Grid<double> getNormalized() const;
            size_t getNumBins() const { return this->numBins; }
            size_t const& at(size_t const&, size_t const&) const;
            void setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const&);
        protected:
            Histogram() = delete;
            Histogram(Histogram const&) = delete;
            Histogram& operator= (Histogram const&) = delete;
        private:
            size_t const numBins;
            Grid<size_t> bins;
            std::shared_ptr<data::Normalizer<size_t>> normalizer;
    };
};
