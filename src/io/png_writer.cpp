#include "png_writer.hpp"

io::PngScopeguard::PngScopeguard(std::string const& fname, size_t const& width, size_t const& height)
: _height(height)
{
    constexpr int PIXELSIZE = 3;
    constexpr int COLORDEPTH = 8;

    _png_file = std::fopen(fname.c_str(), "w");
    if (_png_file == nullptr)
    {
        std::fprintf(stderr, "Could not open file %s.\n", fname.c_str());
        return;
    }

    _png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (_png_ptr == nullptr)
    {
        std::fprintf(stderr, "Could not create write struct for PNG.\n");
        return;
    }

    _info_ptr = png_create_info_struct(_png_ptr);
    if (_info_ptr == nullptr)
    {
        std::fprintf(stderr, "Could not create info struct for PNG.\n");
        return;
    }

    if (setjmp(png_jmpbuf(_png_ptr)))
    {
        std::fprintf(stderr, "Error setting error jump.\n");
        return;
    }

    png_set_IHDR(_png_ptr,
        _info_ptr,
        width,
        height,
        COLORDEPTH,
        PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);

    _row_pointers = (png_byte **) png_malloc(_png_ptr, width * sizeof(png_byte *));
    for (size_t y = 0; y < height; ++y)
    {
        png_byte * row = (png_byte *) png_malloc(_png_ptr, sizeof(uint8_t) * width * PIXELSIZE);
        _row_pointers[y] = row;
    }
}

io::PngScopeguard::~PngScopeguard()
{
    setjmp(png_jmpbuf(_png_ptr));

    for (size_t i = 0; i < _height; ++i) png_free(_png_ptr, _row_pointers[i]);
    png_free(_png_ptr, _row_pointers);
    png_destroy_write_struct(&_png_ptr, &_info_ptr);
    std::fclose(_png_file);
}

io::PngScopeguard::operator bool() const
{
    return      
        /* file pointer valid */
                ( _png_file     != nullptr )
        /* image struct valid */
            &&  ( _png_ptr      != nullptr )
        /* info struct valid */
            &&  ( _info_ptr     != nullptr )
        /* pointer to row pointers valid */
            &&  ( _row_pointers != nullptr )
        /* all row's pointers valid */
            && std::all_of(_row_pointers, _row_pointers+_height,
                    [](png_byte * const ptr) -> bool
                    {
                        return ptr != nullptr;
                    });
}

void
io::PngWriter::write(std::string const& fname, size_t const& scale) const
{
    size_t const width = image->getWidth();
    size_t const height = image->getHeight();
    PngScopeguard guard (fname,  width * scale, height * scale);
    if (!guard) 
    {
        std::fprintf(stderr, "Could not write PNG file. Exiting.\n");
        return;
    }

    FILE * const fp = guard.png_file();
    png_structp const& png_ptr = guard.png_ptr();
    png_infop   const& info_ptr = guard.info_ptr();
    png_byte   ** const row_pointers = guard.row_pointers();

    /* set error handling longjump */
    setjmp(png_jmpbuf(png_ptr));

    /* write image data to row buffer */
    for (size_t j = 0; j < height * scale; ++j)
    {
        png_byte * row = row_pointers[j];
        for (size_t i = 0; i < width * scale; ++i)
        {
            size_t const x = i / scale;
            size_t const y = j / scale;

            vis::color const& color = (*image)(x,y);
            uint8_t const& r = color.R;
            uint8_t const& g = color.G;
            uint8_t const& b = color.B;
            
            *row++ = r; *row++ = g; *row++ = b; 
        }
    }

    /* write to file */
    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);
}
