#include <memory>
#include "histogram.hpp"
#include "../io/filereader.hpp"

namespace data
{
    class TransitionCounter
    {
        virtual void setFilereader(std::shared_ptr<io::FileReader>) = 0;
        virtual const Histogram getHistogram() const = 0;
    };
}
