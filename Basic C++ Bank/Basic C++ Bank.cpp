// --- Begin imports --- //
#include <iostream>
#include <stdlib.h>
#include "Types.h"
#include <iomanip>
#include <locale>
#include "Storing.h"
extern "C" {
    #include "calculations.h"
}
// --- End imports --- //

using namespace std; // I know I shouldn't be relying on the std namespace but it's useful.

// --- Begin variables --- //
bool isRunning = true;
int numberOfUsers = 0;
const int users_capacity = 500;
Types::User users[users_capacity]; // This can take up a lot of space but as of now I have no easy way of starting it over.

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
int manageUserTransfer(Types::User user);
int manageUserLoan(Types::User user);
int showUserLoanCmds(Types::User user);
int newLoan(Types::User user);
int beginSave();
int LoadInfo();
int cleanUp(bool quit);
// --- End forward declarations --- //

int main()
{
    LoadInfo();
    SaveUsers(users);
    system("cls");
    cout << "Do you want to attempt to load from storage? If nothing exists all the values will be 0. (y/any other key)" << endl;
    char option;
    cin >> option;
    if (option == 'y') {
        LoadInfo();
    }
    else {
        cout << "Please fill in the variables." << endl;
        cout << "Bank total: ";
        cin >> total_bank;
        cout << "Bank account interest rate (%): ";
        cin >> bank_ir;
        cout << "Loaning interest rate (%): ";
        cin >> loan_ir;
        cout << "Loaning down payment (%): ";
        cin >> loan_dp;
    }
    SaveInfo();
    //numberOfUsers = 0;
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
            beginSave();
        }
        else if(selected == 1) {
            loginUser();
        }
        else if (selected == 2) {
            createAccount();
        }
        else if (selected == 4) {
            cleanUp(false);
            numberOfUsers = 0;
            main();
        }
        else if (selected == 5) {
            cleanUp(false);
            SaveInfo();
            SaveUsers(users);
            LoadInfo();
        }
    } while (isRunning);

    beginSave();
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
        cout << "5. Save & Clean" << endl;

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

int createAccount() {
    system("cls");
    showBankInfo();
    Types::User user;
    user.exists = true;
    user.balance = 5000;
    total_bank -= 5000;
    user.id = numberOfUsers + 1;
    numberOfUsers += 1;
    cout << "Your user ID is " << user.id << endl;
    cout << "Enter your pin: ";
    cin >> user.pin;
    cout << endl << "Your starting balance is: " << user.balance << endl;

    users[user.id] = user;

    system("cls");
    showBankInfo();
    cout << "User " << user.id << " successfully created." << endl;
    //SaveUsers(users);
    beginSave();

    return 0;
}

int loginUser() {
    system("cls");
    showBankInfo();
    Types::User user;
    int id = 0;
    cout << "Enter your ID: ";
    cin >> id;
    if (users[id].exists == false) {
        system("cls");
        showBankInfo();
        cout << "This user does not exist." << endl;
        return 0;
    }
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
            user.exists = false;
            users[id] = user;
            isLoggedIn = false;
        }
        else if (selected == 2) {
            manageUserTransfer(user);
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

int manageUserTransfer(Types::User user) {
    system("cls");
    showUserInfo(user);
    bool active = true;
    do {
        cout << "1. Transfer In" << endl;
        cout << "2. Transfer Out" << endl;
        cout << "3. Quit" << endl;
        int selected;
        cin >> selected;
        if (selected == 3) {
            active = false;
            system("cls");
            showUserInfo(user);
        }
        else if (selected == 2) {
            system("cls");
            showUserInfo(user);
            cout << "How much would you like to withdraw? (Max: " << user.balance << "): ";
            int amount;
            cin >> amount;
            if (amount <= user.balance) {
                system("cls");
                cout << "Enter your pin to withdraw " << amount << endl << "Pin: ";
                int pin;
                cin >> pin;
                if (user.pin != pin) {
                    system("cls");
                    showUserInfo(user);
                    cout << "Invalid pin.";
                }
                else {
                    user.balance -= amount;
                    total_bank -= amount;
                    users[user.id] = user;
                    SaveInfo();
                    system("cls");
                    showUserInfo(user);
                    cout << "Successfully withdrew " << amount << endl;
                }
            }
            else {
                system("cls");
                showUserInfo(user);
                cout << "Invalid amount..." << endl;
            }
        }
        else if (selected == 1) {
            system("cls");
            showUserInfo(user);
            cout << "How much would you like to deposit? (Max: 100,000,000): ";
            int amount;
            cin >> amount;
            if (amount <= 100000000) {
                system("cls");
                cout << "Enter your pin to deposit " << amount << endl << "Pin: ";
                int pin;
                cin >> pin;
                if (user.pin != pin) {
                    system("cls");
                    showUserInfo(user);
                    cout << "Invalid pin.";
                }
                else {
                    user.balance += amount;
                    total_bank += amount;
                    users[user.id] = user;
                    SaveInfo();
                    system("cls");
                    showUserInfo(user);
                    cout << "Successfully deposited " << amount << endl;
                }
            }
            else {
                system("cls");
                showUserInfo(user);
                cout << "Invalid amount..." << endl;
            }
        }
    } while (active);

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
    //user.loan.due = (amount - dp) + (amount / loan_ir);
    user.loan.due = calculateLoanDue(amount, loan_dp, loan_ir);
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
    beginSave();
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

int beginSave() {
    cout << "Saving info..." << endl;
    SaveNumberOfUsers(numberOfUsers);
    SaveBankIR(bank_ir);
    SaveLoanIR(loan_ir);
    SaveLoanDP(loan_dp);
    SaveBankProfit(bank_profit);
    SaveTotalBank(total_bank);

    SaveInfo();
    cout << "Sorting..." << endl;

    Types::User* Users_Sorted = new Types::User[users_capacity];
    for (size_t i = 0; i < users_capacity; i++)
    {
        Users_Sorted[users[i].id] = users[i];
    }
    for (size_t i = 0; i < users_capacity; i++)
    {
        users[i] = Users_Sorted[i];
    }
    delete[] Users_Sorted;
    cout << "Sorted!" << endl;
    cout << "Saving and reloading..." << endl;
    SaveUsers(users);

    return 0;
}

int LoadInfo() {
    LoadAllInfo();

    numberOfUsers = LoadNumberOfUsers();
    bank_ir = LoadBankIR();
    loan_ir = LoadLoanIR();
    loan_dp = LoadLoanDP();
    bank_profit = LoadBankProfit();
    total_bank = LoadTotalBank();

    system("cls");
    cout << "Loading users..." << endl;
    for (size_t i = 0; i < users_capacity; i++)
    {
        try {
            users[i] = LoadUser(i);
        }
        catch (exception ex) {
            //cout << "Failed to load user " << i << endl;
        }
    }
    cout << "Loaded users!" << endl;
    cout << "Sorting..." << endl;

    Types::User* Users_Sorted = new Types::User[users_capacity];
    for (size_t i = 0; i < users_capacity; i++)
    {
        Users_Sorted[users[i].id] = users[i];
    }
    for (size_t i = 0; i < users_capacity; i++)
    {
        users[i] = Users_Sorted[i];
    }
    delete[] Users_Sorted;
    cout << "Sorted!" << endl;
    cout << "Saving and reloading..." << endl;
    SaveUsers(users);
    cout << "Loading users..." << endl;
    for (size_t i = 0; i < users_capacity; i++)
    {
        try {
            users[i] = LoadUser(i);
        }
        catch (exception ex) {
            //cout << "Failed to load user " << i << endl;
        }
    }
    cout << "Loaded users!" << endl;

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