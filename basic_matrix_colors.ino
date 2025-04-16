#include <Adafruit_NeoPixel.h>
//#include "font.h"  // Include the font header file
#include <WebServer.h>
#include <WiFi.h>
#include <time.h>  // Include the time library

// Define LED matrix details
#define PIN_NEOPIXEL 14
#define NUMPIXELS    64  // 8x8 matrix
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8
#define RGB_BRIGHTNESS 20  // Brightness level (0-255)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_RGB + NEO_KHZ800);

// Replace with your network credentials
const char* ssid = "WaxLand-A2-2G";
const char* password = "DodgeandHonda";

// Timezone details
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -18000; // Example: GMT-5 for EST
const int daylightOffset_sec = 3600;

// Alarm settings
String alarmTime = "";       // Stores the alarm time (HH:MM)
String alarmMessage = "";    // Stores the custom alarm message
bool alarmTriggered = false; // Flag to indicate if the alarm has been triggered
unsigned long alarmStartTime = 0; // Tracks when the alarm started flashing

// Flashing and alarm duration settings
bool flashOn = false;
unsigned long previousFlashMillis = 0;
unsigned long flashInterval = 500;     // Flash interval (500ms)
unsigned long flashDuration = 120000; // Default 2 minutes for alarm

// Web Server
WebServer server(80);

void setup() {
    // Initialize the NeoPixel library
    pixels.begin();
    pixels.setBrightness(RGB_BRIGHTNESS);

    Serial.begin(115200);
    Serial.println("ESP32 LED Matrix Test Starting...");

    // Test basic functionality - Set all LEDs to white
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255));  // Set all pixels to white
    }
    pixels.show();
    delay(1000);

    // Clear the matrix
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, 0);  // Turn off all pixels
    }
    pixels.show();
}

void loop() {
    // Basic test - Cycle through colors
    displayColor(255, 0, 0);  // Red
    delay(1000);
    displayColor(0, 255, 0);  // Green
    delay(1000);
    displayColor(0, 0, 255);  // Blue
    delay(1000);
}

// Function to display a single color across the matrix
void displayColor(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
    pixels.show();
    Serial.print("Displayed color - R: ");
    Serial.print(r);
    Serial.print(", G: ");
    Serial.print(g);
    Serial.print(", B: ");
    Serial.println(b);
}