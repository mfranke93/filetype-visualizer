#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstdio>
#include <ext/stdio_filebuf.h>

namespace io {
    
    class FileReader
    {
    public:
        /**
         * Default constructor.
         * Reads from stdin.
         */
        FileReader();

        ~FileReader();

        /**
         * Constructor.
         * \param File name
         */
        FileReader(std::string const&);

        /**
         * Convert object to boolean.
         * Returns true if stream not empty.
         */
        operator bool () const;

        /**
         * Get next n bytes.
         * \param Number of bytes (n)
         * \return vector of bytes
         */
        std::vector<char> getNext(size_t const&);
        
    protected:
        FileReader(FileReader const&) = delete;
        FileReader& operator=(FileReader const&) = delete;

    private:
        std::istream * input;
    };

};
