#include <Keypad.h> 
#include <LiquidCrystal.h>
#include "SECURITY.h"

using MiProyecto::SECURITY;

//LiquidCrystal lcd (0,1,5,4,3,2);

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
//int pos=0;
SECURITY securitySystem;  

int rojo=11;
int verde=10;
int azul=9;


void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  pinMode(verde,OUTPUT);
  //lcd.print ("Welcome!");
  analogWrite(verde,200);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
   lcd.setCursor(securitySystem.pos++,1);
   //lcd.print(key);
   securitySystem.verify(key);
  }
  if(securitySystem.pos>15){
    securitySystem.pos=0;
  }
}
