#ifndef _WRONG_PASSWORD_EXCEPTION_H_
#define _WRONG_PASSWORD_EXCEPTION_H_
#include <stdexcept>

class WrongPasswordException : public std::exception
{
    public:
    WrongPasswordException() noexcept = default;
    ~WrongPasswordException() = default;
    virtual const char* what() const noexcept
    {
        return "Wrong Password";
    }
};

#endif