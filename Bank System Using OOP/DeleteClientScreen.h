#pragma once
#include <iostream>
#include "Client.h"
#include "clsInputValidate.h"
#include "ClientCard.h"
#include "Screen.h"

class DeleteClientScreen : protected Screen
{
public:
	static void deleteClient() {
		if (!_checkAccessRights(User::enPermissions::p_delete_client)) {
			return;
		}
		_drawScreenHeader("\t\t\t\t\t\t    Delete client screen");

		std::string accountNumber = clsInputValidate::readString("\nPlease enter an account number: ");

		while (!Client::isClientExist(accountNumber)) {
			accountNumber = clsInputValidate::readString("\nAccount number is not found, enter another one: ");
		}

		Client client1 = Client::find(accountNumber);
		ClientCard::printClientInfo(client1);

		char confirm = 'n';
		confirm = clsInputValidate::readChar("\n\nAre you sure you want to delete this client (y/n)? ");

		if (confirm == 'y' || confirm == 'Y') {
			if (client1.Delete()) {
				std::cout << "\n\nClient deleted successfully!\n";
			}
			else {
				std::cout << "\n\nError client in not found.\n";
			}
		}
	}
};

