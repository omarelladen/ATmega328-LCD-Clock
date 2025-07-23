#include "clock_system.h"



LiquidCrystal lcd(PIN_RS,PIN_EN,PIN_D4,PIN_D5,PIN_D6,PIN_D7);
int prev_bt_state = BT_NONE;
unsigned long bt_delay = 0;
bool lcd_is_clean = false;
Date date;
Timer timer;
Chronometer chrono;
Alarm alarm;
int current_menu = 0;
int pos_cursor = 0;

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

void bt_left()
{
    if(current_menu == 1 || current_menu == 2 || current_menu == 3 || current_menu == 4)
    {    
        if(pos_cursor == 8)
        {
            pos_cursor = 0;
            lcd_is_clean = false;
        }
        else if(pos_cursor > 8)
        {
            if(pos_cursor == 11 || pos_cursor == 14)
                pos_cursor -= 2;
            else
                pos_cursor--;
            lcd_is_clean = false;
        }
    }
    else if(current_menu == 5)
    {
        if(pos_cursor == 3)
        {
            pos_cursor = 0;
            lcd_is_clean = false;
        }
        else if(pos_cursor > 2)
        {
            if(pos_cursor == 6 || pos_cursor == 9)
                pos_cursor -= 2;
            else if(pos_cursor == 13)
                pos_cursor -= 3;
            else
                pos_cursor--;
            lcd_is_clean = false;
        } 
    }
}

void bt_right()
{
    if(current_menu == 1 || current_menu == 2 || current_menu == 3 || current_menu == 4)
    {   
        if(pos_cursor == 0)
        {
            pos_cursor = 8;
            lcd_is_clean = false;
        }
        else if(pos_cursor < 15)
        {
            if(pos_cursor == 9 || pos_cursor == 12)
                pos_cursor += 2;
            else
                pos_cursor++;
            lcd_is_clean = false;
        }
    }
    else if(current_menu == 5)
    {
        if(pos_cursor == 0)
        {
            pos_cursor = 3;
            lcd_is_clean = false;
        }
        else if(pos_cursor < 14)
        {
            if(pos_cursor == 4 || pos_cursor == 7)
                pos_cursor += 2;
            else if(pos_cursor == 10)
                pos_cursor += 3;
            else
                pos_cursor++;
            lcd_is_clean = false;
        }
    }
}

void bt_up()
{
    if(pos_cursor == 0)
    {
       if(current_menu > 0)
        {
            current_menu--;
            lcd_is_clean = false;
        }
    } 
    else
    {
        switch(current_menu)
        {
        case 0:
            break;
        case 1:
            date.mv_cur_up_date(&pos_cursor);
            break;
        case 2:
            date.mv_cur_up_time(&pos_cursor);
            break;
        case 3:
            chrono.mv_cur_up(&pos_cursor);
            break;
        case 4:
            timer.mv_cur_up(&pos_cursor);
            break;
        case 5:
            alarm.mv_cur_up(&pos_cursor);
            break;
        default:
            break;
        }
    }
}

void bt_down()
{
    if(pos_cursor == 0)
    {
        if(current_menu < NUM_SCREENS - 1)
        {
            current_menu++;
            lcd_is_clean = false;
        }
    }
    else
    {
        switch(current_menu)
        {
        case 0:
            break;
        case 1:
            date.mv_cur_down_date(&pos_cursor);
            break;
        case 2:
            date.mv_cur_down_time(&pos_cursor);
            break;
        case 3:
            chrono.mv_cur_down(&pos_cursor);
            break;
        case 4:
            timer.mv_cur_down(&pos_cursor);
            break;
        case 5:
            alarm.mv_cur_down(&pos_cursor);
            break;
        default:
            break;
        }
    }
}

void bt_select()
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
        chrono.toggle();
        break;
    case 4:
        timer.toggle();
        break;
    case 5:
        break;
    default:
        break;
    }
}

void toggleLight()
{
    if(PORTB & (1 << PB2)) // PB2 = pino digital 10 (PIN_BACK_LIGHT)
        PORTB&=!(1<<PB2); // digitalWrite(PIN_BACK_LIGHT, LOW);
    else
        PORTB|=(1<<PB2); // digitalWrite(PIN_BACK_LIGHT, HIGH);
    lcd_is_clean = false;
}

void botaoSolto(int bt)
{
    if (bt == BT_DOWN)
        bt_down();
    else if(bt == BT_UP)
        bt_up();
    else if (bt == BT_SELECT)
        bt_select();
    else if(bt == BT_LEFT)
        bt_left();
    else if(bt == BT_RIGHT)
        bt_right();
}

int checkButtonPress()
{
    int16_t bt_analog_value = analogRead(PIN_BOTOES);

    int bt = -1;
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

    //Quando o botao for apertado ou solto
    if((millis() - bt_delay) > DEBOUNCE_TIME)
    {
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
    int bt_pressed = checkButtonPress();
    handleButtonPress(bt_pressed);
    

    // Print each menu
    switch(current_menu)
    {
    case 0:
        lcd.setCursor(0, 0);
        lcd.print(F("Light"));
        lcd.setCursor(0, 1);
        if(PORTB & (1 << PB2)) // PB2 = pino digital 10 (PIN_BACK_LIGHT)
            lcd.print(F("on"));        
        else
            lcd.print(F("off"));

        date.print(&lcd);
        break;
    case 1:
        date.print_date(&lcd);
        break;
    case 2:
        date.print_time(&lcd);
        break;
    case 3:
        chrono.print(&lcd);
        break;
    case 4:
        timer.print(&lcd);
        break;
    case 5:
        alarm.print(&lcd);
        break;
    default:
        break;
    }

    if(!lcd_is_clean)
        clearScreen();
    
    date.execute();
    chrono.execute();
    timer.execute();


    // Print cursor
    if(pos_cursor != 0)
    {
        lcd.setCursor(pos_cursor, 1);
        lcd.print(F("-"));
    }
}
