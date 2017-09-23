#include "ppm_writer.hpp"

void
io::PpmWriter::write(std::string const& fname, size_t const& size) const
{
    if (!image)
    {
        throw std::runtime_error("Uninitialized shared_ptr<vis::Image>");
    }

    size_t const width = image->getWidth() * size;
    size_t const height = image->getHeight() * size;

    auto file = std::fopen(fname.c_str(), "w");

    // PPM header
    std::fprintf(file, "P6\n%lu %lu\n255\n", width, height);

    if (file == nullptr)
    {
        throw std::runtime_error("Could not open output file for writing!");
    }

    // iterate rows
    for (size_t row = 0; row < height; ++row)
    {
        // iterate cols
        for (size_t col = 0; col < width; ++col)
        {
            size_t const x = col / size;
            size_t const y = row / size;
            vis::color const& c = (*image)(x, y);
            std::fprintf(file, "%c%c%c", 
                    static_cast<vis::channel>(c.R), 
                    static_cast<vis::channel>(c.G), 
                    static_cast<vis::channel>(c.B));
        }
    }

    std::fclose(file);
}
