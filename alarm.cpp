#include "alarm.h"

Alarm::Alarm():
minute_start(0),
hour_start(0),
n_repet(1),
interval_min_repet(1),
is_active(true)
{
}

Alarm::~Alarm()
{
}

void Alarm::mv_cur_up(int* pos_cursor)
{
    switch(*pos_cursor)
    {
    case 3:
        if(this->hour_start >= 20)
            this->hour_start -= 20;
        else if(this->hour_start > 13)
            this->hour_start -= 10;
        else
            this->hour_start += 10;
        break;
        break;
    case 4:
        if(this->hour_start == 23)
            this->hour_start = 20;
        else if(this->hour_start % 10 == 9)
            this->hour_start -= 9;
        else
            this->hour_start++;
        break;

    case 6:
        if(this->minute_start >= 50)
            this->minute_start -= 50;
        else
            this->minute_start += 10;
        break;
    case 7:
        if(this->minute_start % 10 == 9)
            this->minute_start -= 9;
        else
            this->minute_start++;
        break;

    default:
        break;
    }
}

void Alarm::mv_cur_down(int* pos_cursor)
{
    switch(*pos_cursor)
    {
    case 3:
        if(this->hour_start < 10)
        {
            if(this->hour_start >= 4)
                this->hour_start += 10;
            else
                this->hour_start += 20;
        }
        else
            this->hour_start -= 10;
        break;
    case 4:
        if(this->hour_start == 20) // 20 down => 23 
            this->hour_start = 23;
        else if(this->hour_start % 10 == 0)
            this->hour_start += 9;
        else
            this->hour_start--;
        break;

    case 6:
        if(this->minute_start < 10)
            this->minute_start += 50;
        else
            this->minute_start -= 10;
        break;
    case 7:
        if(this->minute_start % 10 == 0)
            this->minute_start += 9;
        else
            this->minute_start--;
        break;

    default:
        break;
    }
}

void Alarm::toggle()
{
    // if(is_running)
    //     is_running = false;
    // else
    // {
    //     this->is_running = true;
    //     this->previous_millis = millis() - (this->current_millis - this->previous_millis);
    // }
}

void Alarm::print(LiquidCrystal* lcd) const
{
    lcd->setCursor(0, 0);
    lcd->print(F("Al"));

    if(this->hour_start >= 10)
        lcd->setCursor(3, 0);
    else
    {
        lcd->setCursor(3, 0);
        lcd->print(0);

        lcd->setCursor(4, 0);
    }
    lcd->print(this->hour_start);

    if(this->minute_start >= 10)
        lcd->setCursor(6, 0);
    else
    {
        lcd->setCursor(6, 0);
        lcd->print(0);

        lcd->setCursor(7, 0);
    }
    lcd->print(this->minute_start);


    if(this->n_repet >= 10)
        lcd->setCursor(9, 0);
    else
    {
        lcd->setCursor(9, 0);
        lcd->print(0);

        lcd->setCursor(10, 0);
    }
    lcd->print(this->n_repet);


    if(this->interval_min_repet >= 10)
        lcd->setCursor(13, 0);
    else
    {
        lcd->setCursor(13, 0);
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

void Alarm::update()
{

}

void Alarm::execute()
{
    // if(this->hour == 0 && this->minute == 0 && this->second == 0)
    // {
    //     is_running = false;
    // }

    // if(this->is_running)
    //     this->update();
}
