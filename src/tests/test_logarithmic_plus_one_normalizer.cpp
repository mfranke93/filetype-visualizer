#include "../third_party/catch/catch.hpp"
#include "../data/logarithmic_plus_one_normalizer.hpp"
#include <random>


SCENARIO ("data::LogarithmicPlusOneNormalizer::LogarithmicPlusOneNormalizer()")
{
    GIVEN ("a log+1 normalizer with no initial values")
    {
        WHEN ("calling the constructor")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(data::LogarithmicPlusOneNormalizer logNorm);
            }
        }
    }
}

SCENARIO ("data::LogarithmicPlusOneNormalizer::LogarithmicPlusOneNormalizer(size_t const&, size_t const&)")
{
    GIVEN ("a log+1 normalizer with initial values in the right order")
    {
        WHEN ("calling the constructor")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(data::LogarithmicPlusOneNormalizer logNorm (10, 20));
            }
        }
    }

    GIVEN ("a log+1 normalizer with initial values in the wrong order")
    {
        WHEN ("calling the constructor")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(data::LogarithmicPlusOneNormalizer logNorm (20, 10));
            }
        }
    }
}

SCENARIO ("data::LogarithmicPlusOneNormalizer::seed")
{
    std::random_device rd;
    std::mt19937 mersenne (rd());
    std::uniform_int_distribution<size_t> dist (0, 123456564);

    GIVEN ("an uninitialized log+1 normalizer")
    {
        data::LogarithmicPlusOneNormalizer logNorm;

        WHEN ("adding (random) values to the seed")
        {
            THEN ("no exception is thrown")
            {
                for (size_t i = 0; i < 200; ++i)
                {
                    REQUIRE_NOTHROW(logNorm.seed(dist(mersenne)));
                }
            }
        }
    }
}

SCENARIO ("data::LogarithmicPlusOneNormalizer::normalize")
{
    GIVEN ("a log+1 normalizer with no initial values")
    {
        data::LogarithmicPlusOneNormalizer logNorm;

        WHEN ("attempting to normalize")
        {
            THEN ("except::normalizer_exception is thrown")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(12), except::uninitialized);
            }
        }

        WHEN ("adding one value")
        {
            logNorm.seed(12);

            THEN("normalizing to that value gives 0.0")
            {
                REQUIRE(logNorm.normalize(12) == Approx(0.0));
            }
            THEN ("normalizing a lower value gives a except::normalizer_exception")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(11), except::normalizer_exception);
            }
            THEN ("normalizing a higher value gives a except::normalizer_exception")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(13), except::normalizer_exception);
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
            THEN ("normalizing one lower than the lower one gives a except::normalizer_exception")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(9), except::normalizer_exception);
            }
            THEN ("normalizing one higher than the lower one gives a except::normalizer_exception")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(16), except::normalizer_exception);
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
            THEN ("normalizing one lower than the lower one gives a except::normalizer_exception")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(9), except::normalizer_exception);
            }
            THEN ("normalizing one higher than the lower one gives a except::normalizer_exception")
            {
                REQUIRE_THROWS_AS(logNorm.normalize(16), except::normalizer_exception);
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
