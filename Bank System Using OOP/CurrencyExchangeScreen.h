#pragma once
#include <iostream>
#include <iomanip>
#include "Screen.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "ListCurrenciesScreen.h"
#include "FindCurrencyScreen.h"
#include "UpdateCurrencyRateScreen.h"
#include "ExchangeCalculatorScreen.h"

class CurrencyExchangeScreen : protected Screen
{
private:
	enum enCurrencyOption {
		en_list_currencies,
		en_find_currency,
		en_update_rate,
		en_currency_calculator,
		en_back_to_main_menu
	};

	static short _readCurrencyExchangeMenuOption() {
		std::cout << clsUtil::tabs(5) << "Choose what do you want to do? [1 to 5]? ";

		// Return the number minus 1 because the index in enCurrencyOption starts from zero
		return (clsInputValidate::readIntNumberInRange(1, 5) - 1);
	}

	static void _goBackToMainMenu() {
		std::cout << "\n\n\n" << clsUtil::tabs(4) << "Press any key to go back to currency exchange main menu...";
		std::system("pause>0");
		showCurrencyExchangeScreen();
	}

	static void _drawCurrencyExchangeMenu() {
		std::system("cls");
		_drawScreenHeader("\t\t\t\t\t\tCurrency Exchange Main Menu");
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
		std::cout << clsUtil::tabs(6) << "   Currency Exchange Menu\n";
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
		std::cout << clsUtil::tabs(5) << "[1] List Currencies\n";
		std::cout << clsUtil::tabs(5) << "[2] Find Currency\n";
		std::cout << clsUtil::tabs(5) << "[3] Update Rate\n";
		std::cout << clsUtil::tabs(5) << "[4] Currency Calculator\n";
		std::cout << clsUtil::tabs(5) << "[5] Main Menu\n";
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
	}

	static void _performCurrencyExchangeOption(enCurrencyOption option) {
		switch (option)
		{
		case enCurrencyOption::en_list_currencies:
			_showListCurrenciesScreen();
			_goBackToMainMenu();
			break;
		case enCurrencyOption::en_find_currency:
			_showFindCurrencyScreen();
			_goBackToMainMenu();
			break;
		case enCurrencyOption::en_update_rate:
			_showUpdateRateScreen();
			_goBackToMainMenu();
			break;
		case enCurrencyOption::en_currency_calculator:
			_showCurrencyCalculatorScreen();
			_goBackToMainMenu();
			break;
		case enCurrencyOption::en_back_to_main_menu:
			// Do nothing so that will return to the main menu
			break;
		}
	}

	static void _showListCurrenciesScreen() {
		ListCurrenciesScreen::showCurrenciesListScreen();
	}

	static void _showFindCurrencyScreen() {
		FindCurrencyScreen::showFindCurrencyScreen();
	}

	static void _showUpdateRateScreen() {
		UpdateCurrencyRateScreen::showUpdateRateScreen();
	}

	static void _showCurrencyCalculatorScreen() {
		ExchangeCalculatorScreen::showExchangeCalculatorScreen();
	}

public:
	static void showCurrencyExchangeScreen() {

		if (!_checkAccessRights(User::enPermissions::p_currency_exchange)) {
			std::cout << "\n\n\n" << clsUtil::tabs(5) << "Press any key to go back to main menu...";
			std::system("pause>0");
			return;
		}

		_drawCurrencyExchangeMenu();
		_performCurrencyExchangeOption((enCurrencyOption)_readCurrencyExchangeMenuOption());
	}
};

