#include "Storage.h"
#include <EEPROM.h>

void saveName(String name) {
  for (int i = 0; i < MAX_NAME_LENGTH; i++) {
    if (i < (int)name.length())
      EEPROM.write(EEPROM_ADDR_NAME + i, name[i]);
    else
      EEPROM.write(EEPROM_ADDR_NAME + i, 0);
  }
}

String loadName() {
  char data[MAX_NAME_LENGTH + 1];
  for (int i = 0; i < MAX_NAME_LENGTH; i++) {
    data[i] = EEPROM.read(EEPROM_ADDR_NAME + i);
    if (data[i] == 0xFF) data[i] = 0;
  }
  data[MAX_NAME_LENGTH] = '\0';
  return String(data);
}

// ==== SIMPAN KALIBRASI ====
void saveCalibCA(int val) {
  calibMaxCA = val;
  EEPROM.put(EEPROM_ADDR_CAL_CA, val);
}

void saveCalibCB(int val) {
  calibMaxCB = val;
  EEPROM.put(EEPROM_ADDR_CAL_CB, val);
}

// ==== BACA KALIBRASI (WITH DEFAULT FALLBACK) ====
void loadCalibration() {
  EEPROM.get(EEPROM_ADDR_CAL_CA, calibMaxCA);
  EEPROM.get(EEPROM_ADDR_CAL_CB, calibMaxCB);

  if (calibMaxCA < 500 || calibMaxCA > 1023) {
    saveCalibCA(DEFAULT_CAL_MAX);
  }
  if (calibMaxCB < 500 || calibMaxCB > 1023) {
    saveCalibCB(DEFAULT_CAL_MAX);
  }
}

// ==== SERIAL CLI HANDLER ====
void handleSerial() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // 1. Ubah Nama System
    if (input.startsWith("NAME=")) {
      String newName = input.substring(5);
      newName.trim();
      if (newName.length() > 0 && newName.length() <= 16) {
        displayName = newName;
        saveName(displayName);
        Serial.println(F("Nama berhasil disimpan!"));
      } else {
        Serial.println(F("Error: Max 16 karakter!"));
      }
    }
    // 2. Set Kalib Max CA (misal: CAL_CA=1015)
    else if (input.startsWith("CAL_CA=")) {
      int val = input.substring(7).toInt();
      if (val >= 500 && val <= 1023) {
        saveCalibCA(val);
        Serial.print(F("Kalibrasi CA disimpan: "));
        Serial.println(val);
      } else {
        Serial.println(F("Error: Nilai harus antara 500 - 1023!"));
      }
    }
    // 3. Set Kalib Max CB (misal: CAL_CB=1015)
    else if (input.startsWith("CAL_CB=")) {
      int val = input.substring(7).toInt();
      if (val >= 500 && val <= 1023) {
        saveCalibCB(val);
        Serial.print(F("Kalibrasi CB disimpan: "));
        Serial.println(val);
      } else {
        Serial.println(F("Error: Nilai harus antara 500 - 1023!"));
      }
    }
    // 4. Tampilkan Status
    else if (input == "SHOW") {
      Serial.print(F("Nama System : "));
      Serial.println(displayName);
      Serial.print(F("Max ADC CA  : "));
      Serial.println(calibMaxCA);
      Serial.print(F("Max ADC CB  : "));
      Serial.println(calibMaxCB);
    }
    // 5. Reset Ke Default
    else if (input == "RESET") {
      displayName = VersionControl;
      saveName(displayName);
      saveCalibCA(DEFAULT_CAL_MAX);
      saveCalibCB(DEFAULT_CAL_MAX);
      Serial.println(F("Semua setting berhasil di-reset ke default!"));
    }
  }
}