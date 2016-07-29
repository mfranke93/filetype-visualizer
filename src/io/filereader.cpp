#include "filereader.hpp"

io::FileReader::FileReader(std::string const& fname)
{
   this->input = new std::ifstream(fname, std::ios_base::binary);
    //
    // nothing more to do here right now
}

io::FileReader::FileReader()
{
    this->input = &std::cin;
    //// create ISO C FILE structure from std::cin
    //__gnu_cxx::stdio_filebuf<char> filbuf(stdin, std::ios::out);
    //this->input.std::ios::rdbuf(&filbuf);
}

io::FileReader::~FileReader()
{
    if (this->input == nullptr) delete this->input;
}

io::FileReader::operator bool () const
{
    return bool(*(this->input)); // evaluate badness of stream
}

std::vector<char> io::FileReader::getNext(size_t const& numberBytes)
{
    std::vector<char> v;
    char c;

    for (size_t i = 0; i < numberBytes && this->input; ++i)
    {
        if (!(this->input->get(c)))
        {
            // todo: error handling
        }
        else
        {
            v.push_back(c);
        }
    }

    return v;
}
