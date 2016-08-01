#include "transition_counter.hpp"

namespace data
{
    class StandardSingleByteTransitionCounter: public TransitionCounter
    {
        public:
            StandardSingleByteTransitionCounter(std::shared_ptr<io::FileReader>);
            Histogram const& getHistogram() const override;
            void run() override;
        private:
            void handleBlock(std::vector<char> const&);
            void nextChar(char const&);

            Histogram histogram;
            std::shared_ptr<io::FileReader> fileReader;
            bool started = false;
            char last = 0x00;
    };
}
