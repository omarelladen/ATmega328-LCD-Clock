SKETCH = src/main.ino
PORT = /dev/ttyACM0
BOARD = "arduino:avr:uno"


.PHONY: all verify upload

all: verify

verify:
	arduino --verify \
	        --board $(BOARD) \
	        $(SKETCH)

upload:
	arduino --upload \
	        --board $(BOARD) \
	        --port $(PORT) \
	        $(SKETCH)
