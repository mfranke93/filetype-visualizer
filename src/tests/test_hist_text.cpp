#include "catch.hpp"
#include <random>
#include "../vis/hist_text.hpp"

SCENARIO ("Text histogram")
{
    GIVEN ("A histogram with all zero values")
    {
        std::shared_ptr<data::Histogram> hist = std::make_shared<data::Histogram>(5);
        vis::TextHistogram th (hist);

        WHEN ("nothing more is done")
        {
            THEN ("all values should be ' '")
            {
                std::vector<std::string> v = th.getHistogram();

                for (std::string const& s : v)
                {
                    REQUIRE(s == "     ");
                }
            }
        }

        WHEN ("one value is set to one")
        {
            hist->addEntry(2,2);

            THEN ("one entry should be '#'")
            {
                std::vector<std::string> v = th.getHistogram();

                REQUIRE(v[0] == "     ");
                REQUIRE(v[1] == "     ");
                REQUIRE(v[2] == "  #  ");
                REQUIRE(v[3] == "     ");
                REQUIRE(v[4] == "     ");
            }
        }

        WHEN ("random values are added")
        {
            std::random_device rd;
            std::mt19937 mersenne (rd());
            std::uniform_int_distribution<size_t> dist (0, 123456564);

            for (size_t x = 0; x < 5; ++x)
            {
                for (size_t y = 0; y < 5; ++y)
                {
                    hist->addEntry(x,y,dist(mersenne));
                }
            }

            THEN ("at least one entry is '#'")
            {
                bool at_least_one = false;

                for (std::string const& s : th.getHistogram())
                {
                    if (s.find('#') != std::string::npos)
                    {
                        at_least_one = true;
                    }
                }

                REQUIRE (at_least_one);
            }
            
            THEN ("all entries are one of \" .-+=#\"")
            {
                std::string charset = " .-+=#";
                bool all = true;
                for (std::string const& s : th.getHistogram())
                {
                    for (char const& c : s)
                    {
                        if (charset.find(c) == std::string::npos)
                        {
                            all = false;
                        }
                    }
                }

                REQUIRE (all);
            }
        }
    }
}
