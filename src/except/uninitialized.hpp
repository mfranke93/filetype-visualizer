#include <string>
#include <stdexcept>

#pragma once

namespace except
{
    class uninitialized : public std::logic_error
    {
        public:
            explicit uninitialized(std::string const& what_arg)
            : std::logic_error(what_arg)
            {}
    };
}
