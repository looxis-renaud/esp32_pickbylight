#include <Adafruit_NeoPixel.h>

// Define variables
int slotRow; // variable for Row
int slotCol; // variable for Slot
bool isPlacingItem; // True/1 = place item (blue) | False/0 = pick item (green)
bool isStatusFull; // True/1 = Full (red) | False/0 = Empty (light off) 


// Define constants
const int NUM_LEDS = 144;
const int LEDS_PER_GROUP = 3;
const int NUM_GROUPS = NUM_LEDS / LEDS_PER_GROUP;
const int NUM_ROWS = 4;
const int NUM_COLS = 12;
const int LED_PIN = 14; // Change to match your Arduino pin
const int BRIGHTNESS = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Define mapping array to map LED groups to slots
int slotMapping[NUM_GROUPS][2]; // 2-dimensional array to store row and column for each slot

void executeAction();

void setup() {
  Serial.begin(115200); // Initialize serial communication

  // ToDo Initialize websockets

  strip.begin();
  strip.setBrightness(20);  // Set LED brightness
  strip.show();             // Initialize all pixels to 'off'

  mapLEDsToSlots();   // Map LEDs to slots
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    // Read the incoming line
    String input = Serial.readStringUntil('\n');
    
    // Parse the input line
    int values[4]; // Array to store col, row, and action values
    int index = 0;
    char* token = strtok(const_cast<char*>(input.c_str()), ",");
    while (token != NULL && index < 4) {
      values[index++] = atoi(token); // Convert string to integer
      token = strtok(NULL, ",");
    }
    
    // Assign values to variables
    if (index == 4) {
      slotRow = values[0];
      slotCol = values[1];
      isPlacingItem = values[2];
      isStatusFull = values[3];

      
      // Execute action to send info back to serial monitor
      executeAction();


    if (isPlacingItem) {
      blinkLEDs(slotRow, slotCol, 0, 0, 255, 0); // Blue color for placing item
      } else {
      blinkLEDs(slotRow, slotCol, 0, 255, 0, 0); // Green color for picking item
    }

  delay(5000); // Wait for 5 seconds
  }
 }
}

// Function to execute action
void executeAction() {
  // Your code to perform the action based on the received variables
  // For example:
  Serial.print("Received command: ");
  Serial.print("Row: ");
  Serial.print(slotRow);
  Serial.print(", Col: ");
  Serial.print(slotCol);
  Serial.print(", Action: ");
  Serial.print(isPlacingItem ? "Place" : "Pick");
  Serial.print(", Status: ");
  Serial.println(isStatusFull ? "Full" : "Empty");

}

// Function to map LEDs to slots
void mapLEDsToSlots() {
  int groupIndex = 0;
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      slotMapping[groupIndex][0] = row; // Store row
      slotMapping[groupIndex][1] = col; // Store column
      groupIndex++;
      if (groupIndex >= NUM_GROUPS) {
        return; // All LEDs are mapped
      }
    }
  }
}

// Function to control LED strip based on slot action
void controlLEDStrip(int slotRow, int slotCol, bool isPlacingItem, int red, int green, int blue, int white) {
  // Calculate LED group index from slot row and column
  int groupIndex = slotRow * NUM_COLS + slotCol;

  // Calculate LED indices within the group
  int startLEDIndex = groupIndex * LEDS_PER_GROUP;
  
  // Turn LEDs on or off based on action
  if (isPlacingItem) {
    // Turn LEDs on
    for (int i = 0; i < LEDS_PER_GROUP; i++) {
      // Turn on LED at startLEDIndex + i
      strip.setPixelColor(startLEDIndex + i, strip.Color(red, green, blue, 0)); // White color
    }
  } else {
    // Turn LEDs off
    for (int i = 0; i < LEDS_PER_GROUP; i++) {
      // Turn off LED at startLEDIndex + i
      strip.setPixelColor(startLEDIndex + i, strip.Color(0, 0, 0, 0)); // Off
    }
  }
}

// Function to blink LEDs in a specific color for 5 seconds
void blinkLEDs(int slotRow, int slotCol, int red, int green, int blue, int white) {
  for (int i = 0; i < 10; i++) { // Blink for 5 seconds (10 times with 500ms delay)
    controlLEDStrip(slotRow, slotCol, true, red, green, blue, white); // Turn LEDs on
    strip.show();
    delay(250); // On for 250ms
    controlLEDStrip(slotRow, slotCol, false, red, green, blue, white); // Turn LEDs off
    strip.show();
    delay(250); // Off for 250ms
  }
  // // After blinking, set LEDs to specified color
  if (isStatusFull) 
  for (int i = 0; i < LEDS_PER_GROUP; i++) {
    strip.setPixelColor((slotRow * NUM_COLS + slotCol) * LEDS_PER_GROUP + i, strip.Color(255, 0, 0, 0)); // Set color
  } else 
  for (int i = 0; i < LEDS_PER_GROUP; i++) {
    strip.setPixelColor((slotRow * NUM_COLS + slotCol) * LEDS_PER_GROUP + i, strip.Color(0, 0, 0, 0)); // turn leds off
  }
  strip.show(); // Update LED strip
}
