#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <RTClib.h>

#include <RGBmatrixPanel.h>
#define CLK  8   // USE THIS ON ADAFRUIT METRO M0, etc.
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
#define OLED_RESET 4
RTC_DS3231 rtc;


RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
Adafruit_SSD1306 display(OLED_RESET);
int countdownSeconds = 120 * 60; // 2 hours in seconds

void setup() {
  matrix.begin();
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  DateTime now = rtc.now();
  
  int secondsRemaining = countdownSeconds - (now.hour() * 3600) - (now.minute() * 60) - now.second();
  
  if (secondsRemaining < 0) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Countdown complete!");
    display.display();
    return;
  }
  
  int minutes = secondsRemaining / 60;
  int seconds = secondsRemaining % 60;
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Time remaining: ");
  if (minutes < 10) {
    display.print("0");
  }
  display.print(minutes);
  display.print(":");
  if (seconds < 10) {
    display.print("0");
  }
  display.print(seconds);
  display.display();
  
  delay(1000); // 1 second delay
}
