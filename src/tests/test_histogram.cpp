#include "catch.hpp"
#include <random>
#include "../data/grid.hpp"
#include "../data/histogram.hpp"

// Test Histogram {{{
SCENARIO ("Histogram on predefined values", "")
{
    GIVEN ("A Histogram where all entries are zero")
    {
        data::Histogram h (4);
        
        WHEN ("no assignments have been done")
        {
            THEN ("the normalized grid should be zero everywhere and no std::logic_error is thrown")
            {
                data::Grid<double> g = h.getNormalized();

                for (size_t x = 0; x < 4; ++x)
                {
                    for (size_t y = 0; y < 4; ++y)
                    {
                        REQUIRE(g(x,y) == 0.0);
                    }
                }
            }
        }

        WHEN ("one entry has been added")
        {
            h.addEntry(1,2,4);

            THEN ("ths entry should define the maximum value")
            {
                data::Grid<double> g = h.getNormalized();

                for (size_t x = 0; x < 4; ++x)
                {
                    for (size_t y = 0; y < 4; ++y)
                    {
                        if (x == 1 && y == 2)
                        {
                            REQUIRE(g(x,y) == 1.0);
                        }
                        else
                        {
                            REQUIRE(g(x,y) == 0.0);
                        }
                    }
                }
            }
        }

        WHEN ("each entry has been set to its Manhattan norm")
        {
            for (size_t x = 0; x < 4; ++x)
            {
                for (size_t y = 0; y < 4; ++y)
                {
                    h.addEntry(x,y,x+y);
                }
            }

            THEN ("each entry should have appropriate normalized value in the histogram")
            {
                data::Grid<double> g = h.getNormalized();

                for (size_t x = 0; x < 4; ++x)
                {
                    for (size_t y = 0; y < 4; ++y)
                    {
                        double should_be = static_cast<double>(x+y)/6.0;
                        REQUIRE(g(x,y) == should_be);
                    }
                }
            }
        }
    }

    GIVEN("A histogram where all entries are one")
    {
        data::Histogram h (4);
        for (size_t x = 0; x < 4; ++x)
        {
            for (size_t y = 0; y < 4; ++y)
            {
                h.addEntry(x,y);
            }
        }

        WHEN ("nothing else is done")
        {
            THEN ("all entries in the histogram should be one")
            {
                data::Grid<double> g = h.getNormalized();

                for (size_t x = 0; x < 4; ++x)
                {
                    for (size_t y = 0; y < 4; ++y)
                    {
                        REQUIRE(g(x,y) == 1.0);
                    }
                }
            }
        }
    }
}
// }}}
// Test Histogram with random numbers {{{
SCENARIO ("Histogram with pseudorandom entries", "")
{
    std::random_device rd;
    std::mt19937 mersenne (rd());
    std::uniform_int_distribution<size_t> dist (0, 123456564);

    GIVEN ("A histogram with pseudorandom entries")
    {
        data::Histogram h (20);
        for (size_t x = 0; x < 20; ++x)
        {
            for (size_t y = 0; y < 20; ++y)
            {
                h.addEntry(x,y,dist(mersenne));
            }
        }

        WHEN ("normalizing")
        {
            data::Grid<double> g = h.getNormalized();

            THEN ("all entries should be between zero and one")
            {
                for (size_t x = 0; x < 20; ++x)
                {
                    for (size_t y = 0; y < 20; ++y)
                    {
                        REQUIRE(g(x,y) >= 0.0);
                        REQUIRE(g(x,y) <= 1.0);
                    }
                }
            }

            THEN ("at least one entry must be exactly one")
            {
                bool exactly_one = false;
                for (size_t x = 0; x < 20; ++x)
                {
                    for (size_t y = 0; y < 20; ++y)
                    {
                        if (g(x,y) == 1.0)
                        {
                            exactly_one = true;
                        }
                    }
                }

                REQUIRE(exactly_one);
            }
        }
    }
}
// }}}
