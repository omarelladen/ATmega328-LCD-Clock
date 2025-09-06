#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Chronometer {
    private:
        int8_t second;
        int8_t minute;
        int8_t hour;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool is_running;

    public:
        Chronometer();
        ~Chronometer();
        void curUp(const int8_t pos_cursor);
        void curDown(const int8_t pos_cursor);
        void toggle();
        void secondCount();
        void print(const LiquidCrystal* lcd) const;
        void update();
        void execute();
};
