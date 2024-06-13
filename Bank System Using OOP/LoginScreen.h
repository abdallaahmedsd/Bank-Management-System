#pragma once
#include <iostream>
#include "User.h"
#include "Screen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "MainScreen.h"

class LoginScreen : protected Screen
{
private:
	static void _login() {

		short loginTrails = 0;
		bool loginFail = false;
		std::string username, password;

		do {
			if (loginFail) {
				loginTrails++;
				if (loginTrails == 3) {
					std::cout << "\nInvalid username/password!";
					std::cout << "\n\nYou've been locked after 3 failed trails\n";

					// This for the while loop in main function to stop showing the login screen
					Show_Login_Screen = false;
					std::system("color 47");
					return;
				}
				std::cout << "\nInvalid username/password!\n";
				std::cout << "You have " << 3 - loginTrails << " trails to login\n";


			}

			username = clsInputValidate::readString("\nEnter your username: ");
			password = clsInputValidate::readString("Enter your password: ");

			// The variable 'Current_User' comes from "Global library"
			Current_User = User::find(username, password);

			loginFail = Current_User.isEmpty();

		} while (loginFail);

		Current_User.registerLogin();
		MainScreen::showMainMenu();
	}

public:
	static void showLoginScreen() {
		std::system("color 0f");
		_drawScreenHeader("\t\t\t\t\t\t\tLogin Screen");
		_login();
	}
};

