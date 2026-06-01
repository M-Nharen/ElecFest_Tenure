#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold12pt7b.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  display.drawRect(4, 4, 120, 56, SSD1306_WHITE);
  
  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(18, 30);
  display.print("Elecfest");
  
  display.setFont(); 
  display.setCursor(20, 42);
  display.print("Universe Hello!");
  
  display.display();
  delay(2000);
}
