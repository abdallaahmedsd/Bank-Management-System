#pragma once
#include <iostream>
#include "User.h"
#include "clsInputValidate.h"
#include "Screen.h"
#include "Currency.h"

class ExchangeCalculatorScreen : protected Screen
{
private:
	static std::string _readCurrencyCode() {
		std::string code = clsInputValidate::readString("\nPlease enter currency code: ");

		while (!Currency::isCurrencyExist(code)) {
			code = clsInputValidate::readString("\nCurrency code doesn't exist, enter code again: ");
		}
	}

	static void _printCurrencyInfo(Currency currency) {
		std::cout << "--------------------------------------\n";
		std::cout << "Country Name : " << currency.getCountryName() << std::endl;
		std::cout << "Currency Code: " << currency.getCurrencyCode() << std::endl;
		std::cout << "Currency Name: " << currency.getCurrencyName() << std::endl;
		std::cout << "Rate(1$)     : " << currency.getRate() << std::endl;
		std::cout << "--------------------------------------\n\n";
	}

	static void _printCalculationResults(float amount, Currency currencyFrom, Currency currencyTo) {
		std::cout << "\n\nConvert From [" << currencyFrom.getCurrencyCode()
			<< "] To " << "] " << currencyTo.getCurrencyCode() << "]\n";
		_printCurrencyInfo(currencyFrom);

		if (currencyFrom.getCurrencyCode() == "USD" || currencyTo.getCurrencyCode() == "USD") {
			if (currencyFrom.getCurrencyCode() == "USD") {
				std::cout << "\n" << amount << " USD = " << currencyTo.exchangeFromDollar(amount) << " " << currencyTo.getCurrencyCode();
			}
			else {
				std::cout << "\n" << amount << " " << currencyFrom.getCurrencyCode() << " = "
					<< currencyFrom.exchangeToDollar(amount) << " USD\n";
			}
		}
		else {

			float dollars = currencyFrom.exchangeToDollar(amount);

			std::cout << "\nFirst convert [" << currencyFrom.getCurrencyCode() << "] to [USD]:\n";
			std::cout << amount << " " << currencyFrom.getCurrencyCode() << " = "
				<< dollars << " USD\n";

			std::cout << "\nSecond convert [USD] " << " to [" << currencyTo.getCurrencyCode() << "]:\n";
			_printCurrencyInfo(currencyTo);
			std::cout << dollars << " USD = " << currencyTo.exchangeFromDollar(dollars) << " " << currencyTo.getCurrencyCode() << std::endl;
		}

		/*std::cout << "\n" << amount << " " << currency1.getCurrencyCode() << " = "
			<< currency1.exchange(amount, currency2) << " " << currency2.getCurrencyCode();*/
	}

	static Currency _getCurrency(std::string message) {
		std::string code = clsInputValidate::readString(message);
		while (!Currency::isCurrencyExist(code)) {
			code = clsInputValidate::readString("\nCurrency code is not exist, enter currency1 code again: ");
		}

		Currency currency = Currency::findByCode(code);
		return currency;
	}

public:
	static void showExchangeCalculatorScreen() {

		_drawScreenHeader("\t\t\t\t\t    Currency Exchange Calculator Screen");

		Currency currencyFrom = _getCurrency("\nEnter currency to exchange from: ");
		Currency currencyTo = _getCurrency("\nEnter currency to exchange to: ");

		std::cout << "\nEnter amount to exchange: ";
		float amount = clsInputValidate::readFloatNumber();

		_printCalculationResults(amount, currencyFrom, currencyTo);
	}

};

