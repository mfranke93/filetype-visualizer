#include "filereader.hpp"

io::FileReader::FileReader(std::string const& fname)
:   input(fname, std::ios_base::binary)
{
    // nothing more to do here right now
}

io::FileReader::operator bool () const
{
    return bool(this->input); // evaluate badness of stream
}

std::vector<char> io::FileReader::getNext(size_t const& numberBytes)
{
    std::vector<char> v;
    char c;

    for (size_t i = 0; i < numberBytes && this->input; ++i)
    {
        if (!(this->input.get(c)))
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
