#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==== PIN DEFINITION ====
const int PIN_TA = A0;
const int PIN_TB = A1;
const int PIN_CA = A2;
const int PIN_CB = A3;

// ==== EEPROM ADDRESS MAP ====
#define EEPROM_ADDR_NAME 0
#define EEPROM_ADDR_CAL_CA 16
#define EEPROM_ADDR_CAL_CB 18

#define MAX_NAME_LENGTH 16
const int SAMPLE_COUNT = 10;

// ==== DEFAULT VALUES ====
const int DEFAULT_CAL_MAX = 1015;

// ==== DATA STRUCTURE ====
struct SensorData {
  int tempA;
  int tempB;
  String percentCA;
  String percentCB;
};

// Global Shared Variables
extern String VersionControl;
extern String displayName;
extern int calibMaxCA;
extern int calibMaxCB;

#endif

// JEMBOET IRENG MASKAPAI