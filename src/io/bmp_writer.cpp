#include "bmp_writer.hpp"

void 
io::BmpWriter::write(std::string const& filename,
                     std::shared_ptr<vis::Colormap const> cmap,
                     size_t const& upscale) const
{
    // create image object
    bitmap_image image (this->widthHeight * upscale, this->widthHeight * upscale);

    vis::color c;
    for (size_t x = 0; x < this->widthHeight; x++)
    {
        for (size_t y = 0; y < this->widthHeight; y++)
        {
            cmap->getColor(this->data->at(x + this->widthHeight * y), c);
            
            for (size_t w = 0; w < upscale; ++w)
            {
                for (size_t h = 0; h < upscale; ++h)
                {
                    image.set_pixel(x*upscale+w, y*upscale+h, c.R, c.G, c.B);
                }
            }
        }
    }

    // write to file
    image.save_image(filename);
}
