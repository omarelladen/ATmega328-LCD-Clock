#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Chronometer {
    private:
        uint8_t second;
        uint8_t minute;
        uint8_t hour;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool is_running;

    public:
        Chronometer();
        ~Chronometer();
        void mv_cur_up(uint8_t* pos_cursor);
        void mv_cur_down(uint8_t* pos_cursor);
        void pause();
        void toggle();
        void secondCount();
        void print(LiquidCrystal* lcd) const;
        void update();
        void execute();
};