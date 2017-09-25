#include "standard_single_byte_transition_counter.hpp"

template<unsigned char _value_range>
data::StandardSingleByteTransitionCounter<_value_range>::StandardSingleByteTransitionCounter(std::shared_ptr<io::FileReader> fileReader)
:   histogram(_value_range+1), fileReader(fileReader)
{
    if (!fileReader)
    {
        throw except::uninitialized("Smart pointer to file reader must not be empty.");
    }
    // ctor
    this->histogram.setNormalizer(std::make_shared<data::LogarithmicPlusOneNormalizer>());
}

template<unsigned char _value_range>
data::Histogram const&
data::StandardSingleByteTransitionCounter<_value_range>::getHistogram() const
{
    return this->histogram;
}

template<unsigned char _value_range>
void
data::StandardSingleByteTransitionCounter<_value_range>::run()
{
    if (this->fileReader) // smart pointer filled
    {
        while (this->fileReader->operator bool()) // file reader has input still
        {
            std::vector<unsigned char> nextBlock = this->fileReader->getNext(256);
            this->handleBlock(nextBlock);
        }
    }

    if (this->errorCount > MAXIMUM_ERRORS_SHOWN)
    {
        std::cerr << " ... " << (this->errorCount - MAXIMUM_ERRORS_SHOWN)
            << " more out of range errors suppressed." << std::endl;
    }
}

template<unsigned char _value_range>
void
data::StandardSingleByteTransitionCounter<_value_range>::setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const& norm)
{
    if (!norm)
    {
        throw except::uninitialized("Smart pointer to normalizer not initialized.");
    }
    this->histogram.setNormalizer(norm);
}

template<unsigned char _value_range>
void
data::StandardSingleByteTransitionCounter<_value_range>::handleBlock(std::vector<unsigned char> const& block)
{
    for (unsigned char const& c : block)
    {
        this->nextChar(c);
    }
}

template<unsigned char _value_range>
void
data::StandardSingleByteTransitionCounter<_value_range>::nextChar(unsigned char const& c)
{
    if (c > _value_range)
    {
        ++(this->errorCount);
        if (this->errorCount <= MAXIMUM_ERRORS_SHOWN)
        {
            fprintf(stderr, "Value 0x%X is out of range for data::StandardSingleByteTransitionCounter<0x%X>.\n", c, _value_range);
        }
        return;
    }

    if (this->started)
    {
        /*
         * Just to make this clear:
         * The histogram looks like this:
         *  There is a value at position x,y which indicates
         *  how often a transition y->x has occured. This
         *  may seem the wrong way around, but actually is
         *  more consistent with the reading order: How often
         *  does character ... get followed by ... .
         */
        size_t x = static_cast<size_t>(c);
        size_t y = static_cast<size_t>(this->last);
        this->histogram.addEntry(x,y);
    }
    else
    {
        this->started = true;
    }
    this->last = c;
}
