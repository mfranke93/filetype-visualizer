#include <memory>
#include <string>
#include "../vis/image.hpp"

#pragma once

namespace io
{
    class FileWriter
    {
        public:
            /**
             * Constructor.
             *
             * \param image     Smart pointer to image data to write.
             */
            explicit FileWriter(std::shared_ptr<vis::Image> image)
                : image(image) {};
            virtual ~FileWriter() = default;

            /**
             * Write out the image data.
             *
             * \param fname     File name
             */
            virtual void write(std::string const& fname) const = 0;

        protected:
            FileWriter() = delete;
            FileWriter(FileWriter const&) = delete;
            FileWriter(FileWriter&&) = delete;
            FileWriter& operator= (FileWriter const&) = delete;
            FileWriter& operator= (FileWriter&&) = delete;

            /**
             * Pixel data.
             */
            std::shared_ptr<vis::Image> image;
    };
}
