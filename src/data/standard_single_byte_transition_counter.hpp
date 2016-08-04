#include "transition_counter.hpp"
#include "../data/logarithmic_plus_one_normalizer.hpp"

namespace data
{
    class StandardSingleByteTransitionCounter: public TransitionCounter
    {
        public:
            StandardSingleByteTransitionCounter(std::shared_ptr<io::FileReader>);
            Histogram const& getHistogram() const override;
            void run() override;
        private:
            void handleBlock(std::vector<unsigned char> const&);
            void nextChar(unsigned char const&);

            Histogram histogram;
            std::shared_ptr<io::FileReader> fileReader;
            bool started = false;
            unsigned char last = 0x00;
    };
}
