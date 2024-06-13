#pragma once
#include <iostream>
#include "User.h"
#include "clsInputValidate.h"
#include "UserCard.h"
#include "Screen.h"

class DeleteUserScreen : protected Screen
{
public:
	static void deleteUser() {
		_drawScreenHeader("\t\t\t\t\t\t     Delete user screen");

		std::string username = clsInputValidate::readString("\nPlease enter a username: ");

		while (!User::isUserExist(username)) {
			username = clsInputValidate::readString("\nUsername is not found, enter another one: ");
		}

		if (username == "admin") {
			std::cout << "\n\nYou can't delete this user he is your BOOS!\n";
			return;
		}

		User user = User::find(username);
		UserCard::printUserInfo(user);

		char confirm = 'n';
		confirm = clsInputValidate::readChar("\n\nAre you sure you want to delete this user (y/n)? ");

		if (confirm == 'y' || confirm == 'Y') {
			if (user.Delete()) {
				std::cout << "\n\nUser deleted successfully!\n";
			}
			else {
				std::cout << "\n\nError user in not found.\n";
			}
		}
	}

};

