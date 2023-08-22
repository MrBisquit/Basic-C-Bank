// --- Begin imports --- //
#include <iostream>
#include <stdlib.h>
#include "Types.h"
#include <iomanip>
#include <locale>
#include "Storing.h"
// --- End imports --- //

using namespace std; // I know I shouldn't be relying on the std namespace but it's useful.

// --- Begin variables --- //
bool isRunning = true;
int numberOfUsers = 0;
Types::User users[500]; // This can take up a lot of space but as of now I have no easy way of starting it over.

int bank_ir;
int loan_ir;
int loan_dp;

int bank_profit;
int total_bank = 100000000;
// --- End variables --- //

// --- Begin forward declarations --- //
int showHomeCmds();
int createAccount();
int loginUser();
int loginUser();
int showUserCmds();
int showBankInfo();
int showUserInfo(Types::User user);
int manageUserLoan(Types::User user);
int showUserLoanCmds(Types::User user);
int newLoan(Types::User user);
int cleanUp(bool quit);
// --- End forward declarations --- //

int main()
{
    system("cls");
    cout << "Loading users..." << endl;
    for (size_t i = 0; i < 500; i++)
    {
        try {
            users[i] = LoadUser(i);
        }
        catch(exception ex) {
            //cout << "Failed to load user " << i << endl;
        }
    }
    cout << "Loaded users!" << endl;
    cout << "Sorting..." << endl;

    Types::User Users_Sorted[500];
    for (size_t i = 0; i < 500; i++)
    {
        Users_Sorted[users[i].id] = users[i];
    }
    for (size_t i = 0; i < 500; i++)
    {
        users[i] = Users_Sorted[i];
    }
    cout << "Sorted!" << endl;
    cout << "Saving and reloading..." << endl;
    cout << "Loading users..." << endl;
    for (size_t i = 0; i < 500; i++)
    {
        try {
            users[i] = LoadUser(i);
        }
        catch (exception ex) {
            //cout << "Failed to load user " << i << endl;
        }
    }
    cout << "Loaded users!" << endl;
    SaveUsers(users);
    system("cls");
    cout << "Please fill in the variables." << endl;
    cout << "Bank account interest rate (%): ";
    cin >> bank_ir;
    cout << "Loaning interest rate (%): ";
    cin >> loan_ir;
    cout << "Loaning down payment (%): ";
    cin >> loan_dp;
    numberOfUsers = 0;
    cout << "Ready...";
    do {
        system("cls");
        /*cout << "Welcome to the banking system." << endl;
        cout << "Please select an option from this list." << endl;*/
        showBankInfo();
        int selected = showHomeCmds();
        system("cls");
        if (selected == 3) {
            isRunning = false;
        }
        else if(selected == 1) {
            loginUser();
        }
        else if (selected == 2) {
            createAccount();
        }
        else if (selected == 4) {
            cleanUp(false);
            main();
        }
    } while (isRunning);

    system("cls");
    cout << "Beginning clean up..." << endl;
    cleanUp(true);

    return 0;
}

int showHomeCmds() {
    bool isValid = false;
    int selected = 0;

    do {
        cout << "1. Login as a user" << endl;
        cout << "2. Create a user" << endl;
        cout << "3. Quit" << endl;
        cout << "4. Reset variables" << endl;

        cin >> selected;

        if (selected == 1 ||
            selected == 2 ||
            selected == 3 ||
            selected == 4) {
            isValid = true;
        }
        else {
            cout << "Invalid option." << endl;
        }
    } while (!isValid);

    return selected;
}

int createAccount() {
    system("cls");
    showBankInfo();
    Types::User user;
    user.balance = 5000;
    user.id = numberOfUsers;
    numberOfUsers += 1;
    cout << "Your user ID is " << user.id << endl;
    cout << "Enter your pin: ";
    cin >> user.pin;
    cout << endl << "Your starting balance is: " << user.balance << endl;

    users[user.id] = user;

    system("cls");
    showBankInfo();
    cout << "User " << user.id << " successfully created." << endl;
    SaveUsers(users);

    return 0;
}

int loginUser() {
    system("cls");
    showBankInfo();
    Types::User user;
    int id = 0;
    cout << "Enter your ID: ";
    cin >> id;
    user = users[id];
    cout << "Enter your pin: ";
    int pin = 0;
    cin >> pin;
    if (user.pin != pin) {
        cout << endl << "Incorrect pin.";
        isRunning = false;
        return 0;
    }
    system("cls");
    showUserInfo(user);

    bool isLoggedIn = true;
    do {
        //system("cls");
        int selected = showUserCmds();
        if (selected == 5) {
            isLoggedIn = false;
        }
        else if (selected == 4) {
            user.id = -1;
            users[id] = user;
            isLoggedIn = false;
        }
        else if (selected == 2) {

        }
        else if (selected == 1) {
            system("cls");
            showUserInfo(user);
            cout << "Your current balance is " << user.balance << endl;
        }
        else if (selected == 3) {
            manageUserLoan(user);
        }
    } while (isLoggedIn);

    return 0;
}

int manageUserLoan(Types::User user) {
    system("cls");
    showUserInfo(user);
    bool active = true;

    do {
        system("cls");
        showUserInfo(user);
        int selected = showUserLoanCmds(user);
        if (selected == 4) {
            system("cls");
            showUserInfo(user);
            active = false;
        }
        else if (selected == 1) {
            if (user.loan.active) {
                cout << "The user already has a loan. Would you like to override it? (y/any other key): ";
                char option;
                cin >> option;
                if (option == 'y') {
                    newLoan(user);
                }
            }
            else {
                newLoan(user);
            }
        }
    } while (active);

    return 0;
}

int newLoan(Types::User user) {
    system("cls");
    showUserInfo(user);
    cout << "Amount of loan: ";
    int amount;
    cin >> amount;
    cout << "How many months: ";
    int months;
    cin >> months;
    system("cls");
    showUserInfo(user);
    cout << "Checking info..." << endl;
    int dp = amount / loan_dp;
    if (user.balance >= user.balance - dp);
    else {
        cout << "You do not have enough to fill the down payment of " << dp << "!" << endl;
        cout << "Press any key to continue...";
        cin >> amount;
        return 0;
    }
    cout << "Enter your pin to complete transaction of " << dp << endl << "Pin: ";
    int pin;
    cin >> pin;
    if (user.pin != pin) {
        system("cls");
        showUserInfo(user);
        cout << "Invalid pin.";
        cout << "Press any key to continue...";
        cin;
        return 0;
    }
    system("cls");
    showUserInfo(user);
    cout << "Creating loan..." << endl;
    user.balance -= dp;
    user.loan.active = true;
    user.loan.amount = amount;
    user.loan.due = (amount - dp) + (amount / loan_ir);
    int profit = user.loan.due - amount;
    user.loan.months = months;
    user.loan.paid = dp;
    users[user.id] = user;
    total_bank -= amount - dp;
    system("cls");
    showUserInfo(user);
    cout << "Added loan." << endl;
    cout << "You now owe the bank " << user.loan.due / months << " every month." << endl;
    cout << "You have already paid the bank " << dp << " as a down payment" << endl;
    cin >> amount;
    return 0;
}

int showUserLoanCmds(Types::User user) {
    bool isValid = false;
    int selected = 0;

    do {
        cout << "1. Create a new loan" << endl;
        cout << "2. Add (monthly) payment" << endl;
        cout << "3. Remove loan" << endl;
        cout << "4. Quit" << endl;

        cin >> selected;

        if (selected == 1 ||
            selected == 2 ||
            selected == 3 ||
            selected == 4) {
            isValid = true;
        }
        else {
            cout << "Invalid option." << endl;
        }
    } while (!isValid);

    return selected;
}

int showUserCmds() {
    bool isValid = false;
    int selected = 0;

    do {
        cout << "1. View balance" << endl;
        cout << "2. Transfer" << endl;
        cout << "3. Loans" << endl;
        cout << "4. Delete account" << endl;
        cout << "5. Logout" << endl;

        cin >> selected;

        if (selected == 1 ||
            selected == 2 ||
            selected == 3 ||
            selected == 4 ||
            selected == 5) {
            isValid = true;
        }
        else {
            cout << "Invalid option." << endl;
        }
    } while (!isValid);

    return selected;
}

int showBankInfo() {
    cout << "--------------- Bank info ---------------" << endl;
    cout << "Bank profit: " << bank_profit << endl;
    cout << "Bank total money: " << total_bank << endl;
    cout << "-----------------------------------------" << endl;

    return 0;
}

int showUserInfo(Types::User user) {
    cout << "--------------- User info ---------------" << endl;
    cout << "Balance: " << user.balance << endl;
    if (user.loan.active) {
        cout << "Loan:" << endl;
        cout << "    Amount due: " << user.loan.due << endl;
        cout << "    Paid off: " << user.loan.paid << endl;
        cout << "    Total loan amount: " << user.loan.amount << endl;
    }
    else {
        cout << "Loan: No loan active." << endl;
    }
    cout << "-----------------------------------------" << endl;

    return 0;
}

int cleanUp(bool quit) {
    if (quit) {
        cout << "Clean up finished, quitting...";
    }
    else {
        cout << "Clean up finished...";
    }
    return 0;
}