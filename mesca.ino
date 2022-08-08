/********************************************//**
 *  LCD control functions
 ***********************************************/
#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "Pines.h"
#include "SECURITY.h"
#include "StateMachineLib.h"

#include "Alarma.h"

using MiProyecto::SECURITY;
using MiProyecto::Alarma;
Alarma alarm;
SECURITY securitySystem; 
/** An enum type. 
 *  define states in State Machine 
 */
enum State{
  SECURITY = 0,
  CONFIGS = 1,
  INFORMATION = 2,
  ALARM = 3,
};
 
/** An enum type. 
 *  define Inputs in State Machine 
 */
 


//PROGRAMA
#include "Sensores.h"
#include "Menu.h"

using Sistema::Menu;
Menu menu;

 
/*! Create new StateMachine 4 states and 6 transitions */
StateMachine stateMachine(4, 6);



//async task
using Sensores::FuncSensores;
FuncSensores sens;
AsyncTask asyncTemperatura = sens.getTempAsync();
AsyncTask asyncLuz = sens.getLuzAsync();
boolean enterMenu = false;
AsyncTask asyncAlarm = alarm.getAlarm();

void setup() {
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);

  //lcd.begin(0, 0);
  lcd.setCursor(0,0);
  lcd.print("WELCOME");

  delay(1000);
  lcd.clear();

  EasyBuzzer.setPin(bzz);

  //Starting State Machine
  setup_State_Machine();  
  stateMachine.SetState(State::SECURITY, false, true);
  //lcd.begin(0, 0);
  currentInput = 0;
}

void loop() {
  EasyBuzzer.update();
  //Read value by Serial port
  read_data();

  // Update State Machine
  stateMachine.Update();
  
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
