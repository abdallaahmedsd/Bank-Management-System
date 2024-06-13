#pragma once
#include <iostream>
#include "User.h"
#include "clsInputValidate.h"
#include "Screen.h"
#include "Currency.h"

class FindCurrencyScreen : protected Screen
{
private:
	enum enFindChoice {en_find_by_code, en_find_by_name};

	static void _printCurrencyInfo(Currency currency) {
		std::cout << "\nCurrency Info:\n";
		std::cout << "--------------------------------------\n";
		std::cout << "Country Name : " << currency.getCountryName() << std::endl;
		std::cout << "Currency Code: " << currency.getCurrencyCode() << std::endl;
		std::cout << "Currency Name: " << currency.getCurrencyName() << std::endl;
		std::cout << "Rate(1$)     : " << currency.getRate() << std::endl;
		std::cout << "--------------------------------------\n\n";
	}

	static enFindChoice _readChoice() {
		short choice = 0;
		std::cout << "\nFind by: [1] Code, or [2] Country? ";
		return (enFindChoice)(clsInputValidate::readIntNumberInRange(1,2) - 1);
	}

	static void _find(enFindChoice choice) {

		if (choice == enFindChoice::en_find_by_code) {
			std::string code = clsInputValidate::readString("\nPlease enter currency code: ");
			Currency currency = Currency::findByCode(code);
			_printResults(currency);
		}
		else if (choice == enFindChoice::en_find_by_code) {
			std::string name = clsInputValidate::readString("\nPlease enter country name: ");
			Currency currency = Currency::findByCode(name);
			_printResults(currency);
		}
	}

	static void _printResults(Currency currency) {
		if (currency.isEmpty()) {
			std::cout << "\n\nCurrency not found :-(\n";
		}
		else {
			std::cout << "\n\nCurrency found :-)\n";
			_printCurrencyInfo(currency);
		}
	}

public:
	static void showFindCurrencyScreen() {
		_drawScreenHeader("\t\t\t\t\t\t    Find Currency Screen");
		_find(_readChoice());
	}

};

