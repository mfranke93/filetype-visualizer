#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <exception>
#include "../third_party/bitmap/bitmap_image.hpp"
#include "file_writer.hpp"

#pragma once

namespace io
{
    /**
     * Class to write image data to a Bitmap file.
     */
    class BmpWriter : public FileWriter
    {
        public:
            /**
             * Constructor.
             *
             * \param image Image object containing pixel values
             */
            BmpWriter(std::shared_ptr<vis::Image> image)
                : FileWriter(image) 
            {};

            /**
             * Export to file.
             * \param file name
             * \param upscale value
             */
            void write(std::string const&, size_t const& = 1) const;
    };
}
