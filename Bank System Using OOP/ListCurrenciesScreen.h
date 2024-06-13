#pragma once
#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "Screen.h"
#include "Currency.h"

class ListCurrenciesScreen : protected Screen
{
private:
	static void _printCurrencyInfoInLine(Currency& currency) {
		std::cout << clsUtil::tabs(1) << "| " << std::setw(30) << std::left << currency.getCountryName();
		std::cout << "| " << std::setw(8) << std::left << currency.getCurrencyCode();
		std::cout << "| " << std::setw(45) << std::left << currency.getCurrencyName();
		std::cout << "| " << std::setw(11) << std::left << currency.getRate() << "|" << std::endl;
	}

public:
	static void showCurrenciesListScreen() {

		std::vector <Currency> vCurrencies = Currency::getCurrenciesList();

		std::string title = "\t\t\t\t\t\t   List Currencies Screen";
		std::string subTitle = "\t\t\t\t\t\t      " + std::to_string(vCurrencies.size()) + " - Currencies";

		_drawScreenHeader(title, subTitle);


		std::cout << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------\n\n";
		std::cout << clsUtil::tabs(1) << "| " << std::setw(30) << std::left << "Country";
		std::cout << "| " << std::setw(8) << std::left << "Code";
		std::cout << "| " << std::setw(45) << std::left << "Currency Name";
		std::cout << "| " << std::setw(11) << std::left << "Rate" << "|" << std::endl;
		std::cout << "\n" << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------\n";

		if (vCurrencies.size() == 0) {
			std::cout << "\n" << clsUtil::tabs(7) << "You have no currencies in the system!\n\n";
		}
		else {
			for (Currency& currency : vCurrencies) {
				_printCurrencyInfoInLine(currency);
			}
			std::cout << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------\n";
		}

	}
};

