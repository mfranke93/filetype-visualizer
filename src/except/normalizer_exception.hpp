#include <string>
#include <exception>

#pragma once

namespace except
{
    class normalizer_exception : public std::logic_error
    {
        public:
            explicit normalizer_exception(std::string const& what_arg)
            : std::logic_error(what_arg)
            {}
    };
}
