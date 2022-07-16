#include <LiquidCrystal.h>
#include <Keypad.h>
#include "Menu.h"
#include <EasyBuzzer.h>
#include "AsyncTaskLib.h"

#define analogPin A0 //the thermistor attach to
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-down resistorvoid

//LED
#define BLUE 7
#define GREEN 8
#define RED 9

//const int btn = 48;
const int micro = A1;
const int fotoPin = A2;
const int soundPin = A3;
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {31,33,35,37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39,41,43}; //connect to the column pinouts of the keypad

int pos = 0;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );*/

using Sistema::Menu;
Menu menu;
void readTemp();
AsyncTask asyncTemperatura(2000, true, readTemp );

void luz();
AsyncTask asyncLuz(2000, true, luz );
int outputValue = 0;

void setup(){
  Serial.begin(115200);
  // set up the LCD’s number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(btn, INPUT);
  //pinMode(bzz, OUTPUT);
  EasyBuzzer.setPin(bzz);

  asyncTemperatura.Start();
  asyncLuz.Start();
}

boolean enterMenu = false;

void loop(){  
  EasyBuzzer.update();

  if(enterMenu == true){
    while(enterMenu == true){
      asyncTemperatura.Stop();
      asyncLuz.Stop();
      menu.controlMenu();
      controlConfigs();
    }
  }else{   
    asyncTemperatura.Start();
    asyncLuz.Start();
    while(enterMenu == false){
      asyncTemperatura.Update();
      asyncLuz.Update();
      controlConfigs();
    }
  }
}

void controlConfigs(){
  char key = keypad.getKey();
  if(key == '#' && enterMenu == true){
    enterMenu = false;
    lcd.clear();
  }else if(key == '#' && enterMenu == false){
    enterMenu = true;
    lcd.clear();
  }  
}

void readTemp(){
  long a = 1023 - analogRead(analogPin);
  float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
 
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" C");

  checkTemp(tempC);
}

void checkTemp(float temp){
  int ligth = 255;

  if(temp > menu.getTempHigh()){
    //rojo
    analogWrite(RED, ligth);
  }else if(temp < menu.getTempLow()){
    //azul
    analogWrite(BLUE, ligth);
  }else{
    //verde
    analogWrite(GREEN, ligth);
  }

  delay(1000);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
}

void luz(){
  outputValue = analogRead(fotoPin);
  lcd.setCursor(0, 1);
  lcd.print("Photocell: ");
  lcd.setCursor(11, 1);
  lcd.print(outputValue);//print the temperature on lcd1602
  Serial.println(outputValue);
  delay(1000);
  lcd.setCursor(11, 1);
  lcd.print(" ");  
}

void microfono()
{
  int value = analogRead(soundPin);
  Serial.println(value);
  if(value > 44)
  {
    Serial.println("AHH");
    //digitalWrite(ledPin,HIGH);
    //delay(100);
  }
  else
  {
  //digitalWrite(ledPin,LOW);
  }
  delay(100);
}
