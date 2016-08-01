#include "io/bmp_writer.hpp"
#include <stdio.h>
#include <iostream>
#include "vis/standard_colormap.hpp"

int main(int argc, char ** argv)
{
    std::shared_ptr<vis::StandardColormap const> c = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::BLACK_BODY_HEAT);
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
