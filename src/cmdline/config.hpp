#include <map>
#include <string>
#include "../data/normalizer.hpp"
#include "../vis/standard_colormap.hpp"

#pragma once

namespace config
{
    /**
     * Map from strings to normalizer types, for command line parsing.
     */
    std::map<std::string, data::NormalizerType> const normalizers = {
        { "lin"         , data::NormalizerType::LINEAR                  },
        { "linear"      , data::NormalizerType::LINEAR                  },
        { "log"         , data::NormalizerType::LOGARITHMIC_PLUS_ONE    },
        { "logarithmic" , data::NormalizerType::LOGARITHMIC_PLUS_ONE    }
    };

    /**
     * Map from strings to colormaps, for command line parsing.
     */
    std::map<std::string, vis::PredefinedColormaps> const colormaps = {
        { "redblue"     , vis::PredefinedColormaps::RED_BLUE            },
        { "rdbu"        , vis::PredefinedColormaps::RED_BLUE            },
                                                                        
        { "blackwhite"  , vis::PredefinedColormaps::GRAYSCALE           },
        { "grey"        , vis::PredefinedColormaps::GRAYSCALE           },
        { "gray"        , vis::PredefinedColormaps::GRAYSCALE           },
        { "greyscale"   , vis::PredefinedColormaps::GRAYSCALE           },
        { "grayscale"   , vis::PredefinedColormaps::GRAYSCALE           },
                                                                        
        { "heat"        , vis::PredefinedColormaps::BLACK_BODY_HEAT     },
        { "blackbody"   , vis::PredefinedColormaps::BLACK_BODY_HEAT     },
        { "thermal"     , vis::PredefinedColormaps::BLACK_BODY_HEAT     },
                                                                        
        { "deepsea"     , vis::PredefinedColormaps::DEEP_SEA            },
        { "ocean"       , vis::PredefinedColormaps::DEEP_SEA            }
    };
}
