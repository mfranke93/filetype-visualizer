#include "chargroup_transition_counter.hpp"

data::ChargroupTransitionCounter::ChargroupTransitionCounter(
        std::shared_ptr<io::FileReader> fileReader,
        std::initializer_list<std::string> const& groups)
throw(std::invalid_argument, except::uninitialized)
: fileReader(fileReader)
{
    if (!fileReader)
    {
        throw except::uninitialized("FileReader smart pointer must not be empty.");
    }
    
    /**
     * map
     */
    std::unordered_map<unsigned char, size_t> m;
    size_t i = 0;
    
    for (std::initializer_list<std::string>::const_iterator it = groups.begin(); it != groups.end(); ++i, ++it)
    {
        std::string group = *it;

        for (unsigned char const& c : group)
        {
            if (m.count(c) != 0)
            {
                char buf [256];
                sprintf(buf, "Character '%c' (0x%02X) occured more than once.", c, c);
                throw std::invalid_argument(buf);
            }

            m[c] = i;
        }
    }
    
    bool hasUnmentioned = false;
    // fill unmentioned
    for (unsigned char c = 0; c <= 255; ++c)
    {
        if (m.count(c) == 0)
        {
            m[c] = groups.size();
            hasUnmentioned = true;
        }
    }

    // fill to LUT
    this->lookupTable = new size_t [256];
    for (unsigned char c = 0; c <= 255; ++c)
    {
        this->lookupTable[c] = m[c];
    }

    this->numGroups = hasUnmentioned ? groups.size()+1 : groups.size();
    this->histogram = std::make_shared<data::Histogram>(this->numGroups);
}

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
                    size_t const to   = this->lookupTable[c];
                    size_t const from = this->lookupTable[this->last];

                    this->histogram->addEntry(to, from);
                }

                this->last = c;
            }
        }
    }
}
