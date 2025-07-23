#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Date {
    private:
        int day;
        int month;
        int year;
        int second;
        int minute;
        int hour;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool is_running;

    public:
        Date();
        ~Date();
        void curUpDate(int* pos_cursor);
        void curDownDate(int* pos_cursor);
        void curUpTime(int* pos_cursor);
        void curDownTime(int* pos_cursor);
        void secondCount();
        void print(LiquidCrystal* lcd) const;
        void printDate(LiquidCrystal* lcd) const;
        void printTime(LiquidCrystal* lcd) const;
        void update();
        void execute();
};
