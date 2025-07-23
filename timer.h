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
        void mv_cur_up(int* pos_cursor);
        void mv_cur_down(int* pos_cursor);
        void pause();
        void toggle();
        void secondCount();
        void print(LiquidCrystal* lcd) const;
        void update();
        void execute();
};