#pragma once
#include <iostream>
#include "Client.h"
#include "clsInputValidate.h"
#include "Screen.h"

class TransferScreen : protected Screen
{
private: 
	static void _printClientCard(Client& client) {
		std::cout << "\nClient Card:";
		std::cout << "\n-----------------------------------";
		std::cout << "\nFull Name   : " << client.getFullName();
		std::cout << "\nAcc. Number : " << client.getAccountNumber();
		std::cout << "\nAcc. Balance: " << client.getAccountBalance();
		std::cout << "\n-----------------------------------\n";
	}

	static Client _getSenderClient() {
		std::string accountNumber = clsInputValidate::readString("\nPlease enter an account number to transfer from: ");

		while (!Client::isClientExist(accountNumber)) {
			std::cout << "\nClient with account number [" << accountNumber << "] does not exist";
			accountNumber = clsInputValidate::readString("\nPlease enter a valid account number: ");
		}

		Client client = Client::find(accountNumber);

		return client;
	}

	static Client _getReceiverClient() {
		std::string accountNumber = clsInputValidate::readString("\nPlease enter an account number to transfer to: ");

		while (!Client::isClientExist(accountNumber)) {
			std::cout << "\nClient with account number [" << accountNumber << "] does not exist";
			accountNumber = clsInputValidate::readString("\nPlease enter a valid account number: ");
		}

		Client client = Client::find(accountNumber);

		return client;
	}

public:
	static void showTransferScreen() {
		_drawScreenHeader("\t\t\t\t\t\t\tTransfer Screen");

		Client senderClient = _getSenderClient();
		_printClientCard(senderClient);

		Client receiverClient = _getReceiverClient();
		_printClientCard(receiverClient);

		double amount = 0;
		do {
			std::cout << "\nEnter Transfer Amount: ";
			amount = clsInputValidate::readDoubleNumber();
			if (amount > senderClient.balance) {
				std::cout << "\nAmount exceeds your balance, you can transfer up to " << senderClient.balance;
			}
		} while (amount > senderClient.balance);

		char confirm = clsInputValidate::readChar("\n\nAre you sure you want to complete this transaction (y/n)? ");

		if (confirm == 'y' || confirm == 'Y') {

			if (senderClient.transfer(amount, receiverClient, Current_User.username)) {
				std::cout << "\n\nTransfer done successfully!\n";
				_printClientCard(senderClient);
				_printClientCard(receiverClient);

				// Save the transaction into a file
				//TransferLog::registerTransferLog(senderClient, receiverClient, amount, Current_User.username);
			}
		}

	}
};

