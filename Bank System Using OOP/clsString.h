#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

class clsString
{
private:
	std::string _value;

public:
	clsString() {
		_value = "";
	}

	clsString(std::string value) {
		_value = value;
	}

	void setValue(std::string value) {
		_value = value;
	}
	std::string getValue() {
		return _value;
	}
	__declspec(property(get = getValue, put = setValue)) std::string value;

	static short length(std::string st) {
		return st.length();
	}
	short length() {
		return _value.length();
	}

	static short countWords(std::string st) {
		std::string word = "", delimiter = " ";
		short pos{ 0 }, counter{ 0 };

		while ((pos = st.find(delimiter)) != std::string::npos) {
			word = st.substr(0, pos);

			if (word != "")
				counter++;

			st.erase(0, pos + delimiter.length());
		}

		if (st != "")
			counter++;

		return counter;
	}
	short countWords() {
		return countWords(_value);
	}

	static void printFirstLetterOfEachWord(std::string st) {
		bool isFirstLetter = true;

		for (int i = 0; i < st.length(); i++) {
			if (st.at(i) != ' ' && isFirstLetter) {
				std::cout << st.at(i) << std::endl;
			}

			isFirstLetter = st.at(i) == ' ' ? true : false;
		}
	}
	void printFirstLetterOfEachWord() {
		printFirstLetterOfEachWord(_value);
	}

	static std::string upperFirstLetterOfEachWord(std::string st) {
		bool isFirstLetter = true;

		for (int i = 0; i < st.length(); i++) {
			if (st.at(i) != ' ' && isFirstLetter) {
				if (islower(st.at(i)))
					st.at(i) = toupper(st.at(i));
			}

			isFirstLetter = st.at(i) == ' ' ? true : false;
		}
		return st;
	}
	void upperFirstLetterOfEachWord() {
		_value = upperFirstLetterOfEachWord(_value);
	}

	static std::string lowerFirstLetterOfEachWord(std::string st) {
		bool isFirstLetter = true;

		for (int i = 0; i < st.length(); i++) {
			if (st.at(i) != ' ' && isFirstLetter) {
				if (isupper(st.at(i)))
					st.at(i) = tolower(st.at(i));
			}

			isFirstLetter = st.at(i) == ' ' ? true : false;
		}
		return st;
	}
	void lowerFirstLetterOfEachWord() {
		_value = lowerFirstLetterOfEachWord(_value);
	}

	static std::string lowerString(std::string st) {
		for (int i = 0; i < st.length(); i++) {
			if (st.at(i) != ' ') {
				if (isupper(st.at(i)))
					st.at(i) = tolower(st.at(i));
			}
		}
		return st;
	}
	void lowerString() {
		_value = lowerString(_value);
	}

	static std::string upperString(std::string st) {
		for (int i = 0; i < st.length(); i++) {
			if (st.at(i) != ' ') {
				if (islower(st.at(i)))
					st.at(i) = toupper(st.at(i));
			}
		}
		return st;
	}
	void upperString() {
		_value = upperString(_value);
	}

	static std::string invertStringLetters(std::string st) {
		for (int i = 0; i < st.length(); i++) {
			st.at(i) = invertLetterCase(st.at(i));
		}
		return st;
	}
	void invertStringLetters() {
		_value = invertStringLetters(_value);
	}

	static short countSmallLetters(std::string st) {
		short smalls{ 0 };

		for (int i = 0; i < st.length(); i++) {

			if (islower(st.at(i)))
				smalls++;
		}
		return smalls;
	}
	short countSmallLetters() {
		return countSmallLetters(_value);
	}

	static short countCapitalLetters(std::string st) {
		short capitals{ 0 };

		for (int i = 0; i < st.length(); i++) {

			if (isupper(st.at(i)))
				capitals++;
		}
		return capitals;
	}
	short countCapitalLetters() {
		return countCapitalLetters(_value);
	}

	enum enWhatToCount { capitalLetters, smallLetters, all };
	static short countCharacters(std::string st, enWhatToCount whatToCount = enWhatToCount::all) {

		if (whatToCount == enWhatToCount::all)
			return st.length();

		short count{ 0 };

		for (int i = 0; i < st.length(); i++) {

			if (whatToCount == enWhatToCount::smallLetters && islower(st.at(i)))
				count++;
			else if (whatToCount == enWhatToCount::capitalLetters && isupper(st.at(i)))
				count++;
		}

		return count;
	}
	short countCharacters(enWhatToCount whatToCount = enWhatToCount::all) {
		return countCharacters(_value, whatToCount);
	}

	static short countCharacterRepetition(std::string st, char letter, bool matchCase = true) {
		short countRepetition{ 0 };
		for (int i = 0; i < st.length(); i++) {

			if (matchCase) {
				if (st.at(i) == letter) {
					countRepetition++;
				}
			}
			else {
				if (st.at(i) == toupper(letter) || st.at(i) == tolower(letter))
					countRepetition++;
			}
		}

		return countRepetition;
	}
	short countCharacterRepetition(char letter, bool matchCase = true) {
		return countCharacterRepetition(_value, letter, matchCase);
	}

	static bool isVowel(char letter) {
		letter = tolower(letter);
		return (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u');
	}

	static short countVowelLetters(std::string st) {
		short counter{ 0 };

		for (short i = 0; i < st.length(); i++) {

			if (isVowel(st.at(i)))
				counter++;
		}
		return counter;
	}
	short countVowelLetters() {
		return countVowelLetters(_value);
	}

	static char invertLetterCase(char letter) {
		return (islower(letter)) ? letter = toupper(letter) : letter = tolower(letter);
	}

	static std::vector <std::string> split(std::string st, std::string delimiter = " ") {
		std::vector <std::string> vWords;
		short pos{ 0 };
		std::string word = "";

		while ((pos = st.find(delimiter)) != std::string::npos) {

			word = st.substr(0, pos);

			if (word != "") {
				vWords.push_back(word);
			}

			st.erase(0, pos + delimiter.length());
		}

		if (st != "") {
			vWords.push_back(st);
		}

		return vWords;

	}
	std::vector <std::string> split() {
		return split(_value);
	}

	static std::string trimLeft(std::string text) {

		for (int i = 0; i < text.length(); i++) {

			if (text[i] != ' ')
				return text.substr(i);
		}
	}
	void trimLeft() {
		_value = trimLeft(_value);
	}

	static std::string trimRight(std::string text) {

		for (int i = text.length() - 1; i >= 0; i--) {

			if (text[i] != ' ')
				return text.substr(0, i + 1);

		}
	}
	void trimRight() {
		_value = trimRight(_value);
	}

	static std::string trim(std::string text) {
		return trimRight(trimLeft(text));
	}
	void trim() {
		_value = trim(_value);
	}

	static std::string joinString(std::vector <std::string>& vWords, std::string delimiter = " ") {

		std::string newString = "";

		for (std::string& word : vWords) {
			newString.append(word + delimiter);
		}

		return newString.substr(0, newString.length() - delimiter.length());
	}
	static std::string joinString(std::string arr[], int arrLength, std::string delimiter = " ") {

		std::string join = "";

		for (int i = 0; i < arrLength; i++) {

			join += arr[i] + delimiter;

		}

		return join.substr(0, join.length() - delimiter.length());
	}

	static std::string reverse(std::string st) {

		std::string reversedSting = "", delimiter = " ";

		std::vector <std::string> vWords = split(st, delimiter);
		std::vector<std::string>::iterator iter;

		iter = vWords.end();

		while (iter != vWords.begin()) {
			--iter;
			reversedSting += *iter + delimiter;
		}

		return reversedSting.substr(0, reversedSting.length() - 1);
	}
	void reverse() {
		_value = reverse(_value);
	}

	static bool areSameWords(std::string word1, std::string word2, bool matchCase = true) {

		if (!matchCase) {
			word1 = lowerString(word1);
			word2 = lowerString(word2);
		}

		return (word1 == word2);
	}
	static std::string replaceString(std::string st, std::string wordToReplace, std::string replaceTo, bool matchCase = true) {

		std::string newString = "", delimiter = " ";

		std::vector <std::string> vWords = split(st);

		for (std::string& word : vWords) {

			if (areSameWords(word, wordToReplace, matchCase)) {
				word = replaceTo;
			}

			newString += word + delimiter;
		}

		return newString.substr(0, newString.length() - 1);
	}
	void replaceString(std::string wordToReplace, std::string replaceTo, bool matchCase = true) {
		_value = replaceString(_value, wordToReplace, replaceTo, matchCase);
	}

	static std::string removePunctuations(std::string st) {
		std::string st2 = "";
		for (int i = 0; i < st.length(); i++) {
			if (!ispunct(st[i])) {
				st2 += st[i];
			}
		}
		return st2;
	}
	std::string removePunctuations() {
		return removePunctuations(_value);
	}
};
