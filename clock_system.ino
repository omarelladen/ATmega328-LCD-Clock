#include <LiquidCrystal.h>

#include "defines.h"

#include "chronometer.h"
#include "date.h"
#include "timer.h"
#include "alarm.h"


LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
Date g_date;
Timer g_timer;
Chronometer g_chrono;
Alarm g_alarm(&g_date);

bool g_lcd_is_clean = false;
bool g_light_is_on = true;
int g_current_menu = 0;
int g_pos_cursor = 0;
int g_prev_bt_state = BT_NONE;
unsigned long g_bt_delay = 0;


void setup()
{
    pinMode(PIN_LCD_LIGHT, INPUT);

    lcd.begin(16, 2);

    Serial.begin(9600);
    while (!Serial);
}


void clearScreen()
{
    lcd.clear();
    g_lcd_is_clean = true;
}

void toggleLight()
{
    if(g_light_is_on)
    {
        pinMode(PIN_LCD_LIGHT, OUTPUT);
        digitalWrite(PIN_LCD_LIGHT, LOW);
        g_light_is_on = false;
    }
    else
    {
        pinMode(PIN_LCD_LIGHT, INPUT);
        g_light_is_on = true;
    }
}

void btLeft()
{
    if(g_current_menu == 1 || g_current_menu == 2 || g_current_menu == 3 || g_current_menu == 4)
    {    
        if(g_pos_cursor == 8)
        {
            g_pos_cursor = 0;
            g_lcd_is_clean = false;
        }
        else if(g_pos_cursor > 8)
        {
            if(g_pos_cursor == 11 || g_pos_cursor == 14)
                g_pos_cursor -= 2;
            else
                g_pos_cursor--;
            g_lcd_is_clean = false;
        }
    }
    else if(g_current_menu == 5)
    {
        if(g_pos_cursor == 3)
        {
            g_pos_cursor = 0;
            g_lcd_is_clean = false;
        }
        else if(g_pos_cursor > 2)
        {
            if(g_pos_cursor == 6 || g_pos_cursor == 9)
                g_pos_cursor -= 2;
            else if(g_pos_cursor == 13)
                g_pos_cursor -= 3;
            else
                g_pos_cursor--;
            g_lcd_is_clean = false;
        } 
    }
}

void btRight()
{
    if(g_current_menu == 1 || g_current_menu == 2 || g_current_menu == 3 || g_current_menu == 4)
    {   
        if(g_pos_cursor == 0)
        {
            g_pos_cursor = 8;
            g_lcd_is_clean = false;
        }
        else if(g_pos_cursor < 15)
        {
            if(g_pos_cursor == 9 || g_pos_cursor == 12)
                g_pos_cursor += 2;
            else
                g_pos_cursor++;
            g_lcd_is_clean = false;
        }
    }
    else if(g_current_menu == 5)
    {
        if(g_pos_cursor == 0)
        {
            g_pos_cursor = 3;
            g_lcd_is_clean = false;
        }
        else if(g_pos_cursor < 14)
        {
            if(g_pos_cursor == 4 || g_pos_cursor == 7)
                g_pos_cursor += 2;
            else if(g_pos_cursor == 10)
                g_pos_cursor += 3;
            else
                g_pos_cursor++;
            g_lcd_is_clean = false;
        }
    }
}

void btUp()
{
    if(g_pos_cursor == 0)
    {
       if(g_current_menu > 0)
        {
            g_current_menu--;
            g_lcd_is_clean = false;
        }
    } 
    else
    {
        switch(g_current_menu)
        {
        case 0:
            break;
        case 1:
            g_date.curUpDate(&g_pos_cursor);
            break;
        case 2:
            g_date.curUpTime(&g_pos_cursor);
            break;
        case 3:
            g_chrono.curUp(&g_pos_cursor);
            break;
        case 4:
            g_timer.curUp(&g_pos_cursor);
            break;
        case 5:
            g_alarm.curUp(&g_pos_cursor);
            break;
        default:
            break;
        }
    }
}

void btDown()
{
    if(g_pos_cursor == 0)
    {
        if(g_current_menu < NUM_SCREENS - 1)
        {
            g_current_menu++;
            g_lcd_is_clean = false;
        }
    }
    else
    {
        switch(g_current_menu)
        {
        case 0:
            break;
        case 1:
            g_date.curDownDate(&g_pos_cursor);
            break;
        case 2:
            g_date.curDownTime(&g_pos_cursor);
            break;
        case 3:
            g_chrono.curDown(&g_pos_cursor);
            break;
        case 4:
            g_timer.curDown(&g_pos_cursor);
            break;
        case 5:
            g_alarm.curDown(&g_pos_cursor);
            break;
        default:
            break;
        }
    }
}

void btSelect()
{
    // Selection action for each menu
    switch(g_current_menu)
    {
    case 0:
        toggleLight();
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        g_chrono.toggle();
        break;
    case 4:
        g_timer.toggle();
        break;
    case 5:
        break;
    default:
        break;
    }
}

void btReleased(int bt)
{
    if (bt == BT_DOWN)
        btDown();
    else if(bt == BT_UP)
        btUp();
    else if (bt == BT_SELECT)
        btSelect();
    else if(bt == BT_LEFT)
        btLeft();
    else if(bt == BT_RIGHT)
        btRight();
}

int checkButtonPress()
{
    int bt_analog_value = analogRead(PIN_SHIELD_BTS);

    int bt;
    if ((bt_analog_value < SEL_THRESHOLD) and (bt_analog_value >= LEFT_THRESHOLD))
        bt = BT_SELECT;
    else if((bt_analog_value < LEFT_THRESHOLD) and (bt_analog_value >= UP_THRESHOLD))
        bt = BT_LEFT;
    else if((bt_analog_value < UP_THRESHOLD) and (bt_analog_value >= DOWN_THRESHOLD))
        bt = BT_DOWN;
    else if((bt_analog_value < DOWN_THRESHOLD) and (bt_analog_value >= RIGHT_THRESHOLD))
        bt = BT_UP;
    else if(bt_analog_value < RIGHT_THRESHOLD)
        bt = BT_RIGHT;
    else
        bt = BT_NONE;

    return bt;
}

void handleButtonPress(int bt)
{
    if((millis() - g_bt_delay) > DEBOUNCE_TIME)
    {
        if((bt == BT_NONE) and (g_prev_bt_state != BT_NONE) )
        {
            btReleased(g_prev_bt_state);
            g_bt_delay = millis();
        }
    }
    g_prev_bt_state = bt;
}


void loop()
{
    // Event Management
    int bt_pressed = checkButtonPress();
    handleButtonPress(bt_pressed);
    
    // Print current menu
    switch(g_current_menu)
    {
    case 0:
        g_date.print(&lcd);
        break;
    case 1:
        g_date.printDate(&lcd);
        break;
    case 2:
        g_date.printTime(&lcd);
        break;
    case 3:
        g_chrono.print(&lcd);
        break;
    case 4:
        g_timer.print(&lcd);
        break;
    case 5:
        g_alarm.print(&lcd);
        break;

    default:
        break;
    }

    // Print cursor
    if(g_pos_cursor != 0)
    {
        lcd.setCursor(g_pos_cursor, 1);
        lcd.print(F("-"));
    }

    // Clear screen if needed
    if(!g_lcd_is_clean)
        clearScreen();
    
    // Executions on background
    g_date.execute();
    g_chrono.execute();
    g_timer.execute();
    g_alarm.execute();
}
