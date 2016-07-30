#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

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
        std::shared_ptr<std::istream> input;
        bool const wasInitializedAsCin; // there has to be a better wau
    };

};
