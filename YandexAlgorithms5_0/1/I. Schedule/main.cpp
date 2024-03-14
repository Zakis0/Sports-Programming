#include <bits/stdc++.h>

using namespace std;

const string january = "January";
const string february = "February";
const string march = "March";
const string april = "April";
const string may = "May";
const string june = "June";
const string july = "July";
const string august = "August";
const string september = "September";
const string october = "October";
const string november = "November";
const string december = "December";

const string monday = "Monday";
const string tuesday = "Tuesday";
const string wednesday = "Wednesday";
const string thursday = "Thursday";
const string friday = "Friday";
const string saturday = "Saturday";
const string sunday = "Sunday";

struct Month {
    string name;
    int numOfDays;
    int index;
    Month(string name, int numOfDays, int index) {
        this->name = std::move(name);
        this->numOfDays = numOfDays;
        this->index = index;
    }
    bool operator==(Month const& obj) const {
        return index == obj.index;
    }
    bool operator<(Month const& obj) const {
        return index < obj.index;
    }
    bool operator>(Month const& obj) const {
        return obj < *this;
    }
    bool operator>=(Month const& obj) const {
        return !(*this < obj);
    }
    bool operator<=(Month const& obj) const {
        return !(*this > obj);
    }
};

struct WeekDay {
    string name;
    int index;
    WeekDay(string name, int index) {
        this->name = std::move(name);
        this->index = index;
    }
    WeekDay next() const;
    bool operator==(WeekDay const& obj) const {
        return index == obj.index;
    }
    bool operator<(WeekDay const& obj) const {
        return index < obj.index;
    }
    bool operator>(WeekDay const& obj) const {
        return obj < *this;
    }
    bool operator>=(WeekDay const& obj) const {
        return !(*this < obj);
    }
    bool operator<=(WeekDay const& obj) const {
        return !(*this > obj);
    }
};

Month
January(january, 31, 0),
February(february, 28, 1),
March(march, 31, 2),
April(april, 30, 3),
May(may, 31, 4),
June(june, 30, 5),
July(july, 31, 6),
August(august, 31, 7),
September(september, 30, 8),
October(october, 31, 9),
November(november, 30, 10),
December(december, 31, 11);

vector<Month> months = {January, February, March, April, May, June, July, August, September, October, November, December };

Month strToMonth(const string& monthName) {
    if (monthName == january) return January;
    else if (monthName == february) return February;
    else if (monthName == march) return March;
    else if (monthName == april) return April;
    else if (monthName == may) return May;
    else if (monthName == june) return June;
    else if (monthName == july) return July;
    else if (monthName == august) return August;
    else if (monthName == september) return September;
    else if (monthName == october) return October;
    else if (monthName == november) return November;
    else if (monthName == december) return December;
    return December;
}

WeekDay
Monday(monday, 0),
Tuesday(tuesday, 1),
Wednesday(wednesday, 2),
Thursday(thursday, 3),
Friday(friday, 4),
Saturday(saturday, 5),
Sunday(sunday, 6);

WeekDay strToWeekDay(const string& weekDayName) {
    if (weekDayName == monday) return Monday;
    else if (weekDayName == tuesday) return Tuesday;
    else if (weekDayName == wednesday) return Wednesday;
    else if (weekDayName == thursday) return Thursday;
    else if (weekDayName == friday) return Friday;
    else if (weekDayName == saturday) return Saturday;
    else if (weekDayName == sunday) return Sunday;
    return Sunday;
}
WeekDay indexToWeekDay(int index) {
    if (index == 0) return Monday;
    else if (index == 1) return Tuesday;
    else if (index == 2) return Wednesday;
    else if (index == 3) return Thursday;
    else if (index == 4) return Friday;
    else if (index == 5) return Saturday;
    else if (index == 6) return Sunday;
    return Sunday;
}

WeekDay WeekDay::next() const {
    return indexToWeekDay((index + 1) % 7);
}

bool isLeapYear(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int countDayNumber(int day, const string& monthName, int year) {
    int result = 0;
    for (const Month& month: months) {
        if (month.name == monthName) {
            break;
        }
        result += month.numOfDays;
    }
    result += day;
    if (strToMonth(monthName) > February && isLeapYear(year)) {
        ++result;
    }
    return result;
}

int getDayOfWeekIndex(const string& dayOfWeekOfFirstYearDay, int day, const string& monthName, int year) {
    int index = countDayNumber(day, monthName, year) - 1;
    index += strToWeekDay(dayOfWeekOfFirstYearDay).index;
    index %= 7;
    return index;
}

vector<int> getMaxWeekDayIndexes(int year, const string& dayOfWeekOfFirstYearDay) {
    vector<int> maxWeekDayIndexes;
    maxWeekDayIndexes.emplace_back(strToWeekDay(dayOfWeekOfFirstYearDay).index);
    if(isLeapYear(year)) {
        maxWeekDayIndexes.emplace_back(strToWeekDay(dayOfWeekOfFirstYearDay).next().index);
    }
    return maxWeekDayIndexes;
}

void solve() {
    int n, year, day;
    string dayOfWeekOfFirstYearDay, monthName, weekDay;

    cin >> n >> year;
    vector<int> weekHolidaysCounter(7, 0);

    vector<pair<int, string>> holidays;

    for (int i = 0; i < n; ++i) {
        cin >> day >> monthName;
        holidays.emplace_back(day, monthName);
    }
    cin >> dayOfWeekOfFirstYearDay;

    for (const pair<int, string>& holiday: holidays) {
        day = holiday.first;
        monthName = holiday.second;
        ++weekHolidaysCounter[getDayOfWeekIndex(dayOfWeekOfFirstYearDay, day, monthName, year)];
    }

    for (int index: getMaxWeekDayIndexes(year, dayOfWeekOfFirstYearDay)) {
        --weekHolidaysCounter[index];
    }

    int minHolidaysIndex = 0, maxHolidaysIndex = 0;
    int minHolidays = 1000, maxHolidays = -1000;
    for (int i = 0; i < weekHolidaysCounter.size(); ++i) {
        if (weekHolidaysCounter[i] > maxHolidays) {
            maxHolidays = weekHolidaysCounter[i];
            maxHolidaysIndex = i;
        }
        if (weekHolidaysCounter[i] < minHolidays) {
            minHolidays = weekHolidaysCounter[i];
            minHolidaysIndex = i;
        }
    }
    cout << indexToWeekDay(minHolidaysIndex).name << " " << indexToWeekDay(maxHolidaysIndex).name;
}

int main() {
    solve();
    return 0;
}