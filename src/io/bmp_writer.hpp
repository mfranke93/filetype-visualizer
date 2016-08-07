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
    /**
     * Class to write image data to a Bitmap file.
     */
    class BmpWriter
    {
        public:
            /**
             * Constructor.
             *
             * \param image Image object containing pixel values
             */
            BmpWriter(std::shared_ptr<vis::Image> image)
                : image(image) 
            {}

            /**
             * Export to file.
             * \param file name
             * \param upscale value
             */
            void write(std::string const&, size_t const& = 1) const;
        protected:
            BmpWriter() = delete;
            BmpWriter(BmpWriter const&) = delete;
            BmpWriter& operator= (BmpWriter const&) = delete;
        private:
            /**
             * Reference to pixel data.
             */
            std::shared_ptr<vis::Image> image;
    };
}
