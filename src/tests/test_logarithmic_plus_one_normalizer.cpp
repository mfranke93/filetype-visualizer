#include "../third_party/catch/catch.hpp"
#include "../data/logarithmic_plus_one_normalizer.hpp"

SCENARIO ("LogarithmicPlusOneNormalizer")
{
    GIVEN ("a log+1 normalizer with no initial values")
    {
        data::LogarithmicPlusOneNormalizer logNorm;

        WHEN ("attempting to normalize")
        {
            THEN ("std::out_of_range is thrown")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(12), std::out_of_range);
            }
        }

        WHEN ("adding one value")
        {
            logNorm.seed(12);

            THEN("normalizing to that value gives 0.0")
            {
                REQUIRE(logNorm.normalize(12) == Approx(0.0));
            }
            THEN ("normalizing a lower value gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(11), std::out_of_range);
            }
            THEN ("normalizing a higher value gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(13), std::out_of_range);
            }
        }

        WHEN ("adding two values")
        {
            logNorm.seed(10);
            logNorm.seed(15);

            THEN ("normalizing the lower gives 0.0")
            {
                REQUIRE(logNorm.normalize(10) == Approx(0.0));
            }
            THEN ("normalizing the higher gives 1.0")
            {
                REQUIRE(logNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing one lower than the lower one gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(9), std::out_of_range);
            }
            THEN ("normalizing one higher than the lower one gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(16), std::out_of_range);
            }
        }
    }

    GIVEN ("a log+1 normalizer with initial values")
    {
        data::LogarithmicPlusOneNormalizer logNorm (10, 15);

        WHEN ("when seeding no further values")
        {
            THEN ("normalizing the lower gives 0.0")
            {
                REQUIRE(logNorm.normalize(10) == Approx(0.0));
            }
            THEN ("normalizing the higher gives 1.0")
            {
                REQUIRE(logNorm.normalize(15) == Approx(1.0));
            }
            THEN ("normalizing one lower than the lower one gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(9), std::out_of_range);
            }
            THEN ("normalizing one higher than the lower one gives a std::out_of_range")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(16), std::out_of_range);
            }
        }
    }

    GIVEN ("a log+1 normalizer with initial values")
    {
        data::LogarithmicPlusOneNormalizer logNorm (0, 65535);

        WHEN ("normalizing any value in it's range")
        {
            THEN ("a value between 0 and 1 should be the result")
            {
                bool anyNot = false;
                for (size_t i = 0; i < 65536; ++i)
                {
                    double d = logNorm.normalize(i);
                    anyNot |= (d >= 0.0);
                    anyNot |= (d <= 1.0);
                }

                REQUIRE(anyNot);
            }
        }
    }
}
