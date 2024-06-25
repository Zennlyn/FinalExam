#include "Bank.h"
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <sstream>

Bank::Bank() {}

void Bank::addAccount(const Account &account)
{
    accounts.push_back(account);
}

Account* Bank::findAccount(std::string name) const
{
    for (const Account &acc : accounts)
    {
        int counter {0};
        for (size_t i = 0; i < name.length(); i++)
            if (tolower(acc.name[i]) == tolower(name[i]))
                counter++;
        if (counter == name.length())
            return const_cast<Account*>(&acc);
    }
    return nullptr;
}

void Bank::loadData()
{
    for (Account &acc : accounts)
    {
        std::ifstream dataBalance {"data/userdata/" + acc.name + "Balance.txt"};
        std::ifstream dataHistory {"data/userdata/" + acc.name + "Transaction.txt"};
        dataBalance >> acc.balances;
        std::string information, date, name, activity;
        double amount;
        while (getline(dataHistory, information))
            acc.addHistory(information);
    }
}

void Bank::saveData()
{
    std::ofstream newUsersList {"data/accountList.txt"};
    for (const Account &acc : accounts)
        newUsersList << acc.name << " " << acc.pin << std::endl;
    newUsersList.close();
}

Bank::~Bank() {}