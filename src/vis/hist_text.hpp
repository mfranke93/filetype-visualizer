#include <string>
#include <vector>
#include <memory>
#include <cmath>

#include "../data/histogram.hpp"

#pragma once

namespace vis
{
    /**
     * Class for text histogram.
     * Experimental.
     */
    class TextHistogram
    {
        public:
            /**
             * Constructor.
             *
             * \param Shared pointer to a Histogram object.
             */
            TextHistogram(std::shared_ptr<data::Histogram> const&);

            /**
             * Get strings representing lines of histogram.
             * \return list of strings
             */
            std::vector<std::string> getHistogram() const;
        protected:
            TextHistogram() = delete;
            TextHistogram(TextHistogram const&) = delete;
            TextHistogram& operator= (TextHistogram const&) = delete;
        private:
            /**
             * Histogram.
             */
            std::shared_ptr<data::Histogram> histogram;
    };
}

