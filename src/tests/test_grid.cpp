#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <cmath>
#include "../data/grid.hpp"

SCENARIO ( "grid is initialized as zeros", "" ) {
    GIVEN ("A Grid with no set entries") {
        data::Grid<float> g (3,3);

        for (size_t y = 0; y < 3; ++y)
        {
            for (size_t x = 0; x < 3; ++x)
            {
                REQUIRE(abs(g(x,y)) < 1.0e-9 );
            }
        }
    }
}
