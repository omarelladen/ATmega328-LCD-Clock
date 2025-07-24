//#include <avr/pgmspace.h>
// #include <Arduino.h>
#include <LiquidCrystal.h>
#include "chronometer.h"
#include "date.h"
#include "timer.h"
#include "alarm.h"

// Pins
#define PIN_BUTTONS A0
#define PIN_D4_LCD 4
#define PIN_D5_LCD 5
#define PIN_D6_LCD 6
#define PIN_D7_LCD 7
#define PIN_RS_LCD 8
#define PIN_EN_LCD 9
#define PIN_BACK_LIGHT_LCD 10
#define PIN_D0 0
#define PIN_D1 1
#define PIN_D2 2
#define PIN_D3 3
#define PIN_D11 11
#define PIN_D12 12
#define PIN_D13 13



#define DEBOUNCE_TIME 50

// Analog voltage for LCD shield buttons
#define SEL_THRESHOLD   800
#define LEFT_THRESHOLD  600
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  200
#define RIGHT_THRESHOLD  60

// Buttons
#define BT_NONE 0
#define BT_SELECT 1
#define BT_LEFT   2
#define BT_UP     3
#define BT_DOWN   4
#define BT_RIGHT  5

#define NUM_SCREENS 6


void setup();
void loop();
void clearScreen();
void btLeft();
void btRight();
void btUp();
void btDown();
void btSelect();
void toggleLight();
int checkButtonPress();
void handleButtonPress(int bt);
