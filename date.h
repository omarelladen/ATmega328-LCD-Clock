#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Date {
    private:
        int8_t day;
        int8_t month;
        int8_t year;
        int8_t second;
        int8_t minute;
        int8_t hour;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool is_running;

    public:
        Date();
        ~Date();
        int8_t getHour() const;
        int8_t getMinute() const;
        void curUpDate(const int8_t pos_cursor);
        void curDownDate(const int8_t pos_cursor);
        void curUpTime(const int8_t pos_cursor);
        void curDownTime(const int8_t pos_cursor);
        void secondCount();
        void printDateAndTime(const LiquidCrystal* lcd) const;
        void printDate(const LiquidCrystal* lcd) const;
        void printTime(const LiquidCrystal* lcd) const;
        void update();
        void execute();
};
