#include "../third_party/catch/catch.hpp"
#include <cmath>
#include "../data/grid.hpp"

// Test Grid<float> {{{
SCENARIO ( "Grid of type float", "" )
{
    GIVEN ("A Grid with no set entries")
    {
        data::Grid<float> g (3,3);

        WHEN ("no assignments have been done")
        {
            THEN ("all grid elements should be zero") 
            {
                for (size_t y = 0; y < 3; ++y)
                {
                    for (size_t x = 0; x < 3; ++x)
                    {
                        REQUIRE(g(x,y) == 0.0f );
                    }
                }
            }

            THEN ("the maximum should be zero")
            {
                REQUIRE(g.getMaximum() == 0.0f);
            }
        }

        WHEN ("an element is set to 1.0f") 
        {
            g(1, 2) = 1.0f;

            THEN ("all other elements are still 0.0f")
            {
                for (size_t y = 0; y < 3; ++y)
                {
                    for (size_t x = 0; x < 3; ++x)
                    {
                        if (x != 1 || y != 2) 
                        {
                            REQUIRE(g(x,y) == 0.0f );
                        }
                        else
                        {
                            REQUIRE(g(x,y) == 1.0f );
                        }
                    }
                }
            }

            THEN ("the maximum value should be 1.0f")
            {
                REQUIRE(g.getMaximum() == 1.0f);
            }
        }

        WHEN ("an element is set to 5.0f") 
        {
            g(0,2) = 5.0f;

            THEN ("the maximum value should be 5.0f")
            {
                REQUIRE(g.getMaximum() == 5.0f);
            }
        }

        WHEN ("an element is set to -0.001f") 
        {
            g(0,0) = -0.001f;

            THEN ("the maximum value should be 0.0f") 
            {
                REQUIRE(g.getMaximum() == 0.0f);
            }
        }
    }

    GIVEN ("A Grid with all entries set to their Manhattan norm") 
    {
        data::Grid<float> g (3,3);
        for (size_t y = 0; y < 3; ++y)
        {
            for (size_t x = 0; x < 3; ++x)
            {
                g(x,y) = float(x+y);
            }
        }

        WHEN ("the getMaximum function is called on this") 
        {
            THEN ("the maximum should be the last element, which is 4f") 
            {
                REQUIRE(g.getMaximum() == 4.0f);
            }
        }
    }
}
// }}}
// Test Grid<int> {{{
SCENARIO ("Grid of type int", "") 
{
    GIVEN ("A Grid with no set entries")
    {
        data::Grid<int> g (3,3);

        WHEN ("no assignments have been done")
        {
            THEN ("all grid elements should be zero") 
            {
                for (size_t y = 0; y < 3; ++y)
                {
                    for (size_t x = 0; x < 3; ++x)
                    {
                        REQUIRE(g(x,y) == 0 );
                    }
                }
            }

            THEN ("the maximum should be zero")
            {
                REQUIRE(g.getMaximum() == 0);
            }
        }

        WHEN ("an element is set to 1") 
        {
            g(1, 2) = 1;

            THEN ("all other elements are still 0")
            {
                for (size_t y = 0; y < 3; ++y)
                {
                    for (size_t x = 0; x < 3; ++x)
                    {
                        if (x != 1 || y != 2) 
                        {
                            REQUIRE(g(x,y) == 0 );
                        }
                        else
                        {
                            REQUIRE(g(x,y) == 1 );
                        }
                    }
                }
            }

            THEN ("the maximum value should be 1")
            {
                REQUIRE(g.getMaximum() == 1);
            }
        }

        WHEN ("an element is set to 5") 
        {
            g(0,2) = 5;

            THEN ("the maximum value should be 5")
            {
                REQUIRE(g.getMaximum() == 5);
            }
        }

        WHEN ("an element is set to -1") 
        {
            g(0,0) = -1;

            THEN ("the maximum value should be 0") 
            {
                REQUIRE(g.getMaximum() == 0);
            }
        }
    }

    GIVEN ("A Grid with all entries set to their Manhattan norm") 
    {
        data::Grid<float> g (3,3);
        for (size_t y = 0; y < 3; ++y)
        {
            for (size_t x = 0; x < 3; ++x)
            {
                g(x,y) = x+y;
            }
        }

        WHEN ("the getMaximum function is called on this") 
        {
            THEN ("the maximum should be the last element, which is 4") 
            {
                REQUIRE(g.getMaximum() == 4);
            }
        }
    }
}
// }}}
// Test Grid<size_t> {{{
SCENARIO ("Grid of type size_t", "") 
{
    GIVEN ("A Grid with no set entries")
    {
        data::Grid<size_t> g (3,3);

        WHEN ("no assignments have been done")
        {
            THEN ("all grid elements should be zero") 
            {
                for (size_t y = 0; y < 3; ++y)
                {
                    for (size_t x = 0; x < 3; ++x)
                    {
                        REQUIRE(g(x,y) == 0 );
                    }
                }
            }

            THEN ("the maximum should be zero")
            {
                REQUIRE(g.getMaximum() == 0);
            }
        }

        WHEN ("an element is set to 1") 
        {
            g(1, 2) = 1;

            THEN ("all other elements are still 0")
            {
                for (size_t y = 0; y < 3; ++y)
                {
                    for (size_t x = 0; x < 3; ++x)
                    {
                        if (x != 1 || y != 2) 
                        {
                            REQUIRE(g(x,y) == 0 );
                        }
                        else
                        {
                            REQUIRE(g(x,y) == 1 );
                        }
                    }
                }
            }

            THEN ("the maximum value should be 1")
            {
                REQUIRE(g.getMaximum() == 1);
            }
        }

        WHEN ("an element is set to 5") 
        {
            g(0,2) = 5;

            THEN ("the maximum value should be 5")
            {
                REQUIRE(g.getMaximum() == 5);
            }
        }
    }

    GIVEN ("A Grid with all entries set to their Manhattan norm") 
    {
        data::Grid<float> g (3,3);
        for (size_t y = 0; y < 3; ++y)
        {
            for (size_t x = 0; x < 3; ++x)
            {
                g(x,y) = x+y;
            }
        }

        WHEN ("the getMaximum function is called on this") 
        {
            THEN ("the maximum should be the last element, which is 4") 
            {
                REQUIRE(g.getMaximum() == 4);
            }
        }
    }
}
// }}}
