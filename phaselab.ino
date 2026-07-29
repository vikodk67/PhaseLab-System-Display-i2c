#include "Config.h"
#include "Storage.h"
#include "SensorManager.h"
#include "DisplayManager.h"

// Inisialisasi variabel global dari Config.h
String VersionControl = "1.0.2-not stable";
String displayName = "PHASELAB";

void setup() {
  Serial.begin(9600);

  initSensors();
  initDisplay();

  String saved = loadName();
  if (saved.length() > 0) {
    displayName = saved;
  } else {
    saveName(displayName);
  }

  showIntro();
}

void loop() {
  handleSerial();

  SensorData currentData = readSensors();
  updateDisplay(currentData);

  delay(100);
}