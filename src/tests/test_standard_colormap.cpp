#include "../third_party/catch/catch.hpp"
#include "../vis/standard_colormap.hpp"
#include <random>

// vis::locationizedColor::locationizedColor(double const&, color) {{{
SCENARIO ("vis::locationizedColor::locationizedColor(double const&, color)")
{
    GIVEN ("a vis::locationizedColor with legal location and a color")
    {
        WHEN ("constructing")
        {
            THEN ("no exceptions are thrown")
            {
                REQUIRE_NOTHROW(vis::locationizedColor c (0.0, vis::color(0,0,0)));
            }
        }

        WHEN ("having constructed the object")
        {
            vis::locationizedColor c (0.1256, vis::color(12, 32, 67));

            THEN ("the location value is correct")
            {
                REQUIRE(c.location == Approx(0.1256));
            }

            THEN ("the color value is correct")
            {
                REQUIRE(c.c.R == 12);
                REQUIRE(c.c.G == 32);
                REQUIRE(c.c.B == 67);
            }
        }
    }

    GIVEN ("a vis::locationizedColor with illegal location: negative")
    {
        WHEN ("constructing")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::locationizedColor c (-0.5, vis::color(255, 0, 0)), std::out_of_range);
            }
        }
    }

    GIVEN ("a vis::locationizedColor with illegal location: greater than one")
    {
        WHEN ("constructing")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::locationizedColor c (1.2, vis::color(255, 0, 0)), std::out_of_range);
            }
        }
    }
}
// }}}
// vis::locationizedColor::locationizedColor() {{{
SCENARIO ("vis::locationizedColor::locationizedColor()")
{
    GIVEN ("a vis::locationizedColor with legal no arguments")
    {
        WHEN ("constructing")
        {
            THEN ("no exceptions are thrown")
            {
                REQUIRE_NOTHROW(vis::locationizedColor c ());
            }
        }

        WHEN ("having constructed the object")
        {
            vis::locationizedColor c;

            THEN ("the location value is correct")
            {
                REQUIRE(c.location == 0.0);
            }

            THEN ("the color value is correct")
            {
                REQUIRE(c.c.R == 0);
                REQUIRE(c.c.G == 0);
                REQUIRE(c.c.B == 0);
            }
        }
    }
}
// }}}
// vis::StandardColormap::StandardColormap {{{
SCENARIO ("vis::StandardColormap::StandardColormap")
{
    GIVEN ("A vector of locationizedColor's")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor()); // 0, black
        vec.push_back(vis::locationizedColor(1.0, vis::color(255,255,255)));

        WHEN ("calling the constructor")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(vis::StandardColormap cm (vec));
            }
        }
    }

    GIVEN ("A vector of locationizedColor's where none is 0.0")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor(0.1, vis::color())); // 0.1, black
        vec.push_back(vis::locationizedColor(1.0, vis::color(255,255,255)));

        WHEN ("calling the constructor")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::StandardColormap cm (vec), std::invalid_argument);
            }
        }
    }

    GIVEN ("A vector of locationizedColor's where none is 1.0")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor(0.0, vis::color())); // 0.0, black
        vec.push_back(vis::locationizedColor(0.9, vis::color(255,255,255)));

        WHEN ("calling the constructor")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::StandardColormap cm (vec), std::invalid_argument);
            }
        }
    }

    GIVEN ("A vector of locationizedColor's which is empty")
    {
        std::vector<vis::locationizedColor> vec;

        WHEN ("calling the constructor")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::StandardColormap cm (vec), std::invalid_argument);
            }
        }
    }

    GIVEN ("A vector of locationizedColor's which is unsorted ")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor(0.0, vis::color())); // 0.0, black
        vec.push_back(vis::locationizedColor(0.5, vis::color())); 
        vec.push_back(vis::locationizedColor(0.3, vis::color())); 
        vec.push_back(vis::locationizedColor(1.0, vis::color(255,255,255)));

        WHEN ("calling the constructor")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::StandardColormap cm (vec), std::invalid_argument);
            }
        }
    }
}
// }}}
// vis::StandardColormap::~StandardColormap {{{
SCENARIO ("vis::StandardColormap::~StandardColormap")
{
    GIVEN ("A StandardColormap")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor()); // 0, black
        vec.push_back(vis::locationizedColor(1.0, vis::color(255,255,255)));
        vis::StandardColormap * cm = new vis::StandardColormap (vec);

        WHEN ("deallocating")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(delete cm);
            }
        }
    }
}
// }}}
// vis::StandardColormap::addColor {{{
SCENARIO ("vis::StandardColormap::addColor")
{
    GIVEN ("a StandardColormap")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor()); // 0, black
        vec.push_back(vis::locationizedColor(1.0, vis::color(255,255,255)));
        vis::StandardColormap cm (vec);

        WHEN ("adding a color")
        {
            THEN ("no exception is thrown, regardless on the color and location (range constraints [0;1])")
            {
                // Python random generated location, color pair insertions (50) {{{
               REQUIRE_NOTHROW(cm.addColor(0.235395, vis::color(99, 89, 236)));
               REQUIRE_NOTHROW(cm.addColor(0.587984, vis::color(96, 76, 115)));
               REQUIRE_NOTHROW(cm.addColor(0.825926, vis::color(7, 9, 145)));
               REQUIRE_NOTHROW(cm.addColor(0.951542, vis::color(140, 20, 239)));
               REQUIRE_NOTHROW(cm.addColor(0.774821, vis::color(159, 57, 148)));
               REQUIRE_NOTHROW(cm.addColor(0.862779, vis::color(145, 188, 96)));
               REQUIRE_NOTHROW(cm.addColor(0.962783, vis::color(105, 108, 126)));
               REQUIRE_NOTHROW(cm.addColor(0.896382, vis::color(180, 214, 101)));
               REQUIRE_NOTHROW(cm.addColor(0.074023, vis::color(172, 146, 16)));
               REQUIRE_NOTHROW(cm.addColor(0.218776, vis::color(138, 154, 156)));
               REQUIRE_NOTHROW(cm.addColor(0.536029, vis::color(146, 205, 164)));
               REQUIRE_NOTHROW(cm.addColor(0.820083, vis::color(129, 105, 15)));
               REQUIRE_NOTHROW(cm.addColor(0.151151, vis::color(101, 223, 123)));
               REQUIRE_NOTHROW(cm.addColor(0.630330, vis::color(115, 153, 222)));
               REQUIRE_NOTHROW(cm.addColor(0.981314, vis::color(213, 182, 111)));
               REQUIRE_NOTHROW(cm.addColor(0.284524, vis::color(35, 96, 95)));
               REQUIRE_NOTHROW(cm.addColor(0.192551, vis::color(111, 246, 88)));
               REQUIRE_NOTHROW(cm.addColor(0.079495, vis::color(33, 20, 160)));
               REQUIRE_NOTHROW(cm.addColor(0.738261, vis::color(184, 5, 111)));
               REQUIRE_NOTHROW(cm.addColor(0.961553, vis::color(77, 70, 8)));
               REQUIRE_NOTHROW(cm.addColor(0.870383, vis::color(136, 107, 134)));
               REQUIRE_NOTHROW(cm.addColor(0.413937, vis::color(172, 223, 75)));
               REQUIRE_NOTHROW(cm.addColor(0.494940, vis::color(102, 89, 65)));
               REQUIRE_NOTHROW(cm.addColor(0.245000, vis::color(116, 75, 27)));
               REQUIRE_NOTHROW(cm.addColor(0.124472, vis::color(113, 123, 79)));
               REQUIRE_NOTHROW(cm.addColor(0.484567, vis::color(184, 48, 5)));
               REQUIRE_NOTHROW(cm.addColor(0.350282, vis::color(11, 105, 232)));
               REQUIRE_NOTHROW(cm.addColor(0.163405, vis::color(95, 210, 201)));
               REQUIRE_NOTHROW(cm.addColor(0.980480, vis::color(94, 116, 98)));
               REQUIRE_NOTHROW(cm.addColor(0.568682, vis::color(86, 23, 36)));
               REQUIRE_NOTHROW(cm.addColor(0.768251, vis::color(60, 120, 250)));
               REQUIRE_NOTHROW(cm.addColor(0.181708, vis::color(207, 139, 109)));
               REQUIRE_NOTHROW(cm.addColor(0.920755, vis::color(211, 4, 146)));
               REQUIRE_NOTHROW(cm.addColor(0.376772, vis::color(146, 102, 124)));
               REQUIRE_NOTHROW(cm.addColor(0.394022, vis::color(77, 173, 35)));
               REQUIRE_NOTHROW(cm.addColor(0.890348, vis::color(139, 106, 196)));
               REQUIRE_NOTHROW(cm.addColor(0.273007, vis::color(209, 117, 113)));
               REQUIRE_NOTHROW(cm.addColor(0.959145, vis::color(46, 44, 213)));
               REQUIRE_NOTHROW(cm.addColor(0.022535, vis::color(133, 6, 208)));
               REQUIRE_NOTHROW(cm.addColor(0.665593, vis::color(99, 65, 155)));
               REQUIRE_NOTHROW(cm.addColor(0.934296, vis::color(217, 46, 171)));
               REQUIRE_NOTHROW(cm.addColor(0.366112, vis::color(203, 188, 35)));
               REQUIRE_NOTHROW(cm.addColor(0.121327, vis::color(133, 107, 117)));
               REQUIRE_NOTHROW(cm.addColor(0.866536, vis::color(104, 101, 152)));
               REQUIRE_NOTHROW(cm.addColor(0.721003, vis::color(1, 146, 27)));
               REQUIRE_NOTHROW(cm.addColor(0.754185, vis::color(90, 86, 75)));
               REQUIRE_NOTHROW(cm.addColor(0.638262, vis::color(164, 45, 136)));
               REQUIRE_NOTHROW(cm.addColor(0.434258, vis::color(238, 34, 91)));
               REQUIRE_NOTHROW(cm.addColor(0.336660, vis::color(241, 17, 133)));
               REQUIRE_NOTHROW(cm.addColor(0.821987, vis::color(144, 171, 242)));
               // }}}
            }
        }

        WHEN ("a color has been added")
        {
            vis::color d (255, 0, 0);
            cm.addColor(0.5, d);

            THEN ("the color there should be correct")
            {
                vis::color c = cm.getColor(0.5);
                REQUIRE(c.R == d.R);
                REQUIRE(c.G == d.G);
                REQUIRE(c.B == d.B);
            }
        }
    }
}
// }}}
// vis::StandardColormap::getColor {{{
SCENARIO ("vis::StandardColormap::getColor")
{
    GIVEN ("a StandardColormap black to white")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor()); // 0, black
        vec.push_back(vis::locationizedColor(1.0, vis::color(255,255,255)));
        vis::StandardColormap cm (vec);

        WHEN ("accessing a value in range")
        {
            THEN ("its color should be a greyscale value equal to the distance to zero")
            {
                for (size_t i = 0; i <= 255; i++)
                {
                    vis::channel c = vis::channel(i);
                    double const offset = double(c)/255.0;
                    vis::color const d (c,c,c);
                    vis::color const col = cm.getColor(offset);

                    REQUIRE(col.R == d.R);
                    REQUIRE(col.G == d.G);
                    REQUIRE(col.B == d.B);

                }
            }
        }

        WHEN ("trying to access a color out of range (location < 0)")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::color c = cm.getColor(-23.1), except::normalizer_exception);
            }
        }

        WHEN ("trying to access a color out of range (location > 1)")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::color c = cm.getColor(3.1), except::normalizer_exception);
            }
        }
    }

    GIVEN ("a StandardColormap red to green")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor(0.0, vis::color(255,  0,  0)));
        vec.push_back(vis::locationizedColor(1.0, vis::color(  0,255,  0)));
        vis::StandardColormap cm (vec);

        WHEN ("accessing a value in range")
        {
            THEN ("its color should be a value in linear interpolation between red and green")
            {
                for (size_t i = 0; i <= 255; i++)
                {
                    vis::channel c = vis::channel(i);
                    double const offset = double(c)/255.0;
                    vis::color const d (255-c,c,0);
                    vis::color const col = cm.getColor(offset);

                    // allow some tolerance
                    REQUIRE(abs(int(col.R) - int(d.R)) <= 1);
                    REQUIRE(abs(int(col.G) - int(d.G)) <= 1);
                    REQUIRE(abs(int(col.B) - int(d.B)) <= 1);
                }
            }
        }
    }

    GIVEN ("a StandardColormap blue to red")
    {
        std::vector<vis::locationizedColor> vec;
        vec.push_back(vis::locationizedColor(0.0, vis::color(  0,  0,255)));
        vec.push_back(vis::locationizedColor(1.0, vis::color(255,  0,  0)));
        vis::StandardColormap cm (vec);

        WHEN ("accessing a value in range")
        {
            THEN ("its color should be a value in linear interpolation between blue and red")
            {
                for (size_t i = 0; i <= 255; i++)
                {
                    vis::channel c = vis::channel(i);
                    double const offset = double(c)/255.0;
                    vis::color const d (c,0,255-c);
                    vis::color const col = cm.getColor(offset);

                    // allow some tolerance
                    REQUIRE(abs(int(col.R) - int(d.R)) <= 1);
                    REQUIRE(abs(int(col.G) - int(d.G)) <= 1);
                    REQUIRE(abs(int(col.B) - int(d.B)) <= 1);
                }
            }
        }
    }
}
// }}}
// vis::StandardColormap::getPredefinedColormap {{{
SCENARIO ("vis::StandardColormap::getPredefinedColormap")
{
    GIVEN ("no prerequisites")
    {
        WHEN ("accessing the standard colormap RED_BLUE")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(auto cm = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::RED_BLUE));
            }

            THEN ("the returned colormap should be valid")
            {
                std::shared_ptr<vis::StandardColormap const> cm = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::RED_BLUE);
                REQUIRE(cm);
            }
        }
        
        WHEN ("accessing the standard colormap BLACK_BODY_HEAT")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(auto cm = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::BLACK_BODY_HEAT));
            }

            THEN ("the returned colormap should be valid")
            {
                std::shared_ptr<vis::StandardColormap const> cm = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::BLACK_BODY_HEAT);
                REQUIRE(cm);
            }
        }

        WHEN ("accessing the standard colormap DEEP_SEA")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(auto cm = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::DEEP_SEA));
            }

            THEN ("the returned colormap should be valid")
            {
                std::shared_ptr<vis::StandardColormap const> cm = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::DEEP_SEA);
                REQUIRE(cm);
            }
        }

        WHEN ("accessing the standard colormap GRAYSCALE")
        {
            THEN ("no exception should be thrown")
            {
                REQUIRE_NOTHROW(auto cm = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::GRAYSCALE));
            }

            THEN ("the returned colormap should be valid")
            {
                std::shared_ptr<vis::StandardColormap const> cm = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::GRAYSCALE);
                REQUIRE(cm);
            }
        }

        WHEN ("accessing the standard colormap undefined (force creation of enum entry 999, assuming we never will have that many predefined colormaps)")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(auto cm = vis::StandardColormap::getPredefinedColormap(static_cast<vis::PredefinedColormaps>(999)), std::out_of_range);
            }
        }
    }
}
// }}}
