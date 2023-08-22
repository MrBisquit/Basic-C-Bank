#ifndef STORING_H
#define STORING_H

#include "Types.h"

void SaveUser(Types::User user);
void SaveUsers(Types::User users[]);
void SaveInfo();

Types::User LoadUser(int id);
int LoadNumberOfUsers();
int LoadBankIR();
int LoadLoanIR();
int LoadLoanDP();
int LoadBankProfit();
int LoadTotalBank();

#endif