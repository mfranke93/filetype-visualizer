#include "io/bmp_writer.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char ** argv)
{
    std::shared_ptr<std::vector<double>> data = std::make_shared<std::vector<double>>();

    for (size_t x = 0; x < 512; ++x)
    {
        for (size_t y = 0; y < 512; ++y)
        {
            double val = double(x+y)/1024.0;
            data->push_back(val);   
        }
    }

    io::BmpWriter b (512, data);
    b.write("/home/max/test.bmp");

    return 0;
}
