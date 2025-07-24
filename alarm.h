#pragma once
#include "date.h"

class Alarm {
    private:
        int minute_start;
        int hour_start;
        int n_repet;
        int interval_min_repet;
        bool is_active;
        bool is_alarm_on;
        Date* date;

    public:
        Alarm(Date* date);
        ~Alarm();
        void curUp(int* pos_cursor);
        void curDown(int* pos_cursor);
        void print(LiquidCrystal* lcd) const;
        void execute();
};
