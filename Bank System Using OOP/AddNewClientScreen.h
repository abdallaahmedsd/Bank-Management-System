#pragma once
#include <iostream>
#include "Client.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "Screen.h"
#include "ClientCard.h"

class AddNewClientScreen : protected Screen
{
private: 

	static void _readClientInfo(Client& client) {

		client.firstName = clsInputValidate::readString("Enter first name: ");
		client.lastName = clsInputValidate::readString("Enter last name: ");
		client.email = clsInputValidate::readString("Enter email: ");
		client.phone = clsInputValidate::readString("Enter phone: ");
		client.PINCode = clsInputValidate::readString("Enter password: ");
		std::cout << "Enter balance: ";
		client.balance = clsInputValidate::readDoubleNumber();
	}

public:
	static void addNewClient() {
		if (!_checkAccessRights(User::enPermissions::p_add_new_client)) {
			return;
		}
		_drawScreenHeader("\t\t\t\t\t\t\tAdd New Client");

		std::string accountNumber = clsInputValidate::readString("\nPlease enter an account number: ");

		while (Client::isClientExist(accountNumber)) {
			std::cout << "\nAccount number [" << accountNumber << "] is already exist, ";
			accountNumber = clsInputValidate::readString("choose another one: ");
		}

		Client client1 = Client::getAddNewClientObject(accountNumber);

		_readClientInfo(client1);

		Client::enSaveResult saveResult;
		saveResult = client1.save();

		switch (saveResult)
		{
		case Client::save_succeeded:
			std::cout << "\n\nAccount added successfully!\n";
			ClientCard::printClientInfo(client1);
			break;
		case Client::save_faild_account_num_exist:
			std::cout << "\nError account number is already exist!";
			break;
		}
	}

};

