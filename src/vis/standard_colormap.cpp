#include "standard_colormap.hpp"
#include <iostream>

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
                c1.location = 0.5;
                c1.c = middle;
                vis::locationizedColor c2;
                c2.location = 1.0;
                c2.c = b;

                std::vector<vis::locationizedColor> locCol;
                locCol.push_back(c0);
                locCol.push_back(c1);
                locCol.push_back(c2);

                std::shared_ptr<vis::StandardColormap> c = std::make_shared<vis::StandardColormap> (locCol);
                return c;
            }
            break;

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
        default:
            throw -3;
    }
}
