#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "Config.h"

void initDisplay();
void showIntro();
void updateDisplay(const SensorData& data);

#endif