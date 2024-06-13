#pragma once
#include <iostream>
#include "Client.h"
#include "clsInputValidate.h"
#include "ClientCard.h"
#include "Screen.h"

class FindClientScreen : protected Screen
{
public:
	static void findClient() {
		if (!_checkAccessRights(User::enPermissions::p_find_client)) {
			return;
		}
		_drawScreenHeader("\t\t\t\t\t\t    Find Client Screen");

		std::string accountNumber = clsInputValidate::readString("\nPlease enter an account number: ");
		
		Client client1 = Client::find(accountNumber);

		if (client1.isEmpty()) {
			std::cout << "\nAccount number is not found!";
		}
		else {
			ClientCard::printClientInfo(client1);
		}



	}
};

