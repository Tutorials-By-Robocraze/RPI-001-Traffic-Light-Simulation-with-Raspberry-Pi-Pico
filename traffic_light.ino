#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// Define hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  // For common FC16 MAX7219 modules
#define MAX_DEVICES 4  // Number of 8x8 modules chained

// Pins for Pico
#define DATA_PIN 6
#define CLK_PIN 8
#define CS_PIN 7

// Create Parola object
MD_Parola parola = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Traffic light LEDs
int redLED = 2;
int yellowLED = 3;
int greenLED = 4;

void setup() {
  // Setup LEDs
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Setup Parola
  parola.begin();
  parola.setIntensity(8);   // Brightness (0–15)
  parola.displayClear();
}

// Function to show static message
void showMessage(const char* msg, int durationMs) {
  parola.displayClear();   // clear display first
  parola.displayText(msg, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
  parola.displayAnimate(); // apply text
  delay(durationMs);       // keep it on screen
  parola.displayClear();   // clear after time
}

void loop() {
  // RED phase
  digitalWrite(redLED, HIGH);
  showMessage("STOP", 5000);
  digitalWrite(redLED, LOW);

  // YELLOW phase
  digitalWrite(yellowLED, HIGH);
  showMessage("READY", 2000);
  digitalWrite(yellowLED, LOW);

  // GREEN phase
  digitalWrite(greenLED, HIGH);
  showMessage("GO", 5000);
  digitalWrite(greenLED, LOW);
}
