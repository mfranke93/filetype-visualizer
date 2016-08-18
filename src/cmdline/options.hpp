#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include "../except/upscale_exception.hpp"
#include "../vis/standard_colormap.hpp"
#include "../data/linear_normalizer.hpp"
#include "../data/logarithmic_plus_one_normalizer.hpp"
#include "../data/normalizer.hpp"
#include "config.hpp"

#pragma once

namespace
{
    size_t const SUCCESS = 0;
    size_t const ERROR_IN_COMMANDLINE = 1;
    size_t const ERROR_UNHANDLED_EXCEPTION = 2;

    size_t const SHOWED_HELP_NOW_PLEASE_EXIT = 255;
}

namespace po = boost::program_options;

namespace cmdline
{
    /**
     * Class for boost::program_options command line interface.
     */
    class CommandlineInterface
    {
        public:
            /**
             * Constructor.
             */
            CommandlineInterface();

            /**
             * Store command line arguments.
             *
             * \param argc Argument count
             * \param argv Argument vector
             * \return Success
             */
            size_t store(int const& argc, char ** argv);

            /**
             * Check if std::cin should be used as input.
             *
             * \return Use std::cin
             */
            bool const& getUseCin() const { return this->useCin; };

            /**
             * Get the upscale factor.
             *
             * \return upscale factor
             */
            size_t const& getUpscaleFactor() const { return this->upscaleFactor; };

            /**
             * Get the input file.
             *
             * \return input file
             */
            std::string const& getInputFile() const { return this->inputFile; };

            /**
             * Get the output file.
             *
             * \return output file
             */
            std::string const& getOutputFile() const { return this->outputFile; };

            /**
             * Get whether to use ASCII only.
             *
             * \return ascii only
             */
            bool const& getUseAscii() const { return this->useAscii; };

            /**
             * Get the colormap.
             *
             * \return cmap
             */
            vis::PredefinedColormaps const& getColormap() const { return this->cmap; };

            /**
             * Get the normalizer type.
             */
            data::NormalizerType const& getNormalizerType() const { return this->normalizerType; };

        private:
            /**
             * Use std::cin or file for input?
             */
            bool useCin;

            /**
             * Force size override.
             */
            bool forceSizeOverride;

            /**
             * Factor for scaling output image.
             */
            size_t upscaleFactor;

            /**
             * Use 7 or 8 bit file input transition counter.
             */
            bool useAscii;

            /**
             * Input file name.
             */
            std::string inputFile;

            /**
             * Output file name.
             */
            std::string outputFile;

            /**
             * Colormap to use.
             */
            vis::PredefinedColormaps cmap;

            /**
             * Command line options description.
             */
            po::options_description desc;

            /**
             * Type of normalizer to use.
             */
            data::NormalizerType normalizerType;
    };
}
