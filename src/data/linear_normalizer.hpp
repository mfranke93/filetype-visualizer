#include "normalizer.hpp"

#pragma once

namespace data
{
    template<typename _T>
    class LinearNormalizer : public Normalizer<_T>
    {
        public:
            LinearNormalizer();
            LinearNormalizer(_T const&, _T const&);

            void seed(_T const&) override;
            double normalize(_T const&) const throw(std::out_of_range) override;
        protected:
            LinearNormalizer(LinearNormalizer const&) = delete;
            LinearNormalizer& operator= (LinearNormalizer const&) = delete;

            void calculateNewLinearParameters();
        private:
            bool initialized = false;
            _T minimumValue;
            _T maximumValue;
            double scalingFactor;
            double offset = 0.0;
    };
}

/* types */
template class data::LinearNormalizer<size_t>;
template class data::LinearNormalizer<int>;
template class data::LinearNormalizer<double>;
template class data::LinearNormalizer<float>;
