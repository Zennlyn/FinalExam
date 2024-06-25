#include "Admin.h"
#include <iostream>
#include <algorithm>

Admin::Admin() : password{"admin"} {}

void Admin::showActiveAccount(const Bank &bank) const
{
    std::cout << "Total active accounts: " << bank.accounts.size() << std::endl;
    for (Account acc : bank.accounts)
        std::cout << "Name: " << acc.name << std::endl;
}

bool Admin::getAccess(const std::string _password) const
{
    if (_password == password)
        return true;
    return false;
}

void Admin::deleteAccount(Bank &bank)
{
    std::string username;
    std::cout << "Enter 'c' if you want to cancel." << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    if (username == "c" || username == "C")
        return;
    bank.accounts.erase(std::remove_if(bank.accounts.begin(), bank.accounts.end(), 
                        [username](const Account &acc) {return acc.name == username;}), 
                        bank.accounts.end());
}

Admin::~Admin() {}