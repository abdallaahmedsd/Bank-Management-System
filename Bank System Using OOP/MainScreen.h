#pragma once
#include <iostream>
#include <iomanip>
#include "Screen.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "ListClientsScreen.h"
#include "AddNewClientScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateClientScreen.h"
#include "FindClientScreen.h"
#include "TransactionsScreen.h"
#include "ManageUsersScreen.h"
#include "ListLoginRegisterScreen.h"
#include "CurrencyExchangeScreen.h"

class MainScreen : protected Screen
{
private:
	static short _readMainMenuOption() {
		std::cout << clsUtil::tabs(5) << "Choose what do you want to do? [1 to 10]? ";

		// Return the number minus 1 because the index in enMainMenuOption starts from zero
		return (clsInputValidate::readIntNumberInRange(1, 10) - 1);
	}

	enum enMainMenuOption {
		en_list_clients,
		en_add_new_client,
		en_delete_client,
		en_update_client,
		en_find_client,
		en_transactions,
		en_manage_users,
		en_show_logins_register,
		en_currency_exchange,
		en_logout
	};

	static void _goBackToMainMenu() {
		std::cout << "\n\n\n" << clsUtil::tabs(5) << "Press any key to go back to main menu...";
		std::system("pause>0");
		showMainMenu();
	}

	static void _performMainMenuOption(enMainMenuOption option) {
		switch (option)
		{
		case enMainMenuOption::en_list_clients:
			_showClientsListScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::en_add_new_client:
			_showAddNewClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::en_delete_client:
			_showDeleteClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::en_update_client:
			_showUpdateClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::en_find_client:
			_showFindClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::en_transactions:
			_showTransactionsScreen();
			showMainMenu();
			break;
		case enMainMenuOption::en_manage_users:
			_showManageUsersScreen();
			showMainMenu();
			break;
		case enMainMenuOption::en_show_logins_register:
			_showListLoginRegisterScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::en_currency_exchange:
			_showCurrencyExchangeScreen();
			showMainMenu();
			break;
		case enMainMenuOption::en_logout:
			_logout();
			break;
		}
	}

	static void _drawMainMenu() {
		std::system("cls");
		_drawScreenHeader("\t\t\t\t\t\t\tMain Screen");
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
		std::cout << clsUtil::tabs(7) << "Main Menu\n";
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
		std::cout << clsUtil::tabs(5) << "[01] Show Clients List\n";
		std::cout << clsUtil::tabs(5) << "[02] Add New Client\n";
		std::cout << clsUtil::tabs(5) << "[03] Delete Client\n";
		std::cout << clsUtil::tabs(5) << "[04] Update Client Info\n";
		std::cout << clsUtil::tabs(5) << "[05] Find Client\n";
		std::cout << clsUtil::tabs(5) << "[06] Transactions\n";
		std::cout << clsUtil::tabs(5) << "[07] Manage Users\n";
		std::cout << clsUtil::tabs(5) << "[08] Show Logins List\n";
		std::cout << clsUtil::tabs(5) << "[09] Currency Exchange\n";
		std::cout << clsUtil::tabs(5) << "[10] Logout\n";
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
	}

	static void _showClientsListScreen() {
		ListClientsScreen::showClientsList();
	}

	static void _showAddNewClientScreen() {
		AddNewClientScreen::addNewClient();
	}

	static void _showDeleteClientScreen() {
		DeleteClientScreen::deleteClient();
	}
	
	static void _showUpdateClientScreen() {
		UpdateClientScreen::updateClient();
	}

	static void _showFindClientScreen() {
		FindClientScreen::findClient();
	}

	static void _showTransactionsScreen() {
		TransactionsScreen::showTransactionsMenu();
	}

	static void _showManageUsersScreen() {
		ManageUsersScreen::showManageUsersScreen();
	}

	static void _showListLoginRegisterScreen() {
		ListLoginRegisterScreen::showLoginsRegisterList();
	}

	static void _showCurrencyExchangeScreen() {
		CurrencyExchangeScreen::showCurrencyExchangeScreen();
	}

	static void _logout() {
		Current_User = User::find("", "");
	}

public:
	static void showMainMenu() {
		std::system("color 1f");
		_drawMainMenu();
		_performMainMenuOption((enMainMenuOption)_readMainMenuOption());
	}
};

