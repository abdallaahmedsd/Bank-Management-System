#pragma once
#include <iostream>
#include "Client.h"
#include "clsInputValidate.h"
#include "Screen.h"
#include "ClientCard.h"

class DepositScreen : Screen
{
public:
	static void deposit() {

		_drawScreenHeader("\t\t\t\t\t\t\tDeposit Screen");

		std::string accountNumber = clsInputValidate::readString("\nPlease enter the account number: ");

		while (!Client::isClientExist(accountNumber)) {
			std::cout << "\nClient with account number [" << accountNumber << "] does not exist";
			accountNumber = clsInputValidate::readString("\nPlease enter a valid account number: ");
		}

		Client client = Client::find(accountNumber);
		
		ClientCard::printClientInfo(client);

		double amount = 0;
		std::cout << "\n\nPlease enter the deposit amount: ";
		amount = clsInputValidate::readDoubleNumber();

		char confirm = clsInputValidate::readChar("\n\nAre you sure you want complete this transaction (y/n)? ");

		if (confirm == 'y' || confirm == 'Y') {
			client.deposit(amount);
			std::cout << "\n\nAdded Successfully, your new balance is " << client.balance << "\n";
		}
	}
};

