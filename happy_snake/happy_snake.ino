
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address_1 0x3d //initialize with the I2C addr 0x3C Typically eBay OLED's
#define i2c_Address_2 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO

#define PIXS_MEMORY_COE 10 // how many pixs in the memory

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

//system basic functions----------------------------------

void init_hardwares(void);
void init_displaym(void);
void init_Interrupt(void);

void s_pixs_add(uint8_t x, uint8_t y, uint8_t light, uint8_t v_type);
void s_pixs_change(uint8_t x, uint8_t y, uint8_t light, uint8_t v_type);
void s_pixs_del(uint8_t x, uint8_t y);
void screen_show(void);

//long int pixs_num = (long int)((SCREEN_WIDTH*SCREEN_HEIGHT)/PIXS_MEMORY_COE); 
uint8_t spseq[800][4]; //screen pixs sequence


//end of system basic functions----------------------------------


//game functions----------------------------------
//pix type:
    //0: snake body
    //1: snake head
    //2: snake tail
    //3: fruit
    //4: wall
    //5: empty
long long int frct = 0;
uint8_t direction = 1; //0: up, 1: right, 2: down, 3: left
uint8_t snake_head = 0;
uint8_t snake_tail = 0;
uint8_t snake_seq[800][2] = {}; //800 = pixs_num
void game_init(void);
void random_fruit(void);
void build_wall(void);
void snake_move(void);
void snake_birth(void);
int pixs_check(int *check, int lenght);
void snake_seq_move(uint8_t x, uint8_t y, uint8_t eat, uint8_t *remove_location);


void button_x_remap(void) {direction = 3;Serial.println("left");}
void button_y_remap(void) {direction = 0;Serial.println("up");}
void button_a_remap(void) {direction = 2;Serial.println("down");}
void button_b_remap(void) {direction = 1;Serial.println("right");}

//end of game functions----------------------------------

// main function----------------------------------
void setup(){
    Serial.begin(9600);
    init_hardwares();
    init_displaym();
    init_Interrupt();
    delay(1000);
    game_init();
    snake_birth();
    screen_show();
    delay(1000);
}

void loop() {
    frct ++;
    if (frct%5==0){
      random_fruit();
    }
    snake_move();
    screen_show();
    delay(100);

    Serial.println("finish");
}

// end of main function----------------------------------

// define game functions----------------------------------

void game_init(void){
    direction = 1;
    snake_head = 0;
    snake_tail = 0;
    frct = 0;
}

void snake_seq_move(uint8_t x, uint8_t y, uint8_t eat, uint8_t *remove_location){
    if (snake_head == 800-1){  //800 = pixs_num
        snake_head = 0;
    } else {
        snake_head++;
    }
    snake_seq[snake_head][0] = x;
    snake_seq[snake_head][1] = y;
    if (eat==0){
        remove_location[0] = snake_seq[snake_tail][0];
        remove_location[1] = snake_seq[snake_tail][1];
        snake_tail++;
    } else {
        remove_location[0] = snake_seq[snake_tail-1][0];
        remove_location[1] = snake_seq[snake_tail-1][1];
    }
}

int pixs_check(uint8_t x, uint8_t y){
    for (int i=0; i<800; i++){ 
        if ((spseq[i][0]==x)&&(spseq[i][1]==y)){
            return spseq[i][3];
        }
    }
    return 5;
}

void snake_birth(void){
    uint8_t x = random(20, SCREEN_WIDTH-20);
    uint8_t y = random(10, SCREEN_HEIGHT-10);
    direction = random(0, 3);
    uint8_t snake_head_x = x;
    uint8_t snake_head_y = y;
    uint8_t snake_tail_x = x-2;
    uint8_t snake_tail_y = y;
    snake_head = 2;
    snake_tail = 0;
    snake_seq[2][0] = x; snake_seq[2][1] = y; 
    snake_seq[1][0] = x-1; snake_seq[1][1] = y; 
    snake_seq[0][0] = x-2; snake_seq[0][1] = y; 
    s_pixs_add(x,y,1,1);
    s_pixs_add(x-1,y,1,0);
    s_pixs_add(x-2,y,1,2);
}

void snake_move(void){
    uint8_t new_x = snake_seq[snake_head][0];
    uint8_t new_y = snake_seq[snake_head][1];
    if (direction==0){
        new_y--;
    }
    else if (direction==1){
        new_x++;
    }
    else if (direction==2){
        new_y++;
    }
    else if (direction==3){
        new_x--;
    }
    uint8_t v_type = pixs_check(new_x, new_y);
    
    uint8_t remove_location[2] = {};

    if (v_type == 5){
        s_pixs_add(new_x,new_y,1,1);
        s_pixs_change(snake_seq[snake_head][0],snake_seq[snake_head][1],1,0);
        snake_seq_move(new_x, new_y, 0, remove_location);
        s_pixs_del(remove_location[0], remove_location[1]);

    } else if (v_type == 3){
        s_pixs_add(new_x,new_y,1,1);
        s_pixs_change(snake_seq[snake_head][0],snake_seq[snake_head][1],1,0);
        snake_seq_move(new_x, new_y, 1, remove_location);
        s_pixs_del(remove_location[0], remove_location[1]);
    
    } else if ((v_type ==1)||(v_type ==2)||(v_type ==4)){
        game_init();
        snake_birth();
    }


}

void random_fruit(void){
  s_pixs_add(random(2, SCREEN_WIDTH-2),random(2, SCREEN_HEIGHT-2),1,3);
}

void build_wall(void){
    for (int i=0; i<SCREEN_WIDTH; i++){
        s_pixs_add(i, 0, 1, 4);
        s_pixs_add(i, SCREEN_HEIGHT-1, 1, 4);
    }
    for (int i=0; i<SCREEN_HEIGHT; i++){
        s_pixs_add(0, i, 1, 4);
        s_pixs_add(SCREEN_WIDTH-1, i, 1, 4);
    }
}


// end of game functions----------------------------------


// define system basic functions----------------------------------

void screen_show(void){
    display_1.clearDisplay();
    for (int i=0; i<800; i++){
        if (spseq[i][2]==1){
            display_1.drawPixel(spseq[i][0], spseq[i][1], SH110X_WHITE);
        } else if (spseq[i][2]==0){
            display_1.drawPixel(spseq[i][0], spseq[i][1], SH110X_BLACK);
        }
    }
    display_1.display();
}

void s_pixs_add(uint8_t x, uint8_t y, uint8_t light, uint8_t v_type){
    for (int i=0; i<800; i++){
        if ((spseq[i][2]==2)||
        (spseq[i][0]==0&&spseq[i][1]==0&&spseq[i][2]==0&&spseq[i][3]==0)){
            spseq[i][0] = x;
            spseq[i][1] = y;
            spseq[i][2] = light;
            spseq[i][3] = v_type;
            break;
        }
    }
}

void s_pixs_change(uint8_t x, uint8_t y, uint8_t light, uint8_t v_type){
    for (int i=0; i<800; i++){
        if (spseq[i][0]==x && spseq[i][1]==y){
            spseq[i][2] = light;
            spseq[i][3] = v_type;
            break;
        }
    }
}

void s_pixs_del(uint8_t x, uint8_t y){
    for (int i=0; i<800; i++){
        if (spseq[i][0]==x && spseq[i][1]==y){
            display_1.drawPixel(spseq[i][0], spseq[i][1], SH110X_BLACK);
            spseq[i][2] = 2;
            break;
        }
    }
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

void init_displaym(void){
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

void init_Interrupt(void){
    attachInterrupt(digitalPinToInterrupt(BUTTON_X), button_x_remap, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_Y), button_y_remap, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_A), button_a_remap, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_B), button_b_remap, FALLING);
}

// end of system basic functions----------------------------------




// void update_screen(void){
//     display_1.clearDisplay();
//     display_2.clearDisplay();

//     display_1.setCursor(0, 0);
//     display_1.println("HARDWARE TEST");
//     display_1.setCursor(0, 12);
//     display_1.print("BUTTON_X : ");
//     display_1.print(state_seq[BUTTON_X_SEQ]);

//     display_1.display();
//     display_2.display();
// }


// void update_state_seq(void){
//     state_seq[BUTTON_X_SEQ] = digitalRead(BUTTON_X);
//     state_seq[BUTTON_Y_SEQ] = digitalRead(BUTTON_Y);
//     state_seq[BUTTON_A_SEQ] = digitalRead(BUTTON_A);
//     state_seq[BUTTON_B_SEQ] = digitalRead(BUTTON_B);
//     state_seq[JOYSTICK_X_SEQ] = analogRead(JOYSTICK_X);
//     state_seq[JOYSTICK_Y_SEQ] = analogRead(JOYSTICK_Y);
//     state_seq[ROTARY_KNOB_A_SEQ] = digitalRead(ROTARY_KNOB_A);
//     state_seq[ROTARY_KNOB_B_SEQ] = digitalRead(ROTARY_KNOB_B);
//     state_seq[ROTARY_KNOB_C_SEQ] = digitalRead(ROTARY_KNOB_C);
// }
