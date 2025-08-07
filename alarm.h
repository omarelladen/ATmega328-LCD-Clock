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
        void curUp(int8_t* pos_cursor);
        void curDown(int8_t* pos_cursor);
        void print(LiquidCrystal* lcd) const;
        void execute();
};
