#include "../third_party/catch/catch.hpp"
#include <cmath>
#include "../data/linear_normalizer.hpp"

// Test LinearNormalizer<size_t> {{{
SCENARIO ("A LinearNormalizer<size_t>")
{
    GIVEN ("A normalizer with no values set")
    {
        data::LinearNormalizer<size_t> linNorm;

        WHEN ("we try to normalize on the uninitialized norm")
        {
            THEN ("we get an exception")
            {
                REQUIRE_THROWS_AS (double d = linNorm.normalize(12), std::out_of_range);
            }
        }

        WHEN ("we add one value (12) to the normalizer seed")
        {
            linNorm.seed(12);
            THEN ("normalizing value 12 should yield resulting normalized value 0.0")
            {
                REQUIRE(linNorm.normalize(12) == Approx(0.0));
            }

            THEN ("normalizing value 13 should result in a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(13), std::out_of_range);
            }
        }

        WHEN ("we add two values (12, 14) to the normalizer seed")
        {
            linNorm.seed(12);
            linNorm.seed(14);
            THEN("normalizing 12 should give 0.0")
            {
                REQUIRE(linNorm.normalize(12) == Approx(0.0));
            }

            THEN ("normalizing 13 should give 0.5")
            {
                REQUIRE(linNorm.normalize(13) == Approx(0.5));
            }

            THEN ("normalizing 14 should give 1.0")
            {
                REQUIRE(linNorm.normalize(14) == Approx(1.0));
            }

            THEN ("normalizing 15 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(15), std::out_of_range);
            }

            THEN ("normalizing 11 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(11), std::out_of_range);
            }
        }
    }

    GIVEN ("A normalizer with set start and end points")
    {
        data::LinearNormalizer<size_t> linNorm (10, 15);

        WHEN ("no further values are seeded")
        {
            THEN ("normalizing 10 gives 0.0")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.0));
            }
            THEN ("normalizing 13 gives 0.6")
            {
                REQUIRE(linNorm.normalize(13) == Approx(0.6));
            }
            THEN ("normalizing 15 gives 1.0")
            {
                REQUIRE(linNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing 5 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(5), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another value within the range is added (no change of range)")
        {
            linNorm.seed(12);

            THEN ("normalizing 10 gives 0.0")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.0));
            }
            THEN ("normalizing 13 gives 0.6")
            {
                REQUIRE(linNorm.normalize(13) == Approx(0.6));
            }
            THEN ("normalizing 15 gives 1.0")
            {
                REQUIRE(linNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing 5 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(5), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another value (5) is added below the range")
        {
            linNorm.seed(5);

            THEN ("normalizing 10 gives 0.5")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.5));
            }
            THEN ("normalizing 15 gives 1.0")
            {
                REQUIRE(linNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing 8 gives 0.3")
            {
                CHECK_NOTHROW(linNorm.normalize(8));
                REQUIRE(linNorm.normalize(8) == Approx(0.3));
            }
            THEN ("normalizing 4 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(4), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another value (24) is added above the range")
        {
            linNorm.seed(24);

            THEN ("normalizing 10 gives 0.0")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.0));
            }
            THEN ("normalizing 15 gives 5/14")
            {
                REQUIRE(linNorm.normalize(15) == Approx(5.0/14.0));
            }
            THEN ("normalizing 17 gives 0.5")
            {
                CHECK_NOTHROW(linNorm.normalize(17));
                REQUIRE(linNorm.normalize(17) == Approx(0.5));
            }
            THEN ("normalizing 6 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(6), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }
    }
}
// }}}
// Test LinearNormalizer<int> {{{
SCENARIO ("A LinearNormalizer<int>")
{
    GIVEN ("A normalizer with no values set")
    {
        data::LinearNormalizer<int> linNorm;

        WHEN ("we try to normalize on the uninitialized norm")
        {
            THEN ("we get an exception")
            {
                REQUIRE_THROWS_AS (double d = linNorm.normalize(12), std::out_of_range);
            }
        }

        WHEN ("we add one value (12) to the normalizer seed")
        {
            linNorm.seed(12);
            THEN ("normalizing value 12 should yield resulting normalized value 0.0")
            {
                REQUIRE(linNorm.normalize(12) == Approx(0.0));
            }

            THEN ("normalizing value 13 should result in a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(13), std::out_of_range);
            }
        }

        WHEN ("we add two values (12, 14) to the normalizer seed")
        {
            linNorm.seed(12);
            linNorm.seed(14);
            THEN("normalizing 12 should give 0.0")
            {
                REQUIRE(linNorm.normalize(12) == Approx(0.0));
            }

            THEN ("normalizing 13 should give 0.5")
            {
                REQUIRE(linNorm.normalize(13) == Approx(0.5));
            }

            THEN ("normalizing 14 should give 1.0")
            {
                REQUIRE(linNorm.normalize(14) == Approx(1.0));
            }

            THEN ("normalizing 15 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(15), std::out_of_range);
            }

            THEN ("normalizing 11 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(11), std::out_of_range);
            }
        }

        WHEN ("we add a negative value (-5) and a positive value (5) to the seed")
        {
            linNorm.seed(-5);
            linNorm.seed(5);
            THEN("normalizing -5 should give 0.0")
            {
                REQUIRE(linNorm.normalize(-5) == Approx(0.0));
            }

            THEN ("normalizing 0 should give 0.5")
            {
                REQUIRE(linNorm.normalize(0) == Approx(0.5));
            }

            THEN ("normalizing 14 should give 1.0")
            {
                REQUIRE(linNorm.normalize(5) == Approx(1.0));
            }

            THEN ("normalizing 15 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(15), std::out_of_range);
            }

            THEN ("normalizing -6 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(-6), std::out_of_range);
            }
        }

        WHEN ("we add two negative values (-5, -3) to the seed")
        {
            linNorm.seed(-5);
            linNorm.seed(-3);
            THEN("normalizing -5 should give 0.0")
            {
                REQUIRE(linNorm.normalize(-5) == Approx(0.0));
            }

            THEN ("normalizing -4 should give 0.5")
            {
                REQUIRE(linNorm.normalize(-4) == Approx(0.5));
            }

            THEN ("normalizing -3 should give 1.0")
            {
                REQUIRE(linNorm.normalize(-3) == Approx(1.0));
            }

            THEN ("normalizing 15 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(15), std::out_of_range);
            }

            THEN ("normalizing -2 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(-2), std::out_of_range);
            }

            THEN ("normalizing -6 should throw std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(-6), std::out_of_range);
            }
        }
    }

    GIVEN ("A normalizer with set start and end points in the positive")
    {
        data::LinearNormalizer<int> linNorm (10, 15);

        WHEN ("no further values are seeded")
        {
            THEN ("normalizing 10 gives 0.0")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.0));
            }
            THEN ("normalizing 13 gives 0.6")
            {
                REQUIRE(linNorm.normalize(13) == Approx(0.6));
            }
            THEN ("normalizing 15 gives 1.0")
            {
                REQUIRE(linNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing 5 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(5), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another value within the range is added (no change of range)")
        {
            linNorm.seed(12);

            THEN ("normalizing 10 gives 0.0")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.0));
            }
            THEN ("normalizing 13 gives 0.6")
            {
                REQUIRE(linNorm.normalize(13) == Approx(0.6));
            }
            THEN ("normalizing 15 gives 1.0")
            {
                REQUIRE(linNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing 5 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(5), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another positive value (5) is added below the range")
        {
            linNorm.seed(5);

            THEN ("normalizing 10 gives 0.5")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.5));
            }
            THEN ("normalizing 15 gives 1.0")
            {
                REQUIRE(linNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing 8 gives 0.3")
            {
                CHECK_NOTHROW(linNorm.normalize(8));
                REQUIRE(linNorm.normalize(8) == Approx(0.3));
            }
            THEN ("normalizing 4 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(4), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("a negative value (-5) is added below the range")
        {
            linNorm.seed(-5);

            THEN ("normalizing 10 gives 0.75")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.75));
            }
            THEN ("normalizing 15 gives 1.0")
            {
                REQUIRE(linNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing 5 gives 0.5")
            {
                CHECK_NOTHROW(linNorm.normalize(5));
                REQUIRE(linNorm.normalize(5) == Approx(0.5));
            }
            THEN ("normalizing 0 gives 0.25")
            {
                CHECK_NOTHROW(linNorm.normalize(0));
                REQUIRE(linNorm.normalize(0) == Approx(0.25));
            }
            THEN ("normalizing -5 gives 0.0")
            {
                CHECK_NOTHROW(linNorm.normalize(-5));
                REQUIRE(linNorm.normalize(-5) == Approx(0.0));
            }
            THEN ("normalizing -12 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(-12), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another value (24) is added above the range")
        {
            linNorm.seed(24);

            THEN ("normalizing 10 gives 0.0")
            {
                REQUIRE(linNorm.normalize(10) == Approx(0.0));
            }
            THEN ("normalizing 15 gives 5/14")
            {
                REQUIRE(linNorm.normalize(15) == Approx(5.0/14.0));
            }
            THEN ("normalizing 17 gives 0.5")
            {
                CHECK_NOTHROW(linNorm.normalize(17));
                REQUIRE(linNorm.normalize(17) == Approx(0.5));
            }
            THEN ("normalizing 6 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(6), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }
    }

    GIVEN ("A normalizer with set start point negative and end point positive")
    {
        data::LinearNormalizer<int> linNorm (-5, 5);

        WHEN ("no further values are seeded")
        {
            THEN ("normalizing -5 gives 0.0")
            {
                REQUIRE(linNorm.normalize(-5) == Approx(0.0));
            }
            THEN ("normalizing 0 gives 0.5")
            {
                REQUIRE(linNorm.normalize(0) == Approx(0.5));
            }
            THEN ("normalizing 5 gives 1.0")
            {
                REQUIRE(linNorm.normalize(5) == Approx(1.0));
            }
            THEN ("normalizing -10 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(-10), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another value within the range is added (no change of range)")
        {
            linNorm.seed(1);

            THEN ("normalizing -5 gives 0.0")
            {
                REQUIRE(linNorm.normalize(-5) == Approx(0.0));
            }
            THEN ("normalizing 0 gives 0.5")
            {
                REQUIRE(linNorm.normalize(0) == Approx(0.5));
            }
            THEN ("normalizing 5 gives 1.0")
            {
                REQUIRE(linNorm.normalize(5) == Approx(1.0));
            }
            THEN ("normalizing -10 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(-10), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another negative value (-15) is added below the range")
        {
            linNorm.seed(-15);

            THEN ("normalizing -5 gives 0.5")
            {
                REQUIRE(linNorm.normalize(-5) == Approx(0.5));
            }
            THEN ("normalizing 5 gives 1.0")
            {
                REQUIRE(linNorm.normalize(5) == Approx(1.0));
            }
            THEN ("normalizing -8 gives 0.35")
            {
                CHECK_NOTHROW(linNorm.normalize(-8));
                REQUIRE(linNorm.normalize(-8) == Approx(0.35));
            }
            THEN ("normalizing -16 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(-16), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }

        WHEN ("another value (24) is added above the range")
        {
            linNorm.seed(24);

            THEN ("normalizing -5 gives 0.0")
            {
                REQUIRE(linNorm.normalize(-5) == Approx(0.0));
            }
            THEN ("normalizing 15 gives 20/29")
            {
                REQUIRE(linNorm.normalize(15) == Approx(20.0/29.0));
            }
            THEN ("normalizing 17 gives 22/29")
            {
                CHECK_NOTHROW(linNorm.normalize(17));
                REQUIRE(linNorm.normalize(17) == Approx(22.0/29.0));
            }
            THEN ("normalizing -6 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(-6), std::out_of_range);
            }
            THEN ("normalizing 34 gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(linNorm.normalize(34), std::out_of_range);
            }
        }
    }

    GIVEN ("negative start and end values")
    {
        data::LinearNormalizer<int> linNorm (-10, -5);

        WHEN ("a positive value (10) is added")
        {
            linNorm.seed(10);

            THEN ("values up to that value can be normalized")
            {
                REQUIRE_NOTHROW(linNorm.normalize(10));
            }
            THEN ("normalizing 10 gives 1.0")
            {
                REQUIRE(linNorm.normalize(10) == Approx(1.0));
            }
            THEN ("normalizing -2 gives 0.4")
            {
                REQUIRE(linNorm.normalize(-2) == Approx(0.4));
            }
        }
    }
}
// }}}
// Test initialization with max<min {{{
SCENARIO ("Minimum seed value is larger than maximum seed value")
{
    GIVEN ("A LinearNormalizer<int>")
    {
        data::LinearNormalizer<int> linNorm (10, -10);
        WHEN ("normalizing the minimum value")
        {
            THEN ("the result should be 0.0, not 1.0")
            {
                REQUIRE(linNorm.normalize(-10) == Approx(0.0));
            }
        }
        WHEN ("normalizing the maximum value")
        {
            THEN ("the result should be 1.0, not 0.0")
            {
                REQUIRE(linNorm.normalize(10) == Approx(1.0));
            }
        }
    }
}
// }}}
