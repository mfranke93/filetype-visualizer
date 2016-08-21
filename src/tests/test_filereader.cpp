#include "../third_party/catch/catch.hpp"
#include "../io/filereader.hpp"
#include <stdlib.h>

// io::FileReader::FileReader() {{{
SCENARIO ("io::FileReader::FileReader()")
{
    GIVEN ("a file reader for stdin")
    {
        WHEN ("calling the constructor")
        {
            THEN ("no error is thrown")
            {
                REQUIRE_NOTHROW(io::FileReader f ());
            }
        }
    }
}
// }}}
// io::FileReader::FileReader(std::string const&) {{{
SCENARIO ("io::FileReader::FileReader(std::string const&)")
{
    GIVEN ("a file reader for a file")
    {
        WHEN ("calling the constructor on a valid filename")
        {
            THEN ("no error is thrown")
            {
                // own binary should be in this folder
                REQUIRE_NOTHROW(io::FileReader f ("tests"));
            }
        }

        WHEN ("calling the constructor on an invalid filename")
        {
            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(io::FileReader f ("totally_bullshit_filename-12345.glorp"), std::invalid_argument);
            }

            THEN ("an exception is thrown")
            {
                REQUIRE_THROWS_AS(io::FileReader f (""), std::invalid_argument);
            }
        }
    }
}
// }}}
// io::FileReader::~FileReader {{{
SCENARIO ("io::FileReader::~FileReader")
{
    GIVEN ("a filereader for std::cin")
    {
        io::FileReader * f = new io::FileReader();

        WHEN ("deallocating it")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(delete f);
            }
        }
    }

    GIVEN ("a filereader for a file")
    {
        io::FileReader * f = new io::FileReader("tests");

        WHEN ("deallocating it")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(delete f);
            }
        }
    }
}
// }}}
// io::FileReader::operator bool {{{
SCENARIO ("io::FileReader::operator bool")
{
    srand(time(NULL));
    GIVEN ("a filereader to a file")
    {
        /****************************************************************
         * GENERATE EMPTY TEST INPUT FILE                               *
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
        of << "e";
        of.flush();
        of.close();
        /****************************************************************/
        io::FileReader f (filename);

        WHEN ("calling operator bool")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(bool b = f);
            }

            THEN ("the queue is not empty, and true is returned")
            {
                REQUIRE(f);
            }
        }

        WHEN ("removing the last element and then calling operator bool")
        {
            f.getNext(1);

            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(bool b = f);
            }

            THEN ("the queue is empty, and false is returned")
            {
                REQUIRE(!f);
            }
        }
        std::string syscall = "rm " + filename;
        system(syscall.c_str());
    }
}
// }}}
// io::FileReader::getNext {{{
SCENARIO ("io::FileReader::getNext")
{
    srand(time(NULL));
    GIVEN ("a filereader to a file")
    {
        /****************************************************************
         * GENERATE EMPTY TEST INPUT FILE                               *
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

        io::FileReader f (filename);

        WHEN ("calling getNext on the next 10 chars")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(f.getNext(10));
            }

            THEN ("a vector of size 10 is returned")
            {
                std::vector<unsigned char> vec = f.getNext(10);
                REQUIRE(vec.size() == 10);
            }

            THEN ("the first 10 chars of the string are returned")
            {
                std::vector<unsigned char> vec = f.getNext(10);
                std::string s ("");
                for (unsigned char const& c : vec) s+=c;
                REQUIRE(s == "Hello worl");
            }
        }

        WHEN ("calling getNext on the next 20 chars")
        {
            THEN ("no exception is thrown")
            {
                REQUIRE_NOTHROW(f.getNext(20));
            }

            THEN ("a vector of size 13 is returned")
            {
                std::vector<unsigned char> vec = f.getNext(20);
                REQUIRE(vec.size() == 13);
            }

            THEN ("the first 13 chars of the string are returned")
            {
                std::vector<unsigned char> vec = f.getNext(20);
                std::string s ("");
                for (unsigned char const& c : vec) s+=c;
                REQUIRE(s == "Hello world!\n");
            }
        }

        WHEN ("calling getNext on an empty queue")
        {
            f.getNext(13);

            THEN ("no exception is thrown")
            {
                CHECK (!f);
                REQUIRE_NOTHROW(f.getNext(20));
            }

            THEN ("an empty vector is returned")
            {
                CHECK (!f);
                std::vector<unsigned char> vec = f.getNext(20);
                REQUIRE(vec.empty());
            }
        }
        std::string syscall = "rm " + filename;
        system(syscall.c_str());
    }
}
// }}}
