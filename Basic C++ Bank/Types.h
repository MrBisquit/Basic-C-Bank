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

		bool active = false;
	};
	class User {
	public:
		int id;
		int pin;
		int balance;
		Types::Loan loan;
	};
};

#endif