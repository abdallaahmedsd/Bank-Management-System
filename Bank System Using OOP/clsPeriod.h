#pragma once
#include "clsDate.h"

class clsPeriod
{
public:
	clsPeriod(clsDate startDate, clsDate endDate) {
		this->startDate = startDate;
		this->endDate = endDate;
	}

	void setPeriodStart(clsDate startDate) {
		_startDate = startDate;
	}
	clsDate getPeriodStart() {
		return _startDate;
	}
	__declspec(property(get = getPeriodStart, put = setPeriodStart)) clsDate startDate;

	void setPeriodEnd(clsDate endDate) {
		_endDate = endDate;
	}
	clsDate getPeriodEnd() {
		return _endDate;
	}
	__declspec(property(get = getPeriodEnd, put = setPeriodEnd)) clsDate endDate;

	void print() {
		std::cout << "Period Start: ";
		startDate.print();
		std::cout << "Period End: ";
		endDate.print();
	}

	static bool isPeriodOverlapPeriod2(clsPeriod period1, clsPeriod period2) {
		//return compareDates(period1.endDate, period2.startDate) != enCompareDate::before;
		return !clsDate::isDateBeforeDate2(period1.endDate, period2.startDate);
	}
	bool isPeriodOverlapPeriod2(clsPeriod period2) {
		return isPeriodOverlapPeriod2(*this, period2);
	}

	static short calcPeriodLength(clsPeriod period, bool includeEndDay = false) {
		return clsDate::getDifferenceInDays(period.startDate, period.endDate, includeEndDay);
	}
	short calcPeriodLength(bool includeEndDay = false) {
		return calcPeriodLength(*this, includeEndDay);
	}

	static bool isDateWithinPeriod(clsDate date, clsPeriod period) {
		//return (isDateEqualDate2(period.endDate, date) || isDateEqualDate2(period.startDate, date)) || (isDateAfterDate2(date, period.startDate) && isDateBeforeDate2(date, period.endDate));
		return !(clsDate::isDateBeforeDate2(date, period.startDate) || clsDate::isDateAfterDate2(date, period.endDate));
	}
	bool isDateWithinPeriod(clsDate date) {
		return isDateWithinPeriod(date, *this);
	}

	static short countOverlapDays(clsPeriod period1, clsPeriod period2) {

		clsDate date;
		short counter{ 0 };

		while (isDateWithinPeriod(period2.startDate, period1)) {

			// in case the period 2 end date is before period 1 end date
			if (clsDate::isDateAfterDate2(period2.startDate, period2.endDate)) {
				break;
			}

			counter++;

			// I can't pass <period2.startDate> directly because it takes the clsDate as reference
			date = period2.startDate;
			period2.startDate = clsDate::increaseDateByOneDay(date);
		}

		return counter;
	}
	short countOverlapDays(clsPeriod period2) {
		return countOverlapDays(*this, period2);
	}

private:
	clsDate _startDate;
	clsDate _endDate;
};

