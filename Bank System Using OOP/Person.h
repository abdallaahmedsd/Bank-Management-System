#pragma once
#include <iostream>
#include "InterfaceCommunication.h"

class Person : public InterfaceCommunication
{
public:
	Person(std::string firstName, std::string lastName, std::string email, std::string phone) {
		_firstName = firstName;
		_lastName = lastName;
		_email = email;
		_phone = phone;
	}

	void setFirstName(std::string firstName) {
		_firstName = firstName;
	}

	void setLastName(std::string lastName) {
		_lastName = lastName;
	}

	void setEmail(std::string email) {
		_email = email;
	}

	void setPhone(std::string phone) {
		_phone = phone;
	}

	std::string getFirstName() {
		return _firstName;
	}

	std::string getLastName() {
		return _lastName;
	}

	std::string getEmail() {
		return _email;
	}

	std::string getPhone() {
		return _phone;
	}

	std::string getFullName() {
		return _firstName + " " + _lastName;
	}

	__declspec(property(get = getFirstName, put = setFirstName)) std::string firstName;
	__declspec(property(get = getLastName, put = setLastName)) std::string lastName;
	__declspec(property(get = getEmail, put = setEmail)) std::string email;
	__declspec(property(get = getPhone, put = setPhone)) std::string phone;

	void sendEmail(std::string title, std::string body) {

	}

	void sendSMS(std::string title, std::string body) {

	}

	void sendFax(std::string title, std::string body) {

	}

private:
	std::string _firstName;
	std::string _lastName;
	std::string _email;
	std::string _phone;
};