#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Timer {
    private:
        int8_t second;
        int8_t minute;
        int8_t hour;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool is_running;
        
    public:
        Timer();
        ~Timer();
        void curUp(int8_t* pos_cursor);
        void curDown(int8_t* pos_cursor);
        void toggle();
        void secondCount();
        void print(LiquidCrystal* lcd) const;
        void update();
        void execute();
};
