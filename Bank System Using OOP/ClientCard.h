#pragma once
#include <iostream>
#include "Client.h"

class ClientCard
{
public:
	static void printClientInfo(Client& client) {
		std::cout << "\nClient Card:\n";
		std::cout << "-----------------------------------------\n";
		std::cout << "First name : " << client.firstName << std::endl;
		std::cout << "Lst name   : " << client.lastName << std::endl;
		std::cout << "Full name  : " << client.getFullName() << std::endl;
		std::cout << "Email      : " << client.email << std::endl;
		std::cout << "Phone      : " << client.phone << std::endl;
		std::cout << "Acc. Number: " << client.getAccountNumber() << std::endl;
		std::cout << "Password   : " << client.PINCode << std::endl;
		std::cout << "Balance    : " << client.balance << std::endl;
		std::cout << "-----------------------------------------\n";
	}
};

