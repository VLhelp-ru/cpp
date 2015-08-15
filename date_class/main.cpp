/*
***** COPYRIGHT: VLhelp.ru / program@vlhelp.ru *****

Программа реализует класс Дата (Date).

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_MONTH 12

using namespace std;

unsigned int day_per_month[MAX_MONTH];
char *month_names[MAX_MONTH];

class Date {
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;

	unsigned int day_per_month[MAX_MONTH];
	char *month_names[MAX_MONTH];
public:
	// конструкторы
	Date():year(0), month(0), day(0){initialize();} // без параметров
	Date(unsigned int _year, unsigned int _month, unsigned int _day):year(_year), month(_month), day(_day){initialize();} // с параметрами

	void add_days(unsigned int _days); // добавляет дни к дате
	unsigned int operator-(const Date &other); // перегружаем оператор вычитания, возвращает количество дней между двумя датами

	bool is_leap_year(); // определяет является ли текущий год високосным
	unsigned int days_in_year(); // возвращает количество дней в году
	unsigned int days_from_year_start(); // возвращает количество дней прошедших с начала года
	unsigned int days_to_year_end(); // возвращает количество дней оставшихся до конца года
	unsigned int to_days(); // превращает дату в дни


	void initialize();
	void print();

	// методы для вычленения частей даты
	unsigned int get_year() {return year;}
	unsigned int get_month() {return month;}
	unsigned int get_day() {return day;}

	// методы для установки атрибутов
	void set_year(unsigned int y) {year = y; initialize();}
	void set_month(unsigned int m) {month = m;}
	void set_day(unsigned int d) {day = d;}
};

// добавляет дни к дате
void Date::add_days(unsigned int _days) {
	while (_days > 0) {
		day++;
		_days--;
		if (day > day_per_month[month-1]) { // если дней больше, чем в текущем месяце
			day = 1; // 1-е число
			month++; // увеличиваем месяц
		}
		if (month > MAX_MONTH) { // если месяцев больше, чем максимум в году
			month = 1; // 1-й месяц
			year++; // увеличиваем год
			initialize(); // инициализируем, т.к. год может быть високосным
		}
	}
}

// перегружаем оператор вычитания, возвращает количество дней между двумя датами
unsigned int Date::operator-(const Date &other) {
	Date d1 = *this;
	Date d2 = other;

	unsigned int days1 = d1.to_days();
	unsigned int days2 = d2.to_days();

	return days1 > days2 ? days1 - days2 : days2 - days1;
}

// определяет является ли текущий год високосным
bool Date::is_leap_year() {
	return ((year % 4 == 0 && year % 100 != 0) || ( year % 400 == 0)); // год является високосным в двух случаях: либо он кратен 4, но при этом не кратен 100, либо кратен 400
}

// возвращает количество дней в году
unsigned int Date::days_in_year() {
	return is_leap_year() ? 366 : 365;
}

// возвращает количество дней прошедших с начала года
unsigned int Date::days_from_year_start() {
	unsigned int res = 0;
	for (unsigned int m = 0; m < (month-1); m++) {
		res += day_per_month[m];
	}
	res += day;
	return res;
}

// возвращает количество дней оставшихся до конца года
unsigned int Date::days_to_year_end() {
	return days_in_year()-days_from_year_start();
}

// превращает дату в дни
unsigned int Date::to_days() {
	unsigned int days = 0;
	for (unsigned int y = 1; y < year; y++) {
		days += 365 + ((y % 4 == 0 && y % 100 != 0) || ( y % 400 == 0));
	}
	for (unsigned int m = 0; m < month-1; m++) {
		days += day_per_month[m];
	}
	days += day;
	return days;
}

// инициализация
void Date::initialize() {
	day_per_month[0] = 31;
	day_per_month[1] = is_leap_year() ? 29 : 28;
	day_per_month[2] = 31;
	day_per_month[3] = 30;
	day_per_month[4] = 31;
	day_per_month[5] = 30;
	day_per_month[6] = 31;
	day_per_month[7] = 31;
	day_per_month[8] = 30;
	day_per_month[9] = 31;
	day_per_month[10] = 30;
	day_per_month[11] = 31;

	month_names[0] = (char*)"January";
	month_names[1] = (char*)"February";
	month_names[2] = (char*)"March";
	month_names[3] = (char*)"April";
	month_names[4] = (char*)"May";
	month_names[5] = (char*)"June";
	month_names[6] = (char*)"July";
	month_names[7] = (char*)"August";
	month_names[8] = (char*)"September";
	month_names[9] = (char*)"October";
	month_names[10] = (char*)"November";
	month_names[11] = (char*)"December";
}

void Date::print() {
	printf("%u-%.2u-%.2u\n", year, month, day);
}

int main()
{
	unsigned int y = 0, m = 0, d = 0, ad = 0;

	printf("date1 (year, month, day):\n");
	while (!scanf("%u", &y) == 1);
	while (!scanf("%u", &m) == 1);
	while (!scanf("%u", &d) == 1);
	Date date1(y, m, d);

	printf("date2 (year, month, day):\n");
	while (!scanf("%u", &y) == 1);
	while (!scanf("%u", &m) == 1);
	while (!scanf("%u", &d) == 1);
	Date date2(y, m, d);

	printf("days to add (n >= 0):\n");
	while (!scanf("%u", &ad) == 1);

	printf("Your dates:\n");
	date1.print();
	date2.print();

	printf("Difference between two dates: %u day(s)\n", date1 - date2);

	date1.add_days(ad);
	printf("Date 1 plus %u day(s) is: ", ad);
	date1.print();
	date2.add_days(ad);
	printf("Date 2 plus %u day(s) is: ", ad);
	date2.print();
	return 0;
}
