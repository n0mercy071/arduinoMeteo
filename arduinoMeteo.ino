#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


LiquidCrystal_I2C lcd(0x27,16,2);
RTC_DS3231 rtc;
Adafruit_BME280 bme;

void setup() {
  lcd.init();
  lcd.backlight();

  if (! rtc.begin()) {
    lcd.setCursor(0,0);
    lcd.print("Not find RTC");
    while (1);
  }

  if (! bme.begin(0x76)) {
    lcd.setCursor(0,1);
    lcd.print("Not find BME280");
    while (1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  printTime(0);
  printTemp(1);
  
  delay(5000);
}

/**
 * Печатает время
 * row int Строка для печати
 */
void printTime(int row) {
  DateTime now = rtc.now();
  String sDate = String(now.day(), DEC)
    + "/" + String(now.month(), DEC)
    + " " + String(now.hour(), DEC) 
    + ":" + String(now.minute(), DEC) 
    + ":" + String(now.second(), DEC);
  
  lcd.setCursor(0, row);
  lcd.print(sDate);
}

/**
 * Печатает инфу с датчика BME280
 * row int Строка для печати
 */
void printTemp(int row) {
  String sTemp = String(bme.readTemperature(), 1);
  String sPressure = String(bme.readPressure() * 0.007501F, 1);
  String sHumidity = String(bme.readHumidity(), 0);
  
  String sTempStr = sTemp + "C "
    + sHumidity + "% "
    + sPressure;
  
  lcd.setCursor(0, row);
  lcd.print(sTempStr);
}
