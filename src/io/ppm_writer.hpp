#include <cstdio>

#include "file_writer.hpp"

#pragma once

namespace io
{
    class PpmWriter : public FileWriter
    {
        public:
            explicit PpmWriter(std::shared_ptr<vis::Image> image)
                : FileWriter(image) {};

            void write(std::string const& fname) const override;
    };
}
