#include "DisplayManager.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(0x27, 16, 2);

static int lastTA = -1;
static int lastTB = -1;

// ==== UBAH TIPE DATA INI DARI int MENJADI String ====
static String lastCA = "";
static String lastCB = "";

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
  // CA (Kiri Atas)
  if (data.percentCA != lastCA) {
    lcd.setCursor(0, 0);
    lcd.print("CA:");
    lcd.setCursor(3, 0);
    lcd.print("    "); // Hapus karakter lama
    lcd.setCursor(3, 0);
    lcd.print(data.percentCA); // Langsung print string (misal: "95%" atau "MAX")
    lastCA = data.percentCA;
  }

  // CB (Kiri Bawah)
  if (data.percentCB != lastCB) {
    lcd.setCursor(0, 1);
    lcd.print("CB:");
    lcd.setCursor(3, 1);
    lcd.print("    "); // Hapus karakter lama
    lcd.setCursor(3, 1);
    lcd.print(data.percentCB);
    lastCB = data.percentCB;
  }

  // TA (Kanan Atas)
  if (data.tempA != lastTA) {
    lcd.setCursor(8, 0);
    lcd.print("        ");
    printRight(15, 0, "TA:" + String(data.tempA) + "C");
    lastTA = data.tempA;
  }

  // TB (Kanan Bawah)
  if (data.tempB != lastTB) {
    lcd.setCursor(8, 1);
    lcd.print("        ");
    printRight(15, 1, "TB:" + String(data.tempB) + "C");
    lastTB = data.tempB;
  }
}