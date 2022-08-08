// CONEXIONES DE ARDUINO
#ifndef PINES_h
#define PINES_h

#include "AsyncTaskLib.h"
#include <EasyBuzzer.h>

// CONEXION LCD
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#define analogPin A0 //the thermistor attach to
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-down resistorvoid


const int micro = A1;
const int fotoPin = A2;
const int soundPin = A3;

//LED
#define BLUE 7
#define GREEN 8
#define RED 9

//KEYPAD
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {31,33,35,37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39,41,43}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


//BUTTON
const int btn = 50;

//BUZZER
const int bzz = A7;


//**************************
enum Input
{
  IncorrectPassword = 0,
  CorrectPassword = 1,
  closeSystem = 2,
  ExitConfigs = 3,
  closeInfo = 4,
  ExitInformation = 5,
  dispatchAlarm = 6,
  closeAlarm = 7,
  Unknown = 8,
};
 
/*! Stores last user input */
Input currentInput;


#endif
