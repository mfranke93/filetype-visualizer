#include "grid.hpp"
#include "normalizer.hpp"
#include "linear_normalizer.hpp"
#include "../except/illegal_size_exception.hpp"
#include <cmath>

#pragma once

namespace data 
{
    /**
     * Class to store histograms.
     */
    class Histogram 
    {
        public:
            /**
             * Constructor.
             *
             * \param Size in x and y direction.
             */
            Histogram(size_t const&);

            /**
             * Add an entry.
             *
             * \param x position
             * \param y position
             * \param amount to add, default 1
             */
            void addEntry(size_t const&, size_t const&, size_t const& amount = 1);

            /**
             * Get a grid of normalized values.
             * \return grid
             */
            Grid<double> getNormalized() const;

            /**
             * Get width or height
             * \return grid size
             */
            size_t getNumBins() const { return this->numBins; }

            /**
             * Get value at.
             *
             * \param x position
             * \param y position
             * \return const reference to value at position
             */
            size_t const& at(size_t const&, size_t const&) const;

            /**
             * Set normalizer to use.
             * \param normalizer
             */
            void setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const&);
        protected:
            Histogram() = delete;
            Histogram(Histogram const&) = delete;
            Histogram& operator= (Histogram const&) = delete;
        private:
            /**
             * Number of bins
             */
            size_t const numBins;

            /**
             * Bins
             */
            Grid<size_t> bins;

            /**
             * Normalizer.
             */
            std::shared_ptr<data::Normalizer<size_t>> normalizer;
    };
};
