#ifndef _ILLEGAL_DEPOSIT_AMOUNT_EXCEPTION_H_
#define _ILLEGAL_DEPOSIT_AMOUNT_EXCEPTION_H
#include <stdexcept>

class IllegalDepositAmountException : public std::exception
{
    public:
    IllegalDepositAmountException() noexcept = default;
    ~IllegalDepositAmountException() = default;
    virtual const char* what() const noexcept
    {
        return "Illegal Deposit Amount";
    }
};

#endif