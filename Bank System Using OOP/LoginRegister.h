#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"

class LoginRegister
{
public:
	LoginRegister(std::string date_and_time, std::string username, std::string password, int permissions) {
		_date_and_time = date_and_time;
		_username = username;
		_password = password;
		_permissions = permissions;
	}

	std::string getDateAndTime() {
		return _date_and_time;
	}

	std::string getUsername() {
		return _username;
	}

	std::string getPassword() {
		return _password;
	}

	int getPermissions() {
		return _permissions;
	}



	static std::vector <LoginRegister> getLoginsRegisterList() {
		return _loadLoginRegisterDataFromFile();
	}

private:
	std::string _date_and_time;
	std::string _username;
	std::string _password;
	int _permissions;
	
	static LoginRegister _convertLineToLoginRegisterObject(std::string line, std::string separator = "#//#") {
		std::vector <std::string> vLoginInfo = clsString::split(line, separator);

		// Decrypt the password 
		vLoginInfo.at(2) = clsUtil::decryptText(vLoginInfo.at(2), Encryption_Key);

		return LoginRegister(vLoginInfo.at(0), vLoginInfo.at(1), vLoginInfo.at(2), std::stoi(vLoginInfo.at(3)));
	}

	static std::vector <LoginRegister> _loadLoginRegisterDataFromFile() {

		std::vector <LoginRegister> vLoginRegister;

		std::fstream manageLoginRegister;
		manageLoginRegister.open(LOGIN_REGISTER_FILE_NAME, std::ios::in); // Read Mode

		if (manageLoginRegister.is_open()) {

			std::string line = "";
			while (std::getline(manageLoginRegister, line)) {
				vLoginRegister.push_back(_convertLineToLoginRegisterObject(line));
			}

			manageLoginRegister.close();
		}

		return vLoginRegister;
	}
};

