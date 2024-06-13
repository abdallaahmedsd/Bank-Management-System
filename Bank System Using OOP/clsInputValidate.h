#pragma once
#include <iostream>
#include <string>
#include "clsPeriod.h"
#include "clsDate.h"

class clsInputValidate
{
public:

	static bool isNumberInRange(short n, short from, short to) {
		return !(n < from || n > to);
	}

	static bool isNumberInRange(int n, int from, int to) {
		return !(n < from || n > to);
	}

	static bool isNumberInRange(float n, float from, float to) {
		return !(n < from || n > to);
	}

	static bool isNumberInRange(double n, double from, double to) {
		return !(n < from || n > to);
	}

	static bool isDateBetween(clsDate date, clsDate dateFrom, clsDate dateTo) {

		// In case dateTo is before dateFrom swap them so the function isDateWithinPeriod() works correctly 
		if (clsDate::isDateBeforeDate2(dateTo, dateFrom)) {
			clsDate::swap(dateFrom, dateTo);
		}

		clsPeriod period(dateFrom, dateTo);

		return clsPeriod::isDateWithinPeriod(date, period);
	}

	static int readIntNumber(std::string message = "Invalid number! enter again: ") {

		int Number;

		std::cin >> Number;

		while (std::cin.fail()) {
			// user didn't input a number
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << message;
			std::cin >> Number;
		}

		return Number;
	}

	static int readIntNumberInRange(int from, int to, std::string message = "Number is not within the range, enter again: ") {

		int n = readIntNumber();

		while (!isNumberInRange(n, from, to)) {
			std::cout << message;
			n = readIntNumber();
		}

		return n;

	}

	static float readFloatNumber(std::string message = "Invalid number! enter again: ") {

		float Number;

		std::cin >> Number;

		while (std::cin.fail()) {
			// user didn't input a number
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << message;
			std::cin >> Number;
		}

		return Number;
	}

	static float readFloatNumberInRange(float from, float to, std::string message = "Number is not within the range, enter again: ") {

		float n = readIntNumber();

		while (!isNumberInRange(n, from, to)) {
			std::cout << message;
			n = readIntNumber();
		}

		return n;

	}

	static double readDoubleNumber(std::string message = "Invalid number! enter again: ") {

		double Number;

		std::cin >> Number;

		while (std::cin.fail() || Number < 1) {
			// user didn't input a number
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << message;
			std::cin >> Number;
		}

		return Number;
	}

	static double readDoubleNumberInRange(double from, double to, std::string message = "Number is not within the range, enter again: ") {

		double n = readDoubleNumber();

		while (!isNumberInRange(n, from, to)) {
			std::cout << message;
			n = readDoubleNumber();
		}

		return n;

	}

	static bool isValidDate(clsDate date) {
		return clsDate::isValidDate(date);
	}

	static int readPositiveNumber(std::string message = "Please enter a positive number: ") {

		int n = readIntNumber();

		while (n <= 0) {
			std::cout << message;
			n = readIntNumber();
		}

		return n;
	}

	static std::string readString(std::string prompt = "") {
		std::string st = "";
		if (prompt != "") {
			std::cout << prompt;
		}
		std::getline(std::cin >> std::ws, st);
		return st;
	}

	static char readChar(std::string prompt = "") {
		char c = 'n';
		if (prompt != "") {
			std::cout << prompt;
		}
		std::cin >> c;
		return c;
	}
};


