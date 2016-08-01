#include "io/bmp_writer.hpp"
#include "io/filereader.hpp"
#include "data/standard_single_byte_transition_counter.hpp"
#include <stdio.h>
#include <iostream>
#include <random>
#include "vis/standard_colormap.hpp"

int main(int argc, char ** argv)
{
    std::shared_ptr<io::FileReader> f = std::make_shared<io::FileReader>("../binarytest.bin");
    data::StandardSingleByteTransitionCounter ssbtc (f);

    ssbtc.run();

    std::shared_ptr<vis::StandardColormap const> c = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::DEEP_SEA);
    std::shared_ptr<std::vector<double>> data = ssbtc.getHistogram().getNormalized().asVector();

    io::BmpWriter bmp (256, data);
    std::string fname = argc>1?*++argv:"/home/max/test.bmp";
    bmp.write(fname, c);

    return 0;
}
