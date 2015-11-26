//#define _Digole_Serial_I2C_
#define _Digole_Serial_UART_
#define STEAMTEMPPIN A0    
#define STEAMTHERMISTORNOMINAL 100000      
#define STEAMBCOEFFICIENT 3950
#define STEAMTEMPRESISTOR 100000    
#define NUMTEMPSAMPLES 5
#define TEMPERATURENOMINAL 25   

#include <DigoleSerial.h>
#include <Wire.h>
#include "data.h"

//DigoleSerialDisp mydisp(&Wire,'\x27');
DigoleSerialDisp mydisp(&Serial2, 38400); //UART:Arduino UNO: Pin 1(TX)on arduino to RX on module

const int ftNumber[] = {0,6,10,18,51,120,123};
int samples[NUMTEMPSAMPLES];

void demoFont(int fontNumber) {
  mydisp.clearScreen(); 
  mydisp.setTextPosAbs(0,60); 
  mydisp.setFont(fontNumber);
  mydisp.print("Font = ");
  mydisp.print(fontNumber);
  mydisp.nextTextLine();
  mydisp.print("Espresso");  
}

void cleanLowerSection() {
  mydisp.setDrawWindow(2,69,156,56); 
  mydisp.cleanDrawWindow();
  mydisp.resetDrawWindow();  
}

void showClock(uint x,uint y) {
  mydisp.setColor(255);
  mydisp.setFont(123); 
  mydisp.setTextPosAbs(x,y);
  mydisp.print("21");
  mydisp.setFont(120); 
  mydisp.print(":");
  mydisp.setFont(123); 
  mydisp.print("42");
}

void drawBasicLayout(){
  // Upper section (Temperatures)
  mydisp.setColor(240);
  mydisp.drawVLine(81,25,27);
  mydisp.setFont(10); 
  mydisp.setTextPosAbs(25,9);
  mydisp.print("STEAM");
  mydisp.setTextPosAbs(105,9);
  mydisp.print("COFFEE");

  // Lower section (Dynamic)
  mydisp.drawFrame(1,68,158,58);
}

void drawTemperature(unsigned int tempNumber, float temp){
  mydisp.setColor(255);
  mydisp.setFont(51);

  if (tempNumber == 1){
    mydisp.setDrawWindow(5,10,75,35); 
    mydisp.cleanDrawWindow();
    mydisp.resetDrawWindow();  

    mydisp.setTextPosAbs(5,35);
  }
  else if (tempNumber == 2){
    mydisp.setTextPosAbs(90,35);
  }
  
  mydisp.print(temp,1);
}

void setup() {
  analogReadResolution(10);

  mydisp.begin();
  mydisp.clearScreen(); 

  drawBasicLayout();

  // Temperatures
  // Set values
  mydisp.setColor(255);
  mydisp.setFont(18); 
  mydisp.setTextPosAbs(30,58);
  mydisp.print("125\260C");
  mydisp.setTextPosAbs(110,58);
  mydisp.print("104\260C");
  // Current readings
//  drawTemperature(1,126.7);
  drawTemperature(2,103.1);

  // Heating symbol
  mydisp.setColor(128);
  mydisp.drawDisc(95,53,5);
 
  // Shot
  // Layout
  mydisp.setColor(240);
  mydisp.drawVLine(65,69,56);
  
  // Current readings  
  mydisp.setColor(255);
  mydisp.setFont(51); 
  mydisp.setTextPosAbs(90,93);
  mydisp.print("9.5");
  mydisp.setFont(18); 
  mydisp.setTextPosOffset(2,0);
  mydisp.print("bar");
  mydisp.setTextPosAbs(75,119);
  mydisp.setFont(51);
  // Timer
  mydisp.setColor(255);
  mydisp.print("12.8");
  mydisp.setFont(18); 
  mydisp.setTextPosOffset(2,0);
  mydisp.print("s");
  // Image
  for (int j = 0; j < sizeof(shotImage);j++) {
       mydisp.write(pgm_read_byte_near(shotImage+j));  
  }
  mydisp.write(0);
  mydisp.write(0);

  delay(1000);

  // Clock
  cleanLowerSection();
  // Current value
  showClock(20,115);
}

void loop() {

  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMTEMPSAMPLES; i++) {
   samples[i] = analogRead(STEAMTEMPPIN);
   delay(10);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMTEMPSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMTEMPSAMPLES;
 
  // convert the value to resistance
  average = 1023 / average - 1;
  average = STEAMTEMPRESISTOR / average;
 
  float steinhart;
  steinhart = average / STEAMTHERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= STEAMBCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  drawTemperature(1,steinhart);
  delay(2000);

    mydisp.displayConfig(0);
  mydisp.displayStartScreen(0);


//  drawTemperature(1, average);
  
//  for (float j = 126.7; j > 124.0;j = j - 0.1) {
//      delay(1000);
//      drawTemperature(1,j);  
//  }


//  mydisp.print("Start screen :");
//  delay(1000);
//  mydisp.clearScreen(); 
//  mydisp.displayStartScreen(1);
//  delay(2000);
//  mydisp.clearScreen(); 
//
//char deg = 0xB0;
//
//  // Split espresso screen
//  mydisp.setColor(255);
//  mydisp.drawHLine(0,60,160);
//  mydisp.drawVLine(80,0,60);
//  mydisp.setFont(51);
//  mydisp.setTextPosAbs(2,25);
//  mydisp.print("122\260");
//  mydisp.setFont(18); 
//  mydisp.setTextPosAbs(40,55);
//  mydisp.print("125\260C");
//  mydisp.setTextPosAbs(85,25);
//  mydisp.print("103\260");
//
//  delay(10000);
//
//    for (int j = 0; j < sizeof(ftNumber)/sizeof(int);j++) {
//         demoFont(ftNumber[j]);  
//         delay(2000);
//    }
//
//  mydisp.clearScreen(); 
//  mydisp.displayStartScreen(1);
//  delay(2000);
}

