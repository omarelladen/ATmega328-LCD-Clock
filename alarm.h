#pragma once
#include "date.h"

class Alarm {
    private:
        int8_t minute_start;
        int8_t hour_start;
        int8_t n_repet;
        int8_t interval_min_repet;
        bool is_active;
        bool is_alarm_on;
        Date* date;

    public:
        Alarm(Date* date);
        ~Alarm();
        void curUp(const int8_t pos_cursor);
        void curDown(const int8_t pos_cursor);
        void print(const LiquidCrystal* lcd) const;
        void execute();
};
