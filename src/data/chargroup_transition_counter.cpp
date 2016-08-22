#include "chargroup_transition_counter.hpp"
#include <stdio.h>

void
data::ChargroupTransitionCounter::setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const& norm)
throw(except::uninitialized)
{
    if (!norm)
    {
        throw except::uninitialized("Smart pointer to normalizer not initialized.");
    }
    this->histogram->setNormalizer(norm);
}

data::Histogram const&
data::ChargroupTransitionCounter::getHistogram()
const noexcept
{
    return *(this->histogram);
}

void
data::ChargroupTransitionCounter::run()
noexcept
{
    if (this->fileReader)
    {
        while (this->fileReader->operator bool())
        {
            std::vector<unsigned char> vec = this->fileReader->getNext(256);

            for (unsigned char const& c : vec)
            {
                if (!started)
                {
                    started = true;
                }
                else
                {
                    size_t const to   = this->lookupTable[static_cast<size_t>(c)];
                    size_t const from = this->lookupTable[static_cast<size_t>(this->last)];

                    this->histogram->addEntry(to, from);
                }

                this->last = c;
            }
        }
    }
}
