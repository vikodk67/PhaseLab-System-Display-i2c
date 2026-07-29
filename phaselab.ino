#include "Config.h"
#include "Storage.h"
#include "SensorManager.h"
#include "DisplayManager.h"

// Inisialisasi variabel global dari Config.h
String VersionControl = "1.1.4-not stable";
String displayName = "PHASELAB";
int calibMaxCA = DEFAULT_CAL_MAX;
int calibMaxCB = DEFAULT_CAL_MAX;

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
  loadCalibration();
  showIntro();
}

void loop() {
  handleSerial();

  SensorData currentData = readSensors();
  updateDisplay(currentData);

  delay(100);
}