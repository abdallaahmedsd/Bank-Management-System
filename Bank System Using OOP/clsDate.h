#pragma once
#pragma warning(disable : 4996);
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "clsString.h"

class clsDate
{
public:
	clsDate() {
		time_t current_time = time(nullptr);
		tm* localTime = localtime(&current_time);

		_day = localTime->tm_mday;
		_month = localTime->tm_mon + 1;
		_year = localTime->tm_year + 1900;
	}

	// Take the date in this format dd/mm/yyyy
	clsDate(std::string date) {
		std::vector <std::string> vDate = clsString::split(date, "/");
		_day = stoi(vDate.at(0));
		_month = stoi(vDate.at(1));
		_year = stoi(vDate.at(2));
	}

	clsDate(short day, short month, short year) {
		_day = day;
		_month = month;
		_year = year;
	}

	clsDate(short dayOrderInYear, short year) {
		clsDate date = getDateFromDayNumberInYear(dayOrderInYear, year);
		_day = date.day;
		_month = date.month;
		_year = date.year;
	}

	void setDay(short day) {
		_day = day;
	}

	void setMonth(short month) {
		_month = month;
	}

	void setYear(short year) {
		_year = year;
	}

	short getDay() {
		return _day;
	}

	short getMonth() {
		return _month;
	}

	short getYear() {
		return _year;
	}

	__declspec(property(get = getDay, put = setDay)) short day;
	__declspec(property(get = getMonth, put = setMonth)) short month;
	__declspec(property(get = getYear, put = setYear)) short year;

	static clsDate getSystemDate() {

		time_t current_time = time(nullptr);
		tm* localTime = localtime(&current_time);
		clsDate date;
		date.day = localTime->tm_mday;
		date.month = localTime->tm_mon + 1;
		date.year = localTime->tm_year + 1900;

		return date;
	}

	void print(std::string delimiter = "/") {
		std::cout << convertDateToString() << std::endl;
	}

	static std::string convertDateToString(clsDate date, std::string delimiter = "/") {

		std::string day, month;

		if (date.day < 10) {
			day = "0" + std::to_string(date.day);
		}
		else {
			day = std::to_string(date.day);
		}

		if (date.month < 10) {
			month = "0" + std::to_string(date.month);
		}
		else {
			month = std::to_string(date.month);
		}

		return  day + delimiter + month + delimiter + std::to_string(date.year);
	}
	std::string convertDateToString(std::string delimiter = "/") {
		return  convertDateToString(*this, delimiter);
	}

	static std::string formatDate(clsDate date, std::string dateFormat = "dd/mm/yyyy") {

		std::string formattedDateString = "";

		formattedDateString = clsString::replaceString(dateFormat, "dd", std::to_string(date.day));
		formattedDateString = clsString::replaceString(formattedDateString, "mm", std::to_string(date.month));
		formattedDateString = clsString::replaceString(formattedDateString, "yyyy", std::to_string(date.year));

		return  formattedDateString;
	}
	std::string formatDate(std::string dateFormat = "dd/mm/yyyy") {
		return (*this, dateFormat);
	}

	static bool isLeapYear(short year) {
		return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	}
	bool isLeapYear() {
		return isLeapYear(_year);
	}

	static short numberOfDaysInYear(short year) {
		const short _DAYS_IN_YEAR = 365;
		const short _DAYS_IN_LEAP_YEAR = 366;
		return isLeapYear(year) ? _DAYS_IN_LEAP_YEAR : _DAYS_IN_YEAR;
	}
	short numberOfDaysInYear() {
		return numberOfDaysInYear(_year);
	}

	static int numberOfHoursInYear(int year) {
		return numberOfDaysInYear(year) * 24;
	}
	int numberOfHoursInYear() {
		return numberOfDaysInYear(_year);
	}

	static int numberOfMinutesInYear(int year) {
		return numberOfHoursInYear(year) * 60;
	}
	int numberOfMinutesInYear() {
		return numberOfHoursInYear(_year);
	}

	static int numberOfSecondsInYear(int year) {
		return numberOfMinutesInYear(year) * 60;
	}
	int numberOfSecondsInYear() {
		return numberOfMinutesInYear(_year);
	}

	static short numberOfDaysInMonth(short month, short year) {
		return (month < 1 || month > 12) ? 0 : (month == 2) ? (isLeapYear(year) ? 29 : 28) : (month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;
	}
	short numberOfDaysInMonth() {
		return numberOfDaysInMonth(_month, _year);
	}

	static int numberOfHoursInMonth(short month, short year) {
		return numberOfDaysInMonth(month, year) * 24;
	}
	int numberOfHoursInMonth() {
		numberOfHoursInMonth(_month, _year);
	}

	static int numberOfMinutesInMonth(short month, short year) {
		return numberOfHoursInMonth(month, year) * 60;
	}
	int numberOfMinutesInMonth() {
		return numberOfMinutesInMonth(_month, _year);
	}

	static int numberOfSecondsInMonth(short month, short year) {
		return numberOfMinutesInMonth(month, year) * 60;
	}
	int numberOfSecondsInMonth() {
		return numberOfSecondsInMonth(_month, _year);
	}

	static short getDayOfWeekOrder(short day, short month, short year) {

		int a{ 0 }, y{ 0 }, m{ 0 }, d{ 0 };

		a = (14 - month) / 12;
		y = year - a;
		m = month + (12 * a) - 2;

		d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

		return d;
	}
	static short getDayOfWeekOrder(clsDate date) {

		int a{ 0 }, y{ 0 }, m{ 0 }, d{ 0 };

		a = (14 - date.month) / 12;
		y = date.year - a;
		m = date.month + (12 * a) - 2;

		d = (date.day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

		return d;
	}
	short getDayOfWeekOrder() {
		return getDayOfWeekOrder(*this);
	}

	static std::string getDayName(short dayOrder) {
		std::string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return days[dayOrder];
	}
	std::string getDayName() {
		return getDayName(getDayOfWeekOrder());
	}

	static std::string getMonthName(short monthOrder) {
		std::string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return months[monthOrder - 1];
	}
	std::string getMonthName() {
		return getMonthName(_month);
	}

	static void printMonthCalendar(short month, short year) {

		short numberOfDays = numberOfDaysInMonth(month, year);

		// Find the first day order in the above month => (0 - 6) => (0 = Sun, 1 = Mon, .... 6 = Sat)
		short current = getDayOfWeekOrder(1, month, year);

		printf("\n  --------------- %s ---------------\n\n", getMonthName(month).c_str());
		printf("   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		// Print empty spaces if the first day of the month is NOT Sunday, print until you find the first day in the above month
		short i = 0; // I'll use it the two coming loops
		for (i = 0; i < current; i++) {
			printf("     ");
		}

		for (int j = 1; j <= numberOfDays; j++) {
			printf("%5d", j);

			if (++i == 7) {
				i = 0;
				printf("\n");
			}

		}

		printf("\n\n  -----------------------------------\n\n");
	}
	void printMonthCalendar() {
		printMonthCalendar(_month, _year);
	}

	static void printYearCalendar(short year) {

		printf("\n\n  -----------------------------------\n");
		printf("\n\t   Calendar - %d\n", year);
		printf("\n  -----------------------------------\n");

		for (short i = 1; i <= 12; i++) {
			printMonthCalendar(i, year);
		}

	}
	void printYearCalendar() {
		printYearCalendar(_year);
	}

	static short getDayNumberInYear(clsDate date) {
		short totalDays = 0;

		for (short i = 1; i < date.getMonth(); i++) {
			totalDays += numberOfDaysInMonth(i, date.getYear());
		}

		totalDays += date.getDay();

		return totalDays;
	}
	short getDayNumberInYear() {
		return getDayNumberInYear(*this);
	}

	static bool isDateBeforeDate2(clsDate date1, clsDate date2) {
		return ((date1.getYear() < date2.getYear()) ? true : ((date1.getYear() == date2.getYear()) && (date1.getMonth() < date2.getMonth()) ? true : ((date1.getYear() == date2.getYear()) && (date1.getMonth() == date2.getMonth()) && (date1.getDay() < date2.getDay())) ? true : false));
	}
	bool isDateBeforeDate2(clsDate date2) {
		return isDateBeforeDate2(*this, date2);
	}

	static clsDate getDateFromDayNumberInYear(short dayNumberInYear, short year) {

		clsDate date;
		short monthDays{ 0 };
		short remainingDays = dayNumberInYear;
		date.year = year;
		date.month = 1;

		while (true) {

			monthDays = numberOfDaysInMonth(date.month, year);

			if (remainingDays > monthDays) {
				remainingDays -= monthDays;
				date.month++;
			}
			else {
				date.day = remainingDays;
				break;
			}
		}

		return date;
	}
	clsDate getDateFromDayNumberInYear(short dayNumberInYear) {
		return getDateFromDayNumberInYear(dayNumberInYear, this->year);
	}

	static clsDate addDaysToDate(int daysToAdd, clsDate date) {

		int remainingDays = daysToAdd + getDayNumberInYear(date);
		short monthDays = 0;

		date.month = 1;

		while (true) {
			monthDays = numberOfDaysInMonth(date.month, date.year);

			if (remainingDays > monthDays) {

				remainingDays -= monthDays;
				date.month++;

				if (date.month > 12) {
					date.month = 1;
					date.year++;
				}
			}
			else {
				date.day = remainingDays;
				break;
			}
		}

		return date;
	}
	clsDate addDaysToDate(int daysToAdd) {
		return addDaysToDate(daysToAdd, *this);
	}

	static bool isDateEqualDate2(clsDate date1, clsDate date2) {
		return (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);
	}
	bool isDateEqualDate2(clsDate date2) {
		return isDateEqualDate2(*this, date2);
	}

	static bool isDateAfterDate2(clsDate date1, clsDate date2) {
		return isDateEqualDate2(date1, date2) ? false : !isDateBeforeDate2(date1, date2);
	}
	bool isDateAfterDate2(clsDate date2) {
		return isDateAfterDate2(*this, date2);
	}

	static bool isValidDate(clsDate date) {
		return !(date.year < 1 || (date.month < 1 || date.month > 12) || (date.day > numberOfDaysInMonth(date.month, date.year)));
	}
	bool isValid() {
		return isValidDate(*this);
	}

	static bool isLastDayInMonth(clsDate date) {
		return (date.day == numberOfDaysInMonth(date.month, date.year));
	}
	bool isLastDayInMonth() {
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short month) {
		return (month == 12);
	}
	bool isLastMonthInYear() {
		return isLastMonthInYear(this->month);
	}

	// -------------- Increasing and decreasing date start ----------------------- //
	static clsDate increaseDateByOneDay(clsDate& date) {

		if (isLastDayInMonth(date) && isLastMonthInYear(date.month)) {
			date.year++;
			date.day = 1;
			date.month = 1;
		}
		else if (isLastDayInMonth(date)) {
			date.month++;
			date.day = 1;
		}
		else {
			date.day++;
		}

		return date;
	}
	void increaseDateByOneDay() {
		increaseDateByOneDay(*this);
	}

	static clsDate increaseDateByXDays(clsDate& date, int daysToAdd) {
		for (int i = 1; i <= daysToAdd; i++) {
			date = increaseDateByOneDay(date);
		}

		return date;
	}
	void increaseDateByXDays(int daysToAdd) {
		increaseDateByXDays(*this, daysToAdd);
	}

	static clsDate increaseDateByOneWeek(clsDate& date) {
		for (short i = 1; i <= 7; i++) {
			date = increaseDateByOneDay(date);
		}
		return date;
	}
	void increaseDateByOneWeek() {
		increaseDateByOneWeek(*this);
	}

	static clsDate increaseDateByXWeeks(clsDate& date, int weeksToAdd) {
		for (short i = 1; i <= weeksToAdd; i++) {
			date = increaseDateByOneWeek(date);
		}
		return date;
	}
	void increaseDateByXWeeks(int weeksToAdd) {
		increaseDateByXWeeks(*this, weeksToAdd);
	}

	static clsDate increaseDateByOneMonth(clsDate& date) {
		if (isLastMonthInYear(date.month)) {
			date.year++;
			date.month = 1;
		}
		else {
			date.month++;
		}

		short daysInMonth = numberOfDaysInMonth(date.month, date.year);

		if (date.day > daysInMonth) {
			date.day = daysInMonth;
		}

		return date;
	}
	void increaseDateByOneMonth() {
		increaseDateByOneMonth(*this);
	}

	static clsDate increaseDateByXMonths(clsDate& date, int monthsToAdd) {
		for (short i = 1; i <= monthsToAdd; i++) {
			date = increaseDateByOneMonth(date);
		}
		return date;
	}
	void increaseDateByXMonths(int monthsToAdd) {
		increaseDateByXMonths(*this, monthsToAdd);
	}

	static clsDate increaseDateByOneYear(clsDate& date) {

		date.year++;

		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29) {
			date.day = 28;
		}

		return date;
	}
	void increaseDateByOneYear() {
		increaseDateByOneYear(*this);
	}

	static clsDate increaseDateByXYears(clsDate& date, int yearsToAdd) {
		date.year += yearsToAdd;

		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29) {
			date.day = 28;
		}

		return date;
	}
	void increaseDateByXYears(int yearsToAdd) {
		increaseDateByXYears(*this, yearsToAdd);
	}

	static clsDate increaseDateByOneDecade(clsDate& date) {
		date.year += 10;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29) {
			date.day = 28;
		}
		return date;
	}
	void increaseDateByOneDecade() {
		increaseDateByOneDecade(*this);
	}

	static clsDate increaseDateByXDecades(clsDate& date, int decadesToAdd) {
		date.year += decadesToAdd * 10;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29) {
			date.day = 28;
		}
		return date;
	}
	void increaseDateByXDecades(int decadesToAdd) {
		increaseDateByXDecades(*this, decadesToAdd);
	}

	static clsDate increaseDateByOneCentury(clsDate& date) {
		date.year += 100;
		return date;
	}
	void increaseDateByOneCentury() {
		increaseDateByOneCentury(*this);
	}

	static clsDate increaseDateByOneMillennium(clsDate& date) {
		date.year += 1000;
		return date;
	}
	void increaseDateByOneMillennium() {
		increaseDateByOneMillennium(*this);
	}

	static clsDate decreaseDateByOneDay(clsDate& date) {

		if (date.day == 1) {

			if (date.month == 1) {
				date.month = 12;
				date.year--;
			}
			else {
				date.month--;
			}

			date.day = numberOfDaysInMonth(date.month, date.year);
		}
		else {
			date.day--;
		}

		return date;
	}
	void decreaseDateByOneDay() {
		decreaseDateByOneDay(*this);
	}

	static clsDate decreaseDateByXDay(clsDate& date, int daysToDecrease) {
		for (int i = 1; i <= daysToDecrease; i++) {
			date = decreaseDateByOneDay(date);
		}

		return date;
	}
	void decreaseDateByXDay(int daysToDecrease) {
		decreaseDateByXDay(*this, daysToDecrease);
	}

	static clsDate decreaseDateByOneWeek(clsDate& date) {
		for (short i = 1; i <= 7; i++) {
			date = decreaseDateByOneDay(date);
		}
		return date;
	}
	void decreaseDateByOneWeek() {
		decreaseDateByOneWeek(*this);
	}

	static clsDate decreaseDateByXWeeks(clsDate& date, int weeksToDecrease) {
		for (short i = 1; i <= weeksToDecrease; i++) {
			date = decreaseDateByOneWeek(date);
		}
		return date;
	}
	void decreaseDateByXWeeks(int weeksToDecrease) {
		decreaseDateByXWeeks(*this, weeksToDecrease);
	}

	static clsDate decreaseDateByOneMonth(clsDate& date) {

		if (date.month == 1) {
			date.year--;
			date.month = 12;
		}
		else {
			date.month--;
		}

		short daysInMonth = numberOfDaysInMonth(date.month, date.year);

		if (date.day > daysInMonth) {
			date.day = daysInMonth;
		}

		return date;
	}
	void decreaseDateByOneMonth() {
		decreaseDateByOneMonth(*this);
	}

	static clsDate decreaseDateByXMonths(clsDate& date, int monthsToDecrease) {
		for (short i = 1; i <= monthsToDecrease; i++) {
			date = decreaseDateByOneMonth(date);
		}
		return date;
	}
	void decreaseDateByXMonths(int monthsToDecrease) {
		decreaseDateByXMonths(*this, monthsToDecrease);
	}

	static clsDate decreaseDateByOneYear(clsDate& date) {

		date.year--;

		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29) {
			date.day = 28;
		}

		return date;
	}
	void decreaseDateByOneYear() {
		decreaseDateByOneYear(*this);
	}

	static clsDate decreaseDateByXYears(clsDate& date, int yearsToDecrease) {

		date.year -= yearsToDecrease;

		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29) {
			date.day = 28;
		}

		return date;
	}
	void decreaseDateByXYears(int yearsToDecrease) {
		decreaseDateByXYears(*this, yearsToDecrease);
	}

	static clsDate decreaseDateByOneDecade(clsDate& date) {
		date.year -= 10;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29) {
			date.day = 28;
		}
		return date;
	}
	void decreaseDateByOneDecade() {
		decreaseDateByOneDecade(*this);
	}

	static clsDate decreaseDateByXDecades(clsDate& date, int decadesToDecrease) {
		date.year -= decadesToDecrease * 10;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29) {
			date.day = 28;
		}
		return date;
	}
	void decreaseDateByXDecades(int decadesToDecrease) {
		decreaseDateByXDecades(*this, decadesToDecrease);
	}

	static clsDate decreaseDateByOneCentury(clsDate& date) {
		date.year -= 100;
		return date;
	}
	void decreaseDateByOneCentury() {
		decreaseDateByOneCentury(*this);
	}

	static clsDate decreaseDateByOneMillennium(clsDate& date) {
		date.year -= 1000;
		return date;
	}
	void decreaseDateByOneMillennium() {
		decreaseDateByOneMillennium(*this);
	}
	// -------------- Increasing decreasing date end ----------------------- //

	static void swap(clsDate& date1, clsDate& date2) {
		clsDate temp;
		temp = date1;
		date1 = date2;
		date2 = temp;
	}

	static int getDifferenceInDays(clsDate date1, clsDate date2, bool includeEndDay = false) {

		short swapFlagValue = 1;
		int counter{ 0 };

		if (isDateEqualDate2(date1, date2)) {
			return counter;
		}

		if (!isDateBeforeDate2(date1, date2)) {
			// Swap dates to count the difference in negative
			swapFlagValue = -1;
			swap(date1, date2);
		}

		while (true) {

			counter++;
			date1 = increaseDateByOneDay(date1);

			if (isDateEqualDate2(date1, date2)) {
				return includeEndDay ? ++counter * swapFlagValue : counter * swapFlagValue;
				//return includeEndDay ? (!isAfter ? ++counter : -(++counter)) : (!isAfter ? counter : -(counter));
			}
		}
	}
	int getDifferenceInDays(clsDate date2, bool includeEndDay = false) {
		return getDifferenceInDays(*this, date2, includeEndDay);
	}

	static int countAgeInDays(clsDate birthDate, bool includeEndDay = false) {
		clsDate dateNow;
		dateNow = getSystemDate();
		return getDifferenceInDays(birthDate, dateNow, includeEndDay);
	}
	int countAgeInDays(bool includeEndDay = false) {
		return countAgeInDays(*this, includeEndDay);
	}

	static bool isEndOfWeek(clsDate date) {
		return getDayOfWeekOrder(date) == 6;
	}
	bool isEndOfWeek() {
		return isEndOfWeek(*this);
	}


	static bool isWeekEnd(clsDate date) {
		short dayIndex = getDayOfWeekOrder(date);
		return (dayIndex == 5 || dayIndex == 6);
	}
	bool isWeekEnd() {
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(clsDate date) {
		return !isWeekEnd(date);
	}
	bool isBusinessDay() {
		return isBusinessDay(*this);
	}

	static short daysUntilEndOfWeek(clsDate date) {
		return 6 - getDayOfWeekOrder(date);
	}
	short daysUntilEndOfWeek() {
		return daysUntilEndOfWeek(*this);
	}

	static short daysUntilEndOfMonth(clsDate date) {
		return numberOfDaysInMonth(date.month, date.year) - date.day;
	}
	short daysUntilEndOfMonth() {
		return daysUntilEndOfMonth(*this);
	}

	static short daysUntilEndOfYear(clsDate date) {

		if (isLastMonthInYear(date.month)) {
			return daysUntilEndOfMonth(date);
		}
		else {
			short counter = 0, numberOfDays = 0;
			counter = daysUntilEndOfMonth(date);

			while (date.month < 12) {
				date.month++;
				numberOfDays = numberOfDaysInMonth(date.month, date.year);
				counter += numberOfDays;
			}

			return counter;
		}
	}
	short daysUntilEndOfYear() {
		return daysUntilEndOfYear(*this);
	}

	static short calculateVacationDays(clsDate startDate, clsDate endDate) {
		short countDays{ 0 };
		while (isDateBeforeDate2(startDate, endDate)) {
			if (isBusinessDay(startDate)) {
				countDays++;
			}
			startDate = increaseDateByOneDay(startDate);
		}

		return countDays;
	}
	short calculateVacationDays(clsDate endDate) {
		return calculateVacationDays(*this, endDate);
	}

	static clsDate getVacationReturnDate(short vacationDays, clsDate startDate) {
		int counter{ 0 };

		while (counter < vacationDays) {

			if (isBusinessDay(startDate))
				counter++;

			startDate = increaseDateByOneDay(startDate);
		}

		// In case the return date is a weekend day, count until the next business day
		while (isWeekEnd(startDate)) {
			startDate = increaseDateByOneDay(startDate);
		}

		return startDate;
	}
	clsDate getVacationReturnDate(short vacationDays) {
		return getVacationReturnDate(vacationDays, *this);
	}

	enum enCompareDate { before = -1, after = 1, equal = 0 };

	static enCompareDate compareDates(clsDate date1, clsDate date2) {
		return isDateAfterDate2(date1, date2) ? enCompareDate::after : (isDateBeforeDate2(date1, date2) ? enCompareDate::before : enCompareDate::equal);
	}
	enCompareDate compareDates(clsDate date2) {
		return compareDates(*this, date2);
	}

	static std::string getSystemDateTimeString() {
		std::time_t t = std::time(0);
		std::tm* localTime = std::localtime(&t);

		std::string date_time, hour, min, sec, timePeriod = "AM";

		if (localTime->tm_hour > 12) {
			localTime->tm_hour = localTime->tm_hour - 12;
			timePeriod = "PM";
		}

		hour = (localTime->tm_hour < 10) ? "0" + std::to_string(localTime->tm_hour) : std::to_string(localTime->tm_hour);
		min = (localTime->tm_min < 10) ? "0" + std::to_string(localTime->tm_min) : std::to_string(localTime->tm_min);
		sec = (localTime->tm_sec < 10) ? "0" + std::to_string(localTime->tm_sec) : std::to_string(localTime->tm_sec);


		date_time = convertDateToString(getSystemDate()) + " - "
			+ hour + ":" + min + ":" + sec + " " + timePeriod;

		return date_time;
	}


private:
	short _day = 1;
	short _month = 1;
	short _year = 1900;
};
