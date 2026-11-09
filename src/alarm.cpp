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

void Alarm::curUp(const int8_t pos_cursor)
{
    switch (pos_cursor)
    {
    case 3:
        if (hour_start >= 20)
            hour_start -= 20;
        else if (hour_start > 13)
            hour_start -= 10;
        else
            hour_start += 10;
        break;
    case 4:
        if (hour_start == 23)
            hour_start = 20;
        else if (hour_start % 10 == 9)
            hour_start -= 9;
        else
            hour_start++;
        break;

    case 6:
        if (minute_start >= 50)
            minute_start -= 50;
        else
            minute_start += 10;
        break;
    case 7:
        if (minute_start % 10 == 9)
            minute_start -= 9;
        else
            minute_start++;
        break;

    case 9:
        if (n_repet >= 90)
            n_repet -= 90;
        else
            n_repet += 10;
        break;
    case 10:
        if (n_repet % 10 == 9)
            n_repet -= 9;
        else
            n_repet++;
        break;

    case 13:
        if (interval_min_repet >= 90)
            interval_min_repet -= 90;
        else
            interval_min_repet += 10;
        break;
    case 14:
        if (interval_min_repet % 10 == 9)
            interval_min_repet -= 9;
        else
            interval_min_repet++;
        break;

    default:
        break;
    }
}

void Alarm::curDown(const int8_t pos_cursor)
{
    switch (pos_cursor)
    {
    case 3:
        if (hour_start < 10)
        {
            if (hour_start >= 4)
                hour_start += 10;
            else
                hour_start += 20;
        }
        else
            hour_start -= 10;
        break;
    case 4:
        if (hour_start == 20)
            hour_start = 23;
        else if (hour_start % 10 == 0)
            hour_start += 9;
        else
            hour_start--;
        break;

    case 6:
        if (minute_start < 10)
            minute_start += 50;
        else
            minute_start -= 10;
        break;
    case 7:
        if (minute_start % 10 == 0)
            minute_start += 9;
        else
            minute_start--;
        break;

    case 9:
        if (n_repet < 10)
            n_repet += 90;
        else
            n_repet -= 10;
        break;
    case 10:
        if (n_repet % 10 == 0)
            n_repet += 9;
        else
            n_repet--;
        break;

    case 13:
        if (interval_min_repet < 10)
            interval_min_repet += 90;
        else
            interval_min_repet -= 10;
        break;
    case 14:
        if (interval_min_repet % 10 == 0)
            interval_min_repet += 9;
        else
            interval_min_repet--;
        break;

    default:
        break;
    }
}

void Alarm::print(const LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Al"));

    lcd->setCursor(3, 0);
    if (hour_start < 10)
    {
        lcd->print(0);
        lcd->setCursor(4, 0);
    }
    lcd->print(hour_start);

    lcd->setCursor(6, 0);
    if (minute_start < 10)
    {
        lcd->print(0);
        lcd->setCursor(7, 0);
    }
    lcd->print(minute_start);

    lcd->setCursor(9, 0);
    if (n_repet < 10)
    {
        lcd->print(0);
        lcd->setCursor(10, 0);
    }
    lcd->print(n_repet);

    lcd->setCursor(13, 0);
    if (interval_min_repet < 10)
    {
        lcd->print(0);
        lcd->setCursor(14, 0);
    }
    lcd->print(interval_min_repet);

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

    for (i=0; i < n_repet; i++)
    {
        hour_to_check   = hour_start   + i * interval_min_repet / 60;
        minute_to_check = minute_start + i * interval_min_repet % 60;

        if (hour_to_check == date->getHour() &&
            minute_to_check == date->getMinute())
        {
            if (!is_alarm_on)
            {
                Serial.println(F("Alarm ON"));
                is_alarm_on = true;
            }
            found = true;
            break;
        }
    }

    if (!found && is_alarm_on)
    {
        Serial.println(F("Alarm OFF"));
        is_alarm_on = false;
    }
}
