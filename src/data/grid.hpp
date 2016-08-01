#include <cstddef>
#include <memory>
#include <vector>

#pragma once

namespace data {
    template<typename _T>
        class Grid
        {
            public:
                Grid(Grid const&);
                Grid(size_t const&);
                Grid(size_t const&, size_t const&);
                _T& operator() (size_t const&, size_t const&);
                _T const& operator() (size_t const&, size_t const&) const;
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

