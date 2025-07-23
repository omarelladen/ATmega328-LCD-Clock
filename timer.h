#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Timer {
    private:
        int second;
        int minute;
        int hour;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool is_running;
    public:
        Timer();
        ~Timer();
        void curUp(int* pos_cursor);
        void curDown(int* pos_cursor);
        void toggle();
        void secondCount();
        void print(LiquidCrystal* lcd) const;
        void update();
        void execute();
};
