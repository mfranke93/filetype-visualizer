#include "normalizer.hpp"
#include "../except/normalizer_exception.hpp"
#include "../except/uninitialized.hpp"

#pragma once

namespace data
{
    /**
     * Class for a normalizer with logarithmic scaling.
     *
     * This normalizer can only work on positive integers. In order to be able
     * to handle value zero, inputs are added to 1 and then the logarithm is
     * calculated. The exact formula for the normalizer is
     *      $$ n = \frac{\log(x+1)}{\log(\max(s)+1)} $$
     */
    class LogarithmicPlusOneNormalizer : public Normalizer<size_t>
    {
        public:
            /**
             * Constructor.
             *
             * This is uninitialized.
             */
            LogarithmicPlusOneNormalizer();

            /**
             * Constructor.
             *
             * Initialized maximum and minimum value. Order is irrelevant.
             *
             * \param minimum
             * \param maximum
             */
            LogarithmicPlusOneNormalizer(size_t const&, size_t const&);

            /**
             * Seed a value.
             * This means adding it to the value range, meaning it expands if
             * the value is outside of the previously defined range.
             *
             * \param value to seed
             */
            void seed(size_t const&) override;

            /**
             * Normalize the value.
             *
             * \param value to normalized
             * \return normalized value
             * \throw if value not in range or uninitialized
             */
            double normalize(size_t const&) const override;
        protected:
            LogarithmicPlusOneNormalizer(LogarithmicPlusOneNormalizer const&) = delete;
            LogarithmicPlusOneNormalizer& operator= (LogarithmicPlusOneNormalizer const&) = delete;

            /**
             * Calculate new parameters.
             */
            void calculateNewLogarithmicPlusOneParameters();
        private:
            /**
             * Flag to save whether values are valid yet.
             */
            bool initialized = false;

            /**
             * minimum value
             */
            size_t minimumValue;

            /**
             * maximum value
             */
            size_t maximumValue;

            /**
             * scaling factor
             */
            double scalingFactor;
            
            /**
             * offset
             */
            double offset = 0.0;
    };
}
