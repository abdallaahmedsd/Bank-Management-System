#pragma once
#include <iostream>
#include "Client.h"
#include "clsInputValidate.h"
#include "Screen.h"
#include "Currency.h"

class UpdateCurrencyRateScreen : protected Screen
{
private:
	static void _printCurrencyInfo(Currency currency) {
		std::cout << "\nCurrency Info:\n";
		std::cout << "--------------------------------------\n";
		std::cout << "Country Name : " << currency.getCountryName() << std::endl;
		std::cout << "Currency Code: " << currency.getCurrencyCode() << std::endl;
		std::cout << "Currency Name: " << currency.getCurrencyName() << std::endl;
		std::cout << "Rate(1$)     : " << currency.getRate() << std::endl;
		std::cout << "--------------------------------------\n\n";
	}

public:
	static void showUpdateRateScreen() {

		_drawScreenHeader("\t\t\t\t\t\tUpdate Currency Rate Screen");

		std::string code = clsInputValidate::readString("\n\nPlease enter currency code: ");

		while (!Currency::isCurrencyExist(code)) {
			code = clsInputValidate::readString("\nCurrency code doesn't exist, enter code again: ");
		}

		Currency currency = Currency::findByCode(code);
		_printCurrencyInfo(currency);

		char confirm = clsInputValidate::readChar("\n\nAre you sure you want to update this currency (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			std::cout << "\n\nUpdate Currency Rate:\n";
			std::cout << "-------------------------------\n";
			std::cout << "Enter new rate: ";
			float newRate = clsInputValidate::readFloatNumber();
			currency.updateRate(newRate);
			std::cout << "\n\nCurrency rate updated successfully!\n";
			_printCurrencyInfo(currency);
		}
	}

};

