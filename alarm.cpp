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
    // switch(*pos_cursor)
    // {
    // case 8:
    //     if(this->hour >= 90)
    //         this->hour -= 90;
    //     else
    //         this->hour += 10;
    //     break;
    // case 9:
    //     if(this->hour % 10 == 9)
    //         this->hour -= 9;
    //     else
    //         this->hour++;
    //     break;

    // case 11:
    //     if(this->minute >= 50)
    //         this->minute -= 50;
    //     else
    //         this->minute += 10;
    //     break;
    // case 12:
    //     if(this->minute % 10 == 9)
    //         this->minute -= 9;
    //     else
    //         this->minute++;
    //     break;

    // case 14:
    //     if(this->second >= 50)
    //         this->second -= 50;
    //     else
    //         this->second += 10;
    //     break;
    // case 15:
    //     if(this->second % 10 == 9)
    //         this->second -= 9;
    //     else
    //         this->second++;
    //     break;
    // default:
    //     break;
    // }
}

void Alarm::mv_cur_down(int* pos_cursor)
{
    // switch(*pos_cursor)
    // {
    // case 8:
    //     if(this->hour <= 10)
    //         this->hour += 90;
    //     else
    //         this->hour -= 10;
    //     break;
    // case 9:
    //     if(this->hour % 10 == 0)
    //         this->hour += 9;
    //     else
    //         this->hour--;
    //     break;

    // case 11:
    //     if(this->minute < 10)
    //         this->minute += 50;
    //     else
    //         this->minute -= 10;
    //     break;
    // case 12:
    //     if(this->minute % 10 == 0)
    //         this->minute += 9;
    //     else
    //         this->minute--;
    //     break;

    // case 14:
    //     if(this->second < 10)
    //         this->second += 50;
    //     else
    //         this->second -= 10;
    //     break;
    // case 15:
    //     if(this->second % 10 == 0)
    //         this->second += 9;
    //     else
    //         this->second--;
    //     break;
    // default:
    //     break;
    // }
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
