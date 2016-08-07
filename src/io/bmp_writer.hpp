#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <exception>
#include "../third_party/bitmap/bitmap_image.hpp"
#include "../vis/colormap.hpp"
#include "../vis/image.hpp"

#pragma once

namespace io
{
    class BmpWriter
    {
        public:
            BmpWriter(std::shared_ptr<vis::Image> image)
                : image(image) 
            {}

            /**
             * Export to file.
             * \param file name
             * \param colormap
             * \param upscale value
             */
            void write(std::string const&, size_t const& = 1) const;
        protected:
            BmpWriter() = delete;
            BmpWriter(BmpWriter const&) = delete;
            BmpWriter& operator= (BmpWriter const&) = delete;
        private:
            std::shared_ptr<vis::Image> image;
    };
}
