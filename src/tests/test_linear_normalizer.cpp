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
}
// }}}
