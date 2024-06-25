#ifndef _USERNAME_NOT_FOUND_EXCEPTION_H_
#define _USERNAME_NOT_FOUND_EXCEPTION_H
#include <stdexcept>

class UsernameNotFoundException : public std::exception
{
    public:
    UsernameNotFoundException() noexcept = default;
    ~UsernameNotFoundException() = default;
    virtual const char* what() const noexcept
    {
        return "Username does not exist";
    }
};

#endif