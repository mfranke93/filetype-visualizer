#include "filereader.hpp"

io::FileReader::FileReader(std::string const& fname)
:   wasInitializedAsCin(false)
{
   this->input = std::make_shared<std::ifstream>(fname, std::ios_base::binary);
}

io::FileReader::FileReader()
:   wasInitializedAsCin(true)
{
    /*
     * Initialize this smart pointer with a custom deallocator lambda.
     * This lambda does nothing, which removes the necissity to keep a smart
     * pointer of std::cin in head at program termination to avoid an illegal
     * delete call.
     */
    this->input = std::shared_ptr<std::istream>(&std::cin, [](std::istream * ptr) { /* do nothing */ });
}

io::FileReader::~FileReader()
{
    // dtor
    // nothing to do here
}

io::FileReader::operator bool () const
{
    return bool(*(this->input)); // evaluate badness of stream
}

std::vector<unsigned char> io::FileReader::getNext(size_t const& numberBytes)
{
    std::vector<unsigned char> v;
    char c;

    for (size_t i = 0; i < numberBytes && this->input; ++i)
    {
        if (!(this->input->get(c)))
        {
            // todo: error handling
        }
        else
        {
            v.push_back(static_cast<unsigned char>(c));
        }
    }

    return v;
}
