#include "normalizer.hpp"

#pragma once

namespace data
{
    /**
     * Class for linear normalizing.
     *
     * This maps a value set 
     *      $$ \marhbb{R} \supsetneq S = [a;b] \rightarrow [0;1] $$
     * such that
     *      $$ \mbox{normalized}(x) = \frac{x-a}{b-a} $$
     */
    template<typename _T>
    class LinearNormalizer : public Normalizer<_T>
    {
        public:
            /**
             * Constructor.
             * Leaves object uninitialized.
             */
            LinearNormalizer();

            /**
             * Constructor.
             * Populates minimum and maximum value, order does not matter.
             *
             * \param minimum value
             * \param maximum value
             */
            LinearNormalizer(_T const&, _T const&);

            /**
             * Add value to seed.
             * \param value
             */
            void seed(_T const&) override;

            /**
             * Normalize a value.
             * \param value to normalize
             * \return normalized value
             * \throw if value not in range
             * \throw if object not initialized
             */
            double normalize(_T const&) const override;
        protected:
            LinearNormalizer(LinearNormalizer const&) = delete;
            LinearNormalizer& operator= (LinearNormalizer const&) = delete;

            /**
             * Recalculate factors.
             */
            void calculateNewLinearParameters();
        private:
            /**
             * object initialized yet
             */
            bool initialized = false;

            /**
             * lowest value
             */
            _T minimumValue;
            
            /**
             * highest value
             */
            _T maximumValue;

            /**
             * factor (a in ax+b)
             */
            double scalingFactor;

            /**
             * offset (b in ax+b)
             */
            double offset = 0.0;
    };
}

/* types */
template class data::LinearNormalizer<size_t>;
template class data::LinearNormalizer<int>;
template class data::LinearNormalizer<double>;
template class data::LinearNormalizer<float>;
