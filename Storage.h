#ifndef STORAGE_H
#define STORAGE_H

#include "Config.h"

void saveName(String name);
String loadName();

void saveCalibCA(int val);
void saveCalibCB(int val);
void loadCalibration();

void handleSerial();

#endif