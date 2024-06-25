#ifndef _USERNAME_EXISTS_H_
#define _USERNAME_EXISTS_H_
#include <stdexcept>

class UsernameExists : public std::exception
{
    public:
    UsernameExists() noexcept = default;
    ~UsernameExists() = default;
    virtual const char* what() const noexcept
    {
        return "Username already exist";
    }
};

#endif