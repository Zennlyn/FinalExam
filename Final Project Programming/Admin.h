#ifndef _ADMIN_H_
#define _ADMIN_H_
#include <string>
#include "Account.h"
#include "Bank.h"
#include "exceptions/UsernameNotFoundException.h"
#include "exceptions/WrongPasswordException.h"

class Admin
{
    private:
    std::string password;
    public:
    Admin();
    bool getAccess(const std::string _password) const;
    void showActiveAccount(const Bank &bank) const;
    void deleteAccount(Bank &bank);
    ~Admin();
};

#endif