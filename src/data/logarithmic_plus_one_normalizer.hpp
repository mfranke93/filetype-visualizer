#include "normalizer.hpp"

namespace data
{
    class LogarithmicPlusOneNormalizer : public Normalizer<size_t>
    {
        public:
            LogarithmicPlusOneNormalizer();
            LogarithmicPlusOneNormalizer(size_t const&, size_t const&);

            void seed(size_t const&) override;
            double normalize(size_t const&) const throw(std::out_of_range) override;
        protected:
            LogarithmicPlusOneNormalizer(LogarithmicPlusOneNormalizer const&) = delete;
            LogarithmicPlusOneNormalizer& operator= (LogarithmicPlusOneNormalizer const&) = delete;

            void calculateNewLogarithmicPlusOneParameters();
        private:
            bool initialized = false;
            size_t minimumValue;
            size_t maximumValue;
            double scalingFactor;
            double offset = 0.0;
    };
}
