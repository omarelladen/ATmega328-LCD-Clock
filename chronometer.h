#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Chronometer {
    private:
        uint8_t s;
        uint8_t m;
        uint8_t h;
        unsigned long previous_millis;
        unsigned long current_millis;
        bool chronometer_is_running;

    public:
        Chronometer();
        ~Chronometer();
        uint8_t getS() const;
        uint8_t getM() const;
        uint8_t getH() const;
        void pause();
        void toggle();
        void reset();
        void secCount();
        void print(LiquidCrystal* lcd) const;
        void update();
        void execute();
};