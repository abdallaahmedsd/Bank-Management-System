#pragma once
#include <iostream>
#include <iomanip>
#include "Screen.h"
#include "clsUtil.h"
#include "MainScreen.h"
#include "clsInputValidate.h"
#include "DepositScreen.h"
#include "WithdrawScreen.h"
#include "TransferScreen.h"
#include "TotalBalancesScreen.h"
#include "TransferLogScreen.h"

class TransactionsScreen : protected Screen
{
private:
	static void _goBackToTransactionsMenu() {
		std::cout << "\n\n\n" << clsUtil::tabs(5) << "Press any key to go back to transactions menu...";
		std::system("pause>0");
		showTransactionsMenu();
	}

	enum enTransactionsMenu {
		en_deposit,
		en_withdraw,
		en_transfer,
		en_list_transfer_log,
		en_total_balances,
		en_back_to_main_menu
	};

	static short _readTransactionsMenuOption() {
		std::cout << clsUtil::tabs(5) << "Choose what do you want to do? [1 to 6]? ";

		// Return the number minus 1 because the index in enTransactionsMenu starts from zero
		return (clsInputValidate::readIntNumberInRange(1, 6) - 1);
	}

	static void _drawTransactionsMenu() {
		std::system("cls");
		_drawScreenHeader("\t\t\t\t\t\t    Transactions Screen");
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
		std::cout << clsUtil::tabs(6) << "    Main Transactions Menu\n";
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
		std::cout << clsUtil::tabs(5) << "[1] Deposit\n";
		std::cout << clsUtil::tabs(5) << "[2] Withdraw\n";
		std::cout << clsUtil::tabs(5) << "[3] Transfer\n";
		std::cout << clsUtil::tabs(5) << "[4] List Transfer Logs\n";
		std::cout << clsUtil::tabs(5) << "[5] Total Balances\n";
		std::cout << clsUtil::tabs(5) << "[6] Main Menu\n";
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
	}

	static void _performTransactionsOption(enTransactionsMenu option) {
		switch (option)
		{
		case enTransactionsMenu::en_deposit:
			_showDepositScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenu::en_withdraw:
			_showWithdrawScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenu::en_transfer:
			_showTransferScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenu::en_list_transfer_log:
			_showTransferLogScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenu::en_total_balances:
			_showTotalBalances();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsMenu::en_back_to_main_menu:
			break;
		}
	}

	static void _showDepositScreen() {
		DepositScreen::deposit();
	}

	static void _showWithdrawScreen() {
		WithdrawScreen::withdraw();
	}

	static void _showTransferScreen() {
		TransferScreen::showTransferScreen();
	}

	static void _showTransferLogScreen() {
		TransferLogScreen::showTransferLogScreen();
	}

	static void _showTotalBalances() {
		TotalBalancesScreen::totalBalances();
	}

public:
	static void showTransactionsMenu() {

		if (!_checkAccessRights(User::enPermissions::p_transactions)) {
			std::cout << "\n\n\n" << clsUtil::tabs(5) << "Press any key to go back to main menu...";
			std::system("pause>0");
			return;
		}

		_drawTransactionsMenu();
		_performTransactionsOption((enTransactionsMenu)_readTransactionsMenuOption());
	}

};



