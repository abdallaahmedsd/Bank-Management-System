#pragma once
#pragma once
#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "Screen.h"
#include "LoginRegister.h"

class ListLoginRegisterScreen : protected Screen
{
private:
	static void _printLoginInfoInLine(LoginRegister& userLoginInfo) {
		std::cout << clsUtil::tabs(2) << "| " << std::setw(30) << std::left << userLoginInfo.getDateAndTime();
		std::cout << "| " << std::setw(20) << std::left << userLoginInfo.getUsername();
		std::cout << "| " << std::setw(20) << std::left << userLoginInfo.getPassword();
		std::cout << "| " << std::setw(20) << std::left << userLoginInfo.getPermissions() << std::endl;
	}

public:
	static void showLoginsRegisterList() {

		if (!_checkAccessRights(User::enPermissions::p_show_logins_list)) {
			return;
		}

		std::vector <LoginRegister> vLoginsInfo = LoginRegister::getLoginsRegisterList();

		std::string title = "\t\t\t\t\t\tLogin Register List Screen";
		std::string subTitle = "\t\t\t\t\t\t\t" + std::to_string(vLoginsInfo.size()) + " - User(s)";

		_drawScreenHeader(title, subTitle);

		std::cout << clsUtil::tabs(2) << "-------------------------------------------------------------------------------------------\n\n";
		std::cout << clsUtil::tabs(2) << "| " << std::setw(30) << std::left << "Date/Time";
		std::cout << "| " << std::setw(20) << std::left << "Username";
		std::cout << "| " << std::setw(20) << std::left << "Password";
		std::cout << "| " << std::setw(20) << std::left << "Permissions" << std::endl;
		std::cout << "\n" << clsUtil::tabs(2) << "-------------------------------------------------------------------------------------------\n";


		if (vLoginsInfo.size() == 0) {
			std::cout << "\n" << clsUtil::tabs(5) << "You have no logged users in the system!\n\n";
		}
		else {
			for (LoginRegister& loginInfo : vLoginsInfo) {
				_printLoginInfoInLine(loginInfo);
			}
		}
		std::cout << clsUtil::tabs(2) << "-------------------------------------------------------------------------------------------\n";

	}



};

