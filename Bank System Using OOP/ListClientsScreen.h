#pragma once
#include <iostream>
#include <iomanip>
#include "Screen.h"
#include "Client.h"
#include "clsUtil.h"

class ListClientsScreen : protected Screen
{
private:
	static void _printClientInfoInLine(Client& client) {
		std::cout << clsUtil::tabs(1) << "| " << std::setw(15) << std::left << client.getAccountNumber();
		std::cout << "| " << std::setw(20) << std::left << client.getFullName();
		std::cout << "| " << std::setw(15) << std::left << client.getPhone();
		std::cout << "| " << std::setw(20) << std::left << client.getEmail();
		std::cout << "| " << std::setw(12) << std::left << client.getPINCode();
		std::cout << "| " << std::setw(17) << std::left << client.getAccountBalance() << std::endl;
	}


public:
	static void showClientsList() {

		if (!_checkAccessRights(User::enPermissions::p_show_clients_list)) {
			return;
		}

		std::vector <Client> vClients = Client::getClientsList();

		std::string title = "\t\t\t\t\t\t    List Clients Screen";
		std::string subTitle = "\t\t\t\t\t\t      " + std::to_string(vClients.size()) + " - Client(s)";

		_drawScreenHeader(title, subTitle);

		std::cout << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------------\n\n";
		std::cout << clsUtil::tabs(1) << "| " << std::setw(15) << std::left << "Account Number";
		std::cout << "| " << std::setw(20) << std::left << "Client Name";
		std::cout << "| " << std::setw(15) << std::left << "Phone Number";
		std::cout << "| " << std::setw(20) << std::left << "Client Email";
		std::cout << "| " << std::setw(12) << std::left << "Password";
		std::cout << "| " << std::setw(17) << std::left << "Account Balance" << std::endl;
		std::cout << "\n" << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------------\n";


		if (vClients.size() == 0) {
			std::cout << "\n" << clsUtil::tabs(7) << "You have no client in the system!\n\n";
		}
		else {
			for (Client& client : vClients) {
				_printClientInfoInLine(client);
			}
		}
		std::cout << clsUtil::tabs(1) << "-------------------------------------------------------------------------------------------------------------\n";

	}

};

