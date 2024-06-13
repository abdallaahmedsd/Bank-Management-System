#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "Person.h"
#include "clsDate.h"
#include "clsUtil.h"

const std::string USERS_FILE_NAME{ "users.txt" };
const std::string LOGIN_REGISTER_FILE_NAME = "login_register.txt";
const short Encryption_Key = 3;

class User : public Person
{
private:
	enum enMode { empty_Mode, update_Mode, add_New_Mode };
	enMode _mode;
	std::string _username;
	std::string _password;
	int _permissions;
	bool _markForDelete = false;
	

	static User _convertLineToUserObject(std::string line, std::string separator = "#//#") {

		std::vector <std::string> vUserData = clsString::split(line, separator);
		
		// Decrypt the password 
		vUserData.at(5) = clsUtil::decryptText(vUserData.at(5), Encryption_Key);

		return User(enMode::update_Mode, vUserData.at(0), vUserData.at(1), vUserData.at(2), vUserData.at(3), vUserData.at(4), vUserData.at(5), stoi(vUserData.at(6)));
	}

	static std::string _convertUserObjectToLine(User& user, std::string separator = "#//#") {

		// Encrypt the password before saving it to file
		user.password = clsUtil::encryptText(user.password, Encryption_Key);
			
		std::string st = "";
		st = user.firstName + separator
			+ user.lastName + separator
			+ user.email + separator
			+ user.phone + separator
			+ user.getUsername() + separator
			+ user.password + separator
			+ std::to_string(user.permissions);

		return st;
	}

	static User _getEmptyUserObject() {
		return User(enMode::empty_Mode, "", "", "", "", "", "", 0);
	}

	static void _saveUsersDataToFile(std::vector <User>& vUsers) {

		std::fstream manageUsers;
		manageUsers.open(USERS_FILE_NAME, std::ios::out); // Overwrite Mode

		if (manageUsers.is_open()) {

			for (User& user : vUsers) {
				if (user._markForDelete == false) {
					manageUsers << _convertUserObjectToLine(user) << std::endl;
				}
			}

			manageUsers.close();
		}
	}

	static std::vector <User> _loadUsersDataFromFile() {

		std::vector <User> vUsers;

		std::fstream manageUsers;
		manageUsers.open(USERS_FILE_NAME, std::ios::in); // Read Mode

		if (manageUsers.is_open()) {

			std::string line = "";
			User user = find("");
			while (std::getline(manageUsers, line)) {
				user = _convertLineToUserObject(line);
				vUsers.push_back(user);
			}

			manageUsers.close();
		}

		return vUsers;
	}

	void _update() {

		std::vector <User> vUsers = _loadUsersDataFromFile();

		for (User& user : vUsers) {
			if (user.getUsername() == this->getUsername()) {
				user = *this;
				break;
			}
		}

		_saveUsersDataToFile(vUsers);
	}

	void _addDataLineToFile(std::string line) {
		std::fstream manageUsers;
		manageUsers.open(USERS_FILE_NAME, std::ios::out | std::ios::app); // Write and Append Mode

		if (manageUsers.is_open()) {
			manageUsers << line << std::endl;
			manageUsers.close();
		}
	}

	void _addNew() {
		_addDataLineToFile(_convertUserObjectToLine(*this));
	}

	std::string _prepareLoginRecord(std::string separator = "#//#") {

		std::string loginRecord = "";
		loginRecord = clsDate::getSystemDateTimeString() + separator
			+ username + separator + clsUtil::encryptText(password, Encryption_Key) + separator + std::to_string(permissions);

		return loginRecord;
	}

public:
	User(enMode mode, std::string firstName, std::string lastName, std::string email, std::string phone, std::string username, std::string password, int permissions)
		: Person(firstName, lastName, email, phone) {
		_mode = mode;
		_username = username;
		_password = password;
		_permissions = permissions;
	}

	void setUsername(std::string username) {
		_username = username;
	}
	std::string getUsername() {
		return _username;
	}
	__declspec(property(get = getUsername, put = setUsername)) std::string username;

	void setPassword(std::string password) {
		_password = password;
	}
	std::string getPassword() {
		return _password;
	}
	__declspec(property(get = getPassword, put = setPassword)) std::string password;

	void setPermissions(int permissions) {
		_permissions = permissions;
	}
	int getPermissions() {
		return _permissions;
	}
	__declspec(property(get = getPermissions, put = setPermissions)) int permissions;

	bool isEmpty() {
		return (_mode == enMode::empty_Mode);
	}

	static User find(std::string username) {

		std::fstream manageUsers;
		manageUsers.open(USERS_FILE_NAME, std::ios::in); // Read Mode

		if (manageUsers.is_open()) {

			std::string line = "";

			while (std::getline(manageUsers, line)) {
				User user = _convertLineToUserObject(line);
				if (user.getUsername() == username) {
					manageUsers.close();
					return user;
				}
			}
		}

		return _getEmptyUserObject();
	}

	static User find(std::string username, std::string password) {

		std::fstream manageUsers;
		manageUsers.open(USERS_FILE_NAME, std::ios::in); // Read Mode

		if (manageUsers.is_open()) {

			std::string line = "";

			while (std::getline(manageUsers, line)) {
				User user = _convertLineToUserObject(line);
				if (user.getUsername() == username && user.password == password) {
					manageUsers.close();
					return user;
				}
			}
		}

		return _getEmptyUserObject();
	}

	static User getAddNewUserObject(std::string username) {
		return User(enMode::add_New_Mode, "", "", "", "", username, "", 0);
	}

	static std::vector <User> getUsersList() {
		return _loadUsersDataFromFile();
	}
	 
	static bool isUserExist(std::string username) {
		User user = find(username);
		return !user.isEmpty();
	}

	enum enSaveResult { save_faild_empty_object, save_succeeded, save_faild_account_num_exist };

	enSaveResult save() {
		switch (_mode)
		{
		case User::empty_Mode:

			if (isEmpty()) {
				return enSaveResult::save_faild_empty_object;
			}

		case User::update_Mode:

			_update();
			return enSaveResult::save_succeeded;

		case User::add_New_Mode:

			if (isUserExist(_username)) {
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

		std::vector <User> vUsers = _loadUsersDataFromFile();

		for (User& user : vUsers) {
			if (user.getUsername() == getUsername()) {
				user._markForDelete = true;
				_saveUsersDataToFile(vUsers);
				*this = _getEmptyUserObject();
				return true;
			}
		}

		return false;
	}

	enum enPermissions {
		p_all = -1,
		p_show_clients_list = 1,
		p_add_new_client = 2, 
		p_delete_client = 4,
		p_update_client = 8,
		p_find_client = 16,
		p_transactions = 32,
		p_manage_users = 64,
		p_show_logins_list = 128,
		p_currency_exchange = 256
	};

	bool checkAccessPermissions(enPermissions permissions) {

		/*if (this->permissions == enPermissions::p_all)
			return true;
		if ((this->permissions & permissions) == permissions)
			return true;
		else
			return false;*/

		return ((this->permissions == enPermissions::p_all) || ((this->permissions & permissions) == permissions));
	}

	void registerLogin() {

		std::string userRecord = _prepareLoginRecord();

		std::fstream manageUsers;
		manageUsers.open(LOGIN_REGISTER_FILE_NAME, std::ios::out | std::ios::app); // Write Mode

		if (manageUsers.is_open()) {
			manageUsers << userRecord << std::endl;
			manageUsers.close();
		}
	}

};