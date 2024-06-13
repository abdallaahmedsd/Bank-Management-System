#pragma once
#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "Screen.h"
#include "User.h"

class ListUsersScreen : protected Screen
{
private:
	static void _printUserInfoInLine(User& user) {

		std::cout << clsUtil::tabs(1) << "| " << std::setw(15) << std::left << user.getUsername();
		std::cout << "| " << std::setw(25) << std::left << user.getFullName();
		std::cout << "| " << std::setw(15) << std::left << user.getPhone();
		std::cout << "| " << std::setw(20) << std::left << user.getEmail();
		std::cout << "| " << std::setw(10) << std::left << user.password;
		std::cout << "| " << std::setw(12) << std::left << user.permissions << std::endl;
	}

public:
	static void showUsersList() {
		std::vector <User> vUsers = User::getUsersList();

		std::string title = "\t\t\t\t\t\t    List Users Screen";
		std::string subTitle = "\t\t\t\t\t\t      " + std::to_string(vUsers.size()) + " - User(s)";

		_drawScreenHeader(title, subTitle);

		std::cout << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------------\n\n";
		std::cout << clsUtil::tabs(1) << "| " << std::setw(15) << std::left << "Username";
		std::cout << "| " << std::setw(25) << std::left << "Full Name";
		std::cout << "| " << std::setw(15) << std::left << "Phone Number";
		std::cout << "| " << std::setw(20) << std::left << "User Email";
		std::cout << "| " << std::setw(10) << std::left << "Password";
		std::cout << "| " << std::setw(12) << std::left << "Permissions" << std::endl;
		std::cout << "\n" << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------------\n";


		if (vUsers.size() == 0) {
			std::cout << "\n" << clsUtil::tabs(7) << "You have no user in the system!\n\n";
		}
		else {
			for (User& user : vUsers) {
				_printUserInfoInLine(user);
			}
		}
		std::cout << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------------\n";

	}
};

