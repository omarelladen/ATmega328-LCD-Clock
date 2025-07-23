#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Date {
    private:
        uint8_t day;
        uint8_t month;
        uint8_t year;
        uint8_t second;
        uint8_t minute;
        uint8_t hour;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool is_running;

    public:
        Date();
        ~Date();
        void pause();
        void toggle();
        void reset();
        void secondCount();
        void print(LiquidCrystal* lcd) const;
        void print_date(LiquidCrystal* lcd) const;
        void print_time(LiquidCrystal* lcd) const;
        void update();
        void execute();
};