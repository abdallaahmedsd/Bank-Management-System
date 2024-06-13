#pragma once
#include <iostream>
#include "Client.h"
#include "clsInputValidate.h"
#include "ClientCard.h"
#include "Screen.h"

class UpdateClientScreen : protected Screen
{
private:
	static void _changeClientInfo(Client& client) {

		std::cout << "\nUpdate Client Info:";
		std::cout << "\n----------------------------";

		char confirm = 'n';

		confirm = clsInputValidate::readChar("\nDo you want to change the first name (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			client.firstName = clsInputValidate::readString("Enter first name: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the last name (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			client.lastName = clsInputValidate::readString("Enter last name: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the email (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			client.email = clsInputValidate::readString("Enter email: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the phone (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			client.phone = clsInputValidate::readString("Enter phone: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the PINCode (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			client.PINCode = clsInputValidate::readString("Enter PINCode: ");
		}

		confirm = clsInputValidate::readChar("\nDo you want to change the balance (y/n)? ");
		if (confirm == 'y' || confirm == 'Y') {
			std::cout << "Enter balance: ";
			client.balance = clsInputValidate::readDoubleNumber();
		}
	}

public:
	static void updateClient() {

		if (!_checkAccessRights(User::enPermissions::p_update_client)) {
			return;
		}

		_drawScreenHeader("\t\t\t\t\t\t    Update Client Screen");

		std::string accountNumber = clsInputValidate::readString("\nPlease enter an account number: ");
		while (!Client::isClientExist(accountNumber)) {
			accountNumber = clsInputValidate::readString("\nAccount number is not found, please enter again: ");
		}

		Client client1 = Client::find(accountNumber);
		ClientCard::printClientInfo(client1);

		char confirm = clsInputValidate::readChar("\nAre you sure you want to update this client (y/n)? ");

		if (confirm == 'y' || confirm == 'Y') {

			_changeClientInfo(client1);
			ClientCard::printClientInfo(client1);

			Client::enSaveResult saveResult;
			saveResult = client1.save();

			switch (saveResult)
			{
			case Client::save_faild_empty_object:
				std::cout << "\n\nError! account was not saved because it's empty.\n";
				break;
			case Client::save_succeeded:
				std::cout << "\n\nAccount updated successfully!\n";
				break;
			}
		}
	}
};

