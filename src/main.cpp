#include "io/bmp_writer.hpp"
#include "io/filereader.hpp"
#include "data/standard_single_byte_transition_counter.hpp"
#include <stdio.h>
#include <iostream>
#include <random>
#include "vis/standard_colormap.hpp"

int main(int argc, char ** argv)
{
    if ((argc != 2) && (argc != 3))
    {
        printf("Usage: %s [in] out\n", *argv);
        return 1;
    }

    std::string fname;
    std::shared_ptr<io::FileReader> f;
    if (argc==2)
    {
        fname = argv[1];
        f = std::make_shared<io::FileReader> ();
    }
    else if (argc==3)
    {
        fname=argv[2];
        f = std::make_shared<io::FileReader> (argv[1]);
    }

    data::StandardSingleByteTransitionCounter ssbtc (f);

    ssbtc.run();

    std::shared_ptr<vis::StandardColormap const> c = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::BLACK_BODY_HEAT);
    std::shared_ptr<std::vector<double>> data = ssbtc.getHistogram().getNormalized().asVector();

    io::BmpWriter bmp (256, data);
    bmp.write(fname, c);

    return 0;
}
