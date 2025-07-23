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
        void mv_cur_up_date(int* pos_cursor);
        void mv_cur_down_date(int* pos_cursor);
        void mv_cur_up_time(int* pos_cursor);
        void mv_cur_down_time(int* pos_cursor);
        void pause();
        void toggle();
        void reset();
        void secondCount();
        void print(LiquidCrystal* lcd) const;
        void print_date(LiquidCrystal* lcd) const;
        void print_time(LiquidCrystal* lcd) const;
        void update();
        void execute();
};