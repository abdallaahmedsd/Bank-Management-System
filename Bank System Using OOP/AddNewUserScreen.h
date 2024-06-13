#pragma once
#pragma once
#include <iostream>
#include "User.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "Screen.h"
#include "UserCard.h"

class AddNewUserScreen : protected Screen
{
	static void _readUserInfo(User& user) {
		user.firstName = clsInputValidate::readString("Enter first name: ");
		user.lastName = clsInputValidate::readString("Enter last name: ");
		user.email = clsInputValidate::readString("Enter email: ");
		user.phone = clsInputValidate::readString("Enter phone: ");
		user.password = clsInputValidate::readString("Enter password: ");
		user.permissions = _readPermissionsToSet();
	}

	static int _readPermissionsToSet() {

		char permission = clsInputValidate::readChar("\n\nDo you want to give this user full permissions (y/n)? ");

		if (permission == 'y' || permission == 'Y') {
			return -1;
		}
		else {
			short count = 0;
			std::cout << "\n\nDo you want to give access to:\n";

			std::string arrPermissions[] = { "Show client list" , "Add new client", "Delete client", "Update client", "Find client", "Transactions", "Manage users", "Show Login List", "Currency Exchange" };

			for (int i = 0; i < 9; i++) {

				std::string prompt = arrPermissions[i] + " (y/n)? ";
				permission = clsInputValidate::readChar(prompt);

				if (permission == 'y' || permission == 'Y') {
					count += pow(2, i);
				}
			}

			return count;
		}
	}

public:
	static void addNewUser() {

		_drawScreenHeader("\t\t\t\t\t\t     Add New User");

		std::string username = clsInputValidate::readString("\nPlease enter a username: ");

		while (User::isUserExist(username)) {
			std::cout << "\nUsername [" << username << "] is already exist, ";
			username = clsInputValidate::readString("choose another one: ");
		}

		User user = User::getAddNewUserObject(username);

		_readUserInfo(user);

		User::enSaveResult saveResult;
		saveResult = user.save();

		switch (saveResult)
		{
		case User::save_succeeded:
			std::cout << "\n\nUser added successfully!\n";
			UserCard::printUserInfo(user);
			break;
		case User::save_faild_account_num_exist:
			std::cout << "\nError account number is already exist!";
			break;
		}
	}

};