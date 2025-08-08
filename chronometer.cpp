#include "chronometer.h"

Chronometer::Chronometer():
second(0),
minute(0),
hour(0),
previous_millis(millis()),
current_millis(0),
is_running(false)
{
}

Chronometer::~Chronometer()
{
}

void Chronometer::curUp(int8_t* pos_cursor)
{
    switch (*pos_cursor)
    {
    case 8:
        if (this->hour >= 90)
            this->hour -= 90;
        else
            this->hour += 10;
        break;
    case 9:
        if (this->hour % 10 == 9)
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
void Chronometer::curDown(int8_t* pos_cursor)
{
    switch (*pos_cursor)
    {
    case 8:
        if (this->hour < 10)
            this->hour += 90;
        else
            this->hour -= 10;
        break;
    case 9:
        if (this->hour % 10 == 0)
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

void Chronometer::toggle()
{
    if (is_running)
        is_running = false;
    else
    {
        this->is_running = true;
        this->previous_millis = millis() - (this->current_millis - this->previous_millis);
    }
}

void Chronometer::secondCount()
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
}

void Chronometer::print(LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Chrono"));

    lcd->setCursor(8, 0);
    if (this->hour < 10)
    {
        lcd->print(0);
        lcd->setCursor(9, 0);
    }
    lcd->print(this->hour);

    lcd->setCursor(11, 0);
    if (this->hour < 10)
    {
        lcd->print(0);
        lcd->setCursor(12, 0);
    }
    lcd->print(this->minute);

    lcd->setCursor(14, 0);
    if (this->hour < 10)
    {
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
    if (this->current_millis - this->previous_millis >= 1000)
    {
        this->previous_millis = this->current_millis;
        this->secondCount();
    }
}

void Chronometer::execute()
{
    if (this->hour >= 100)
    {
        is_running = false;
        this->hour = 0; // restart
    }

    if (this->is_running)
        this->update();
}
