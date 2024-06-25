#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h> //header for system("cls")
#include <ctype.h>
#include "Account.h"
#include "Bank.h"
#include "Admin.h"
#include "exceptions/InvalidOptionException.h"
#include "exceptions/WrongPasswordException.h"
#include "exceptions/UsernameExists.h"
#include "exceptions/IllegalTransferAmountException.h"
#include "exceptions/InsufficientBalancesException.h"

using namespace std;

void displayUserMenu(string username) 
{
    cout << std::setw(70) << std::setfill('=') << "" << endl;
    cout << std::setfill(' '); // Reset
    cout << std::setw((50 - username.length())/2) << "" << "Hello, Mr./Mrs. " << username << endl;
    cout << std::setw(70) << std::setfill('=') << "" << endl;
    cout << "These are the services that we can do for you" << endl;
    cout << "1. View Account Balance" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. View Transaction History" << endl;
    cout << "5. Transfer Money" << endl;
    cout << "6. Change PIN" << endl;
    cout << "7. Logout" << endl;
    cout << std::setw(70) << std::setfill('=') << "" << endl;
    cout << "Enter your choice: ";
}

void adminMenu()
{
    cout << "These are the things you can do as an administrator" << endl;
    cout << "1. Show all active members" << endl;
    cout << "2. Delete an account" << endl;
    cout << "3. Logout" << endl;
}

void transferHelperFunction(Bank &bank, Account* yourAccount)
{
    string destinatedName;
    Account* destinatedAcc;
    double amount;
    while (true)
    {
        cout << "Enter the destinated username: ";
        cin >> destinatedName;
        destinatedAcc = bank.findAccount(destinatedName);
        try
        {
            if (!destinatedAcc)
                throw UsernameNotFoundException();
            break;
        }
        catch (const UsernameNotFoundException &ex)
        {
            cerr << ex.what() << endl;
            continue;
        }
    }
    while (true)
    {
        cout << "How much do you want to transfer? ";
        cin >> amount;
        try
        {
            if (amount < 0)
                throw IllegalTransferAmountException();
            if (amount > yourAccount->getBalances())
                throw InsufficientFundsException();
            break; 
        }
        catch (const InsufficientFundsException &ex)
        {
            cerr << ex.what() << endl;
            continue;
        }
        catch (const IllegalTransferAmountException &ex)
        {
            cerr << ex.what() << endl;
            continue;
        }
    }
    yourAccount->transfer(destinatedAcc->getUsername(), amount);
    destinatedAcc->getTransferred(yourAccount->getUsername(), amount);
}

int main()
{
    Bank bank;
    // Collecting the existing data
    ifstream usersList {"data/accountList.txt"};
    string accName, accPin;
    while (usersList >> accName >> accPin)
    {
        Account existAcc {accName, accPin};
        bank.addAccount(existAcc);
    }
    usersList.close();
    bank.loadData();
    // Start the program
    string username, pin;
    int choice;
    char opt;
    bool flag {true};
    do
    {
        system("cls"); // Clear the console
        cout << "Zenbank Management System" << endl;
        while (true)
        {
            cout << "Enter q or Q if you want to quit" << endl;
            cout << "Enter a or A if you are an admin" << endl;
            cout << "Do you already have an account? (Y/N/A/Q): ";
            try 
            {
                cin >> opt;
                if (opt != 'y' && opt != 'Y' && opt != 'n' && opt != 'N' &&
                    opt != 'q' && opt != 'Q' && opt != 'a' && opt != 'A')
                    throw InvalidOptionException();
                break;
            }
            catch (const InvalidOptionException &ex)
            {
                cerr << ex.what() << endl;
            }
        }

        // The user already has an account
        if (opt == 'y' || opt == 'Y')
        {
            Account* yourAccount;
            int attempt {3};
            while (attempt)
            {
                try
                {
                    cout << "Username: ";
                    cin >> username;
                    if (!bank.findAccount(username))
                        throw UsernameNotFoundException();
                    break;
                }
                catch (const UsernameNotFoundException &ex)
                {
                    cerr << ex.what() << endl;
                    attempt--;
                }
            }
            if (!attempt)
            {
                cout << "Sorry, your attempt chance has expired. Press any key to back to menu." << endl;
                cin >> opt;
                continue;
            }
            else
            {
                attempt = 3;
                yourAccount = bank.findAccount(username);
                while (attempt)
                {
                    cout << "Enter your pin: ";
                    try
                    {
                        cin >> pin;
                        if (!yourAccount->getAccess(pin))
                            throw WrongPasswordException();
                        break;
                    }
                    catch (const WrongPasswordException &ex)
                    {
                        cerr << ex.what() << endl;
                        attempt--;
                    }
                }
                if (!attempt)
                {
                    cout << "Sorry, your attempt chance has expired. Press any key to back to menu." << endl;
                    cin >> opt;
                    continue;
                }
            }
            // Someone has already successfully logged in to his/her account
            bool quit {false};
            while (!quit)
            {
                displayUserMenu(yourAccount->getUsername());
                double amount;
                cin >> choice;
                try
                {
                    switch (choice)
                    {
                        case 1: // Check Balances
                            cout<< "Your balances is: $" << yourAccount->getBalances() << endl;
                            break;
                        case 2: // Deposit
                            yourAccount->deposit();
                            break;
                        case 3: // Withdraw
                            yourAccount->withdraw();
                            break;
                        case 4: // View Transaction History
                            yourAccount->displayTransaction();
                            break;
                        case 5: // Transfer Money
                            transferHelperFunction(bank, yourAccount);
                            break;
                        case 6: // Change PIN
                            yourAccount->changePassword();
                            break;
                        case 7: // Logout
                            yourAccount->saveData();
                            quit = true;
                            break;
                        default:
                            throw InvalidOptionException();
                            break;;
                    }
                }
                catch (const InvalidOptionException &ex)
                {
                    cerr << ex.what() << endl;
                    continue;
                }
            }
        }

        // Create a new account
        else if (opt == 'n' || opt == 'N')
        {
            while (true)
            {
                cout << "Please enter your username: ";
                cin >> username;
                try
                {
                    if (bank.findAccount(username))
                        throw UsernameExists();
                }
                catch (const UsernameExists &ex)
                {
                    cerr << ex.what() << endl;
                    continue;
                }
                break;
            }
            while (true)
            {
                string pin2;
                cout << "Please enter your PIN (6-8 digits): ";
                cin >> pin;
                cout << "Please re-enter your PIN: ";
                cin >> pin2;
                if (pin != pin2)
                    cout << "The PINs do not match. Please try again." << endl;
                else
                {
                    Account newAccount {username, pin};
                    bank.addAccount(newAccount);
                    cout << "Your account has been created." << endl;
                    ofstream createBalanceFile {"data/userdata/" + username + "Balance.txt"};
                    ofstream createHistoryFile {"data/userdata/" + username + "Transaction.txt"};
                    createBalanceFile << newAccount.getBalances();
                    createHistoryFile << std::left << setw(25) << "Date" << "|" << setw(15) << "Activity" << "|" << setw(15) << "Name" << "|" << setw(10) << "Amount";
                    createBalanceFile.close();
                    createHistoryFile.close();
                    break;
                }   
            }
            continue;
        }
        
        // Quit
        else if (opt == 'q' || opt == 'Q')
        {
            bank.saveData();
            break;
        }

        // Admin
        else if (opt == 'a' || opt == 'A')
        {
            Admin admin;
            int attempt {3};
            string password;
            char tempOpt;
            while (attempt)
            {
                cout << "Enter your password: ";
                try
                {
                    cin >> password;
                    if (!admin.getAccess(password))
                        throw WrongPasswordException();
                    break;
                }
                catch (const WrongPasswordException &ex)
                {
                    cerr << ex.what() << endl;
                    attempt--;
                }
            }
            if (!attempt)
            {
                cout << "Sorry, your attempt chance has expired. Press any key to back to menu." << endl;
                cin >> tempOpt;
                continue;
            }
            else
            {
                int choice;
                bool quit {false};
                while(!quit)
                {
                    adminMenu();
                    cout << "Enter your choice: ";
                    cin >> choice;
                    try
                    {
                        switch (choice)
                        {
                            case 1:
                                admin.showActiveAccount(bank);
                                break;
                            case 2:
                                admin.deleteAccount(bank);
                                break;
                            case 3:
                                quit = true;
                                break;
                            default:
                                throw InvalidOptionException();
                                break;
                        }
                    }
                    catch (const InvalidOptionException &ex)
                    {
                        cerr << ex.what() << endl;
                        continue;
                    }
                }
            }
        }

        // Exit
        while (true)
        {
            cout << "Do you still want to do transaction? (Y/N): ";
            try
            {
                cin >> opt;
                if (opt != 'y' && opt != 'Y' && opt != 'n' && opt != 'N')
                    throw InvalidOptionException(); 
                break;
            }
            catch (const InvalidOptionException &ex)
            {
                cerr << ex.what() << endl;
            }
        }
        if (opt == 'n' || opt == 'N')
        {
            bank.saveData();
            flag = false;
        }
    } while (flag);
    return 0;
}