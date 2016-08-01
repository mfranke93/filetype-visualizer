#include "io/bmp_writer.hpp"
#include <stdio.h>
#include <iostream>
#include "vis/standard_colormap.hpp"

int main(int argc, char ** argv)
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
    std::shared_ptr<std::vector<double>> data = std::make_shared<std::vector<double>>();

    for (size_t x = 0; x < 512; ++x)
    {
        for (size_t y = 0; y < 512; ++y)
        {
            double val = double(x+y)/1024.0;
            data->push_back(val);   
        }
    }

    io::BmpWriter bmp (512, data);
    bmp.write("/home/max/test.bmp", c);

    return 0;
}
