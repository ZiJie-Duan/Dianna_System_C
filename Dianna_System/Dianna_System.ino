#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define interruptPin1 20
#define interruptPin2 19
#define interruptPin3 18
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#include <map>

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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int cont = 0;
int cont2 = 0;
int cont3 = 0;
int state = 0;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             
  display.println("Interrupt TEST");
  display.display();

  pinMode(interruptPin1, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), print_text1, FALLING);
    pinMode(interruptPin2, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(interruptPin2), print_text2, FALLING);
        pinMode(interruptPin3, INPUT_PULLDOWN);
        attachInterrupt(digitalPinToInterrupt(interruptPin3), print_text3, FALLING);
}


void loop() {
  Serial.println(digitalRead(interruptPin1));
  if (state == 1){
    cont ++;
    display.clearDisplay();
    display.setCursor(0,30);  
    display.println("input1");
    display.println(cont);
    display.display();
    state = 0;
  } else if (state == 2){
    cont2 ++;
    display.clearDisplay();
    display.setCursor(42,40);
    display.println("input2");
    display.println(cont2);
    display.display();
    state = 0;
  } else if (state == 3){
    cont3 ++;
    display.clearDisplay();
    display.setCursor(84,40);
    display.println("input3");
    display.println(cont3);
    display.display();
    state = 0;
  }

}

void print_text1(){

  state = 1;
}

void print_text2(){

  state = 2;
}

void print_text3(){

  state = 3;
}
