#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "Screen.h"
#include "Client.h"
#include "clsUtil.h"

class TransferLogScreen : protected Screen
{
private:
	static void _printClientInfoInLine(Client::stTransferLog &transferLogInfo) {
		
		std::cout << clsUtil::tabs(1) << "| " << std::setw(30) << std::left << transferLogInfo.dateAndTime;
		std::cout << "| " << std::setw(8) << std::left << transferLogInfo.sourceAccNumber;
		std::cout << "| " << std::setw(8) << std::left << transferLogInfo.destinationAccNumber;
		std::cout << "| " << std::setw(12) << std::left << transferLogInfo.amount;
		std::cout << "| " << std::setw(12) << std::left << transferLogInfo.sourceAccBalance;
		std::cout << "| " << std::setw(12) << std::left << transferLogInfo.destinationAccBalance;
		std::cout << "| " << std::setw(15) << std::left << transferLogInfo.username << std::endl;
	}

public:
	static void showTransferLogScreen() {
		std::vector <Client::stTransferLog> vTransferLogs = Client::getTransferLogList();

		std::string title = "\t\t\t\t\t\tTransfer Log List Screen";
		std::string subTitle = "\t\t\t\t\t\t\t" + std::to_string(vTransferLogs.size()) + " Record(s)";

		_drawScreenHeader(title, subTitle);

		std::cout << clsUtil::tabs(1) << "---------------------------------------------------------------------------------------------------------\n\n";
		std::cout << clsUtil::tabs(1) << "| " << std::setw(30) << std::left << "Date/Time";
		std::cout << "| " << std::setw(8) << std::left << "s.Acc";
		std::cout << "| " << std::setw(8) << std::left << "d.Acc";
		std::cout << "| " << std::setw(12) << std::left << "Amount";
		std::cout << "| " << std::setw(12) << std::left << "s.Balance";
		std::cout << "| " << std::setw(12) << std::left << "d.Balance";
		std::cout << "| " << std::setw(15) << std::left << "Username" << std::endl;
		std::cout << "\n" << clsUtil::tabs(1) << "---------------------------------------------------------------------------------------------------------\n";
	
		if (vTransferLogs.size() == 0) {
			std::cout << "\n" << clsUtil::tabs(7) << "You have no transfer logs in the system!\n\n";
		}
		else {
			for (Client::stTransferLog& transferLog : vTransferLogs) {
				_printClientInfoInLine(transferLog);
			}
		}
		std::cout << clsUtil::tabs(1) << "---------------------------------------------------------------------------------------------------------\n";
	}



};

