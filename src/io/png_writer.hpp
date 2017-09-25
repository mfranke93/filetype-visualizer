#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <png.h>

#include "file_writer.hpp"

#pragma once

namespace io
{
    /**
     * Class to handle RAII-ness of PNG output object. Keeps the C code away
     * from the C++ stuff in the PNG writer. The constructor handles all the
     * malloc() calls and libPNG stuff, and error handling. The destructor
     * handles all deallocations.
     */
    class PngScopeguard
    {
        public:
            /**
             * Constructor. Initializes libPNG data structs.
             *
             * \param _p1       Output filename.
             * \param _p2       Width of output image.
             * \param _p3       Height of output image.
             */
            PngScopeguard(std::string const&, size_t const&, size_t const&);

            /**
             * Destructor. Handles the deallocations and cleanups.
             */
            ~PngScopeguard();

            /**
             * Evaluates whether all libPNG structs have been correctly
             * initialized.
             */
            operator bool() const;

            /**
             * Output file.
             */
            FILE        *   const   png_file()      { return _png_file; }

            /**
             * PNG struct.
             */
            png_structp     const&  png_ptr()       { return _png_ptr; }

            /**
             * PNG info struct.
             */
            png_infop       const&  info_ptr()      { return _info_ptr; }

            /**
             * Row pointers for image pixel data.
             */
            png_byte    **  const   row_pointers()  { return _row_pointers; }

        private:
            FILE        *   _png_file;
            png_structp     _png_ptr;
            png_infop       _info_ptr;
            png_byte    **  _row_pointers;

            /**
             * Image height. Needed for the row pointers.
             */
            size_t const _height;
    };

    class PngWriter : public FileWriter
    {
        public:
            PngWriter(std::shared_ptr<vis::Image> image)
                : FileWriter(image)
            {};

            /**
             * Write out the image data to a PNG file.
             *
             * \param fname     File name
             * \param size      Image upscaling (output pixels per data pixel).
             */
            void write(std::string const& fname, size_t const& size = 1) const override;
    };
}
