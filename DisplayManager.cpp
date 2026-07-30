#include "DisplayManager.h"
#include "Config.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int LED_LOADING_PIN = 5;
const int LED_READY_PIN   = 6;

static LiquidCrystal_I2C lcd(0x27, 16, 2);

static int lastTA = -1;
static int lastTB = -1;

static String lastCA = "";
static String lastCB = "";

byte customBlock[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

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
  pinMode(LED_LOADING_PIN, OUTPUT);
  pinMode(LED_READY_PIN, OUTPUT);
  
  digitalWrite(LED_LOADING_PIN, LOW);
  digitalWrite(LED_READY_PIN, LOW);

  lcd.init();
  lcd.backlight();
  
  lcd.createChar(0, customBlock);
}

void showIntro() {
  digitalWrite(LED_LOADING_PIN, HIGH);
  digitalWrite(LED_READY_PIN, LOW);

  lcd.clear();
  
  printCenter(1, displayName);
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(0);
    delay(290);
  }

  delay(300);
  lcd.clear();

  digitalWrite(LED_LOADING_PIN, LOW);
  digitalWrite(LED_READY_PIN, HIGH);
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