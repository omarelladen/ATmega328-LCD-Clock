#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Alarm {
    private:
        int minute_start;
        int hour_start;
        int n_repet;
        int interval_min_repet;
        bool is_active;
    public:
        Alarm();
        ~Alarm();
        void mv_cur_up(int* pos_cursor);
        void mv_cur_down(int* pos_cursor);
        void toggle();
        void print(LiquidCrystal* lcd) const;
        void update();
        void execute();
};