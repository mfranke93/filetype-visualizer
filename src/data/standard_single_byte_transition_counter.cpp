#include "standard_single_byte_transition_counter.hpp"
#include <cstdio>

data::StandardSingleByteTransitionCounter::StandardSingleByteTransitionCounter(std::shared_ptr<io::FileReader> fileReader)
:   histogram(256), fileReader(fileReader)
{
    // ctor
}

data::Histogram const&
data::StandardSingleByteTransitionCounter::getHistogram() const
{
    return this->histogram;
}

void
data::StandardSingleByteTransitionCounter::run()
{
    if (this->fileReader) // smart pointer filled
    {
        while (this->fileReader->operator bool()) // file reader has input still
        {
            std::vector<unsigned char> nextBlock = this->fileReader->getNext(1);
            this->handleBlock(nextBlock);
        }
    }
}

void
data::StandardSingleByteTransitionCounter::handleBlock(std::vector<unsigned char> const& block)
{
    for (unsigned char const& c : block)
    {
        this->nextChar(c);
    }
}

void data::StandardSingleByteTransitionCounter::nextChar(unsigned char const& c)
{
    if (this->started)
    {
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
