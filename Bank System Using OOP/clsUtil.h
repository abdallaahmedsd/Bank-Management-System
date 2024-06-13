#pragma once
#include <iostream>
#include <cmath>
#include "clsDate.h"

class clsUtil {
public:

	static void Srand() {
		srand((unsigned)time(NULL));
	}

	static int randomNumber(int from, int to) {
		int randomNumber = rand() % (to - from + 1) + from;
		return randomNumber;
	}

	enum enCharType { smallLetter = 1, cpitalLetter, digit, specialChar, mixChars };

	static char getRandomCharacter(enCharType charType) {

		if (charType == enCharType::mixChars) {
			charType = (enCharType)randomNumber(1, 3);
		}

		switch (charType)
		{
		case smallLetter:
			return char(randomNumber(97, 122));
		case cpitalLetter:
			return char(randomNumber(65, 90));
		case specialChar:
			return char(randomNumber(33, 47));
		case digit:
			return char(randomNumber(48, 57));
		default:
			return char(randomNumber(48, 57));
		}
	}

	static std::string generateWord(enCharType charType, short length) {
		std::string word = "";
		for (int i = 1; i <= length; i++) {
			word += getRandomCharacter(charType);
		}
		return word;
	}

	static std::string generateKey(enCharType charType) {
		std::string key = "";
		key = generateWord(charType, 4) + "-"
			+ generateWord(charType, 4) + "-"
			+ generateWord(charType, 4) + "-"
			+ generateWord(charType, 4);

		return key;
	}

	enum enIsPrime { prime, notPrime };

	static enIsPrime isPrime(int number) {
		int M = round(number / 2);
		if (number == 1)
			return enIsPrime::notPrime;
		for (int i = 2; i <= M; i++) {
			if (number % i == 0)
				return enIsPrime::notPrime;
		}
		return enIsPrime::prime;
	}

	static bool isPerfect(int number) {
		int sum = 0, M = 0;
		M = round(number / 2);
		for (int i = 1; i <= M; i++) {
			if (number % i == 0) {
				sum += i;
			}
		}
		return number == sum;
	}

	static int reverseNumber(int number) {
		int remainder = 0, reverse = 0;
		while (number > 0) {
			remainder = number % 10;
			number = number / 10;
			reverse = reverse * 10 + remainder;
		}
		return reverse;
	}

	static short countDigitRepetition(short digitToCheck, int mainNumber) {
		short remainder = 0, frequency = 0;
		while (mainNumber > 0) {
			remainder = mainNumber % 10;
			mainNumber /= 10;
			if (remainder == digitToCheck)
				frequency++;
		}
		return frequency;
	}

	static bool isPalindrome(int number) {
		return number == reverseNumber(number);
	}

	static std::string encryptText(std::string text, short EncryptionKey) {
		for (int i = 0; i < text.length(); i++) {
			text[i] = char(int(text[i] + EncryptionKey));
		}
		return text;
	}

	static std::string decryptText(std::string text, short EncryptionKey) {
		for (int i = 0; i < text.length(); i++) {
			text[i] = char(int(text[i] - EncryptionKey));
		}
		return text;
	}

	static short elementRepeated(int arr[100], int element, int arrayLength) {

		int elementRepeated = 0;
		for (int i = 0; i < arrayLength; i++) {
			if (arr[i] == element) {
				elementRepeated++;
			}
		}
		return elementRepeated;
	}

	static short elementRepeated(std::string arr[100], std::string element, int arrayLength) {

		int elementRepeated = 0;
		for (int i = 0; i < arrayLength; i++) {
			if (arr[i] == element) {
				elementRepeated++;
			}
		}
		return elementRepeated;
	}

	static int maxNumberInArray(int arr[100], int arrLength) {
		int maxNumber = 0;
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] > maxNumber)
				maxNumber = arr[i];
		}
		return maxNumber;
	}

	static int minNumberInArray(int arr[100], int arrLength) {
		int minNumber = arr[0];
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] < minNumber)
				minNumber = arr[i];
		}
		return minNumber;
	}

	static int sumArrayElements(int arr[100], int arrLength) {
		int sum = 0;
		for (int i = 0; i < arrLength; i++) {
			sum += arr[i];
		}
		return sum;
	}

	static float arrayAverage(int arr[100], int arrLength) {
		return (float)sumArrayElements(arr, arrLength) / arrLength;
	}

	static void swap(int& num1, int& num2) {
		int temp = 0;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void swap(double& num1, double& num2) {
		double temp = 0;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void swap(float& num1, float& num2) {
		float temp = 0;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void swap(std::string& st1, std::string& st2) {
		std::string temp = "";
		temp = st1;
		st1 = st2;
		st2 = temp;
	}

	static  void swap(clsDate& A, clsDate& B)
	{
		clsDate::swap(A, B);
	}

	static void shuffleArrayElements(int arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++)
			swap(arr[randomNumber(0, arrLength - 1)], arr[randomNumber(0, arrLength - 1)]);
	}

	static void shuffleArrayElements(std::string arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++)
			swap(arr[randomNumber(0, arrLength - 1)], arr[randomNumber(0, arrLength - 1)]);
	}

	static void reverseArray(int arr[100], int arrLength) {
		for (int i = 0; i < arrLength / 2; i++) {
			swap(arr[i], arr[arrLength - 1 - i]);
		}
	}

	static void reverseArray(std::string arr[100], int arrLength) {
		for (int i = 0; i < arrLength / 2; i++) {
			swap(arr[i], arr[arrLength - 1 - i]);
		}
	}

	static void fillArrayWithRandomNumbers(int arr1[100], int arrLength, int randomNumFrom, int randomNumTo) {
		for (int i = 0; i <= arrLength - 1; i++) {
			arr1[i] = randomNumber(randomNumFrom, randomNumTo);
		}
	}

	static void fillArrayWithKeys(std::string arr1[100], int arrLength, enCharType charType) {
		for (int i = 0; i <= arrLength - 1; i++) {
			arr1[i] = generateKey(charType);
		}
	}

	static short indexOf(int numberToSearch, int arr[100], int arrayLength) {
		for (int i = 0; i < arrayLength; i++) {
			if (arr[i] == numberToSearch)
				return i;
		}
		return -1;
	}

	static short indexOf(std::string stringToSearch, std::string arr[100], int arrayLength) {
		for (int i = 0; i < arrayLength; i++) {
			if (arr[i] == stringToSearch)
				return i;
		}
		return -1;
	}

	static bool isNumberInArray(int numberToSearch, int arr[100], int arrayLength) {
		return indexOf(numberToSearch, arr, arrayLength) != -1;
	}

	static bool isStringInArray(std::string stringToSearch, std::string arr[100], int arrayLength) {
		return indexOf(stringToSearch, arr, arrayLength) != -1;
	}

	static std::string tabs(short NumberOfTabs)
	{
		std::string t = "";

		for (int i = 1; i <= NumberOfTabs; i++)
		{
			t += "\t";
		}
		return t;

	}

	static std::string NumberToText(int Number) {
		if (Number == 0) {
			return"";
		}

		if (Number >= 1 && Number <= 19) {
			std::string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven", "Eight","Nine","Ten","Eleven",
				"Twelve","Thirteen","Fourteen", "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99) {
			std::string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };

			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 999) {
			return NumberToText(Number / 100) + "hundred " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 999999) {
			return   NumberToText(Number / 1000) + "Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 999999999) {
			return   NumberToText(Number / 1000000) + "Million " + NumberToText(Number % 1000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billion " + NumberToText(Number % 1000000000);
		}
	}
	
	// N must be an integer number of 4 digits
	/*static short encryptNumber(short n) {

		std::string nums[4];

		int remainder = 0, reverse = 0, counter = 0;
		while (n > 0) {
			remainder = n % 10;
			n = n / 10;
			reverse = ((reverse * 10 + remainder) + 7) % 10;

			nums[counter] = std::to_string(reverse);
			counter++;
		}

		std::string num = nums[3] + nums[2] + nums[1] + nums[0];

		return std::stoi(num);
	}*/



};



