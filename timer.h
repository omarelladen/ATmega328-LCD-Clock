#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Timer {
    private:
        uint8_t second;
        uint8_t minute;
        uint8_t hour;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool is_running;
        uint8_t pos_cursor;

    public:
        Timer();
        ~Timer();
        void mv_cur_up();
        void mv_cur_down();
        void mv_cur_left();
        void mv_cur_right();
        void pause();
        void toggle();
        void reset();
        void secondCount();
        void print(LiquidCrystal* lcd) const;
        void update();
        void execute();
};