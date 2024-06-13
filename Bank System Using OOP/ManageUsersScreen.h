#pragma once
#include <iostream>
#include <iomanip>
#include "Screen.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "ListUsersScreen.h"
#include "AddNewUserScreen.h"
#include "DeleteUserScreen.h"
#include "UpdateUserScreen.h"
#include "FindUserScreen.h"

class ManageUsersScreen : protected Screen
{
private:
	static void _drawManageUsersMenu() {
		std::system("cls");
		_drawScreenHeader("\t\t\t\t\t\t    Manage Users Screen");
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
		std::cout << clsUtil::tabs(6) << "  Main Manage Users Menu\n";
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
		std::cout << clsUtil::tabs(5) << "[1] Show Users List\n";
		std::cout << clsUtil::tabs(5) << "[2] Add New User\n";
		std::cout << clsUtil::tabs(5) << "[3] Delete User\n";
		std::cout << clsUtil::tabs(5) << "[4] Update User Info\n";
		std::cout << clsUtil::tabs(5) << "[5] Find User\n";
		std::cout << clsUtil::tabs(5) << "[6] Main Menu\n";
		std::cout << clsUtil::tabs(4) << "     ================================================\n";
	}

	static void _goBackToManageUsersMenu() {
		std::cout << "\n\n\n" << clsUtil::tabs(5) << "Press any key to go back to manage users menu...";
		std::system("pause>0");
		showManageUsersScreen();
	}

	static short _readManageUsersMenuOption() {
		std::cout << clsUtil::tabs(5) << "Choose what do you want to do? [1 to 6]? ";

		// Return the number minus 1 because the index in enManageUsersOption statrs from zero
		return (clsInputValidate::readIntNumberInRange(1, 6) - 1);
	}

	enum enManageUsersOption {
		en_list_users,
		en_add_new_user,
		en_delete_user,
		en_update_user,
		en_find_user,
		en_main_menu
	};

	static void _performManageUsersMenuOption(enManageUsersOption option) {
		switch (option)
		{
		case enManageUsersOption::en_list_users:
			_showListUsersScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOption::en_add_new_user:
			_showAddNewUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOption::en_delete_user:
			_showDeleteUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOption::en_update_user:
			_showUpdateUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOption::en_find_user:
			_showFindUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOption::en_main_menu:
			// nothing to happen here I handled it in MainMenu
			break;
		}
	}

	static void _showListUsersScreen() {
		ListUsersScreen::showUsersList();
	}

	static void _showAddNewUserScreen() {
		AddNewUserScreen::addNewUser();
	}

	static void _showDeleteUserScreen() {
		DeleteUserScreen::deleteUser();
	}

	static void _showUpdateUserScreen() {
		UpdateUserScreen::updateUser();
	}

	static void _showFindUserScreen(){
		FindUserScreen::findUser();
	}

public:
	static void showManageUsersScreen() {

		if (!_checkAccessRights(User::enPermissions::p_manage_users)) {
			std::cout << "\n\n\n" << clsUtil::tabs(5) << "Press any key to go back to main menu...";
			std::system("pause>0");
			return;
		}

		_drawManageUsersMenu();
		_performManageUsersMenuOption((enManageUsersOption)_readManageUsersMenuOption());
	}
};

