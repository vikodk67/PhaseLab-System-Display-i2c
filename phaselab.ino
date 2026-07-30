#include "Config.h"
#include "Storage.h"
#include "SensorManager.h"
#include "DisplayManager.h"

String VersionControl = "V1.2.8";
String displayName = "PHSLAB-" + VersionControl;
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
   analogReference(DEFAULT); 
  SensorData currentData = readSensors();
  updateDisplay(currentData);
  delay(5);
}