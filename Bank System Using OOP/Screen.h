#pragma once
#include <iostream>
#include "clsUtil.h"
#include "User.h"
#include "Global.h"
#include "clsDate.h"
#include "clsString.h"

class Screen
{
protected:

	static void _drawScreenHeader(std::string title, std::string subTitle = "") {

		std::system("cls");

		std::cout << "\n" << clsUtil::tabs(5) << "------------------------------------------\n\n";
		std::cout << title << std::endl;
		if (subTitle != "") {
			std::cout << subTitle << std::endl;
		}
		std::cout << "\n" << clsUtil::tabs(5) << "------------------------------------------\n";
		std::cout << clsUtil::tabs(5) << "Username: " << Current_User.username;
		std::cout << clsUtil::tabs(2) << "  Date: " << clsDate::convertDateToString(clsDate::getSystemDate()) << std::endl;
		std::cout << clsUtil::tabs(5) << "------------------------------------------\n";
	}

	static bool _checkAccessRights(User::enPermissions permissions) {
		if (!Current_User.checkAccessPermissions(permissions)) {
			std::system("cls");
			std::cout << "\n" << clsUtil::tabs(5) << "------------------------------------------\n\n";
			std::cout << clsUtil::tabs(5) << "   Access Denied!, Contact Your Admin\n";
			std::cout << "\n" << clsUtil::tabs(5) << "------------------------------------------\n\n";
			return false;
		}
		else {
			return true;
		}
	}

};
