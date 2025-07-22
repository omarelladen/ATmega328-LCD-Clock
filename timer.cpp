#include "timer.h"

Timer::Timer():
second(0),
minute(30),
hour(0),
previous_millis(millis()),
current_millis(0),
is_running(false),
pos_cursor(8)
{
}

Timer::~Timer()
{
}

void Timer::mv_cur_up()
{
    switch(pos_cursor)
    {
    case 8:
        break;
    case 9:
        break;
    case 11:
        break;
    case 12:
        break;
    case 14:
        break;
    case 15:
        break;
    default:
        break;
    }
}
void Timer::mv_cur_down()
{

}

void Timer::mv_cur_left()
{
    if(this->pos_cursor > 8)
    {
        if(pos_cursor == 11 || pos_cursor == 14)
            this->pos_cursor -= 2;
        else
            this->pos_cursor--;
    }
}
void Timer::mv_cur_right()
{
    if(this->pos_cursor < 15)
    {
        if(pos_cursor == 9 || pos_cursor == 12)
            this->pos_cursor += 2;
        else
            this->pos_cursor++;
    }
}

void Timer::pause()
{
    this->is_running=false;
}

void Timer::toggle()
{
    if(is_running)
        is_running = false;
    else
    {
        this->is_running = true;
        this->previous_millis = millis() - (this->current_millis - this->previous_millis);
    }
}

void Timer::reset()
{
    this->second=this->minute=this->hour=0;
    this->is_running=false;
}

void Timer::secondCount()
{
    this->second--;
    if(this->second == 255)
    {
        this->second = 59;  ///// -1
        this->minute--;
    }
    if(this->minute == 255)
    {
        this->minute = 59;
        this->hour--;
    }
}

void Timer::print(LiquidCrystal* lcd) const
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

    lcd->setCursor(this->pos_cursor, 1);
    lcd->print(F("_"));
}

void Timer::update()
{
    this->current_millis = millis();
    if(this->current_millis - this->previous_millis >= 1)
    {
        this->previous_millis = this->current_millis;
        this->secondCount();
    }
}

void Timer::execute()
{
    if(this->hour == 0 && this->minute == 0 && this->second == 0)
    {
        is_running = false;
    }

    if(this->is_running)
        this->update();
}