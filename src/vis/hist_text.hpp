#include <string>
#include <vector>
#include <memory>
#include <cmath>

#include "../data/histogram.hpp"

#pragma once

namespace vis
{
    class TextHistogram
    {
        public:
            TextHistogram(std::shared_ptr<data::Histogram> const&);

            std::vector<std::string> getHistogram() const;
        protected:
            TextHistogram() = delete;
            TextHistogram(TextHistogram const&) = delete;
            TextHistogram& operator= (TextHistogram const&) = delete;
        private:
            std::shared_ptr<data::Histogram> histogram;
    };
}

