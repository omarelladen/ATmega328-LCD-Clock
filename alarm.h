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
        void curUp(int* pos_cursor);
        void curDown(int* pos_cursor);
        void print(LiquidCrystal* lcd) const;
        void update();
        void execute();
};
