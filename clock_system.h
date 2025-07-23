//#include <avr/pgmspace.h>
// #include <Arduino.h>
#include <LiquidCrystal.h>
#include "chronometer.h"
#include "date.h"
#include "timer.h"
#include "alarm.h"

// Pins
#define PIN_BOTOES A0
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7
#define PIN_RS 8
#define PIN_EN 9
#define PIN_BACK_LIGHT 10

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

