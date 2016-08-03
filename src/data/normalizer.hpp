#include <cmath>
#include <stdexcept>

namespace data
{
    template<typename _T>
    class Normalizer
    {
        public:
            /**
             * Seed the normalizer.
             *
             * Depending on what is expected of the normalizer, it might be
             * enough to just pass it the minimum and maximum value.
             *
             * \param Value to add to normalizer initialization.
             */
            virtual void seed(_T const&) = 0;

            /**
             * Normalize a value.
             *
             * This takes a value of type _T and returns a double.
             *
             * \param Value to be normalized
             * \return Normalized value between 0 and 1
             * \throw std::out_of_range if value not in normalizable range.
             *        This usually means the value is larger or smaller than any value
             *        passed to seed function.
             */
            virtual double normalize(_T const&) const throw(std::out_of_range) = 0;
    };
}
