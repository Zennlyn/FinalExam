#ifndef _BANK_H_
#define _BANK_H_
#include <string>
#include <vector>
#include "Account.h"

class Admin;

class Bank
{
    friend class Admin;
    private:
    std::vector <Account> accounts;
    public:
    Bank();
    void addAccount(const Account &account);
    Account* findAccount(std::string name) const;
    void loadData();
    void saveData();
    ~Bank();
};

#endif