#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit DRV2605 Continuous Vibration Test");

  if (!drv.begin()) {
    Serial.println("Could not find DRV2605");
    while (1) delay(10);
  }
  
  drv.selectLibrary(1);                 // Select the basic haptic library
  drv.setMode(DRV2605_MODE_INTTRIG);     // Set to internal trigger mode
  
  // Set a continuous vibration effect with a lower intensity (using waveform)
  drv.setWaveform(0, 1);  // Select a lower intensity waveform from the library
  drv.setWaveform(1, 0);   // End the waveform sequence
}

void loop() {
  drv.go();  // Start the continuous vibration
}
