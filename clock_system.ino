//#include <avr/pgmspace.h>
// #include <Arduino.h>
#include <LiquidCrystal.h>
#include "clock_system.h"
#include "chronometer.h"

LiquidCrystal lcd(PIN_RS,PIN_EN,PIN_D4,PIN_D5,PIN_D6,PIN_D7);
int8_t prev_bt_state = BT_NONE;
unsigned long bt_delay = 0;
bool lcd_is_clean = false;
Chronometer chrono;

void setup()
{
    // Luz
    pinMode(PIN_BACK_LIGHT, OUTPUT); // DDRB|=(1<<DDB2);
    digitalWrite(PIN_BACK_LIGHT, HIGH); // PORTB|=(1<<PB2);

    lcd.begin(16, 2);
    Serial.begin(9600);
}


void clearScreen()
{
    lcd.clear();
    lcd_is_clean = true;
}

void back()
{
    chrono.reset();
}

void up()
{
}

void down()
{

}

void select()
{
    chrono.toggle();
}

void toggleLight()
{
    if(PORTB & (1 << PB2)) // PB2 = pino digital 10 (PIN_BACK_LIGHT)
        PORTB&=!(1<<PB2); // digitalWrite(PIN_BACK_LIGHT, LOW);
    else
        PORTB|=(1<<PB2); // digitalWrite(PIN_BACK_LIGHT, HIGH);
}

void botaoSolto(int8_t bt)
{
    if (bt == BT_DOWN)
        down();
    else if(bt == BT_UP)
        up();
    else if (bt == BT_SELECT)
        select();
    else if(bt == BT_LEFT)
        back();
    else if(bt == BT_RIGHT)
        toggleLight();
}

uint8_t checkButtonPress()
{
    int16_t bt_analog_value = analogRead(PIN_BOTOES);

    int8_t bt = -1;
    if ((bt_analog_value < SEL_THRESHOLD) and (bt_analog_value >= LEFT_THRESHOLD))
        bt = (BT_SELECT);
    else if((bt_analog_value < LEFT_THRESHOLD) and (bt_analog_value >= UP_THRESHOLD))
        bt = (BT_LEFT);
    else if((bt_analog_value < UP_THRESHOLD) and (bt_analog_value >= DOWN_THRESHOLD))
        bt = (BT_DOWN);
    else if((bt_analog_value < DOWN_THRESHOLD) and (bt_analog_value >= RIGHT_THRESHOLD))
        bt = (BT_UP);
    else if(bt_analog_value < RIGHT_THRESHOLD)
        bt = (BT_RIGHT);
    else 
        bt = (BT_NONE);

    return bt;
}

void handleButtonPress(int8_t bt)
{

    //Quando o botao for apertado ou solto
    if((millis() - bt_delay) > DEBOUNCE_TIME)
    {
        // Apertado
        // if ((bt != BT_NONE) and (prev_bt_state == BT_NONE) )
        // {
        //   bt_delay = millis();
        // }

        // Solto
        if((bt == BT_NONE) and (prev_bt_state != BT_NONE) )
        {
            botaoSolto(prev_bt_state);
            bt_delay = millis();
        }
    }
    prev_bt_state = bt;
}


void loop()
{
    uint8_t bt_pressed = checkButtonPress();
    handleButtonPress(bt_pressed);
    chrono.execute();
    chrono.print(lcd);
    // Serial.println(millis());
}