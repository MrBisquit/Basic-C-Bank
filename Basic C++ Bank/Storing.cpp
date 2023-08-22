#include <iostream>
#include <fstream>
#include <windows.h>

#include "Storing.h"
#include "Types.h"

using namespace std;

int numberOfUsers_S = 0;

int bank_ir_S;
int loan_ir_S;
int loan_dp_S;

int bank_profit_S;
int total_bank_S = 100000000;

// Credits: https://stackoverflow.com/a/875264/16426057
std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

void LoadAllInfo() {

}

void SaveUser(Types::User user) {
	ofstream myfile(user.id + ".udat");
	if (myfile.is_open())
	{
		myfile << user.balance << endl;
		myfile << user.id << endl;
		myfile << user.pin << endl;

		myfile << user.loan.active << endl;
		myfile << user.loan.amount << endl;
		myfile << user.loan.current_month << endl;
		myfile << user.loan.due << endl;
		myfile << user.loan.months << endl;
		myfile << user.loan.paid << endl;

		myfile.close();
	}
	else cout << "Unable to open file";
}

void SaveUsers(Types::User users[]) {
	// sizeof(users)
	for (size_t i = 0; i < 500; i++)
	{
		//cout << "Saving " << users[i].id << endl;
		SaveUser(users[i]);
		//cout << "Saved " << users[i].id << endl;
	}
}

void SaveInfo() {
	ofstream myfile(".idat");
	if (myfile.is_open())
	{
		myfile << "This is a line.\n";
		myfile << "This is another line.\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

Types::User LoadUser(int id) {
	Types::User user;
	return user;
}

int LoadNumberOfUsers() {
	return numberOfUsers_S;
}

int LoadBankIR() {
	return bank_ir_S;
}

int LoadLoanIR() {
	return loan_ir_S;
}

int LoadLoanDP() {
	return loan_dp_S;
}

int LoadBankProfit() {
	return bank_profit_S;
}

int LoadTotalBank() {
	return total_bank_S;
}