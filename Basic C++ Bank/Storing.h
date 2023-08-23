#ifndef STORING_H
#define STORING_H

#include "Types.h"

void SaveUser(Types::User user);
void SaveUsers(Types::User users[]);
void SaveInfo();

int LoadAllInfo();
Types::User LoadUser(int id);
int LoadNumberOfUsers();
int LoadBankIR();
int LoadLoanIR();
int LoadLoanDP();
int LoadBankProfit();
int LoadTotalBank();

int SaveNumberOfUsers(int value);
int SaveBankIR(int value);
int SaveLoanIR(int value);
int SaveLoanDP(int value);
int SaveBankProfit(int value);
int SaveTotalBank(int value);

#endif