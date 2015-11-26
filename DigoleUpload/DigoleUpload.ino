/*
The upload speed for Start Screen and User font is about 7s/1K bytes
This demo code show you how to upload start screen and
 user fonts, the user fonts have 4 sections-0,1,2,3, each section has 4096 bytes
 you can upload your user font to any section, and you also can combine
 adjacent sections together for large font data.
 the font identify number for each sections are: 200 to 203.
 if you upload your font to section #2, use setFont(202) to use it.
 
 NOTE: once you uploaded start screen or user font, you don't need upload
 it again if unchanged, the adapter will store it in flash memory
 the DATA structure of user font is same as U8Glib
 */

//#define _Digole_Serial_SPI_           //Select Hardware SPI communications
//#define _Digole_Serial_SoftSPI_       //Select SOFT SPI communications
//#define _Digole_Serial_I2C_           //Select I2C communications
#define _Digole_Serial_UART_            //Select USART (Serial1 or Serial2) communications

// This #include statement was automatically added by the Spark IDE.
#include <DigoleSerial.h>
#include <Wire.h>

//DigoleSerialDisp mydisp(D2, D3, SS);      //SOFT SPI setup - specify DATA, CLOCK, SS pins
//DigoleSerialDisp mydisp(SS);              //Hardware SPI setup - specify SS pin
//DigoleSerialDisp mydisp('\x27');    //I2C specified - specify Pointer to Wire object, I2C address of Digole
DigoleSerialDisp mydisp(&Serial2, 38400);    //USART (Serial 1 or 2) - specify &Serial1 or &Serial2 and baudrate

#include "mydata.h"

void resetpos(void) //for demo use, reset display position and clean the demo line
{
  mydisp.setPrintPos(0, 1);
  delay(3000); //delay 2 seconds
  mydisp.println("                "); //display space, use to clear the demo line
  mydisp.setPrintPos(0, 1);
}

void setup() {
  mydisp.begin();
  mydisp.displayStartScreen(0);
  mydisp.clearScreen();
  //mydisp.print("uploading start screen now...(1024 bytes)");
  //delay(500);            //this delay is very important, it will let module to clear the receive buffer
  //mydisp.uploadStartScreen(1024,startscreenMV);
  //delay(500);
  //mydisp.clearScreen();
  mydisp.print("uploading 1st user font now...)");
  delay(500);            //this delay is very important, it will let module to clear the receive buffer
//  mydisp.uploadUserFont(sizeof(userfont1),userfont1,0);
  delay(500);
  mydisp.clearScreen();
  mydisp.setFont(200);
  mydisp.drawStr(0,0,"0123456789ABCDEFGHIJKabcdefg");
  resetpos();
  mydisp.print("uploading 2nd user font now...");
  delay(500);            //this delay is very important, it will let module to clear the receive buffer
//  mydisp.uploadUserFont(sizeof(userfont2),userfont2,1);
  delay(500);
  mydisp.clearScreen();
  mydisp.setFont(201);
  mydisp.drawStr(0,0,"0123456789ABCDEFGHIJKabcdefg");
  resetpos();
  mydisp.print("uploading 3rd font now...)");
  delay(500);            //this delay is very important, it will let module to clear the receive buffer
//  mydisp.uploadUserFont(sizeof(userfont3),userfont3,2);
  delay(500);
  mydisp.clearScreen();
  mydisp.setFont(202);
  mydisp.drawStr(0,0,"0123456789ABCDEFGHIJKabcdefg");
  resetpos();
  delay(1000);
}
void loop() {}

