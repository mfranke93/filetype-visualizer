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
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;

        return ERROR_UNHANDLED_EXCEPTION;
    }

    return SUCCESS;
}