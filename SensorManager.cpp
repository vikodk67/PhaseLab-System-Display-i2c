#include "SensorManager.h"

static int samplesTA[SAMPLE_COUNT];
static int samplesTB[SAMPLE_COUNT];
static int samplesCA[SAMPLE_COUNT];
static int samplesCB[SAMPLE_COUNT];
static int indexSample = 0;

static float smoothTA = 0;
static float smoothTB = 0;
static float smoothCA = 0;
static float smoothCB = 0;

static const float ALPHA = 0.08; 
int readSmoothedAnalog(int pin) {
  long sum = 0;
  int numReadings = 32; // Number of samples to average

  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(pin);
    delayMicroseconds(50); // Small pause between reads
  }

  return sum / numReadings; // Return average value
}
static int readAdcClean(int pin) {
  readSmoothedAnalog(pin);
  //analogRead(pin);
  return analogRead(pin);
}

void initSensors() {
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    samplesTA[i] = 0;
    samplesTB[i] = 0;
    samplesCA[i] = 0;
    samplesCB[i] = 0;
  }
  
  smoothTA = readAdcClean(PIN_TA);
  smoothTB = readAdcClean(PIN_TB);
  smoothCA = readAdcClean(PIN_CA);
  smoothCB = readAdcClean(PIN_CB);
}

SensorData readSensors() {
  int rawTA = readAdcClean(PIN_TA);
  int rawTB = readAdcClean(PIN_TB);
  int rawCA = readAdcClean(PIN_CA);
  int rawCB = readAdcClean(PIN_CB);

  samplesTA[indexSample] = rawTA;
  samplesTB[indexSample] = rawTB;
  samplesCA[indexSample] = rawCA;
  samplesCB[indexSample] = rawCB;

  indexSample++;
  if (indexSample >= SAMPLE_COUNT) indexSample = 0;

  long totalTA = 0, totalTB = 0, totalCA = 0, totalCB = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    totalTA += samplesTA[i];
    totalTB += samplesTB[i];
    totalCA += samplesCA[i];
    totalCB += samplesCB[i];
  }

  float avgTA = (float)totalTA / SAMPLE_COUNT;
  float avgTB = (float)totalTB / SAMPLE_COUNT;
  float avgCA = (float)totalCA / SAMPLE_COUNT;
  float avgCB = (float)totalCB / SAMPLE_COUNT;

  smoothTA = (ALPHA * avgTA) + ((1.0 - ALPHA) * smoothTA);
  smoothTB = (ALPHA * avgTB) + ((1.0 - ALPHA) * smoothTB);
  smoothCA = (ALPHA * avgCA) + ((1.0 - ALPHA) * smoothCA);
  smoothCB = (ALPHA * avgCB) + ((1.0 - ALPHA) * smoothCB);

  float voltageTA = smoothTA * (5.0 / 1023.0);
  float voltageTB = smoothTB * (5.0 / 1023.0);

  SensorData data;
  data.tempA = (int)(voltageTA * 100.0);
  data.tempB = (int)(voltageTB * 100.0);

  int valCA = constrain(map((int)smoothCA, 0, calibMaxCA, 0, 100), 0, 100);
  int valCB = constrain(map((int)smoothCB, 0, calibMaxCB, 0, 100), 0, 100);

  data.percentCA = (valCA >= 100) ? "MAX" : String(valCA) + "%";
  data.percentCB = (valCB >= 100) ? "MAX" : String(valCB) + "%";

  return data;
}