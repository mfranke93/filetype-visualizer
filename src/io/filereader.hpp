#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

#pragma once

namespace io {
    
    class FileReader
    {
    public:
        /**
         * Default constructor.
         * Reads from stdin.
         */
        FileReader() noexcept;

        ~FileReader() noexcept;

        /**
         * Constructor.
         * \param File name
         */
        explicit FileReader(std::string const&) throw (std::invalid_argument);

        /**
         * Convert object to boolean.
         * Returns true if stream not empty.
         */
        operator bool () const noexcept;

        /**
         * Get next n bytes.
         * \param Number of bytes (n)
         * \return vector of bytes
         */
        std::vector<unsigned char> getNext(size_t const&) noexcept;
        
    protected:
        FileReader(FileReader const&) = delete;
        FileReader& operator=(FileReader const&) = delete;

    private:
        std::shared_ptr<std::istream> input;
    };
};
