/*
 * Project yellow-tft-display
 * Description: Example app for Jamis_SSD1322 
 * Author: James Hagerman
 * Date: 2019-09-28
 */

#include "application.h"

#include <Adafruit_GFX.h>
#include "Jamis_SSD1322.h"

SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_TRACE);

#define PIN_DC       D9  // DC: HIGH=Data, LOW=Command
#define PIN_RES      D10 // Reset: HIGH during operation, LOW triggers reset)
#define PIN_CS       A5  // Chip Select

Jamis_SSD1322 display = Jamis_SSD1322(256, 64, &SPI, PIN_DC, PIN_RES, PIN_CS, 16*MHZ);

// bool meshGWStatus = false;
// void meshMsgHandler(const char *event, const char *data) {
//   meshGWStatus = !meshGWStatus;
//   digitalWrite(D7, meshGWStatus);
// }

uint8_t i = 0;
bool ledState = false;

void setup() {
  pinMode(D7, OUTPUT);

  display.begin();

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Draw initial stuff:
  display.clearDisplay();

  // Test grayscale output:
  while (i<16) {
    display.drawPixel(i, 0, i);
    display.drawPixel(i, 1, i);
    display.drawPixel(i, 2, i);
    display.drawPixel(i, 3, i);
    display.drawPixel(i, 4, i);
    i += 1;
  }

  // Draw Lines:
  display.drawFastHLine(10, 15, 10, 0xf);
  display.drawFastVLine(10, 15, 10, 0xf);
  display.drawLine(10, 15, 17, 22, 0xf);

  // Draw gradient rects:
  i = 0;
  while (i<16) {
    display.drawRect(128-(i*2), 30-i, 10, 10, 0xf-i);
    i += 1;
  }
  display.fillRect(128, 30, 10, 10, 0xf);

  // Draw gradient filled rects:
  i = 0;
  while (i<16) {
    display.fillRect(128-(i*2), 50-i, 10, 10, 0xf-i);
    i += 1;
  }
  display.fillRect(128, 50, 10, 10, 0xf);

  // Draw gradient circles:
  i = 0;
  while (i<16) {
    display.drawCircle(192-(i*2), 50-i, 10, 0xf-i);
    i += 1;
  }
  display.fillCircle(192, 50, 10, 0xf);

    // Draw gradient filled circles:
  i = 0;
  while (i<16) {
    display.fillCircle(220-(i*2), 30-i, 10, 0xf-i);
    i += 1;
  }
  display.fillCircle(220, 30, 10, 0xf);

  // Draw text:
  display.setTextWrap(true);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println("Temperature:");
  display.setCursor(0, 40);
  display.println("Humidity:");

  display.display();

  delay(1000);

  // Mesh.subscribe("mesh-msg", meshMsgHandler);
}

void loop() {
  i+=1;
  if (i>64) {
    i = 0;
  }
  display.clearDisplay();
  display.drawPixel(i, i, 0xf);
  display.drawCircle(i, i, 10, 0xf);
  display.display();
  ledState = !ledState;
  digitalWrite(D7, ledState);
}
