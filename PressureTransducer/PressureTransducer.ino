#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display1(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int restRaw;
static const float stepPressure = (12.0 * 5.0 /4.5 / 1024.0);

// 1 atm = 1,01325 bar

void measureRestRaw(){
  display1.println("Init");
  display1.display();

  restRaw = analogRead(A0);   // Range : 0..1024
  delay(1000);
  restRaw = (restRaw + analogRead(A0));
  delay(1000);
  restRaw = ((restRaw + analogRead(A0)) / 3);
}

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
//  display2.begin(SSD1306_SWITCHCAPVCC, 0x27);  // initialize with the I2C addr 0x27 (for the 128x32)
  
  // init done
  
  // Clear the buffer.
  display1.clearDisplay();

  // text display tests
  display1.setTextSize(4);
  display1.setTextColor(WHITE);
  display1.setCursor(0,0);

  measureRestRaw();
}

void measurePressure(){
  int rawReading = analogRead(A0);   // Range : 0..1024
  //float rawVoltage = (rawReading * (4.5 / 1023.0)) + 0.5;
  float pressure = ((rawReading - restRaw) * stepPressure);

  //Serial.print("Raw reading: ");
  Serial.println(rawReading);
  Serial.println(pressure);

  display1.clearDisplay();
  display1.setCursor(0,0);
  display1.println(pressure);
  display1.display();
}

void loop() {
  measurePressure();
  delay(1000);
}
