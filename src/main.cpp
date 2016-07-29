#include "io/filereader.hpp"
#include <stdio.h>

int main(int argc, char ** argv)
{
    io::FileReader f ("/home/max/.vimrc");
    std::vector<char> v = f.getNext(20);

    for (char const& c : v)
    {
        printf("%X ", c);
    }
    printf("     ");
    for (char const& c : v)
    {
        printf("%c", c);
    }
    printf("\n");

    return 0;
}
