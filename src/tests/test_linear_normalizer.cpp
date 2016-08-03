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
                REQUIRE_NOTHROW(linNorm.normalize(8));
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
                REQUIRE_NOTHROW(linNorm.normalize(17));
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
