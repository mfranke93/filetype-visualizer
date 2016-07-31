#include "data/histogram.hpp"
#include "vis/hist_text.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char ** argv)
{
    data::Histogram h (40);
    for (size_t y = 0; y < 40; ++y)
    {
        for (size_t x = 0; x < 40; ++x)
        {
            h.addEntry(x, y, 40*41 - (x-15)*(y-20) - y);
        }
    }

    vis::TextHistogram th (&h);
    std::vector<std::string> v = th.getHistogram();

    for (std::string const& s:v) {
        std::cout << s << std::endl;
    }

    return 0;
}
