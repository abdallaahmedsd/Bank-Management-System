#pragma once
#include <iostream>
#include <iomanip>
#include "Client.h"
#include "clsInputValidate.h"
#include "Screen.h"

class TotalBalancesScreen : Screen
{

private:
	static void _printClientInfoInLine(Client& client) {
		std::cout << clsUtil::tabs(3) << "| " << std::setw(20) << std::left << client.getAccountNumber();
		std::cout << "| " << std::setw(30) << std::left << client.getFullName();
		std::cout << "| " << std::setw(20) << std::left << client.getAccountBalance() << std::endl;
	}

public:
	static void totalBalances() {

		std::vector <Client> vClients = Client::getClientsList();

		std::string title = "\t\t\t\t\t\t    Total Balances Screen";
		std::string subTitle = "\t\t\t\t\t\t\t" + std::to_string(vClients.size()) + " Balances";

		_drawScreenHeader(title, subTitle);

		std::cout << clsUtil::tabs(3) << "-------------------------------------------------------------------------\n\n";
		std::cout << clsUtil::tabs(3) << "| " << std::setw(20) << std::left << "Account Number";
		std::cout << "| " << std::setw(30) << std::left << "Client Name";
		std::cout << "| " << std::setw(20) << std::left << "Account Balance" << std::endl;
		std::cout << "\n" << clsUtil::tabs(3) << "-------------------------------------------------------------------------\n";


		if (vClients.size() == 0) {
			std::cout << "\n" << clsUtil::tabs(4) << "You have no available clients in the system yet!\n\n";
		}
		else {
			for (Client& client : vClients) {
				_printClientInfoInLine(client);
			}
		}
		std::cout << clsUtil::tabs(3) << "-------------------------------------------------------------------------\n\n";

		double totalBalances = Client::getTotalBalances();
		std::cout << clsUtil::tabs(6) << "Total Balances = " << totalBalances << std::endl;
		std::cout << clsUtil::tabs(5) << "(" << clsString::trim(clsUtil::NumberToText(totalBalances)) << ")" << std::endl;

	}

};

