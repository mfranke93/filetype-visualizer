#include <string>
#include <stdexcept>

#pragma once

namespace except
{
    /**
     * Class for exceptions with map access.
     */
    class bad_mapping : public std::logic_error
    {
        public:
            explicit bad_mapping(std::string const& what_arg)
            : std::logic_error(what_arg)
            {}
    };
}
