#include "io/bmp_writer.hpp"
#include "io/filereader.hpp"
#include "data/standard_single_byte_transition_counter.hpp"
#include <stdio.h>
#include <iostream>
#include <random>
#include "vis/standard_colormap.hpp"
#include "cmdline/options.hpp"

int main(int argc, char ** argv)
{
    cmdline::CommandlineInterface i;
    size_t ret = i.store(argc, argv);
    if (ret != SUCCESS)
    {
        return ret;
    }

    std::shared_ptr<io::FileReader> f;
    if (i.getUseCin())
    {
        f = std::make_shared<io::FileReader>();
    }
    else
    {
        f = std::make_shared<io::FileReader>(i.getInputFile());
    }
    data::StandardSingleByteTransitionCounter ssbtc (f);

    ssbtc.run();

    std::shared_ptr<vis::StandardColormap const> c = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::BLACK_BODY_HEAT);
    std::shared_ptr<std::vector<double>> data = ssbtc.getHistogram().getNormalized().asVector();

    io::BmpWriter bmp (256, data);
    bmp.write(i.getOutputFile(), c);

    return SUCCESS;
}
