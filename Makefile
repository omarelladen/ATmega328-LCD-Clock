SRC = src/main.ino
PORT = /dev/ttyACM0
BOARD = "arduino:avr:uno"


.PHONY: all verify upload

all: verify

verify:
	arduino --verify \
	        --board $(BOARD) \
	        $(SRC)

upload:
	arduino --upload \
	        --board $(BOARD) \
	        --port $(PORT) \
	        $(SRC)
