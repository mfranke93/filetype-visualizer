#include <memory>
#include "histogram.hpp"
#include "../io/filereader.hpp"

#pragma once

namespace data
{
    class TransitionCounter
    {
        public:
            virtual void setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const&) = 0;
            virtual Histogram const& getHistogram() const = 0;
            virtual void run() = 0;
    };
}
