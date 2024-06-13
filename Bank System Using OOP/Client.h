#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Person.h"
#include "clsString.h"
#include "clsUtil.h"
#include "Global.h"

const std::string CLIENTS_FILE_NAME{ "clients.txt" };
const std::string TRANSFERS_LOG__FILE_NAME = "transfers_log.txt";

class Client : public Person
{
private:
	enum enMode { empty_Mode, update_Mode, add_New_Mode };
	enMode _mode;
	std::string _accountNumber;
	std::string _PINCode;
	double _accountBalance;
	bool _markForDelete = false;

	struct stTransferLog;
	static stTransferLog _convertLineTransferLogToRecord(std::string line, std::string separator = "#//#") {
		std::vector <std::string> vTransferLogInfo = clsString::split(line, separator);

		stTransferLog transferLogRecord;

		transferLogRecord.dateAndTime = vTransferLogInfo.at(0);
		transferLogRecord.sourceAccNumber = vTransferLogInfo.at(1);
		transferLogRecord.destinationAccNumber = vTransferLogInfo.at(2);
		transferLogRecord.amount = std::stod(vTransferLogInfo.at(3));
		transferLogRecord.sourceAccBalance = std::stod(vTransferLogInfo.at(4));
		transferLogRecord.destinationAccBalance = std::stod(vTransferLogInfo.at(5));
		transferLogRecord.username = vTransferLogInfo.at(6);

		return transferLogRecord;
	}

	static Client _convertLineToClientObject(std::string line, std::string separator = "#//#") {

		std::vector <std::string> vClientData = clsString::split(line, separator);

		// Decrypt the password 
		vClientData.at(5) = clsUtil::decryptText(vClientData.at(5), Encryption_Key);

		return Client(enMode::update_Mode, vClientData.at(0), vClientData.at(1), vClientData.at(2), vClientData.at(3), vClientData.at(4), vClientData.at(5), stod(vClientData.at(6)));
	}

	static std::string _convertClientObjectToLine(Client client, std::string separator = "#//#") {

		// Encrypt the password before saving it into the database
		client.PINCode = clsUtil::encryptText(client.PINCode, Encryption_Key);

		std::string st = "";
		st = client.firstName + separator
			+ client.lastName + separator
			+ client.email + separator
			+ client.phone + separator
			+ client.getAccountNumber() + separator
			+ client.PINCode + separator 
			+ std::to_string(client.balance);

		return st;
	}

	static Client _getEmptyClientObject() {
		return Client(enMode::empty_Mode, "", "", "", "", "", "", 0);
	}

	static void _saveClientsDataToFile(std::vector <Client>& vClients) {

		std::fstream manageClients;
		manageClients.open(CLIENTS_FILE_NAME, std::ios::out); // Overwrite Mode

		if (manageClients.is_open()) {

			for (Client& client : vClients) {
				if (client._markForDelete == false) {
					manageClients << _convertClientObjectToLine(client) << std::endl;
				}
			}

			manageClients.close();
		}
	}

	static std::vector <Client> _loadClientsDataFromFile() {

		std::vector <Client> vClients;

		std::fstream manageClients;
		manageClients.open(CLIENTS_FILE_NAME, std::ios::in); // Read Mode

		if (manageClients.is_open()) {

			std::string line = "";


			Client client = Client::find("");

			while (std::getline(manageClients, line)) {
				client = _convertLineToClientObject(line);
				vClients.push_back(client);
			}

			manageClients.close();
		}

		return vClients;
	}

	void _update() {

		std::vector <Client> vClients = _loadClientsDataFromFile();

		for (Client& client : vClients) {
			if (client.getAccountNumber() == this->getAccountNumber()) {
				client = *this;
				break;
			}
		}

		_saveClientsDataToFile(vClients);
	}

	void _addDataLineToFile(std::string line) {
		std::fstream manageClients;
		manageClients.open(CLIENTS_FILE_NAME, std::ios::out | std::ios::app); // Read Mode

		if (manageClients.is_open()) {
			manageClients << line << std::endl;
			manageClients.close();
		}
	}

	void _addNew() {
		_addDataLineToFile(_convertClientObjectToLine(*this));
	}

	std::string _prepareTransferLogRecord(double amount, Client& receiverClient, std::string username, std::string separator = "#//#") {

		std::string transferRecord = "";

		transferRecord = clsDate::getSystemDateTimeString() + separator
			+ this->getAccountNumber() + separator
			+ receiverClient.getAccountNumber() + separator
			+ std::to_string(amount) + separator
			+ std::to_string(this->getAccountBalance()) + separator
			+ std::to_string(receiverClient.getAccountBalance()) + separator + username;

		return transferRecord;
	}

	void _registerTransferLog(double amount, Client& receiverClient, std::string username) {

		std::string userRecord = _prepareTransferLogRecord(amount, receiverClient, username);

		std::fstream manageUsers;
		manageUsers.open(TRANSFERS_LOG__FILE_NAME, std::ios::out | std::ios::app); // Write Mode

		if (manageUsers.is_open()) {
			manageUsers << userRecord << std::endl;
			manageUsers.close();
		}
	}


public:

	Client(enMode mode, std::string firstName, std::string lastName, std::string email, std::string phone, std::string accountNumber, std::string PINCode, double accountBalance)
		: Person(firstName, lastName, email, phone) {
		_mode = mode;
		_accountNumber = accountNumber;
		_PINCode = PINCode;
		_accountBalance = accountBalance;
	}

	void setAccountBalance(double amount) {
		_accountBalance = amount;
	}
	double getAccountBalance() {
		return _accountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) double balance;

	void setPINCode(std::string PINCode) {
		_PINCode = PINCode;
	}
	std::string getPINCode() {
		return _PINCode;
	}
	__declspec(property(get = getPINCode, put = setPINCode)) std::string PINCode;

	// The accountNumber data member has no set member function cause it's read only
	std::string getAccountNumber() {
		return _accountNumber;
	}

	bool isEmpty() {
		return (_mode == enMode::empty_Mode);
	}

	static Client find(std::string accountNumber) {

		std::fstream manageClients;
		manageClients.open(CLIENTS_FILE_NAME, std::ios::in); // Read Mode

		if (manageClients.is_open()) {

			std::string line = "";

			while (std::getline(manageClients, line)) {
				Client client = _convertLineToClientObject(line);
				if (client.getAccountNumber() == accountNumber) {
					manageClients.close();
					return client;
				}
			}
		}

		return _getEmptyClientObject();
	}

	static Client find(std::string accountNumber, std::string PINCode) {

		std::fstream manageClients;
		manageClients.open(CLIENTS_FILE_NAME, std::ios::in); // Read Mode

		if (manageClients.is_open()) {

			std::string line = "";

			while (std::getline(manageClients, line)) {
				Client client = _convertLineToClientObject(line);
				if (client.getAccountNumber() == accountNumber && client.PINCode == PINCode) {
					manageClients.close();
					return client;
				}
			}
		}

		return _getEmptyClientObject();
	}

	static Client getAddNewClientObject(std::string accountNumber) {
		return Client(enMode::add_New_Mode, "", "", "", "", accountNumber, "", 0);
	}

	static bool isClientExist(std::string accountNumber) {
		Client client = find(accountNumber);
		return !client.isEmpty();
	}

	enum enSaveResult { save_faild_empty_object, save_succeeded, save_faild_account_num_exist };

	enSaveResult save() {
		switch (_mode)
		{
		case Client::empty_Mode:

			if (isEmpty()) {
				return enSaveResult::save_faild_empty_object;
			}

		case Client::update_Mode:

			_update();
			return enSaveResult::save_succeeded;

		case Client::add_New_Mode:

			if (isClientExist(_accountNumber)) {
				return enSaveResult::save_faild_account_num_exist;
			}
			else {
				_addNew();

				_mode = enMode::update_Mode;
				return enSaveResult::save_succeeded;
			}
		}
	}

	bool Delete() {

		std::vector <Client> vClients = _loadClientsDataFromFile();

		for (Client& client : vClients) {
			if (client.getAccountNumber() == getAccountNumber()) {
				client._markForDelete = true;
				_saveClientsDataToFile(vClients);
				*this = _getEmptyClientObject();
				return true;
			}
		}

		return false;
	}

	void deposit(double amount) {
		this->balance += amount;
		save();
	}

	bool withdraw(double amount) {
		if (amount <= this->balance) {
			this->balance -= amount;
			save();
			return true;
		}

		return false;
	}

	bool transfer(double amount, Client& receiverClient, std::string username) {

		if (amount <= this->balance) {
			this->withdraw(amount);
			receiverClient.deposit(amount);
			_registerTransferLog(amount, receiverClient, username);
			return true;
		}

		return false;
	}

	static std::vector <Client> getClientsList() {
		return _loadClientsDataFromFile();
	}

	static double getTotalBalances() {

		std::vector <Client> vClients = _loadClientsDataFromFile();
		double total = 0;

		for (Client& client : vClients) {
			total += client.balance;
		}

		return total;
	}

	struct stTransferLog {
		std::string dateAndTime;
		std::string sourceAccNumber;
		std::string destinationAccNumber;
		std::string username;
		double amount;
		double sourceAccBalance;
		double destinationAccBalance;
	};

	static std::vector <stTransferLog> getTransferLogList() {
		std::vector <stTransferLog> vTransferLogs;

		std::fstream manageTransferLogs;
		manageTransferLogs.open(TRANSFERS_LOG__FILE_NAME, std::ios::in); // Read Mode

		if (manageTransferLogs.is_open()) {

			std::string line = "";
			while (std::getline(manageTransferLogs, line)) {
				vTransferLogs.push_back(_convertLineTransferLogToRecord(line));
			}

			manageTransferLogs.close();
		}

		return vTransferLogs;
	}
};

