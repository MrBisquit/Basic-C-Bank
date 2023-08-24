#include "Calculations.h";
int calculateLoanDue(int amount, int loan_dp, int loan_ir) {
	int dp = amount / loan_dp;
	return (amount - dp) + (amount / loan_ir);
}