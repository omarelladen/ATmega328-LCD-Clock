//#include <avr/pgmspace.h>
// #include <Arduino.h>
#include <LiquidCrystal.h>
#include "clock_system.h"
#include "chronometer.h"

#define NUM_SCREENS 7

LiquidCrystal lcd(PIN_RS,PIN_EN,PIN_D4,PIN_D5,PIN_D6,PIN_D7);
int8_t prev_bt_state = BT_NONE;
unsigned long bt_delay = 0;
bool lcd_is_clean = false;
Chronometer chrono;
uint8_t current_menu = 0;

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
    if(current_menu > 0)
    {
        current_menu--;
        lcd_is_clean = false;
    }

}

void down()
{

    if(current_menu < NUM_SCREENS - 1)
    {
        current_menu++;
        lcd_is_clean = false;
    }

}

void select()
{
    // Selection action for each menu
    switch(current_menu)
    {
    case 0:
        toggleLight();
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        chrono.toggle();
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        break;
    }
}

void toggleLight()
{
    if(PORTB & (1 << PB2)) // PB2 = pino digital 10 (PIN_BACK_LIGHT)
    {
        PORTB&=!(1<<PB2); // digitalWrite(PIN_BACK_LIGHT, LOW);
    }
    else
    {
        PORTB|=(1<<PB2); // digitalWrite(PIN_BACK_LIGHT, HIGH);
    }

    lcd_is_clean = false;
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
        ;
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
    
    
    lcd.setCursor(0, 1);
    lcd.print(current_menu);

    // Print for each menu
    switch(current_menu)
    {
    case 0:
        lcd.setCursor(0, 0);
        if(PORTB & (1 << PB2)) // PB2 = pino digital 10 (PIN_BACK_LIGHT)
            lcd.print(F("Light on"));        
        else
            lcd.print(F("Light off"));
        break;
    case 1:
        // date.print(&lcd);
        break;
    case 2:
        // date.edit_time(&lcd);
        break;
    case 3:
        // date.edit_date(&lcd);
        break;
    case 4:
        chrono.print(&lcd);
        break;
    case 5:
        // timer.exe(&lcd);
        break;
    case 6:
        break;
        // alarm.exe(&lcd);
    default:
        break;
    }

    if(!lcd_is_clean)
        clearScreen();
    
    chrono.execute();
}