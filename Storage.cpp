#include "Storage.h"
#include <EEPROM.h>

void saveName(String name) {
  for (int i = 0; i < MAX_NAME_LENGTH; i++) {
    if (i < (int)name.length())
      EEPROM.write(EEPROM_ADDR + i, name[i]);
    else
      EEPROM.write(EEPROM_ADDR + i, 0);
  }
}

String loadName() {
  char data[MAX_NAME_LENGTH + 1];
  for (int i = 0; i < MAX_NAME_LENGTH; i++) {
    data[i] = EEPROM.read(EEPROM_ADDR + i);
    if (data[i] == 0xFF) data[i] = 0;
  }
  data[MAX_NAME_LENGTH] = '\0';
  return String(data);
}

void handleSerial() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("NAME=")) {
      String newName = input.substring(5);
      newName.trim();

      if (newName.length() > 0 && newName.length() <= 16) {
        displayName = newName;
        saveName(displayName);
        Serial.println(F("Nama disimpan!"));
      } else {
        Serial.println(F("Max 16 karakter!"));
      }
    }
    else if (input == "SHOW") {
      Serial.print(F("Nama saat ini: "));
      Serial.println(displayName);
    }
    else if (input == "RESET") {
      displayName = VersionControl;
      saveName(displayName);
      Serial.println(F("Reset ke default."));
    }
  }
}