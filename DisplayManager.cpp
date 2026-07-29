#include "DisplayManager.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27

static int lastTA = -1;
static int lastTB = -1;
static int lastCA = -1;
static int lastCB = -1;

static void printCenter(int row, String text) {
  int col = (16 - text.length()) / 2;
  if (col < 0) col = 0;
  lcd.setCursor(col, row);
  lcd.print(text);
}

static void printRight(int colEnd, int row, String text) {
  int startCol = colEnd - text.length() + 1;
  if (startCol < 0) startCol = 0;
  lcd.setCursor(startCol, row);
  lcd.print(text);
}

void initDisplay() {
  lcd.init();
  lcd.backlight();
}

void showIntro() {
  lcd.clear();
  printCenter(0, "Welcome to");
  printCenter(1, displayName);
  delay(3500);
  lcd.clear();
}

void updateDisplay(const SensorData& data) {
  // CA 
  if (data.percentCA != lastCA) {
    lcd.setCursor(0, 0);
    lcd.print("CA:");
    lcd.setCursor(3, 0);
    lcd.print("    ");
    lcd.setCursor(3, 0);
    lcd.print(data.percentCA);
    lcd.print("%");
    lastCA = data.percentCA;
  }

  // CB 
  if (data.percentCB != lastCB) {
    lcd.setCursor(0, 1);
    lcd.print("CB:");
    lcd.setCursor(3, 1);
    lcd.print("    ");
    lcd.setCursor(3, 1);
    lcd.print(data.percentCB);
    lcd.print("%");
    lastCB = data.percentCB;
  }

  // TA
  if (data.tempA != lastTA) {
    lcd.setCursor(8, 0);
    lcd.print("        ");
    printRight(15, 0, "TA:" + String(data.tempA) + "C");
    lastTA = data.tempA;
  }

  // TB
  if (data.tempB != lastTB) {
    lcd.setCursor(8, 1);
    lcd.print("        ");
    printRight(15, 1, "TB:" + String(data.tempB) + "C");
    lastTB = data.tempB;
  }
}