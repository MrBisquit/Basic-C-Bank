#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

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

int LoadAllInfo() {
	string filename = "C:\\BankSys\\.idat";
	ifstream myfile(filename);
	int cl = 0;
	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line)) {
			cl++;

			if (cl == 1) {
				numberOfUsers_S = stoi(line);
			}
			else if (cl == 2) {
				bank_ir_S = stoi(line);
			}
			else if (cl == 3) {
				loan_ir_S = stoi(line);
			}
			else if (cl == 4) {
				loan_dp_S = stoi(line);
			}
			else if (cl == 5) {
				bank_profit_S = stoi(line);
			}
			else if (cl == 6) {
				total_bank_S = stoi(line);
			}
		}
	}
	else cout << "Unable to open file";

	return 0;
}

void SaveUser(Types::User user) {
	string filename = "C:\\BankSys\\" + to_string(user.id) + ".udat";
	ofstream myfile(filename);
	if (myfile.is_open())
	{
		myfile << user.balance << endl;
		myfile << user.id << endl;
		myfile << user.pin << endl;

		if (user.loan.active) {
			myfile << "true" << endl;
		}
		else {
			myfile << "false" << endl;
		}
		myfile << user.loan.amount << endl;
		myfile << user.loan.current_month << endl;
		myfile << user.loan.due << endl;
		myfile << user.loan.months << endl;
		myfile << user.loan.paid << endl;

		if (user.exists) {
			myfile << "true" << endl;
		}
		else {
			myfile << "false" << endl;
		}

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
	string filename = "C:\\BankSys\\.idat";
	ofstream myfile(filename);
	if (myfile.is_open())
	{
		myfile << numberOfUsers_S << endl;
		myfile << bank_ir_S << endl;
		myfile << loan_ir_S << endl;
		myfile << loan_dp_S << endl;
		myfile << bank_profit_S << endl;
		myfile << total_bank_S << endl;
		myfile.close();
	}
	else cout << "Unable to open file";
}

Types::User LoadUser(int id) {
	Types::User user;
	string filename = "C:\\BankSys\\" + to_string(id) + ".udat";
	ifstream myfile(filename);
	int cl = 0;
	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line)) {
			cl++;
			
			if (cl == 1) {
				user.balance = stoi(line);
			}
			else if (cl == 2) {
				user.id = stoi(line);
			}
			else if (cl == 3) {
				user.pin = stoi(line);
			}
			else if (cl == 4) {
				if (line == "true") {
					user.loan.active = true;
				}
				else {
					user.loan.active = false;
				}
			}
			else if (cl == 5) {
				user.loan.amount = stoi(line);
			}
			else if (cl == 6) {
				user.loan.current_month = stoi(line);
			}
			else if (cl == 7) {
				user.loan.due = stoi(line);
			}
			else if (cl == 8) {
				user.loan.months = stoi(line);
			}
			else if (cl == 9) {
				user.loan.paid = stoi(line);
			}
			else if (cl == 10) {
				if (line == "true") {
					user.exists = true;
				}
				else {
					user.exists = false;
				}
			}
		}
	}
	else cout << "Unable to open file";
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


int SaveNumberOfUsers(int value) {
	numberOfUsers_S = value;
	return 0;
}

int SaveBankIR(int value) {
	bank_ir_S = value;
	return 0;
}

int SaveLoanIR(int value) {
	loan_ir_S = value;
	return 0;
}

int SaveLoanDP(int value) {
	loan_dp_S = value;
	return 0;
}

int SaveBankProfit(int value) {
	bank_profit_S = value;
	return 0;
}

int SaveTotalBank(int value) {
	total_bank_S = value;
	return 0;
}