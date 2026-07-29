#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==== PIN DEFINITION ====
const int PIN_TA = A0;
const int PIN_TB = A1;
const int PIN_CA = A2;
const int PIN_CB = A3;

// ==== CONSTANTS ====
#define EEPROM_ADDR 0
#define MAX_NAME_LENGTH 16
const int SAMPLE_COUNT = 10;

// ==== DATA STRUCTURE ====
struct SensorData {
  int tempA;
  int tempB;
  int percentCA;
  int percentCB;
};

// Global Versioning & Name
extern String VersionControl;
extern String displayName;

#endif

// JEMBOET IRENG MASKAPAI