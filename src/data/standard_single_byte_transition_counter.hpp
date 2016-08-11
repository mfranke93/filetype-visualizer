#include "transition_counter.hpp"
#include "../data/logarithmic_plus_one_normalizer.hpp"

#pragma once

namespace data
{
    class StandardSingleByteTransitionCounter: public TransitionCounter
    {
        public:
            StandardSingleByteTransitionCounter(std::shared_ptr<io::FileReader>);
            Histogram const& getHistogram() const override;
            void run() override;
            void setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const&) override;
        private:
            void handleBlock(std::vector<unsigned char> const&);
            void nextChar(unsigned char const&);

            Histogram histogram;
            std::shared_ptr<io::FileReader> fileReader;
            bool started = false;
            unsigned char last = 0x00;
    };
}
