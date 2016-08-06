#include <vector>
#include <memory>
#include <string>
#include "../third_party/bitmap/bitmap_image.hpp"
#include "../vis/colormap.hpp"

#pragma once

namespace io
{
    class BmpWriter
    {
        public:
            BmpWriter(size_t const& widthHeight, std::shared_ptr<std::vector<double>> data)
                : widthHeight(widthHeight), data(data) 
            {}

            /**
             * Export to file.
             * \param file name
             * \param colormap
             * \param upscale value
             */
            void write(std::string const&, std::shared_ptr<vis::Colormap const>, size_t const& = 1) const;
        protected:
            BmpWriter() = delete;
            BmpWriter(BmpWriter const&) = delete;
            BmpWriter& operator= (BmpWriter const&) = delete;
        private:
            /**
             * Width and height of image.
             */
            size_t const widthHeight;

            /**
             * Vector containing the data.
             * Row-major.
             * Assumed to be normalized.
             */
            std::shared_ptr<std::vector<double>> const data;
    };
}
