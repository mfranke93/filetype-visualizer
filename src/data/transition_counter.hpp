#include <memory>
#include "histogram.hpp"
#include "../io/filereader.hpp"

namespace data
{
    class TransitionCounter
    {
        public:
            virtual Histogram const& getHistogram() const = 0;
            virtual void run() = 0;
    };
}
