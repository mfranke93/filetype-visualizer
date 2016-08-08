#include <string>
#include <exception>

namespace except
{
    class illegal_size : public std::logic_error
    {
        public:
            explicit illegal_size(std::string const& what_arg)
            : std::logic_error(what_arg)
            {}
    };
}
