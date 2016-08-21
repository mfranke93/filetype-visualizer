#include "../third_party/catch/catch.hpp"
#include "../data/standard_single_byte_transition_counter.hpp"
#include <stdlib.h>

// data::AsciiTransitionCounter::AsciiTransitionCounter {{{
SCENARIO ("data::AsciiTransitionCounter::AsciiTransitionCounter")
{
    GIVEN ("a legal file reader")
    {
        std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>();

        WHEN ("calling the constructor")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW (data::AsciiTransitionCounter tc (f));
            }
        }
    }

    GIVEN ("an unfilled file reader")
    {
        std::shared_ptr<io::FileReader> f;

        WHEN ("calling the constructor")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS (data::AsciiTransitionCounter tc (f), except::uninitialized);
            }
        }
    }
}
// }}}
// data::AsciiTransitionCounter::getHistogram {{{
SCENARIO ("data::AsciiTransitionCounter::getHistogram")
{
    GIVEN ("an empty transition counter")
    {
        std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>();
        data::AsciiTransitionCounter tc (f);

        WHEN ("accessing the histogram")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(data::Histogram const& h = tc.getHistogram());
            }

            THEN ("it has the right size (128)")
            {
                data::Histogram const& h = tc.getHistogram();
                REQUIRE(h.getNumBins() == 128);
            }

            THEN ("all it's entries are zero")
            {
                data::Histogram const& h = tc.getHistogram();
                bool b = true;
                for (size_t x = 0; x < 128; ++x)
                {
                    for (size_t y = 0; y < 128; ++y)
                    {
                        b = b && (h.at(x,y) == 0);
                    }
                }
                REQUIRE(b);
            }
        }
    }
}
// }}}
// data::AsciiTransitionCounter::run {{{
SCENARIO ("data::AsciiTransitionCounter::run")
{
    srand(time(NULL));
    GIVEN ("an empty transition counter")
    {
        /****************************************************************
         * GENERATE TEST INPUT FILE WITH STRING "Hello world!\x0a"      *
         ****************************************************************/
        auto randchar = []() -> char
        {
            const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string filename_random_part (8, 0);
        std::generate_n(filename_random_part.begin(), 8, randchar);
        std::string filename = "/tmp/temp_catch_testfile_" + filename_random_part + ".txt";

        std::ofstream of (filename);
        of << "Hello world!\n";
        of.flush();
        of.close();
        /****************************************************************/

        std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>(filename);
        data::AsciiTransitionCounter tc (f);

        WHEN ("running the transition counter")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(tc.run());
            }


            THEN ("the histogram containst the values as specified")
            {
                tc.run();
                data::Histogram const& h = tc.getHistogram();

                REQUIRE(h.at(0x65, 0x48) == 1);
                REQUIRE(h.at(0x6c, 0x65) == 1);
                REQUIRE(h.at(0x6c, 0x6c) == 1);
                REQUIRE(h.at(0x6f, 0x6c) == 1);
                REQUIRE(h.at(0x20, 0x6f) == 1);
                REQUIRE(h.at(0x77, 0x20) == 1);
                REQUIRE(h.at(0x6f, 0x77) == 1);
                REQUIRE(h.at(0x72, 0x6f) == 1);
                REQUIRE(h.at(0x6c, 0x72) == 1);
                REQUIRE(h.at(0x64, 0x6c) == 1);
                REQUIRE(h.at(0x21, 0x64) == 1);
                REQUIRE(h.at(0x0a, 0x21) == 1);
                REQUIRE(h.at(0x7f, 0x7f) == 0);
            }
        }

        /****************************************************************
         * DELETE TEMPORARY FILE                                        *
         ****************************************************************/
        std::string syscall = "rm " + filename;
        system(syscall.c_str());
    }
}
// }}}
// data::AsciiTransitionCounter::setNormalizer {{{
SCENARIO ("data::AsciiTransitionCounter::setNormalizer")
{
    GIVEN ("an empty transition counter")
    {
        std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>();
        data::AsciiTransitionCounter tc (f);

        WHEN ("calling setNormalizer with a legal smart pointer")
        {
            THEN ("no exception is thrown")
            {
                std::shared_ptr<data::LogarithmicPlusOneNormalizer> norm = std::make_shared<data::LogarithmicPlusOneNormalizer>();
                REQUIRE_NOTHROW(tc.setNormalizer(norm));
            }
        }

        WHEN ("calling setNormalizer with an illegal smart pointer")
        {
            THEN ("an exception is thrown")
            {
                std::shared_ptr<data::LogarithmicPlusOneNormalizer> norm;
                REQUIRE_THROWS_AS(tc.setNormalizer(norm), except::uninitialized);
            }
        }
    }
}
// }}}
// data::ByteTransitionCounter::ByteTransitionCounter {{{
SCENARIO ("data::ByteTransitionCounter::ByteTransitionCounter")
{
    GIVEN ("a legal file reader")
    {
        std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>();

        WHEN ("calling the constructor")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW (data::ByteTransitionCounter tc (f));
            }
        }
    }

    GIVEN ("an unfilled file reader")
    {
        std::shared_ptr<io::FileReader> f;

        WHEN ("calling the constructor")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS (data::ByteTransitionCounter tc (f), except::uninitialized);
            }
        }
    }
}
// }}}
// data::ByteTransitionCounter::getHistogram {{{
SCENARIO ("data::ByteTransitionCounter::getHistogram")
{
    GIVEN ("an empty transition counter")
    {
        std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>();
        data::ByteTransitionCounter tc (f);

        WHEN ("accessing the histogram")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(data::Histogram const& h = tc.getHistogram());
            }

            THEN ("it has the right size (256)")
            {
                data::Histogram const& h = tc.getHistogram();
                REQUIRE(h.getNumBins() == 256);
            }

            THEN ("all it's entries are zero")
            {
                data::Histogram const& h = tc.getHistogram();
                bool b = true;
                for (size_t x = 0; x < 256; ++x)
                {
                    for (size_t y = 0; y < 256; ++y)
                    {
                        b = b && (h.at(x,y) == 0);
                    }
                }
                REQUIRE(b);
            }
        }
    }
}
// }}}
// data::ByteTransitionCounter::run {{{
SCENARIO ("data::ByteTransitionCounter::run")
{
    srand(time(NULL));
    GIVEN ("an empty transition counter")
    {
        /****************************************************************
         * GENERATE TEST INPUT FILE WITH STRING "Hello world!\x0a"      *
         ****************************************************************/
        auto randchar = []() -> char
        {
            const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string filename_random_part (8, 0);
        std::generate_n(filename_random_part.begin(), 8, randchar);
        std::string filename = "/tmp/temp_catch_testfile_" + filename_random_part + ".txt";

        std::ofstream of (filename);
        of << "Hello world!\n";
        of.flush();
        of.close();
        /****************************************************************/

        std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>(filename);
        data::ByteTransitionCounter tc (f);

        WHEN ("running the transition counter")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(tc.run());
            }


            THEN ("the histogram containst the values as specified")
            {
                tc.run();
                data::Histogram const& h = tc.getHistogram();

                REQUIRE(h.at(0x65, 0x48) == 1);
                REQUIRE(h.at(0x6c, 0x65) == 1);
                REQUIRE(h.at(0x6c, 0x6c) == 1);
                REQUIRE(h.at(0x6f, 0x6c) == 1);
                REQUIRE(h.at(0x20, 0x6f) == 1);
                REQUIRE(h.at(0x77, 0x20) == 1);
                REQUIRE(h.at(0x6f, 0x77) == 1);
                REQUIRE(h.at(0x72, 0x6f) == 1);
                REQUIRE(h.at(0x6c, 0x72) == 1);
                REQUIRE(h.at(0x64, 0x6c) == 1);
                REQUIRE(h.at(0x21, 0x64) == 1);
                REQUIRE(h.at(0x0a, 0x21) == 1);
                REQUIRE(h.at(0x7f, 0x7f) == 0);
            }
        }

        /****************************************************************
         * DELETE TEMPORARY FILE                                        *
         ****************************************************************/
        std::string syscall = "rm " + filename;
        system(syscall.c_str());
    }
}
// }}}
// data::ByteTransitionCounter::setNormalizer {{{
SCENARIO ("data::ByteTransitionCounter::setNormalizer")
{
    GIVEN ("an empty transition counter")
    {
        std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>();
        data::ByteTransitionCounter tc (f);

        WHEN ("calling setNormalizer with a legal smart pointer")
        {
            THEN ("no exception is thrown")
            {
                std::shared_ptr<data::LogarithmicPlusOneNormalizer> norm = std::make_shared<data::LogarithmicPlusOneNormalizer>();
                REQUIRE_NOTHROW(tc.setNormalizer(norm));
            }
        }

        WHEN ("calling setNormalizer with an illegal smart pointer")
        {
            THEN ("an exception is thrown")
            {
                std::shared_ptr<data::LogarithmicPlusOneNormalizer> norm;
                REQUIRE_THROWS_AS(tc.setNormalizer(norm), except::uninitialized);
            }
        }
    }
}
// }}}
