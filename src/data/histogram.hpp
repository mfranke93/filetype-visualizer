#include "grid.hpp"

namespace data 
{
    class Histogram 
    {
        public:
            Histogram(size_t const&);
            void addEntry(size_t const&, size_t const&, size_t const& amount = 1);
            Grid<double> getNormalized() const;
        protected:
            Histogram() = delete;
            Histogram(Histogram const&) = delete;
            Histogram& operator= (Histogram const&) = delete;
        private:
            size_t const numBins;
            Grid<size_t> bins;
    };
};
