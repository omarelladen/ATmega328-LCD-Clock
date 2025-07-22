#include "chronometer.h"

Chronometer::Chronometer():
second(0),
minute(0),
hour(98),
previous_millis(millis()),
current_millis(0),
is_running(false)
{
}

Chronometer::~Chronometer()
{
}

void Chronometer::pause()
{
    this->is_running=false;
}

void Chronometer::toggle()
{
    if(is_running)
        is_running = false;
    else
    {
        this->is_running = true;
        this->previous_millis = millis() - (this->current_millis - this->previous_millis);
    }
}

void Chronometer::reset()
{
    this->second=this->minute=this->hour=0;
    this->is_running=false;
}

void Chronometer::secondCount()
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

void Chronometer::print(LiquidCrystal* lcd) const
{
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
}

void Chronometer::update()
{
    this->current_millis = millis();
    if(this->current_millis - this->previous_millis >= 1)
    {
        this->previous_millis = this->current_millis;
        this->secondCount();
    }
}

void Chronometer::execute()
{
    if(this->hour > 99)
    {
        is_running = false;
        this->hour = 0; // restart
    }

    if(this->is_running)
        this->update();
}