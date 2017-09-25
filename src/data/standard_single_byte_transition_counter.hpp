#include <iostream>
#include "transition_counter.hpp"
#include "../data/logarithmic_plus_one_normalizer.hpp"

#pragma once

// maximum of errors shown before additional errors are suppressed
#define MAXIMUM_ERRORS_SHOWN 10

namespace data
{
    /**
     * Class for a standard byte for byte transition counter.
     */
    template<unsigned char _value_range>
    class StandardSingleByteTransitionCounter: public TransitionCounter
    {
        public:
            /**
             * Constructor.
             * 
             * \param A FileReader reference
             * \throw on empty smart pointer
             */
            StandardSingleByteTransitionCounter(std::shared_ptr<io::FileReader>);

            /**
             * Get a const reference to the histogram.
             *
             * \return histogram
             */
            Histogram const& getHistogram() const override;

            /**
             * Run the counter.
             */
            void run() override;

            /**
             * Set which normalizer to use.
             * 
             * \param Normalizer
             */
            void setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const&) override;
        private:
            /**
             * Handle a block of bytes.
             *
             * \param vector of byte values
             */
            void handleBlock(std::vector<unsigned char> const&);

            /**
             * Handle the next char.
             *
             * \param next char
             */
            void nextChar(unsigned char const&);

            /**
             * Histogram.
             */
            Histogram histogram;

            /**
             * Input file reader.
             */
            std::shared_ptr<io::FileReader> fileReader;

            /**
             * Flag that states whether the file read process has started.
             * This is needed as there is no transition to the first byte.
             */
            bool started = false;

            /**
             * Last char.
             */
            unsigned char last = 0x00;

            /**
             * Error count.
             */
            size_t errorCount = 0;
    };

    template class StandardSingleByteTransitionCounter<127>;
    template class StandardSingleByteTransitionCounter<255>;

    typedef StandardSingleByteTransitionCounter<127> AsciiTransitionCounter;
    typedef StandardSingleByteTransitionCounter<255> ByteTransitionCounter;
}
