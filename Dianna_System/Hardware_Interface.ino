

void Hardware_Interface::init_hardware(){
    Adafruit_SSD1306 display(OLED.SCREEN_WIDTH, OLED.SCREEN_HEIGHT, &Wire, OLED.OLED_RESET);
    display.begin(SSD1306_SWITCHCAPVCC, OLED.SCREEN_ADDRESS);
    display.display();
    delay(2000); // Pause for 2 seconds
    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println("Auto Film Developer");
    display.display();
}