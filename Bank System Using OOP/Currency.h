#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"

const std::string CURRENCIES_FILE_NAME = "currencies.txt";

class Currency
{
public:
	enum enMode { en_empty_mode, en_update_mode };

	Currency(enMode mode, std::string countryName, std::string currencyCode, std::string currencyName, float rate) {
		_mode = mode;
		_countryName = countryName;
		_currencyCode = currencyCode;
		_currencyName = currencyName;
		_rate = rate;
	}

	std::string getCurrencyCode() {
		return _currencyCode;
	}

	std::string getCurrencyName() {
		return _currencyName;
	}

	std::string getCountryName() {
		return _countryName;
	}

	float getRate() {
		return _rate;
	}

	void updateRate(float newRate) {
		_rate = newRate;
		_update();
	}

	bool isEmpty() {
		return (this->_mode == enMode::en_empty_mode);
	}

	static bool isCurrencyExist(std::string currencyCode) {
		Currency currency = findByCode(currencyCode);
		return (!currency.isEmpty());
	}

	static Currency findByCode(std::string currencyCode) {

		currencyCode = clsString::upperString(currencyCode);

		std::vector <Currency> vCurrencies = getCurrenciesList();

		for (Currency& currency : vCurrencies) {
			if (currency.getCurrencyCode() == currencyCode) {
				return currency;
			}
		}

		return _getEmptyCurrencyObject();
	}

	static Currency findByName(std::string countryName) {

		countryName = clsString::upperString(countryName);

		std::vector <Currency> vCurrencies = getCurrenciesList();

		for (Currency& currency : vCurrencies) {
			if (clsString::upperString(currency.getCountryName()) == countryName) {
				return currency;
			}
		}

		return _getEmptyCurrencyObject();
	}

	static std::vector <Currency> getCurrenciesList() {
		return _loadCurrenciesFromFile();
	}

	static float exchangeToDollar(float currencyRate, float amount) {
		return float(amount / currencyRate);
	}
	float exchangeToDollar(float amount) {
		return exchangeToDollar(this->_rate, amount);
	}

	static float exchangeFromDollar(float currencyRate, float amount) {
		return currencyRate * amount;
	}
	float exchangeFromDollar(float amount) {
		return exchangeFromDollar(this->_rate, amount);
	}

	static float exchange(float amount, Currency exchangeFrom, Currency exchangeTo) {
		if (exchangeFrom.getCurrencyCode() == "UDS") {
			return (exchangeFromDollar(exchangeTo.getRate(), amount));
		}
		else if (exchangeTo.getCurrencyCode() == "UDS") {
			return (exchangeToDollar(exchangeFrom.getRate(), amount));
		}
		else {
			float dollars = (exchangeToDollar(exchangeFrom.getRate(), amount));
			return (exchangeFromDollar(exchangeTo.getRate(), dollars));
		}
	}
	float exchange(float amount, Currency exchangeTo) {
		return exchange(amount, *this, exchangeTo);
	}


private:
	std::string _countryName;
	std::string _currencyName;
	std::string _currencyCode;
	float _rate;
	enMode _mode;

	static std::string _convertCurrencyObjectToLine(Currency &currency, std::string separator = "#//#") {
		
		std::string line = "";

		line = currency.getCountryName() + separator
			+ currency.getCurrencyCode() + separator
			+ currency.getCurrencyName() + separator
			+ std::to_string(currency.getRate());

		return line;
	}

	static Currency _convertLineToCurrencyObject(std::string line, std::string separator = "#//#") {

		std::vector <std::string> vCurrencyData = clsString::split(line, separator);

		return Currency(enMode::en_update_mode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], std::stof(vCurrencyData[3]));
	}

	static void _saveCurrenciesToFile(std::vector <Currency> &vCurrencies) {

		std::fstream manageCurrency;

		manageCurrency.open(CURRENCIES_FILE_NAME, std::ios::out); // Overwrite Mode

		if (manageCurrency.is_open()) {

			for (Currency& currency : vCurrencies) {
				manageCurrency << _convertCurrencyObjectToLine(currency) << std::endl;
			}

			manageCurrency.close();
		}
	}

	static std::vector <Currency> _loadCurrenciesFromFile() {

		std::vector <Currency> vCurrencies;

		std::fstream manageCurrencies;
		manageCurrencies.open(CURRENCIES_FILE_NAME, std::ios::in); // Read Mode

		if (manageCurrencies.is_open()) {
			std::string line = "";

			while (std::getline(manageCurrencies, line)) {
				vCurrencies.push_back(_convertLineToCurrencyObject(line));
			}

			manageCurrencies.close();
		}

		return vCurrencies;
	}

	void _update() {

		std::vector <Currency> vCurrencies = _loadCurrenciesFromFile();

		for (Currency& currency : vCurrencies) {
			if (currency.getCurrencyCode() == this->getCurrencyCode()) {
				currency = *this;
				break;
			}
		}

		_saveCurrenciesToFile(vCurrencies);
	}

	static Currency _getEmptyCurrencyObject() {
		return Currency(enMode::en_empty_mode, "", "", "", 0);
	}
};

