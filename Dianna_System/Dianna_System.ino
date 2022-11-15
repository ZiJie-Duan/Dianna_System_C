
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address_1 0x3d //initialize with the I2C addr 0x3C Typically eBay OLED's
#define i2c_Address_2 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display_1 = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SH1106G display_2 = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup(){
  Serial.begin(9600);
  delay(250); // wait for the OLED to power up
  display_1.begin(i2c_Address_1, true); // Address 0x3C default
  display_1.display();
  delay(2000);
  display_1.clearDisplay();
  // draw a single pixel
  display_1.drawPixel(10, 10, SH110X_WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display_1.display();
    delay(250); // wait for the OLED to power up
  display_2.begin(i2c_Address_2, true); // Address 0x3C default
  display_2.display();
  delay(2000);
  display_2.clearDisplay();
  // draw a single pixel
  display_2.drawPixel(10, 10, SH110X_WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display_2.display();

  display_1.clearDisplay();
  display_2.clearDisplay();
  delay(2000);
  display_1.display();
  display_2.display();
}

void loop() {

}