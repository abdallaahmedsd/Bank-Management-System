#pragma once
#include <iostream>
#include "User.h"
#include "clsInputValidate.h"
#include "UserCard.h"
#include "Screen.h"

class FindUserScreen : protected Screen
{
public:
	static void findUser() {

		_drawScreenHeader("\t\t\t\t\t\t     Find User Screen");

		std::string username = clsInputValidate::readString("\nPlease enter a username: ");

		User user = User::find(username);

		if (user.isEmpty()) {
			std::cout << "\nUsername number is not found!";
		}
		else {
			UserCard::printUserInfo(user);
		}



	}
};

