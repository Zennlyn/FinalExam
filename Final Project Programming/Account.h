#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include <string>
#include <vector>
#include <ctime>
#include "exceptions/IllegalDepositAmountException.h"
#include "exceptions/InsufficientBalancesException.h"
#include "exceptions/WrongPasswordException.h"

class Bank;
class Admin;

struct Transaction
{
    std::string information;
};

class Account
{
    friend class Bank; // Bank can access its data
    friend class Admin; // Admin can access its data
    friend void transferHelperFunction(Bank &bank, Account* yourAccount);
    private:
    std::string name, pin;
    double balances;
    std::vector <Transaction> transactions_record;
    std::string getCurrentTime();
    void addHistory(std::string name, std::string activity, double amount, std::string date);
    void addHistory(std::string information);
    public:
    Account();
    Account(std::string name, std::string pin);
    bool getAccess(const std::string _pin) const;
    std::string getUsername() const;
    double getBalances() const;
    void deposit();
    void withdraw();
    void transfer(std::string toAcc, double amount);
    void getTransferred(std::string fromAcc, double amount);
    void changePassword();
    void displayTransaction() const;
    void saveData();
    bool operator==(const Account &other) const;
    ~Account();
};

#endif