#include "data/grid.hpp"
#include <stdio.h>

int main(int argc, char ** argv)
{
    data::Grid<float> g (4,4);

    g(1,1) = 2;
    g(2,1) = 1.4;

    for (size_t y=0; y<4; ++y)
    {
    for (size_t x=0; x<4; ++x)
    {
        printf("%f ", g(x,y));

    }
    printf("\n");
    }
}
