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

