#include "bmp_writer.hpp"

void 
io::BmpWriter::write(std::string const& filename,
                     size_t const& upscale) const
{
    // create image object
    bitmap_image image (this->image->getWidth() * upscale, this->image->getHeight() * upscale);

    for (size_t x = 0; x < this->image->getWidth(); x++)
    {
        for (size_t y = 0; y < this->image->getHeight(); y++)
        {
            vis::color const c = (*this->image)(x,y);
            
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
