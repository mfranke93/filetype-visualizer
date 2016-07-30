#include "data/histogram.hpp"
#include <stdio.h>

int main(int argc, char ** argv)
{
    data::Histogram h (4);
    for (size_t y = 0; y < 4; ++y)
    {
        for (size_t x = 0; x < 4; ++x)
        {
            h.addEntry(x, y, x+y);
        }
    }

    data::Grid<double> normalized = h.getNormalized();
    for (size_t y = 0; y < 4; ++y)
    {
        for (size_t x = 0; x < 4; ++x)
        {
            printf("%f ", normalized(x,y));
        }
        printf("\n");
    }
    return 0;
}
