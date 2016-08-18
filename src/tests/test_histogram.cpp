#include "../third_party/catch/catch.hpp"
#include <random>
#include "../data/grid.hpp"
#include "../data/histogram.hpp"
#include "../data/linear_normalizer.hpp"
#include "../data/logarithmic_plus_one_normalizer.hpp"

// data::Histogram::Histogram {{{
SCENARIO ("data::Histogram::Histogram")
{
    GIVEN ("a histogram being initialized with size 0x0")
    {
        WHEN ("constructor is called")
        {
            THEN ("a illegal_size exception is thrown")
            {
                REQUIRE_THROWS_AS(data::Histogram h (0), except::illegal_size);
            }
        }
    }

    GIVEN ("a histogram being initialized with legal size")
    {
        WHEN ("constructor is called")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(data::Histogram h (12));
            }
        }
    }
}
// }}}
// data::Histogram::addEntry {{{
SCENARIO ("data::Histogram::addEntry")
{
    GIVEN ("a histogram")
    {
        data::Histogram h (20);

        WHEN ("adding a value to a legal position")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(h.addEntry(10, 5));
            }
        }

        WHEN ("adding a value to a legal position (amount not equal to one)")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(h.addEntry(10, 5, 6));
            }
        }

        WHEN ("adding a value to an illegal position")
        {
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.addEntry(20, 5, 6), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.addEntry(21, 5, 6), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.addEntry(2, 20), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.addEntry(2, 2045), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.addEntry(20, 5), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.addEntry(20, 20), std::out_of_range);
            }
        }
    }
}
// }}}
// data::Histogram::getNumBins {{{
SCENARIO ("data::Histogram::getNumBins")
{
    GIVEN ("a histogram of given size")
    {
        data::Histogram h (324);

        WHEN ("accessing the size")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(size_t const i = h.getNumBins());
            }

            THEN ("the correct value is returned")
            {
                REQUIRE(324 == h.getNumBins());
            }
        }
    }
}
// }}}
// data::Histogram::at {{{
SCENARIO ("data::Histogram::at")
{
    GIVEN ("a histogram with empty grid")
    {
        data::Histogram h (40);

        WHEN ("accessing the values in grid")
        {
            THEN ("no exception is thrown")
            {
                for (size_t x = 0; x < 40; ++x)
                {
                    for (size_t y = 0; y < 40; ++y)
                    {
                        REQUIRE_NOTHROW(size_t const g = h.at(x,y));
                    }
                }
            }
            THEN ("they should all be zero")
            {
                for (size_t x = 0; x < 40; ++x)
                {
                    for (size_t y = 0; y < 40; ++y)
                    {
                        CHECK(h.at(x,y) == 0);
                    }
                }
            }
        }

        WHEN ("accessing values outside of grid")
        {
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(40, 0), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(41, 0), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(0, 40), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(0, 41), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(100, 41), std::out_of_range);
            }
        }
    }

    GIVEN ("a histogram with non-empty grid")
    {
        data::Histogram h (40);
        std::random_device rd;
        std::mt19937 mersenne (rd());
        std::uniform_int_distribution<size_t> dist (0, 123456);
        for (size_t x = 0; x < 40; ++x)
        {
            for (size_t y = 0; y < 40; ++y)
            {
                h.addEntry(x, y, dist(mersenne));
            }
        }

        WHEN ("accessing the values in grid")
        {
            THEN ("no exception is thrown")
            {
                for (size_t x = 0; x < 40; ++x)
                {
                    for (size_t y = 0; y < 40; ++y)
                    {
                        REQUIRE_NOTHROW(size_t const g = h.at(x,y));
                    }
                }
            }
        }

        WHEN ("accessing values outside of grid")
        {
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(40, 0), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(41, 0), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(0, 40), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(0, 41), std::out_of_range);
            }
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(h.at(100, 41), std::out_of_range);
            }
        }
    }
}
// }}}
// data::Histogram::getNormalized {{{
SCENARIO ("data::Histogram::getNormalized", "")
{
    GIVEN ("A Histogram where all entries are zero")
    {
        data::Histogram h (4);
        std::shared_ptr<data::LinearNormalizer<size_t>> linNorm = std::make_shared<data::LinearNormalizer<size_t>>();
        h.setNormalizer(linNorm);
        
        WHEN ("no assignments have been done")
        {
            THEN ("no std::logic_error is thrown")
            {
                REQUIRE_NOTHROW(data::Grid<double> g = h.getNormalized());
            }

            THEN ("the normalized grid should be zero everywhere")
            {
                data::Grid<double> g = h.getNormalized();

                for (size_t x = 0; x < 4; ++x)
                {
                    for (size_t y = 0; y < 4; ++y)
                    {
                        REQUIRE(g(x,y) == Approx(0.0));
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
                            REQUIRE(g(x,y) == Approx(1.0));
                        }
                        else
                        {
                            REQUIRE(g(x,y) == Approx(0.0));
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
                        REQUIRE(g(x,y) == Approx(should_be));
                    }
                }
            }
        }
    }

    GIVEN("A histogram with linear normalizer where all entries are one")
    {
        data::Histogram h (4);
        std::shared_ptr<data::LinearNormalizer<size_t>> linNorm = std::make_shared<data::LinearNormalizer<size_t>>();
        h.setNormalizer(linNorm);
        for (size_t x = 0; x < 4; ++x)
        {
            for (size_t y = 0; y < 4; ++y)
            {
                h.addEntry(x,y);
            }
        }

        WHEN ("nothing else is done")
        {
            THEN ("all entries in the histogram should be zero")
            {
                data::Grid<double> g = h.getNormalized();

                for (size_t x = 0; x < 4; ++x)
                {
                    for (size_t y = 0; y < 4; ++y)
                    {
                        REQUIRE(g(x,y) == Approx(0.0));
                    }
                }
            }
        }
    }
    GIVEN("A histogram with log+1 normalizer where all entries are one")
    {
        data::Histogram h (4);
        std::shared_ptr<data::LogarithmicPlusOneNormalizer> logNorm = std::make_shared<data::LogarithmicPlusOneNormalizer>();
        h.setNormalizer(logNorm);
        for (size_t x = 0; x < 4; ++x)
        {
            for (size_t y = 0; y < 4; ++y)
            {
                h.addEntry(x,y);
            }
        }

        WHEN ("nothing else is done")
        {
            THEN ("all entries in the histogram should be zero")
            {
                data::Grid<double> g = h.getNormalized();

                for (size_t x = 0; x < 4; ++x)
                {
                    for (size_t y = 0; y < 4; ++y)
                    {
                        REQUIRE(g(x,y) == Approx(0.0));
                    }
                }
            }
        }
    }

    std::random_device rd;
    std::mt19937 mersenne (rd());
    std::uniform_int_distribution<size_t> dist (0, 123456564);

    GIVEN ("A histogram with linear normalizer and pseudorandom entries")
    {
        data::Histogram h (20);
        std::shared_ptr<data::LinearNormalizer<size_t>> linNorm = std::make_shared<data::LinearNormalizer<size_t>>();
        h.setNormalizer(linNorm);
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
                        if (g(x,y) == Approx(1.0))
                        {
                            exactly_one = true;
                        }
                    }
                }

                REQUIRE(exactly_one);
            }
        }
    }

    GIVEN ("A histogram with log+1 normalizer and pseudorandom entries")
    {
        data::Histogram h (20);
        std::shared_ptr<data::LogarithmicPlusOneNormalizer> linNorm = std::make_shared<data::LogarithmicPlusOneNormalizer>();
        h.setNormalizer(linNorm);
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
                        if (g(x,y) == Approx(1.0))
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
// data::Histogram::setNormalizer {{{
SCENARIO ("data::Histogram::setNormalizer")
{
    GIVEN ("a Histogram")
    {
        data::Histogram h (20);

        WHEN ("setting the normalizer correctly")
        {
            std::shared_ptr<data::LinearNormalizer<size_t>> norm = std::make_shared<data::LinearNormalizer<size_t>>();

            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(h.setNormalizer(norm));
            }
        }

        WHEN ("setting the normalizer to an empty shared_ptr")
        {
            std::shared_ptr<data::LinearNormalizer<size_t>> norm;

            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(h.setNormalizer(norm), except::uninitialized);
            }
        }
    }
} 
// }}}
