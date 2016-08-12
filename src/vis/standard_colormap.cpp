#include "standard_colormap.hpp"

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

void vis::StandardColormap::getColor(double const& location, color& c) const throw(except::normalizer_exception)
{
    if (location < 0.0 || location > 1.0)
    {
        throw except::normalizer_exception("Value is not in range [0;1].");
    }

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
throw(std::out_of_range)
{
    switch (type)
    {
        // red through white to blue color map {{{
        case vis::PredefinedColormaps::RED_BLUE:
            {
                vis::color a (255, 0, 0);
                vis::color b (0, 0, 255);
                vis::color middle (255, 255, 255);

                vis::locationizedColor c0 (0.0, a);
                vis::locationizedColor c1 (0.475, middle);
                vis::locationizedColor c2 (0.525, middle);
                vis::locationizedColor c3 (1.0, b);

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
        // black to white grayscale color map {{{
        case vis::PredefinedColormaps::GRAYSCALE:
            {
                vis::color a (0, 0, 0);
                vis::color b (255, 255, 255);

                vis::locationizedColor c0 (0.0, a);
                vis::locationizedColor c1 (1.0, b);

                std::vector<vis::locationizedColor> locCol;
                locCol.push_back(c0);
                locCol.push_back(c1);

                std::shared_ptr<vis::StandardColormap> c = std::make_shared<vis::StandardColormap> (locCol);
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

vis::PredefinedColormaps
vis::getPredefinedColormapType(std::string type)
throw(std::invalid_argument)
{
    // lower case
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type == "rdbu")
    {
        return vis::PredefinedColormaps::RED_BLUE;
    }
    else if (type == "heat")
    {
        return vis::PredefinedColormaps::BLACK_BODY_HEAT;
    }
    else if (type == "deepsea")
    {
        return vis::PredefinedColormaps::DEEP_SEA;
    }
    else if (type == "gray" || type == "grey")
    {
        return vis::PredefinedColormaps::GRAYSCALE;
    }
    else
    {
        char buf [256];
        sprintf(buf, "No such color map: %s", type.c_str());
        throw std::invalid_argument(buf);
    }
}
