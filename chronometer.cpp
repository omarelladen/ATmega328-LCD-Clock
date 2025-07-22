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
    chronometer_is_running=false;
}

uint8_t Chronometer::getS() const {return s;}

uint8_t Chronometer::getM() const {return m;}

uint8_t Chronometer::getH() const {return h;}

void Chronometer::pause()
{
    chronometer_is_running=false;
}

void Chronometer::toggle()
{
    if(chronometer_is_running)
        chronometer_is_running = false;
    else
    {
        chronometer_is_running = true;
        previous_millis = millis() - (current_millis - previous_millis);
    }
}

void Chronometer::reset()
{
    s=m=h=0;
    chronometer_is_running=false;
}

void Chronometer::secCount()
{
    s++;
    if(s == 60)
    {
        s = 0;
        m++;
    }
    if(m == 60)
    {
        m = 0;
        h++;
    }
}

void Chronometer::print(LiquidCrystal lcd) const
{
    if(h >= 10)
        lcd.setCursor(8, 0);
    else
    {
        lcd.setCursor(8, 0);
        lcd.print(0);

        lcd.setCursor(9, 0);
    }
    lcd.print(h);

    if(m >= 10)
        lcd.setCursor(11, 0);
    else
    {
        lcd.setCursor(11, 0);
        lcd.print(0);

        lcd.setCursor(12, 0);
    }
    lcd.print(m);

    if(s >= 10)
        lcd.setCursor(14, 0);
    else
    {
        lcd.setCursor(14, 0);
        lcd.print(0);

        lcd.setCursor(15, 0);
    }
    lcd.print(s);

    lcd.setCursor(10, 0);
    lcd.print(F(":"));
    lcd.setCursor(13, 0);
    lcd.print(F(":"));
}

void Chronometer::update()
{
    current_millis = millis();
    if(current_millis - previous_millis >= 1000)
    {
        previous_millis = current_millis;
        secCount();
    }
}

void Chronometer::execute()
{
    if(chronometer_is_running)
        update();
}