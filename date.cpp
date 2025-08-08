#include "date.h"

Date::Date():
day(0),
month(0),
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

int8_t Date::getHour() { return this->hour; }
int8_t Date::getMinute() { return this->minute; }

void Date::curUpDate(int8_t* pos_cursor)
{
    switch (*pos_cursor)
    {
    case 8:
        if (this->day >= 30)
            this->day -= 30;
        else if (this->day >= 22)
            this->day -= 20;
        else
            this->day += 10;
        break;
    case 9:
        if (this->day == 31)
            this->day = 30;
        else if (this->day % 10 == 9)
            this->day -= 9;
        else
            this->day++;
        break;
    case 11:
        if (this->month <= 2)
            this->month += 10;
        else if (this->month >= 10)
            this->month -= 10;
        break;
    case 12:
        if (this->month == 12)
            this->month = 10;
        else if (this->month % 10 == 9)
            this->month -= 9;
        else
            this->month++;
        break;
    case 14:
        if (this->year >= 90)
            this->year -= 90;
        else
            this->year += 10;
        break;
    case 15:
        if (this->year % 10 == 9)
            this->year -= 9;
        else
            this->year++;
        break;
    default:
        break;
    }
}
void Date::curDownDate(int8_t* pos_cursor)
{
    switch (*pos_cursor)
    {
    case 8:
        if (this->day <= 1)
            this->day += 30;
        else if (this->day < 10)
            this->day += 20;
        else
            this->day -= 10;
        break;
    case 9:
        if (this->day == 30)
            this->day = 31;
        else if (this->day % 10 == 0)
            this->day += 9;
        else
            this->day--;
        break;
    case 11:
        if (this->month <= 2)
            this->month += 10;
        else if (this->month >= 10)
            this->month -= 10;
        break;
    case 12:
        if (this->month == 10)
            this->month = 12;
        else if (this->month % 10 == 0)
            this->month += 9;
        else
            this->month--;
        break;
    case 14:
        if (this->year < 10)
            this->year += 90;
        else
            this->year -= 10;
        break;
    case 15:
        if (this->year % 10 == 0)
            this->year += 9;
        else
            this->year--;
        break;
    default:
        break;
    }
}

void Date::curUpTime(int8_t* pos_cursor)
{
    switch (*pos_cursor)
    {
    case 8:
        if (this->hour >= 20)
            this->hour -= 20;
        else if (this->hour > 13)
            this->hour -= 10;
        else
            this->hour += 10;
        break;
    case 9:
        if (this->hour == 23)
            this->hour = 20;
        else if (this->hour % 10 == 9)
            this->hour -= 9;
        else
            this->hour++;
        break;
    case 11:
        if (this->minute >= 50)
            this->minute -= 50;
        else
            this->minute += 10;
        break;
    case 12:
        if (this->minute % 10 == 9)
            this->minute -= 9;
        else
            this->minute++;
        break;
    case 14:
        if (this->second >= 50)
            this->second -= 50;
        else
            this->second += 10;
        break;
    case 15:
        if (this->second % 10 == 9)
            this->second -= 9;
        else
            this->second++;
        break;
    default:
        break;
    }
}
void Date::curDownTime(int8_t* pos_cursor)
{
    switch (*pos_cursor)
    {
    case 8:
        if (this->hour < 10)
        {
            if (this->hour >= 4)
                this->hour += 10;
            else
                this->hour += 20;
        }
        else
            this->hour -= 10;
        break;
    case 9:
        if (this->hour == 20) // 20 down => 23 
            this->hour = 23;
        else if (this->hour % 10 == 0)
            this->hour += 9;
        else
            this->hour--;
        break;

    case 11:
        if (this->minute < 10)
            this->minute += 50;
        else
            this->minute -= 10;
        break;
    case 12:
        if (this->minute % 10 == 0)
            this->minute += 9;
        else
            this->minute--;
        break;

    case 14:
        if (this->second < 10)
            this->second += 50;
        else
            this->second -= 10;
        break;
    case 15:
        if (this->second % 10 == 0)
            this->second += 9;
        else
            this->second--;
        break;
    default:
        break;
    }
}

void Date::secondCount()
{
    this->second++;

    if (this->second == 60)
    {
        this->second = 0;
        this->minute++;
    }
    if (this->minute == 60)
    {
        this->minute = 0;
        this->hour++;
    }
    if (this->hour == 24)
    {
        this->hour = 0;
        this->day++;
    }
    if (this->day == 32)
    {
        this->day = 0;
        this->month++;
    }
    if (this->month == 13)
    {
        this->month = 0;
        this->year++;
    }
    if (this->year == 100)
    {
        this->year = 0;
    }
}

void Date::print(LiquidCrystal* lcd) const
{
    lcd->setCursor(4, 1);
    if (this->day < 10)
    {
        lcd->print(0);
        lcd->setCursor(5, 1);
    }
    lcd->print(this->day);

    lcd->setCursor(7, 1);
    if (this->month < 10)
    {
        lcd->print(0);
        lcd->setCursor(8, 1);
    }
    lcd->print(this->month);

    lcd->setCursor(10, 1);
    if (this->year < 10)
    {
        lcd->print(0);
        lcd->setCursor(11, 1);
    }
    lcd->print(this->year);

    lcd->setCursor(4, 0);
    if (this->hour < 10)
    {
        lcd->print(0);
        lcd->setCursor(5, 0);
    }
    lcd->print(this->hour);

    lcd->setCursor(7, 0);
    if (this->minute < 10)
    {
        lcd->print(0);
        lcd->setCursor(8, 0);
    }
    lcd->print(this->minute);

    lcd->setCursor(10, 0);
    if (this->second < 10)
    {
        lcd->print(0);
        lcd->setCursor(11, 0);
    }
    lcd->print(this->second);

    lcd->setCursor(6, 0);
    lcd->print(F(":"));
    lcd->setCursor(9, 0);
    lcd->print(F(":"));
    lcd->setCursor(6, 1);
    lcd->print(F("/"));
    lcd->setCursor(9, 1);
    lcd->print(F("/"));
}

void Date::printDate(LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Date"));

    if (this->day >= 10)
        lcd->setCursor(8, 0);
    else
    {
        lcd->setCursor(8, 0);
        lcd->print(0);

        lcd->setCursor(9, 0);
    }
    lcd->print(this->day);

    if (this->month >= 10)
        lcd->setCursor(11, 0);
    else
    {
        lcd->setCursor(11, 0);
        lcd->print(0);

        lcd->setCursor(12, 0);
    }
    lcd->print(this->month);

    if (this->year >= 10)
        lcd->setCursor(14, 0);
    else
    {
        lcd->setCursor(14, 0);
        lcd->print(0);

        lcd->setCursor(15, 0);
    }
    lcd->print(this->year);

    lcd->setCursor(10, 0);
    lcd->print(F("/"));
    lcd->setCursor(13, 0);
    lcd->print(F("/"));
}

void Date::printTime(LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Time"));

        if (this->hour >= 10)
        lcd->setCursor(8, 0);
    else
    {
        lcd->setCursor(8, 0);
        lcd->print(0);

        lcd->setCursor(9, 0);
    }
    lcd->print(this->hour);

    if (this->minute >= 10)
        lcd->setCursor(11, 0);
    else
    {
        lcd->setCursor(11, 0);
        lcd->print(0);

        lcd->setCursor(12, 0);
    }
    lcd->print(this->minute);

    if (this->second >= 10)
        lcd->setCursor(14, 0);
    else
    {
        lcd->setCursor(14, 0);
        lcd->print(0);

        lcd->setCursor(15, 0);
    }
    lcd->print(this->second);

    lcd->setCursor(10, 0);
    lcd->print(F(":"));
    lcd->setCursor(13, 0);
    lcd->print(F(":"));
}


void Date::update()
{
    this->current_millis = millis();
    if (this->current_millis - this->previous_millis >= 1000)
    {
        this->previous_millis = this->current_millis;
        this->secondCount();
    }
}

void Date::execute()
{


    if (this->is_running)
        this->update();
}
