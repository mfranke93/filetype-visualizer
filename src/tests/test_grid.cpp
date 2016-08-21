#include "../third_party/catch/catch.hpp"
#include <cmath>
#include "../data/grid.hpp"

// data::Grid<float>::Grid(Grid const&) {{{
SCENARIO ( "data::Grid<float>::Grid(Grid const&)", "" )
{
    GIVEN ("A Grid with no set entries")
    {
        data::Grid<float> g (3,3);

        WHEN ("copy-constructoring this into a new grid")
        {
            THEN ("no exceptions should be thrown") 
            {
                REQUIRE_NOTHROW(data::Grid<float> h (g));
            }
        }
    }
}
// }}}
// data::Grid<float>::Grid(size_t const&) {{{
SCENARIO ("data::Grid<float>::Grid(size_t const&)")
{
    GIVEN ("an empty Grid")
    {
        WHEN ("calling the constructor with a legal size value")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(data::Grid<float> g (2));
            }
        }

        WHEN ("calling the constructor with an illegal size value")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(data::Grid<float> g (0), except::illegal_size);
            }
        }
    }
}
// }}}
// data::Grid<float>::Grid(size_t const&, size_t const&) {{{
SCENARIO ("data::Grid<float>::Grid(size_t const&, size_t const&)")
{
    GIVEN ("an empty Grid")
    {
        WHEN ("calling the constructor with two legal size values")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(data::Grid<float> g (2,2));
            }
        }

        WHEN ("calling the constructor with one or two illegal size value")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(data::Grid<float> g (0, 2), except::illegal_size);
            }
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(data::Grid<float> g (2, 0), except::illegal_size);
            }
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(data::Grid<float> g (0, 0), except::illegal_size);
            }
        }
    }
}
// }}}
// data::Grid<float>::~Grid {{{
SCENARIO ("data::Grid<float>::~Grid")
{
    GIVEN ("an empty Grid")
    {
        data::Grid<float> * g = new data::Grid<float> (10);

        WHEN ("calling the destructor")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(delete g);
            }
        }
    }

    GIVEN ("a filled Grid")
    {
        data::Grid<float> * g = new data::Grid<float> (10);

        (*g)(2, 4) = 2.2f;
        (*g)(3, 4) = 2.2f;
        (*g)(2, 5) = 2.2f;
        (*g)(4, 6) = 2.2f;
        (*g)(4, 7) = 2.2f;

        WHEN ("calling the destructor")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(delete g);
            }
        }
    }
}
// }}}
// data::Grid<float>::operator() {{{
SCENARIO ("data::Grid<float>::operator()")
{
    GIVEN ("an empty Grid")
    {
        data::Grid<float> g (3,3);
        WHEN ("writing to it")
        {
            THEN ("no exceptions are thrown")
            {
                REQUIRE_NOTHROW(g(1,1) = 2.2f);
            }
            THEN ("no exceptions are thrown")
            {
                REQUIRE_NOTHROW(g(0,0) = 2.2f);
            }
            THEN ("no exceptions are thrown")
            {
                REQUIRE_NOTHROW(g(2,2) = 2.2f);
            }
            THEN ("no exceptions are thrown")
            {
                REQUIRE_NOTHROW(g(2,1) = 2.2f);
            }
        }

        WHEN ("writing outside of it")
        {
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(g(3,0) = 2.2f, std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(g(0,3) = 2.2f, std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(g(3,3) = 2.2f, std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(g(1,23) = 2.2f, std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(g(332,2) = 2.2f, std::out_of_range);
            }
        }
    }
}
// }}}
// data::Grid<float>::operator() const {{{
SCENARIO ("data::Grid<float>::operator() const")
{
    GIVEN ("a filled Grid")
    {
        data::Grid<float> g (10);

        g(2, 4) = 2.2f;
        g(3, 4) = 2.2f;
        g(2, 5) = 2.2f;
        g(4, 6) = 2.2f;
        g(4, 7) = 2.2f;

        data::Grid<float> const h (g);

        WHEN ("accessing a value inside")
        {
            THEN ("no exception is thrown")
            {
                for (size_t x = 0; x < 10; ++x)
                {
                    for (size_t y = 0; y < 10; ++y)
                    {
                        REQUIRE_NOTHROW(float const f = h(x,y));
                    }
                }
            }

            THEN ("it will be correct")
            {
                REQUIRE(h(0,0) == 0.0f);
            }
            THEN ("it will be correct")
            {
                REQUIRE(h(2,2) == 0.0f);
            }
            THEN ("it will be correct")
            {
                REQUIRE(h(2,5) == 2.2f);
            }
        }

        WHEN ("accessing a value outside the Grid")
        {
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(float const f = h(10, 5), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(float const f = h(1, 10), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(float const f = h(10, 10), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(float const f = h(11, 5), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(float const f = h(9, 35), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(float const f = h(132, 25), std::out_of_range);
            }
        }
    }
}
// }}}
// data::Grid<float>::getMaximum {{{
SCENARIO ("data::Grid<float>::getMaximum")
{
    GIVEN ("an empty Grid")
    {
        data::Grid<float> g (5);

        WHEN ("calling the getMaximum function")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(float const f = g.getMaximum());
            }

            THEN ("the value 0 is returned")
            {
                REQUIRE(g.getMaximum() == 0.0f);
            }
        }
    }

    GIVEN ("a non-empty grid")
    {
        data::Grid<float> g (5);
        g(1,1) = 12.0f;
        g(3,2) = -16.0f;
        g(2,1) = 3.441;
        g(4,4) = 0.0001;

        WHEN ("calling the getMaximum function")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(float const f = g.getMaximum());
            }

            THEN ("the maximum is returned")
            {
                REQUIRE(g.getMaximum() == 12.0f);
            }
        }
    }
}
// }}}
// data::Grid<float>::asVector {{{
SCENARIO ("data::Grid<float>::asVector")
{
    GIVEN ("an empty Grid")
    {
        data::Grid<float> g (5);

        WHEN ("calling the asVector function")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(std::shared_ptr<std::vector<float>> vec = g.asVector());
            }
        }

        WHEN ("calling the asVector function")
        {
            std::shared_ptr<std::vector<float>> vec = g.asVector();
            THEN ("the shared pointer is not empty")
            {
                REQUIRE(vec);
            }
            THEN ("the length of the vector is correct")
            {
                REQUIRE(vec->size() == 25);
            }
            THEN ("the elements are correctly all zero")
            {
                for (float const& f : *vec)
                {
                    CHECK(f == 0.0f);
                }
            }
        }
    }

    GIVEN ("a non-empty grid")
    {
        data::Grid<float> g (5);
        g(1,1) = 12.0f;
        g(3,2) = -16.0f;
        g(2,1) = 3.441;
        g(4,4) = 0.0001;

        WHEN ("calling the asVector function")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(std::shared_ptr<std::vector<float>> vec = g.asVector());
            }
        }

        WHEN ("calling the asVector function")
        {
            std::shared_ptr<std::vector<float>> vec = g.asVector();
            THEN ("the shared pointer is not empty")
            {
                REQUIRE(vec);
            }
            THEN ("the length of the vector is correct")
            {
                REQUIRE(vec->size() == 25);
            }
            THEN ("the elements are all correctly set in row-major")
            {
                CHECK(vec->at(0+5*0) == 0.0f);
                CHECK(vec->at(1+5*0) == 0.0f);
                CHECK(vec->at(2+5*0) == 0.0f);
                CHECK(vec->at(3+5*0) == 0.0f);
                CHECK(vec->at(4+5*0) == 0.0f);
                CHECK(vec->at(0+5*1) == 0.0f);
                CHECK(vec->at(1+5*1) == 12.0f);
                CHECK(vec->at(2+5*1) == 3.441f);
                CHECK(vec->at(3+5*1) == 0.0f);
                CHECK(vec->at(4+5*1) == 0.0f);
                CHECK(vec->at(0+5*2) == 0.0f);
                CHECK(vec->at(1+5*2) == 0.0f);
                CHECK(vec->at(2+5*2) == 0.0f);
                CHECK(vec->at(3+5*2) == -16.0f);
                CHECK(vec->at(4+5*2) == 0.0f);
                CHECK(vec->at(0+5*3) == 0.0f);
                CHECK(vec->at(1+5*3) == 0.0f);
                CHECK(vec->at(2+5*3) == 0.0f);
                CHECK(vec->at(3+5*3) == 0.0f);
                CHECK(vec->at(4+5*3) == 0.0f);
                CHECK(vec->at(0+5*4) == 0.0f);
                CHECK(vec->at(1+5*4) == 0.0f);
                CHECK(vec->at(2+5*4) == 0.0f);
                CHECK(vec->at(3+5*4) == 0.0f);
                CHECK(vec->at(4+5*4) == 0.0001f);
            }
        }
    }
}
// }}}
