#include "timer.h"


Timer::Timer():
second(0),
minute(0),
hour(0),
previous_millis(millis()),
current_millis(0),
is_running(false)
{
}

Timer::~Timer()
{
}

void Timer::curUp(const int8_t pos_cursor)
{
    switch (pos_cursor)
    {
    case 8:
        if (hour >= 90)
            hour -= 90;
        else
            hour += 10;
        break;
    case 9:
        if (hour % 10 == 9)
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

void Timer::curDown(const int8_t pos_cursor)
{
    switch (pos_cursor)
    {
    case 8:
        if (hour < 10)
            hour += 90;
        else
            hour -= 10;
        break;
    case 9:
        if (hour % 10 == 0)
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

void Timer::toggle()
{
    if (is_running)
        is_running = false;
    else
    {
        is_running = true;
        previous_millis = millis() - (current_millis - previous_millis);
    }
}

void Timer::secondCount()
{
    second--;
    if (second == -1)
    {
        second = 59;
        minute--;
    }
    if (minute == -1)
    {
        minute = 59;
        hour--;
    }
}

void Timer::print(const LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Timer"));

    lcd->setCursor(8, 0);
    if (hour < 10)
    {
        lcd->print(0);
        lcd->setCursor(9, 0);
    }
    lcd->print(hour);

    lcd->setCursor(11, 0);
    if (minute < 10)
    {
        lcd->print(0);
        lcd->setCursor(12, 0);
    }
    lcd->print(minute);

    lcd->setCursor(14, 0);
    if (second < 10)
    {
        lcd->print(0);
        lcd->setCursor(15, 0);
    }
    lcd->print(second);

    lcd->setCursor(10, 0);
    lcd->print(F(":"));
    lcd->setCursor(13, 0);
    lcd->print(F(":"));
}

void Timer::update()
{
    current_millis = millis();
    if (current_millis - previous_millis >= 1000)
    {
        previous_millis = current_millis;
        secondCount();
    }
}

void Timer::execute()
{
    if (hour == 0 &&
        minute == 0 &&
        second == 0)
    {
        is_running = false;
    }

    if (is_running)
        update();
}
