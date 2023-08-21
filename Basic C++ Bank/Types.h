#ifndef Types_H
#define Types_H

static class Types {
public:
	class Loan {
	public:
		int amount;
		int months;
		int paid;
		int due;
		int current_month;
	};
	class User {
	public:
		int id;
		int pin;
		int balance;
		Types::Loan loans;
	};
};

#endif