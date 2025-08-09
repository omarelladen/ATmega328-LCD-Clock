#include "alarm.h"

Alarm::Alarm(Date* date):
minute_start(0),
hour_start(0),
n_repet(0),
interval_min_repet(1),
is_active(true),
is_alarm_on(false),
date(date)
{
}

Alarm::~Alarm()
{
}

void Alarm::curUp(int8_t* pos_cursor)
{
    switch (*pos_cursor)
    {
    case 3:
        if (this->hour_start >= 20)
            this->hour_start -= 20;
        else if (this->hour_start > 13)
            this->hour_start -= 10;
        else
            this->hour_start += 10;
        break;
    case 4:
        if (this->hour_start == 23)
            this->hour_start = 20;
        else if (this->hour_start % 10 == 9)
            this->hour_start -= 9;
        else
            this->hour_start++;
        break;
    case 6:
        if (this->minute_start >= 50)
            this->minute_start -= 50;
        else
            this->minute_start += 10;
        break;
    case 7:
        if (this->minute_start % 10 == 9)
            this->minute_start -= 9;
        else
            this->minute_start++;
        break;
    case 9:
        if (this->n_repet >= 90)
            this->n_repet -= 90;
        else
            this->n_repet += 10;
        break;
    case 10:
        if (this->n_repet % 10 == 9)
            this->n_repet -= 9;
        else
            this->n_repet++;
        break;
    case 13:
        if (this->interval_min_repet >= 90)
            this->interval_min_repet -= 90;
        else
            this->interval_min_repet += 10;
        break;
    case 14:
        if (this->interval_min_repet % 10 == 9)
            this->interval_min_repet -= 9;
        else
            this->interval_min_repet++;
        break;
    default:
        break;
    }
}

void Alarm::curDown(int8_t* pos_cursor)
{
    switch (*pos_cursor)
    {
    case 3:
        if (this->hour_start < 10)
        {
            if (this->hour_start >= 4)
                this->hour_start += 10;
            else
                this->hour_start += 20;
        }
        else
            this->hour_start -= 10;
        break;
    case 4:
        if (this->hour_start == 20) // 20 down => 23 
            this->hour_start = 23;
        else if (this->hour_start % 10 == 0)
            this->hour_start += 9;
        else
            this->hour_start--;
        break;
    case 6:
        if (this->minute_start < 10)
            this->minute_start += 50;
        else
            this->minute_start -= 10;
        break;
    case 7:
        if (this->minute_start % 10 == 0)
            this->minute_start += 9;
        else
            this->minute_start--;
        break;
    case 9:
        if (this->n_repet < 10)
            this->n_repet += 90;
        else
            this->n_repet -= 10;
        break;
    case 10:
        if (this->n_repet % 10 == 0)
            this->n_repet += 9;
        else
            this->n_repet--;
        break;
    case 13:
        if (this->interval_min_repet < 10)
            this->interval_min_repet += 90;
        else
            this->interval_min_repet -= 10;
        break;
    case 14:
        if (this->interval_min_repet % 10 == 0)
            this->interval_min_repet += 9;
        else
            this->interval_min_repet--;
        break;
    default:
        break;
    }
}

void Alarm::print(LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Al"));

    lcd->setCursor(3, 0);
    if (this->hour_start < 10)
    {
        lcd->print(0);
        lcd->setCursor(4, 0);
    }
    lcd->print(this->hour_start);

    lcd->setCursor(6, 0);
    if (this->minute_start < 10)
    {
        lcd->print(0);
        lcd->setCursor(7, 0);
    }
    lcd->print(this->minute_start);

    lcd->setCursor(9, 0);
    if (this->n_repet < 10)
    {
        lcd->print(0);
        lcd->setCursor(10, 0);
    }
    lcd->print(this->n_repet);

    lcd->setCursor(13, 0);
    if (this->interval_min_repet < 10)
    {
        lcd->print(0);
        lcd->setCursor(14, 0);
    }
    lcd->print(this->interval_min_repet);

    lcd->setCursor(5, 0);
    lcd->print(F(":"));
    lcd->setCursor(11, 0);
    lcd->print(F("x"));
    lcd->setCursor(15, 0);
    lcd->print(F("m"));
}

void Alarm::execute()
{
    bool found = false;
    int8_t hour_to_check;
    int8_t minute_to_check;
    int8_t i;

    for (i=0; i < this->n_repet; i++)
    {
        hour_to_check = this->hour_start + i * interval_min_repet / 60;
        minute_to_check = this->minute_start + i * interval_min_repet % 60;

        if (hour_to_check == date->getHour() && minute_to_check == date->getMinute())
        {
            if (!this->is_alarm_on)
            {
                Serial.println(F("Alarm ON"));
                this->is_alarm_on = true;
            }
            found = true;
            break;
        }
    }

    if (!found && this->is_alarm_on) 
    {
        Serial.println(F("Alarm OFF"));
        this->is_alarm_on = false;
    }
}
