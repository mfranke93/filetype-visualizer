#include <cstddef>
#include <memory>
#include <vector>

#include "../except/illegal_size_exception.hpp"

#pragma once

// TODO: add doc
// TODO: add exceptions

namespace data {
    template<typename _T>
        class Grid
        {
            public:
                Grid(Grid const&);
                Grid(size_t const&) throw (except::illegal_size);
                Grid(size_t const&, size_t const&) throw (except::illegal_size);
                _T& operator() (size_t const&, size_t const&) throw(std::out_of_range);
                _T const& operator() (size_t const&, size_t const&) const throw(std::out_of_range);
                _T getMaximum() const;
                std::shared_ptr<std::vector<_T>> asVector() const;
            protected:
                Grid() = delete;
                Grid& operator=(Grid const&) = delete;
            private:
                _T * data;
                size_t const x_size;
                size_t const y_size;
        };
};

