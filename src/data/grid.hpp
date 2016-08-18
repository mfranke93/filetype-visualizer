#include <cstddef>
#include <memory>
#include <vector>

#include "../except/illegal_size_exception.hpp"

#pragma once

namespace data {
    /**
     * Class to store data on a 2D grid.
     */
    template<typename _T>
    class Grid
    {
        public:
            /**
             * Copy constructor.
             * \param other
             */
            Grid(Grid const&) noexcept;

            /**
             * Constructor.
             * For width=height.
             * \param width
             * \throw if size is 0
             */
            explicit Grid(size_t const&) throw (except::illegal_size);

            /**
             * Constructor.
             * \param width
             * \param height
             * \throw if total size is 0
             */
            explicit Grid(size_t const&, size_t const&) throw (except::illegal_size);

            /**
             * Destructor.
             */
            ~Grid() noexcept;

            /**
             * Non-const accessor.
             *
             * \param x coordinate
             * \param y coordinate
             * \return value at x,y
             * \throw if any coordinate is too large
             */
            _T& operator() (size_t const&, size_t const&) throw(std::out_of_range);

            /**
             * const accessor.
             *
             * \param x coordinate
             * \param y coordinate
             * \return value at x,y
             * \throw if any coordinate is too large
             */
            _T const& operator() (size_t const&, size_t const&) const throw(std::out_of_range);

            /**
             * Get highest value.
             * \return maximum
             */
            _T getMaximum() const noexcept;

            /**
             * Flatten to list.
             * \return vector
             */
            std::shared_ptr<std::vector<_T>> asVector() const noexcept;
        protected:
            Grid() = delete;
            Grid& operator=(Grid const&) = delete;
        private:
            /**
             * Pointer to values
             */
            _T * data;

            /**
             * width
             */
            size_t const x_size;

            /**
             * height
             */
            size_t const y_size;
    };
};

