#include "options.hpp"

cmdline::CommandlineInterface::CommandlineInterface()
:   desc("Options")
{
    this->desc.add_options()
        ("help,h", "Print help messages")
        ("in,i", po::value<std::string>(&inputFile), "Input file")
        ("out,o", po::value<std::string>(&outputFile)->default_value("out.bmp"), "Output file")
        ("upscale,s", po::value<size_t>(&upscaleFactor)->default_value(1), "Size scaling of output image. May not be 0")
        ("cmap,c", po::value<std::string>(), "Colormap to use. Defaults to heat map. Options are: RdBu, heat, deepsea")
        ("normalizer,n", po::value<std::string>()->default_value("log"), "Normalizer to use. Defaults to logarithmic. Options are: log, lin")
        ("ascii,a", po::bool_switch(&useAscii), "Use ASCII (7 bit charset) only")
        ;
}

size_t
cmdline::CommandlineInterface::store(int const& argc, char ** argv)
{
    try 
    {
        po::variables_map vm;

        try
        {
            po::store(po::command_line_parser(argc, argv).options(this->desc).run(), vm);

            if (vm.count("help"))
            {
                std::cout << "Generic help text" << std::endl;
                std::cout << std::endl << "Not very helpful" << std::endl;
                std::cout << std::endl << this->desc << std::endl;

                return SHOWED_HELP_NOW_PLEASE_EXIT;
            }

            po::notify(vm);
        }
        catch (po::required_option& e)
        {
            std::cerr << e.what() << std::endl;

            return ERROR_IN_COMMANDLINE;
        }
        catch (po::error& e)
        {
            std::cerr << e.what() << std::endl;

            return ERROR_IN_COMMANDLINE;
        }

        /* get other values */
        if (vm.count("in"))
        {
            this->useCin = false;
        }
        else
        {
            this->useCin = true;
        }

        if (vm["upscale"].as<size_t>() == 0)
        {
            throw except::upscale_exception("Cannot scale by 0");
        }
        else if (vm["upscale"].as<size_t>() > 7)
        {
            throw except::upscale_exception("May not scale by more than 7");
        }

        if (vm.count("cmap"))
        {
            this->cmap = vis::getPredefinedColormapType(vm["cmap"].as<std::string>());
        }
        else
        {
            this->cmap = vis::PredefinedColormaps::BLACK_BODY_HEAT;
        }

        if (vm.count("normalizer"))
        {
            this->normalizerType = cmdline::CommandlineInterface::getNormalizerTypeFromString(vm["normalizer"].as<std::string>());
        }
        else
        {
            this->normalizerType = data::NormalizerType::LOGARITHMIC_PLUS_ONE;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;

        return ERROR_UNHANDLED_EXCEPTION;
    }

    return SUCCESS;
}

data::NormalizerType 
cmdline::CommandlineInterface::getNormalizerTypeFromString(std::string name)
throw(std::invalid_argument)
{
    // lower case
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    if (name == "lin")
    {
        return data::NormalizerType::LINEAR;
    }
    else if (name == "log")
    {
        return data::NormalizerType::LOGARITHMIC_PLUS_ONE;
    }
    else
    {
        char buf [256];
        sprintf(buf, "No such color map: %s", name.c_str());
        throw std::invalid_argument(buf);
    }
};
