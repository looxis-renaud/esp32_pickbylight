# esp32_pickbylight
ESP32 Microcontroller to control an WS2812b LED Matrix for a Pick By Light System

## Color Picker
- https://www.rapidtables.com/web/color/RGB_Color.html

## Requirements

- install FastLED library https://github.com/FastLED/FastLED
## ChatGPT Prompt

using an esp32 microcontroller and the fastled library, I want to control a matrix of ws2812b addressable LEDs for a "pick by light" system

I have 15 sets of 3 LEDs each (45 LED total), in 3 rows and 5 columns.
The rows are labeled A, B and C
the columns are labeled 1, 2, 3, 4 and 5, the LEDs are positioned and wired accordingly.

I have variables "action", status, "row" and "column"
row instructs the microcontroller in which row the 3 LEDs are,
column instructs the microcontroller at which position the 3 LEDs are,
action instructs the microcontroller in which color the LEDs should blink for 10 seconds
status instructs the microcontroller in which color the LED should light up after the 10 seconds of blinking.

Examples:
When I receive the values (over ESP-Now Communication protocol for example):
row = A
column = 3
action = pick
status = full

then I want the 3 LEDs at position "A3" to blink pink (Red = 255, Green = 0, Blue = 255) for 10 seconds and light up RED afterwards until further instructions are received.

When I receive the values
row = B
column = 4
action = place
status = full

then I want the 3 LEDs at position "B4" to blink turquoise (Red = 0, Green = 255, Blue = 255) for 10 seconds and turn Red afterwards until new instructions are received.

The reception of the values
row = C
column = 1
action = pick
status = empty

should let the 3 LEDs at position "C1" blink in Pink color again for 10 seconds, but turn the LEDs green after that until further notice.

Please write the basic code for this.

