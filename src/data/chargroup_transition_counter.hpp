#include "transition_counter.hpp"

namespace data
{
    class ChargroupTransitionCounter : public TransitionCounter
    {
    
        private:
            /**
             * Here, the mapping from the 256 unsigned char values to <= 256
             * size_t values is stored. This way, lookup of the char group's
             * index is in O(1) instead of O(c) (for c number char groups,
             * where it would actually be O(c log 256)).
             */
            size_t * lookupTable;
    };
}
