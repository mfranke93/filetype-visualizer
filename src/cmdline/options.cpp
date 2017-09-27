#include "options.hpp"

cmdline::CommandlineInterface::CommandlineInterface()
:   desc("Options")
{
    this->desc.add_options()
        ("help,h", "Print help messages")

        ("in,i",            po::value<std::string>(&inputFile),                             "Input file")
        ("out,o",           po::value<std::string>(&outputFile)->default_value("out.ppm"),  "Output file")
        ("upscale,s",       po::value<size_t>(&upscaleFactor)->default_value(1),            "Size scaling of output image. May not be 0")
        ("cmap,c",          po::value<std::string>(),                                       "Colormap to use. Defaults to heat map."
                                                                                            " Options are: RdBu, heat, deepsea, gray/grey")
        ("normalizer,n",    po::value<std::string>()->default_value("log"),                 "Normalizer to use. Defaults to logarithmic."
                                                                                            " Options are: log, lin")
        ("ascii,a",         po::bool_switch(&useAscii),                                     "Use ASCII (7 bit charset) only")
        ("force-size",      po::bool_switch(&forceSizeOverride),                            "Force a larger size for image than normally allowed")
        ("file-type,T",     po::value<std::string>()->default_value("ppm"),                 "Filetype of output. Defaults to ppm."
                                                                                            " Options are ppm, png.")
        ("margin,m",        po::value<std::string>()->default_value("0"),                   "Margin of output image, in pixels."
                                                                                            " Can be given as \"value\";\"valueX,valueY\" or"
                                                                                            " \"valueLeft,valueRight,valueTop,valueBottom\"."
                                                                                            " Default value is 0.")
        ("margin-color",    po::value<std::string>()->default_value("000000"),              "Color of margin. Given as 3 byte hexadecimal string."
                                                                                            " Default value is \"000000\".")
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
            if (!this->forceSizeOverride)
            {
                throw except::upscale_exception("May not scale by more than 7");
            }
        }

        if (vm.count("cmap"))
        {
            std::string s = vm["cmap"].as<std::string>();
            std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            try
            {
                this->cmap = config::colormaps.at(s);
            }
            catch (std::out_of_range& e)
            {
                char buf [256];
                sprintf(buf, "No such color map: %s", s.c_str());
                throw std::invalid_argument(buf);
            }
        }
        else
        {
            this->cmap = vis::PredefinedColormaps::BLACK_BODY_HEAT;
        }

        if (vm.count("normalizer"))
        {
            std::string name = vm["normalizer"].as<std::string>();
            // lower case
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            try
            {
                this->normalizerType = config::normalizers.at(name);
            }
            catch (std::out_of_range& e)
            {
                char buf [256];
                sprintf(buf, "No such normalizer: %s", name.c_str());
                throw std::invalid_argument(buf);
            }
        }
        else
        {
            this->normalizerType = data::NormalizerType::LOGARITHMIC_PLUS_ONE;
        }

        if (vm.count("file-type"))
        {
            std::string name = vm["file-type"].as<std::string>();
            // lower case
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            try
            {
                this->outputFilewriterGenerator = config::filewriters.at(name);
            }
            catch (std::out_of_range& e)
            {
                char buf [256];
                sprintf(buf, "No such output filetype: %s", name.c_str());
                throw std::invalid_argument(buf);
            }
        }
        else
        {
            this->outputFilewriterGenerator = config::filewriters.at("ppm");
        }

        if (vm.count("margin"))
        {
            std::string marginStr = vm["margin"].as<std::string>();
            size_t l, r, t, b; l=r=t=b=0;
            int retVal = std::sscanf(marginStr.c_str(), "%lu,%lu,%lu,%lu", &l, &r, &t, &b);

            if (retVal != 4)
            {
                int retVal = std::sscanf(marginStr.c_str(), "%lu,%lu", &l, &t);
                if (retVal != 2)
                {
                    int retVal = std::sscanf(marginStr.c_str(), "%lu", &l);
                    if (retVal != 1)
                    {
                        char buf [256];
                        std::sprintf(buf, "Could not parse margins from string '%s'.\n", marginStr.c_str());
                        throw std::invalid_argument(buf);
                    }
                    else
                    {
                        r = t = b = l;
                    }
                }
                else 
                {
                    r = l; b = t;
                }
            }

            marginLeft = l; marginRight  = r;
            marginTop  = t; marginBottom = b;
        }
        else
        {
            marginLeft = marginRight = marginTop = marginBottom = 0;
        }

        if (vm.count("margin-color"))
        {
            std::string colStr = vm["margin-color"].as<std::string>();
            uint32_t hex = 0;
            if (std::sscanf(colStr.c_str(), "%x", &hex) == EOF)
            {
                char buf[256];
                std::sprintf(buf, "Could not parse hex color '%s'.\n", colStr.c_str());
                throw std::invalid_argument(buf);
            }

            vis::channel r = (hex >> 16) & 0xFF;
            vis::channel g = (hex >> 8)  & 0xFF;
            vis::channel b =  hex        & 0xFF;

            marginColor = vis::color(r, g, b);
        }
        else
        {
            marginColor = vis::color(0,0,0);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;

        return ERROR_UNHANDLED_EXCEPTION;
    }

    return SUCCESS;
}
