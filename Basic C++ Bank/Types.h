#ifndef Types_H
#define Types_H

static class Types {
public:
	class Loan {
	public:
		int amount = 0;
		int months = 0;
		int paid = 0;
		int due = 0;
		int current_month = 0;

		bool active = false;
	};
	class User {
	public:
		int id = 0;
		int pin = 0;
		int balance = 0;
		Types::Loan loan;
		bool exists = false;
	};
};

#endif