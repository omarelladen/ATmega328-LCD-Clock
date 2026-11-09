#include "date.h"


Date::Date():
day(1),
month(1),
year(0),
second(0),
minute(0),
hour(0),
previous_millis(millis()),
current_millis(0),
is_running(true)
{
}

Date::~Date()
{
}

int8_t Date::getHour()   const { return hour; }
int8_t Date::getMinute() const { return minute; }

void Date::curUpDate(const int8_t pos_cursor)
{
    switch (pos_cursor)
    {
    case 8:
        if (day == 21 && (month == 4 || month == 6 || month == 9 || month == 11))
            day = 1;
        else if (day == 20 && month == 2)
            day = 10;
        else if (day == 21 && month == 2)
            day = 11;
        else if (day == 19 && month == 2 && year % 4 != 0)
            day = 9;
        else if (day > 30)
            day -= 30;
        else if (day == 30)
            day = 10;
        else if (day >= 22)
            day -= 20;
        else
            day += 10;
        break;
    case 9:
        if (day == 29 && month == 2 && year % 4 == 0)
            day = 20;
        else if (day == 28 && month == 2 && year % 4 != 0)
            day = 20;
        else if (day == 30 && (month == 4 || month == 6 || month == 9 || month == 11))
            ;
        else if (day == 31)
            day = 30;
        else if (day == 9)
            day = 1;
        else if (day % 10 == 9)
            day -= 9;
        else
            day++;
        break;

    case 11:
        if (day == 31 && month == 1)
            ;
        else if (month <= 2)
            month += 10;
        else if (month == 10)
            month = 1;
        else if (month > 10)
            month -= 10;
        break;
    case 12:
        if (day == 31 && month != 7)
            ;
        else if (day > 28 && month == 1 && year % 4 != 0)
            ;
        else if (day > 29 && month == 1 && year % 4 == 0)
            ;
        else if (month == 12)
            month = 10;
        else if (month == 9)
            month = 1;
        else
            month++;
        break;

    case 14:
        if (month == 2 && day == 29 && year % 4 == 0)
            ;
        else if (year >= 90)
            year -= 90;
        else
            year += 10;
        break;
    case 15:
        if (month == 2 && day == 29 && year % 4 == 0)
            ;
        else if (year % 10 == 9)
            year -= 9;
        else
            year++;
        break;

    default:
        break;
    }
}
void Date::curDownDate(const int8_t pos_cursor)
{
    switch (pos_cursor)
    {
    case 8:
        if (day == 1 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11))
            day = 21;
        else if (day == 9 && month == 2 && year % 4 != 0)
            day = 19;
        else if (day <= 1)
            day += 30;
        else if (day < 10)
            day += 20;
        else if (day == 10 && month == 2)
            day = 20;
        else if (day == 10)
            day = 30;
        else
            day -= 10;
        break;
    case 9:
        if (day == 20 && month == 2 && year % 4 != 0)
            day = 28;
        else if (day == 30 && (month == 4 || month == 6 || month == 9 || month == 11))
            ;
        else if (day == 30)
            day = 31;
        else if (day == 1)
            day = 9;
        else if (day % 10 == 0)
            day += 9;
        else
            day--;
        break;

    case 11:
        if (day == 31 && month == 1)
            ;
        else if (month <= 2)
            month += 10;
        else if (month == 10)
            month = 1;
        else if (month > 10)
            month -= 10;
        break;
    case 12:
        if (day == 31 && month != 8)
            ;
        else if (day > 28 && month == 3 && year % 4 != 0)
            ;
        else if (day > 29 && month == 3 && year % 4 == 0)
            ;
        else if (month == 10)
            month = 12;
        else if (month == 1)
            month = 9;
        else
            month--;
        break;

    case 14:
        if (month == 2 && day == 29 && year % 4 == 0)
            ;
        else if (year < 10)
            year += 90;
        else
            year -= 10;
        break;
    case 15:
        if (month == 2 && day == 29 && year % 4 == 0)
            ;
        else if (year % 10 == 0)
            year += 9;
        else
            year--;
        break;

    default:
        break;
    }
}

void Date::curUpTime(const int8_t pos_cursor)
{
    switch (pos_cursor)
    {
    case 8:
        if (hour >= 20)
            hour -= 20;
        else if (hour > 13)
            hour -= 10;
        else
            hour += 10;
        break;
    case 9:
        if (hour == 23)
            hour = 20;
        else if (hour % 10 == 9)
            hour -= 9;
        else
            hour++;
        break;

    case 11:
        if (minute >= 50)
            minute -= 50;
        else
            minute += 10;
        break;
    case 12:
        if (minute % 10 == 9)
            minute -= 9;
        else
            minute++;
        break;

    case 14:
        if (second >= 50)
            second -= 50;
        else
            second += 10;
        break;
    case 15:
        if (second % 10 == 9)
            second -= 9;
        else
            second++;
        break;

    default:
        break;
    }
}

void Date::curDownTime(const int8_t pos_cursor)
{
    switch (pos_cursor)
    {
    case 8:
        if (hour < 10)
        {
            if (hour >= 4)
                hour += 10;
            else
                hour += 20;
        }
        else
            hour -= 10;
        break;
    case 9:
        if (hour == 20)
            hour = 23;
        else if (hour % 10 == 0)
            hour += 9;
        else
            hour--;
        break;

    case 11:
        if (minute < 10)
            minute += 50;
        else
            minute -= 10;
        break;
    case 12:
        if (minute % 10 == 0)
            minute += 9;
        else
            minute--;
        break;

    case 14:
        if (second < 10)
            second += 50;
        else
            second -= 10;
        break;
    case 15:
        if (second % 10 == 0)
            second += 9;
        else
            second--;
        break;

    default:
        break;
    }
}

void Date::secondCount()
{
    second++;

    if (second == 60)
    {
        second = 0;
        minute++;
    }
    if (minute == 60)
    {
        minute = 0;
        hour++;
    }
    if (hour == 24)
    {
        hour = 0;
        day++;
    }

    if ((day == 31 && (month == 4 || month == 6 || month == 9 || month == 11)) ||
        (day == 29 && month == 2 && year % 4 != 0) ||
        (day == 30 && month == 2 && year % 4 == 0) ||
        day == 32)
    {
        day = 1;
        month++;
    }
    if (month == 13)
    {
        month = 1;
        year++;
    }

    if (year == 100)
    {
        year = 0;
    }
}

void Date::printDateAndTime(const LiquidCrystal* lcd) const
{
    lcd->setCursor(4, 1);
    if (day < 10)
    {
        lcd->print(0);
        lcd->setCursor(5, 1);
    }
    lcd->print(day);

    lcd->setCursor(7, 1);
    if (month < 10)
    {
        lcd->print(0);
        lcd->setCursor(8, 1);
    }
    lcd->print(month);

    lcd->setCursor(10, 1);
    if (year < 10)
    {
        lcd->print(0);
        lcd->setCursor(11, 1);
    }
    lcd->print(year);

    lcd->setCursor(4, 0);
    if (hour < 10)
    {
        lcd->print(0);
        lcd->setCursor(5, 0);
    }
    lcd->print(hour);

    lcd->setCursor(7, 0);
    if (minute < 10)
    {
        lcd->print(0);
        lcd->setCursor(8, 0);
    }
    lcd->print(minute);

    lcd->setCursor(10, 0);
    if (second < 10)
    {
        lcd->print(0);
        lcd->setCursor(11, 0);
    }
    lcd->print(second);

    lcd->setCursor(6, 0);
    lcd->print(F(":"));
    lcd->setCursor(9, 0);
    lcd->print(F(":"));
    lcd->setCursor(6, 1);
    lcd->print(F("/"));
    lcd->setCursor(9, 1);
    lcd->print(F("/"));
}

void Date::printDate(const LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Date"));

    if (day >= 10)
        lcd->setCursor(8, 0);
    else
    {
        lcd->setCursor(8, 0);
        lcd->print(0);

        lcd->setCursor(9, 0);
    }
    lcd->print(day);

    if (month >= 10)
        lcd->setCursor(11, 0);
    else
    {
        lcd->setCursor(11, 0);
        lcd->print(0);

        lcd->setCursor(12, 0);
    }
    lcd->print(month);

    if (year >= 10)
        lcd->setCursor(14, 0);
    else
    {
        lcd->setCursor(14, 0);
        lcd->print(0);

        lcd->setCursor(15, 0);
    }
    lcd->print(year);

    lcd->setCursor(10, 0);
    lcd->print(F("/"));
    lcd->setCursor(13, 0);
    lcd->print(F("/"));
}

void Date::printTime(const LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Time"));

    if (hour >= 10)
        lcd->setCursor(8, 0);
    else
    {
        lcd->setCursor(8, 0);
        lcd->print(0);

        lcd->setCursor(9, 0);
    }
    lcd->print(hour);

    if (minute >= 10)
        lcd->setCursor(11, 0);
    else
    {
        lcd->setCursor(11, 0);
        lcd->print(0);

        lcd->setCursor(12, 0);
    }
    lcd->print(minute);

    if (second >= 10)
        lcd->setCursor(14, 0);
    else
    {
        lcd->setCursor(14, 0);
        lcd->print(0);

        lcd->setCursor(15, 0);
    }
    lcd->print(second);

    lcd->setCursor(10, 0);
    lcd->print(F(":"));
    lcd->setCursor(13, 0);
    lcd->print(F(":"));
}

void Date::update()
{
    current_millis = millis();
    if (current_millis - previous_millis >= 1000)
    {
        previous_millis = current_millis;
        secondCount();
    }
}

void Date::execute()
{
    if (is_running)
        update();
}
