#include "standard_colormap.hpp"
#include <iostream>
#include <stdexcept>

void vis::StandardColormap::addColor(double const& location, color const& c)
{
    // find index at which to add
    std::vector<vis::locationizedColor>::iterator it = this->colors.begin();
    while ((it+1)->location < location) ++it;
    
    // insert there
    vis::locationizedColor lc;
    lc.location = location;
    lc.c = c;
    this->colors.insert(it, lc);
}

void vis::StandardColormap::getColor(double const& location, color& c) const
{
    // find interval
    std::vector<vis::locationizedColor>::const_iterator it = this->colors.begin();
    while ((it+1)->location < location) ++it;

    vis::locationizedColor a = *it;
    vis::locationizedColor b = *(1+it);

    // linear interpolation
    c.R = channel( (double(b.c.R) * (location - a.location) + double(a.c.R) * (b.location - location))/(b.location - a.location));
    c.G = channel( (double(b.c.G) * (location - a.location) + double(a.c.G) * (b.location - location))/(b.location - a.location));
    c.B = channel( (double(b.c.B) * (location - a.location) + double(a.c.B) * (b.location - location))/(b.location - a.location));
}

std::shared_ptr<vis::StandardColormap const> 
vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps const& type)
{
    switch (type)
    {
        // red through white to blue color map {{{
        case vis::PredefinedColormaps::RED_BLUE:
            {
                vis::color a;
                a.R = 255;
                a.G = 0;
                a.B = 0;

                vis::color b;
                b.R = 0;
                b.G = 0;
                b.B = 255;

                vis::color middle;
                middle.R = 255;
                middle.G = 255;
                middle.B = 255;

                vis::locationizedColor c0;
                c0.location = 0.0;
                c0.c = a;
                vis::locationizedColor c1;
                c1.location = 0.475;
                c1.c = middle;
                vis::locationizedColor c2;
                c2.location = 0.525;
                c2.c = middle;
                vis::locationizedColor c3;
                c3.location = 1.0;
                c3.c = b;

                std::vector<vis::locationizedColor> locCol;
                locCol.push_back(c0);
                locCol.push_back(c1);
                locCol.push_back(c2);
                locCol.push_back(c3);

                std::shared_ptr<vis::StandardColormap> c = std::make_shared<vis::StandardColormap> (locCol);
                return c;
            }
            break;
        // }}}
        // black through red and yellow to white color map {{{
        case vis::PredefinedColormaps::BLACK_BODY_HEAT:
            {
                vis::color col;
                vis::locationizedColor l;
                std::vector<vis::locationizedColor> vec;

                // black at 0
                col.R = col.G = col.B  = 0;
                l.c = col;
                l.location = 0.0;
                vec.push_back(l);

                // red at 0.4
                col.R = 220;
                l.c = col;
                l.location = 0.4;
                vec.push_back(l);

                // yellow at 0.8;
                col.G = 255;
                l.c = col;
                l.location = 0.8;
                vec.push_back(l);

                // white at 1
                col.B = 255;
                l.c = col;
                l.location = 1.0;
                vec.push_back(l);

                std::shared_ptr<vis::StandardColormap> c = std::make_shared<vis::StandardColormap> (vec);
                return c;
            } 
            break;
        // }}}
        // black through blue to light blue color map {{{
        case vis::PredefinedColormaps::DEEP_SEA:
            {
                vis::color col;
                vis::locationizedColor l;
                std::vector<vis::locationizedColor> vec;

                // black at 0
                col.R = col.G = col.B  = 0;
                l.c = col;
                l.location = 0.0;
                vec.push_back(l);

                // deep blue at 0.1
                col.B = 50;
                l.c = col;
                l.location = 0.1;
                vec.push_back(l);

                // middle blue at 0.6;
                col.B = 180;
                col.G = 80;
                l.c = col;
                l.location = 0.6;
                vec.push_back(l);

                // light cyan at 0.9
                col.B = 255;
                col.G = 220;
                l.c = col;
                l.location = 0.9;
                vec.push_back(l);

                // white at 1
                col.R = col.G = col.B  = 255;
                l.c = col;
                l.location = 1.0;
                vec.push_back(l);

                std::shared_ptr<vis::StandardColormap> c = std::make_shared<vis::StandardColormap> (vec);
                return c;
            } 
            break;
        // }}}
        // default: throw exception {{{
        default:
            char s [255];
            sprintf(s, "%s: Unhandled colormap style: %d.", __PRETTY_FUNCTION__, type);
            throw std::out_of_range(s);
        // }}}
    }
}
