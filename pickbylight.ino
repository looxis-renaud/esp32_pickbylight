/*
* Prompt written by Etienne
* Coded by ChatGPT
*/

#include <FastLED.h>

#define NUM_LEDS 45
#define DATA_PIN 2
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// Define the number of rows and columns
#define NUM_ROWS 3
#define NUM_COLS 5

// Define colors
CRGB pink(255, 0, 255);
CRGB turquoise(0, 255, 255);
CRGB red(255, 0, 0);
CRGB green(0, 255, 0);

// Define color indices for action and status
#define ACTION_PICK 0
#define ACTION_PLACE 1
#define STATUS_FULL 0
#define STATUS_EMPTY 1

// Map row and column labels to array indices
char rowLabels[NUM_ROWS] = {'A', 'B', 'C'};
char colLabels[NUM_COLS] = {'1', '2', '3', '4', '5'};

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(100);  // Set LED brightness
}

void loop() {
  // Example values
  char row = 'A';  // Example row
  char column = '3';  // Example column
  char action = 'p';  // 'p' for pick, 'l' for place
  char status = 'f';  // 'f' for full, 'e' for empty

  // Convert row and column labels to indices
  int rowIndex = -1;
  int colIndex = -1;
  for (int i = 0; i < NUM_ROWS; i++) {
    if (rowLabels[i] == row) {
      rowIndex = i;
      break;
    }
  }
  for (int i = 0; i < NUM_COLS; i++) {
    if (colLabels[i] == column) {
      colIndex = i;
      break;
    }
  }

  // Check if row and column are valid
  if (rowIndex == -1 || colIndex == -1) {
    // Invalid row or column
    return;
  }

  // Set LED index based on row and column
  int ledIndex = (rowIndex * NUM_COLS) + colIndex;

  // Set LED color based on action and status
  CRGB color;
  if (action == 'p') {
    if (status == 'f') {
      color = pink;
    } else {
      color = green;
    }
  } else {
    if (status == 'f') {
      color = turquoise;
    } else {
      color = red;
    }
  }

  // Blink LEDs for 10 seconds
  for (int i = 0; i < 100; i++) {
    leds[ledIndex] = color;
    FastLED.show();
    delay(50);  // 50ms delay for 10Hz blinking
    leds[ledIndex] = CRGB::Black;
    FastLED.show();
    delay(50);  // 50ms delay for 10Hz blinking
  }

  // Set LED color after blinking
  if (status == 'f') {
    leds[ledIndex] = red;  // Change to red if status is full
  } else {
    leds[ledIndex] = green;  // Change to green if status is empty
  }
  FastLED.show();

  // Wait for further instructions
  // You can implement communication protocol here to receive new instructions
}
