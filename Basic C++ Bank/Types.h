#ifndef Types_H
#define Types_H

static class Types {
public:
	class User {
	public:
		int id;
		int pin;
		int balance;
		Types::Loan loans;
	};
	class Loan {
	public:
		int amount;
		int months;
		int paid;
		int due;
		int current_month;
	};
};

#endif