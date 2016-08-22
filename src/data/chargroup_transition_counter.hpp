#include "transition_counter.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <initializer_list>
#include "../except/uninitialized.hpp"

namespace data
{
    /**
     * Class to do transition counting where multiple characters are counted as
     * one group, i.e lower case alphabet, numbers, white space characters,
     * control characters...
     */
    class ChargroupTransitionCounter : public TransitionCounter
    {
        public:
            /**
             * Constructor.
             *
             * Is initialized as a list of strings, each representing one group
             * of characters. Characters that are in none of the strings are
             * put in a last implicit group.
             *
             * \param initializer list
             * \throw if a character is in more than one group
             */
            template<typename ITERABLE_CHARS>
            ChargroupTransitionCounter(
                    std::shared_ptr<io::FileReader> const& f,
                    std::vector<ITERABLE_CHARS> const& groups)
                throw(std::invalid_argument, except::uninitialized)
            : fileReader(f)
            {
                if (!f) throw except::uninitialized("File reader must be initialized.");
                /**
                 * map
                 */
                std::unordered_map<unsigned char, size_t> m;
                size_t i = 0;
                
                for (auto it = groups.begin(); it != groups.end(); ++i, ++it)
                {
                    ITERABLE_CHARS group = *it;
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
                for (size_t c = 0; c <= 255; ++c)
                {
                    if (m.count(static_cast<unsigned char>(c)) == 0)
                    {
                        m[c] = groups.size();
                        hasUnmentioned = true;
                    }
                }

                // fill to LUT
                for (size_t c = 0; c < 256; ++c)
                {
                    this->lookupTable[c] = m[static_cast<unsigned char>(c)];
                }

                this->numGroups = hasUnmentioned ? groups.size()+1 : groups.size();
                this->histogram = std::make_shared<data::Histogram>(this->numGroups);
            }
    
            /**
             * Set the normalizer.
             *
             * \param normalizer
             * \throw if smart pointer empty
             */
            void setNormalizer(std::shared_ptr<data::Normalizer<size_t>> const&) throw(except::uninitialized) override;

            /**
             * Get the histogram.
             * \return the histogram
             */
            Histogram const& getHistogram() const noexcept override;

            /**
             * Run the normalizer.
             */
            void run() noexcept override;
        private:
            /**
             * Here, the mapping from the 256 unsigned char values to <= 256
             * size_t values is stored. This way, lookup of the char group's
             * index is in O(1) instead of O(c) (for c number char groups,
             * where it would actually be O(c log 256)).
             */
            size_t lookupTable [256];

            /**
             * Number of groups.
             */
            size_t numGroups;

            /**
             * histogram
             */
            std::shared_ptr<Histogram> histogram;

            /**
             * first group processed?
             */
            bool started = false;

            /**
             * last group
             */
            size_t last = 0;

            /**
             * The file reader.
             */
            std::shared_ptr<io::FileReader> fileReader;
    };
}
