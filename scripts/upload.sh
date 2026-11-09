#!/bin/sh

CODE=src/clock_system.ino
PORT=/dev/ttyACM0

arduino --upload "$CODE" \
        --port "$PORT"
