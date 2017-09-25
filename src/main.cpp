#include "io/filereader.hpp"
#include "data/standard_single_byte_transition_counter.hpp"
#include <stdio.h>
#include <iostream>
#include <random>
#include "vis/standard_colormap.hpp"
#include "vis/image_builder.hpp"
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

    std::shared_ptr<data::TransitionCounter> transitionCounter;
    if (i.getUseAscii())
    {
        transitionCounter = std::make_shared<data::AsciiTransitionCounter>(f);
    }
    else
    {
        transitionCounter = std::make_shared<data::ByteTransitionCounter>(f);
    }

    std::shared_ptr<data::Normalizer<size_t>> norm;
    switch (i.getNormalizerType())
    {
        case data::NormalizerType::LOGARITHMIC_PLUS_ONE:
            norm = std::make_shared<data::LogarithmicPlusOneNormalizer>();
            break;
        case data::NormalizerType::LINEAR:
            norm = std::make_shared<data::LinearNormalizer<size_t>>();
            break;
        default:
            return ERROR_IN_COMMANDLINE;
    }

    transitionCounter->setNormalizer(norm);
    transitionCounter->run();

    std::shared_ptr<vis::StandardColormap const> c = vis::StandardColormap::getPredefinedColormap(i.getColormap());
    std::shared_ptr<std::vector<double>> data = transitionCounter->getHistogram().getNormalized().asVector();
    size_t const size = transitionCounter->getHistogram().getNumBins();
    std::shared_ptr<vis::Image> img = vis::ImageBuilder::buildImageFromData(size, size, data, c);

    std::shared_ptr<io::FileWriter> writer = i.getOutputFilewriter(img);
    writer->write(i.getOutputFile(), i.getUpscaleFactor());

    return SUCCESS;
}
