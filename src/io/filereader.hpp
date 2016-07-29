#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>

namespace io {
    
    class FileReader
    {
    public:
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
        FileReader() = delete;
        FileReader(FileReader const&) = delete;
        FileReader& operator=(FileReader const&) = delete;

    private:
        std::ifstream input;
    };

};
