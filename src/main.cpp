#include "io/bmp_writer.hpp"
#include <stdio.h>
#include <iostream>
#include <random>
#include "vis/standard_colormap.hpp"

int main(int argc, char ** argv)
{
    std::random_device rd;
    std::mt19937 mersenne (rd());

    std::shared_ptr<vis::StandardColormap const> c = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::BLACK_BODY_HEAT);
    std::shared_ptr<std::vector<double>> data = std::make_shared<std::vector<double>>();

    for (size_t x = 0; x < 512; ++x)
    {
        for (size_t y = 0; y < 512; ++y)
        {
            std::uniform_real_distribution<double> dist (double(x)/512.0, double(y)/512.0);
            double val = dist(mersenne) * dist(mersenne);
            data->push_back(val);   
        }
    }

    io::BmpWriter bmp (512, data);

    std::string fname = argc>1?*++argv:"/home/max/test.bmp";

    bmp.write(fname, c);

    return 0;
}
