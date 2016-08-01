#include "bmp_writer.hpp"

void io::BmpWriter::write(std::string const& filename) const
{
    // create image object
    bitmap_image image (this->widthHeight, this->widthHeight);

    unsigned char val;
    for (size_t x = 0; x < this->widthHeight; ++x)
    {
        for (size_t y = 0; y < this->widthHeight; ++y)
        {
            // grey values until cmaps exist
            val = (unsigned char)(255*this->data->at(x + this->widthHeight * y));
            
            image.set_pixel(x, y, val, val, val);
        }
    }

    // write to file
    image.save_image(filename);
}
