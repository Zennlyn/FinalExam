#ifndef _ILLEGAL_TRANSFER_AMOUNT_EXCEPTION_H_
#define _ILLEGAL_TRANSFER_AMOUNT_EXCEPTION_H
#include <stdexcept>

class IllegalTransferAmountException : public std::exception
{
    public:
    IllegalTransferAmountException() noexcept = default;
    ~IllegalTransferAmountException() = default;
    virtual const char* what() const noexcept
    {
        return "Illegal Transfer Amount";
    }
};

#endif