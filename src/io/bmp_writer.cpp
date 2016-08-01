#include "bmp_writer.hpp"

void io::BmpWriter::write(std::string const& filename, std::shared_ptr<vis::Colormap> cmap) const
{
    // create image object
    bitmap_image image (this->widthHeight, this->widthHeight);

    vis::color c;
    for (size_t x = 0; x < this->widthHeight; ++x)
    {
        for (size_t y = 0; y < this->widthHeight; ++y)
        {
            cmap->getColor(this->data->at(x + this->widthHeight * y), c);
            
            image.set_pixel(x, y, c.R, c.G, c.B);
        }
    }

    // write to file
    image.save_image(filename);
}
