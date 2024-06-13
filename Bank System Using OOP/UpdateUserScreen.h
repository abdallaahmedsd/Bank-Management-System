#pragma once
#include <iostream>
#include "User.h"
#include "clsInputValidate.h"
#include "UserCard.h"
#include "Screen.h"

class UpdateUserScreen : protected Screen
{
private:
	static int _readPermissionsToSet() {

		char permission = clsInputValidate::readChar("\n\nDo you want to give this user full permissions (y/n)? ");

		if (permission == 'y' || permission == 'Y') {
			return -1;
		}
		else {
			short count = 0;
			std::cout << "\n\nDo you want to give access to:\n";

			std::string arrPermissions[] = { "Show client list" , "Add new client", "Delete client", "Update client", "Find client", "Transactions", "Manage users", "Show Login List", "Currency Exchange"};

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

	static void _changeUserInfo(User& user) {

		std::cout << "\nUpdate User Info:";
		std::cout << "\n----------------------------";

		char confirm = 'n';

		confirm = clsInputValidate::readChar("\nDo you want to change the first name (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			user.firstName = clsInputValidate::readString("Enter first name: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the last name (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			user.lastName = clsInputValidate::readString("Enter last name: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the email (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			user.email = clsInputValidate::readString("Enter email: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the phone (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			user.phone = clsInputValidate::readString("Enter phone: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the password (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			user.password = clsInputValidate::readString("Enter PINCode: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the permissions (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			user.permissions = _readPermissionsToSet();
		}
	}

public:
	static void updateUser() {

		_drawScreenHeader("\t\t\t\t\t\t    Update User Screen");

		std::string username = clsInputValidate::readString("\nPlease enter a username: ");
		while (!User::isUserExist(username)) {
			username = clsInputValidate::readString("\nUsername is not found, please enter again: ");
		}

		User user1 = User::find(username);
		UserCard::printUserInfo(user1);

		char confirm = clsInputValidate::readChar("\nAre you sure you want to update this user (y/n)? ");

		if (confirm == 'y' || confirm == 'Y') {

			_changeUserInfo(user1);

			User::enSaveResult saveResult;
			saveResult = user1.save();

			switch (saveResult)
			{
			case User::save_faild_empty_object:
				std::cout << "\n\nError! user was not saved because it's empty.\n";
				break;
			case User::save_succeeded:
				std::cout << "\n\nUser info updated successfully!\n";
				UserCard::printUserInfo(user1);
				break;
			}
		}
	}
};

