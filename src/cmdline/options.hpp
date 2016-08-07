#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include "../except/upscale_exception.hpp"

namespace
{
    size_t const SUCCESS = 0;
    size_t const ERROR_IN_COMMANDLINE = 1;
    size_t const ERROR_UNHANDLED_EXCEPTION = 2;

    size_t const SHOWED_HELP_NOW_PLEASE_EXIT = 999;
}

namespace po = boost::program_options;

namespace cmdline
{
    class CommandlineInterface
    {
        public:
            CommandlineInterface();

            size_t store(int const& argc, char ** argv);

            bool const& getUseCin() const { return this->useCin; };
            size_t const& getUpscaleFactor() const { return this->upscaleFactor; };
            std::string const& getInputFile() const { return this->inputFile; };
            std::string const& getOutputFile() const { return this->outputFile; };

        private:
            bool useCin;
            size_t upscaleFactor;

            std::string inputFile;
            std::string outputFile;

            po::options_description desc;
    };
}
