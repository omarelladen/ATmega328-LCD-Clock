#include "chronometer.h"

Chronometer::Chronometer():
s(0),
m(0),
h(0),
previous_millis(millis()),
current_millis(0),
chronometer_is_running(false)
{
}

Chronometer::~Chronometer()
{
}

uint8_t Chronometer::getS() const {return this->s;}

uint8_t Chronometer::getM() const {return this->m;}

uint8_t Chronometer::getH() const {return this->h;}

void Chronometer::pause()
{
    this->chronometer_is_running=false;
}

void Chronometer::toggle()
{
    if(chronometer_is_running)
        chronometer_is_running = false;
    else
    {
        this->chronometer_is_running = true;
        this->previous_millis = millis() - (this->current_millis - this->previous_millis);
    }
}

void Chronometer::reset()
{
    this->s=this->m=this->h=0;
    this->chronometer_is_running=false;
}

void Chronometer::secCount()
{
    this->s++;
    if(this->s == 60)
    {
        this->s = 0;
        this->m++;
    }
    if(this->m == 60)
    {
        this->m = 0;
        this->h++;
    }
}

void Chronometer::print(LiquidCrystal* lcd) const
{
    if(this->h >= 10)
        lcd->setCursor(8, 0);
    else
    {
        lcd->setCursor(8, 0);
        lcd->print(0);

        lcd->setCursor(9, 0);
    }
    lcd->print(this->h);

    if(this->m >= 10)
        lcd->setCursor(11, 0);
    else
    {
        lcd->setCursor(11, 0);
        lcd->print(0);

        lcd->setCursor(12, 0);
    }
    lcd->print(this->m);

    if(this->s >= 10)
        lcd->setCursor(14, 0);
    else
    {
        lcd->setCursor(14, 0);
        lcd->print(0);

        lcd->setCursor(15, 0);
    }
    lcd->print(this->s);

    lcd->setCursor(10, 0);
    lcd->print(F(":"));
    lcd->setCursor(13, 0);
    lcd->print(F(":"));
}

void Chronometer::update()
{
    this->current_millis = millis();
    if(this->current_millis - this->previous_millis >= 1000)
    {
        this->previous_millis = this->current_millis;
        this->secCount();
    }
}

void Chronometer::execute()
{
    if(this->chronometer_is_running)
        this->update();
}