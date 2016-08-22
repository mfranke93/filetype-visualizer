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
            ChargroupTransitionCounter(
                    std::shared_ptr<io::FileReader>,
                    std::initializer_list<std::string> const&)
                throw(std::invalid_argument, except::uninitialized);
    
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
            size_t * lookupTable;

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
