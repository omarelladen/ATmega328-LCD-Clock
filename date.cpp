#include "date.h"

Date::Date():
day(22),
month(7),
year(25),
second(0),
minute(20),
hour(17),
previous_millis(millis()),
current_millis(0),
is_running(true)
{
}

Date::~Date()
{
}

void Date::pause()
{
    this->is_running=false;
}

void Date::toggle()
{
    if(is_running)
        is_running = false;
    else
    {
        this->is_running = true;
        this->previous_millis = millis() - (this->current_millis - this->previous_millis);
    }
}

void Date::reset()
{
    this->second=this->minute=this->hour=0;
    this->is_running=false;
}

void Date::secondCount()
{
    this->second++;
    if(this->second == 60)
    {
        this->second = 0;
        this->minute++;
    }
    if(this->minute == 60)
    {
        this->minute = 0;
        this->hour++;
    }
}

void Date::print(LiquidCrystal* lcd) const
{
    if(this->day >= 10)
        lcd->setCursor(8, 1);
    else
    {
        lcd->setCursor(8, 1);
        lcd->print(0);

        lcd->setCursor(9, 1);
    }
    lcd->print(this->day);

    if(this->month >= 10)
        lcd->setCursor(11, 1);
    else
    {
        lcd->setCursor(11, 1);
        lcd->print(0);

        lcd->setCursor(12, 1);
    }
    lcd->print(this->month);

    if(this->year >= 10)
        lcd->setCursor(14, 1);
    else
    {
        lcd->setCursor(14, 1);
        lcd->print(0);

        lcd->setCursor(15, 1);
    }
    lcd->print(this->year);


    if(this->hour >= 10)
        lcd->setCursor(8, 0);
    else
    {
        lcd->setCursor(8, 0);
        lcd->print(0);

        lcd->setCursor(9, 0);
    }
    lcd->print(this->hour);

    if(this->minute >= 10)
        lcd->setCursor(11, 0);
    else
    {
        lcd->setCursor(11, 0);
        lcd->print(0);

        lcd->setCursor(12, 0);
    }
    lcd->print(this->minute);

    if(this->second >= 10)
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

    lcd->setCursor(10, 1);
    lcd->print(F("/"));
    lcd->setCursor(13, 1);
    lcd->print(F("/"));
}

void Date::update()
{
    this->current_millis = millis();
    if(this->current_millis - this->previous_millis >= 1000)
    {
        this->previous_millis = this->current_millis;
        this->secondCount();
    }
}

void Date::execute()
{
    if(this->is_running)
        this->update();
}