#include "SensorManager.h"

static int samplesTA[SAMPLE_COUNT];
static int samplesTB[SAMPLE_COUNT];
static int samplesCA[SAMPLE_COUNT];
static int samplesCB[SAMPLE_COUNT];
static int indexSample = 0;

void initSensors() {
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    samplesTA[i] = 0;
    samplesTB[i] = 0;
    samplesCA[i] = 0;
    samplesCB[i] = 0;
  }
}

SensorData readSensors() {
  samplesTA[indexSample] = analogRead(PIN_TA);
  samplesTB[indexSample] = analogRead(PIN_TB);
  samplesCA[indexSample] = analogRead(PIN_CA);
  samplesCB[indexSample] = analogRead(PIN_CB);

  indexSample++;
  if (indexSample >= SAMPLE_COUNT) indexSample = 0;

  long totalTA = 0, totalTB = 0, totalCA = 0, totalCB = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    totalTA += samplesTA[i];
    totalTB += samplesTB[i];
    totalCA += samplesCA[i];
    totalCB += samplesCB[i];
  }

  int avgTA = totalTA / SAMPLE_COUNT;
  int avgTB = totalTB / SAMPLE_COUNT;
  int avgCA = totalCA / SAMPLE_COUNT;
  int avgCB = totalCB / SAMPLE_COUNT;

  // Konversi LM35
  float voltageTA = avgTA * (5.0 / 1023.0);
  float voltageTB = avgTB * (5.0 / 1023.0);

  SensorData data;
  data.tempA = voltageTA * 100.0;
  data.tempB = voltageTB * 100.0;

  // Gunakan variabel kalibrasi dari EEPROM
  int valCA = constrain(map(avgCA, 0, calibMaxCA, 0, 100), 0, 100);
  int valCB = constrain(map(avgCB, 0, calibMaxCB, 0, 100), 0, 100);

  data.percentCA = (valCA >= 100) ? "MAX" : String(valCA) + "%";
  data.percentCB = (valCB >= 100) ? "MAX" : String(valCB) + "%";

  return data;
}