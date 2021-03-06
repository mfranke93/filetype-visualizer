#include "../third_party/catch/catch.hpp"
#include "../vis/image.hpp"

// vis::Image::Image {{{
SCENARIO ("vis::Image::Image")
{
    GIVEN ("An image with illegal width")
    {
        WHEN ("Calling the constructor")
        {
            THEN ("An exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::Image i (0, 200), std::length_error);
            }
        }
    }

    GIVEN ("An image with illegal height")
    {
        WHEN ("Calling the constructor")
        {
            THEN ("An exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::Image i (200, 0), std::length_error);
            }
        }
    }

    GIVEN ("An image with illegal width and height")
    {
        WHEN ("Calling the one parameter constructor")
        {
            THEN ("An exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::Image i (0), std::length_error);
            }
        }
    }

    GIVEN ("An image with illegal width and height")
    {
        WHEN ("Calling the two parameter constructor")
        {
            THEN ("An exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::Image i (0, 0), std::length_error);
            }
        }
    }

    GIVEN ("An image with legal with and height")
    {
        THEN ("no exception should be thrown (vis::Image::Image(size_t const&))")
        {
            REQUIRE_NOTHROW(vis::Image i (200));
        }

        THEN ("no exception should be thrown (vis::Image::Image(size_t const&, size_t const&))")
        {
            REQUIRE_NOTHROW(vis::Image i (200, 200));
        }
    }
}
// }}}
// vis::Image::operator() {{{}
SCENARIO ("vis::Image::operator()")
{
    GIVEN ("An image with legal width and height")
    {
        vis::Image img (200, 300);

        WHEN ("Accessing its width")
        {
            size_t const w = img.getWidth();
            THEN ("the correct value should be returned")
            {
                REQUIRE(w == 200);
            }
        }

        WHEN ("Accessing its height")
        {
            size_t const h = img.getHeight();
            THEN ("the correct value should be returned")
            {
                REQUIRE(h == 300);
            }
        }

        WHEN ("No values have been written yet")
        {
            THEN ("All values should be zero (black)")
            {
                bool allZero = true;
                for (size_t x = 0; x < img.getWidth(); ++x)
                {
                    for (size_t y = 0; y < img.getHeight(); ++y)
                    {
                        vis::color const c = img(x,y);
                        if (c.R != 0 || c.G != 0 || c.B != 0)
                        {
                            allZero = false;
                        }
                    }
                }
                REQUIRE(allZero);
            }
        }

        WHEN ("Having written one value")
        {
            vis::color c (255, 0, 127);
            img(100, 150) = c;

            THEN ("This value should be correct (const accessor)")
            {
                vis::color const d = img(100, 150);
                REQUIRE( c.R == d.R );
                REQUIRE( c.G == d.G );
                REQUIRE( c.B == d.B );
            }

            THEN ("This value should be correct (non-const accessor)")
            {
                vis::color d = img(100, 150);
                REQUIRE( c.R == d.R );
                REQUIRE( c.G == d.G );
                REQUIRE( c.B == d.B );
            }
        }

        WHEN ("Accessing an x coordinate out of range")
        {
            THEN ("an exception is thrown (non-const accessor)")
            {
                REQUIRE_THROWS_AS(vis::color d = img(300, 300), std::out_of_range);
            }

            THEN ("an exception is thrown (const accessor)")
            {
                REQUIRE_THROWS_AS(vis::color const d = img(300, 300), std::out_of_range);
            }
        }

        WHEN ("Accessing an y coordinate out of range")
        {
            THEN ("an exception is thrown (non-const accessor)")
            {
                REQUIRE_THROWS_AS(vis::color d = img(100, 500), std::out_of_range);
            }

            THEN ("an exception is thrown (const accessor)")
            {
                REQUIRE_THROWS_AS(vis::color const d = img(100, 500), std::out_of_range);
            }
        }
        WHEN ("Accessing an x and y coordinate out of range")
        {
            THEN ("an exception is thrown (non-const accessor)")
            {
                REQUIRE_THROWS_AS(vis::color d = img(600, 500), std::out_of_range);
            }

            THEN ("an exception is thrown (const accessor)")
            {
                REQUIRE_THROWS_AS(vis::color const d = img(600, 500), std::out_of_range);
            }
        }
    }
}
// }}}
// vis::Image::~Image {{{}
SCENARIO ("vis::Image::~Image")
{
    GIVEN ("An initialized Image object in the heap")
    {
        vis::Image * img = new vis::Image(200);
        WHEN ("Deleting the object")
        {
            THEN ("No double free should occur")
            {
                REQUIRE_NOTHROW(delete img);
            }
        }
    }
}
// }}}
// vis::Image::getWidth {{{}
SCENARIO ("vis::Image::getWidth")
{
    GIVEN ("An image object")
    {
        vis::Image i (200);
        WHEN ("comparing getWidth with given width")
        {
            THEN ("both should be equal")
            {
                REQUIRE (i.getWidth() == 200);
            }
        }
    }
}
// }}}
// vis::Image::getHeight {{{}
SCENARIO ("vis::Image::getHeight")
{
    GIVEN ("An image object")
    {
        vis::Image i (200);
        WHEN ("comparing getHeight with given height")
        {
            THEN ("both should be equal")
            {
                REQUIRE (i.getHeight() == 200);
            }
        }
    }
}
// }}}
