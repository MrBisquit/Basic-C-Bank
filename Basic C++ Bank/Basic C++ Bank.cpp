#include <iostream>
#include <stdlib.h>
#include "Types.h"

using namespace std;

bool isRunning = true;
int numberOfUsers = 0;
Types::User users[500];

int bank_ir;
int loan_ir;
int loan_dp;

int bank_profit;
int total_bank = 100000000;

int showHomeCmds();
int createAccount();
int loginUser();
int loginUser();
int showUserCmds();
int cleanUp(bool quit);

int main()
{
    system("cls");
    cout << "Please fill in the variables." << endl;
    cout << "Bank account interest rate (%): ";
    cin >> bank_ir;
    cout << "Loaning interest rate (%): ";
    cin >> loan_ir;
    cout << "Loaning down payment (%): ";
    cin >> loan_ir;
    numberOfUsers = 0;
    cout << "Ready...";
    do {
        system("cls");
        cout << "Welcome to the banking system." << endl;
        cout << "Please select an option from this list." << endl;
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
    cout << "Beginning cleanup..." << endl;
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
    Types::User user;
    user.balance = 100000;
    user.id = numberOfUsers;
    numberOfUsers += 1;
    cout << "Your user ID is " << user.id << endl;
    cout << "Enter your pin: ";
    cin >> user.pin;
    cout << endl << "Your starting balance is: " << user.balance << endl;

    users[user.id] = user;

    system("cls");
    cout << "User " << user.id << " successfully created." << endl;

    return 0;
}

int loginUser() {
    system("cls");
    Types::User user;
    int id = 0;
    cout << "Enter your ID: ";
    cin >> id;
    user = users[id];
    cout << endl << "Enter your pin: ";
    int pin = 0;
    cin >> pin;
    if (user.pin != pin) {
        cout << endl << "Incorrect pin.";
        isRunning = false;
        return 0;
    }
    system("cls");

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
            cout << "Your current balance is " << user.balance << endl;
        }
    } while (isLoggedIn);

    return 0;
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

}

int cleanUp(bool quit) {
    if (quit) {
        cout << "Cleanup finished, quitting...";
    }
    else {
        cout << "Cleanup finished...";
    }
    return 0;
}