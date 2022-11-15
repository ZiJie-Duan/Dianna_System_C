
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address_1 0x3d //initialize with the I2C addr 0x3C Typically eBay OLED's
#define i2c_Address_2 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO

#define BUZZER 5
#define BUTTON_X 25
#define BUTTON_Y 26
#define BUTTON_A 27
#define BUTTON_B 4
#define JOYSTICK_X 32
#define JOYSTICK_Y 33
#define ROTARY_KNOB_A 34
#define ROTARY_KNOB_B 39
#define ROTARY_KNOB_C 36

#define BUTTON_X_SEQ 0
#define BUTTON_Y_SEQ 1
#define BUTTON_A_SEQ 2
#define BUTTON_B_SEQ 3
#define JOYSTICK_X_SEQ 4
#define JOYSTICK_Y_SEQ 5
#define ROTARY_KNOB_A_SEQ 6
#define ROTARY_KNOB_B_SEQ 7
#define ROTARY_KNOB_C_SEQ 8

Adafruit_SH1106G display_1 = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SH1106G display_2 = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int state_seq[9];

void update_screen(void);
void update_state_seq(void);
void init_hardwares(void);

void setup(){
    init_hardwares();
    Serial.begin(9600);
    delay(250); // wait for the OLED to power up
    display_1.begin(i2c_Address_1, true);
    display_1.display();
    display_1.setTextSize(1);
    display_1.setTextColor(SH110X_WHITE);
    display_2.begin(i2c_Address_2, true);
    display_2.display();
    display_2.setTextSize(1);
    display_2.setTextColor(SH110X_WHITE);
}

void loop() {
    update_state_seq();
    update_screen();
    delay(100);
}

void update_screen(void){
    display_1.clearDisplay();
    display_2.clearDisplay();

    display_1.setCursor(0, 0);
    display_1.println("HARDWARE TEST");
    display_1.setCursor(0, 12);
    display_1.print("BUTTON_X : ");
    display_1.print(state_seq[BUTTON_X_SEQ]);
    display_1.setCursor(0, 24);
    display_1.print("BUTTON_Y : ");
    display_1.print(state_seq[BUTTON_Y_SEQ]);
    display_1.setCursor(0, 36);
    display_1.print("BUTTON_A : ");
    display_1.print(state_seq[BUTTON_A_SEQ]);
    display_1.setCursor(0, 48);
    display_1.print("BUTTON_B : ");
    display_1.print(state_seq[BUTTON_B_SEQ]);

    display_2.setCursor(0, 0);
    display_2.println("HARDWARE TEST");
    display_2.setCursor(0, 12);
    display_2.print("JOYSTICK_X : ");
    display_2.print(state_seq[JOYSTICK_X_SEQ]);
    display_2.setCursor(0, 24);
    display_2.print("JOYSTICK_Y : ");
    display_2.print(state_seq[JOYSTICK_Y_SEQ]);
    display_2.setCursor(0, 36);
    display_2.print("ROTARY_KNOB_A : ");
    display_2.print(state_seq[ROTARY_KNOB_A_SEQ]);
    display_2.setCursor(0, 48);
    display_2.print("ROTARY_KNOB_B : ");
    display_2.print(state_seq[ROTARY_KNOB_B_SEQ]);

    display_1.display();
    display_2.display();
}

void init_hardwares(void){
    pinMode(BUZZER, OUTPUT);
    pinMode(BUTTON_X, INPUT_PULLDOWN);
    pinMode(BUTTON_Y, INPUT_PULLDOWN);
    pinMode(BUTTON_A, INPUT_PULLDOWN);
    pinMode(BUTTON_B, INPUT_PULLDOWN);
    pinMode(ROTARY_KNOB_A, INPUT_PULLUP);
    pinMode(ROTARY_KNOB_B, INPUT_PULLUP);
    pinMode(ROTARY_KNOB_C, INPUT_PULLUP);
}

void update_state_seq(void){
    state_seq[BUTTON_X_SEQ] = digitalRead(BUTTON_X);
    state_seq[BUTTON_Y_SEQ] = digitalRead(BUTTON_Y);
    state_seq[BUTTON_A_SEQ] = digitalRead(BUTTON_A);
    state_seq[BUTTON_B_SEQ] = digitalRead(BUTTON_B);
    state_seq[JOYSTICK_X_SEQ] = analogRead(JOYSTICK_X);
    state_seq[JOYSTICK_Y_SEQ] = analogRead(JOYSTICK_Y);
    state_seq[ROTARY_KNOB_A_SEQ] = digitalRead(ROTARY_KNOB_A);
    state_seq[ROTARY_KNOB_B_SEQ] = digitalRead(ROTARY_KNOB_B);
    state_seq[ROTARY_KNOB_C_SEQ] = digitalRead(ROTARY_KNOB_C);
    if (state_seq[BUTTON_X_SEQ] == 1){
        digitalWrite(BUZZER, LOW);
    } else {
        digitalWrite(BUZZER, HIGH);
    }
}
