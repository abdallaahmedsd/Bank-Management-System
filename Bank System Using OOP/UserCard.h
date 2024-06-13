#pragma once
#include <iostream>
#include "User.h"

class UserCard
{
public:
	static void printUserInfo(User& user) {
		std::cout << "\nUser Card:\n";
		std::cout << "-----------------------------------------\n";
		std::cout << "Username   : " << user.username << std::endl;
		std::cout << "Full name  : " << user.getFullName() << std::endl;
		std::cout << "Email      : " << user.email << std::endl;
		std::cout << "Phone      : " << user.phone << std::endl;
		std::cout << "Password   : " << user.password << std::endl;
		std::cout << "Permissions: " << user.permissions << std::endl;
		std::cout << "-----------------------------------------\n";
	}

};

