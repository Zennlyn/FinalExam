#include "Account.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::ostream &operator<<(std::ostream &os, const Transaction &transaction)
{
    os << transaction.information;
    return os;
}

bool Account::operator==(const Account &other) const
{
    return name == other.name;
}

std::string tmToString(const std::tm& timeStruct) 
{
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeStruct);
    return std::string(buffer);
}

Account::Account() {}

Account::Account(std::string name, std::string pin)
    : name{name}, pin{pin}, balances{0} {}

void Account::addHistory(std::string name, std::string activity, double amount, std::string date)
{
    std::stringstream ss;
    ss << std::left << std::setw(25) << date << "|" << std::setw(15) << activity << "|" << std::setw(15) << name << "|" << ((activity == "deposit" || activity == "transferredFrom") ? "+" : "-") << amount;
    Transaction newHistory {ss.str()};
    transactions_record.push_back(newHistory);
}

void Account::addHistory(std::string information)
{
    Transaction loadHistory {information};
    transactions_record.push_back(loadHistory);
}

std::string Account::getCurrentTime() 
{
    // Declaring argument for time()
    time_t tt;
    // Getting the current time
    time(&tt);
    // Converting it to local time
    std::tm* ti = localtime(&tt);
    // Returning the local time structure
    return tmToString(*ti);
}

bool Account::getAccess(const std::string _pin) const
{
    if (_pin == pin)
        return true;
    return false;
}

std::string Account::getUsername() const
{
    return name;
}

double Account::getBalances() const
{
    return balances;
}

void Account::deposit()
{
    double amount;
    while (true)
    {
        std::cout << "How much do you want to deposit? ";
        try
        { 
            std::cin >> amount;
            if (amount < 0)
                throw IllegalDepositAmountException();
        }
        catch (const IllegalDepositAmountException &ex)
        {
            std::cerr << ex.what() << std::endl;
            continue;
        }
        break;
    }
    addHistory(name, "deposit", amount, getCurrentTime());
    balances += amount;
    std::cout << "Received!" << std::endl;
}

void Account::withdraw()
{
    double amount;
    while (true)
    {
        std::cout << "How much do you want to withdraw? ";
        try
        { 
            std::cin >> amount;
            if (amount > balances)
                throw InsufficientFundsException();
        }
        catch (const InsufficientFundsException &ex)
        {
            std::cerr << ex.what() << std::endl;
            continue;
        }
        break;
    }
    addHistory(name, "withdraw", amount, getCurrentTime());
    balances -= amount;
    std::cout << "Please take your money: $" << amount << std::endl;
}

void Account::transfer(std::string toAcc, double amount)
{
    balances -= amount;
    addHistory(toAcc, "transferredTo", amount, getCurrentTime());
}

void Account::getTransferred(std::string fromAcc, double amount)
{
    balances += amount;
    addHistory(fromAcc, "transferredFrom", amount, getCurrentTime());
    std::cout << "Transferred" << std::endl;
}

void Account::changePassword()
{
    std::string _pin, newPin, newPin2;
    int attempt {3};
    while (attempt)
    {
        std::cout << "Enter your old password: ";
        try
        {
            std::cin >> _pin;
            if (_pin != pin)
            {
                attempt--;
                throw WrongPasswordException();
            }
        }
        catch (const WrongPasswordException &ex)
        {
            std::cerr << ex.what() << std::endl;
            continue;
        }
        break;
    }
    if (!attempt)
    {
        std::cout << "You have to remember your old PIN in order to change to a new one." << std::endl;
    }
    else
    {
        while (true)
        {
            std::cout << "Enter your new PIN: ";
            std::cin >>newPin;
            std::cout << "Re-enter your new PIN: ";
            std::cin >>newPin2;
            if (newPin != newPin2)
                std::cout << "The PINs do not match. Please try again." << std::endl;
            else
            {
                pin = newPin;
                std::cout << "Your PIN has already been changed." << std::endl;
                break;
            }
        }
    }
}

void Account::displayTransaction() const
{
    if(!transactions_record.empty())
        for (auto transaction : transactions_record)
            std::cout << transaction << std::endl;
    else
        std::cout << "There is no transaction done in your account." << std::endl;
}

void Account::saveData()
{
    std::ofstream dataBalance {"data/userdata/" + name + "Balance.txt"};
    // Clear the existing data
    std::ofstream clearHistory {"data/userdata/" + name + "Transaction.txt", std::ios::trunc};
    clearHistory.close();
    // Update to a new one
    std::ofstream dataHistory {"data/userdata/" + name + "Transaction.txt", std::ios::app};
    dataBalance << balances;
    for (auto transaction : transactions_record)
        dataHistory << transaction << std::endl;
    dataBalance.close();
    dataHistory.close();
}

Account::~Account() {}