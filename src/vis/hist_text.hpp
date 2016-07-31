#include <string>
#include <vector>

#include "../data/histogram.hpp"

#pragma once

namespace vis
{
    class TextHistogram
    {
        public:
            TextHistogram(data::Histogram *);

            std::vector<std::string> getHistogram() const;
        protected:
            TextHistogram() = delete;
            TextHistogram(TextHistogram const&) = delete;
            TextHistogram& operator= (TextHistogram const&) = delete;
        private:
            data::Histogram * histogram;
    };
}

