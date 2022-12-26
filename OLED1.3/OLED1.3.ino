/**************************************************************************
 * 1306_simple_pico.ino
 * 
 * SSD1306 checkout
 * 
 */
 // 在树莓派上运行OLED1.3 首先需要注意修改 pico内部的iic引脚映射，接着修改Adafruit_SSD1306.h文件，移除掉提示不存在的库文件
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1327.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C 

//Perhaps the following 2 lines are required for the Pico?  Or use 4,5 instead of (6u), (7u)?
//#define PIN_WIRE_SDA   (21u)
//#define PIN_WIRE_SCL   (22u)
Adafruit_SSD1327 display(128, 128, &Wire, OLED_RESET, 1000000);

void setup() {
  Serial.begin(9600);
  delay(1000);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1327_WHITE);        // Draw white text
  display.setCursor(0,30);             
}

void loop() {
  Serial.println(F("FINSIH 1"));
  display.println("Plus Oil Dianna");
  display.display();
  delay(10000);
}