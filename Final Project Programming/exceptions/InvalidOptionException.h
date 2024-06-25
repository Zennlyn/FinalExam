#ifndef _INVALID_OPTION_EXCEPTION_H_
#define _INVALID_OPTION_EXCEPTION_H_
#include <stdexcept>

class InvalidOptionException : public std::exception
{
    public:
    InvalidOptionException() noexcept = default;
    ~InvalidOptionException() = default;
    virtual const char* what() const noexcept
    {
        return "Invalid Option";
    }
};

#endif