#include <string>
#include <exception>

#pragma once

namespace except
{
    class upscale_exception : public std::logic_error
    {
        public:
            explicit upscale_exception(std::string const& what_arg)
            : std::logic_error(what_arg)
            {}
    };
}
