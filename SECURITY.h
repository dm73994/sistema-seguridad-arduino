// LED.h
#ifndef SECURITY_h
#define SECURITY_h

#include <string.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (0,1,5,4,3,2);

namespace MiProyecto{
  class SECURITY {
    
    private:
      String password = "123456";
      String passwordEntered = "";
      int index = 0;
      int tries = 3;
      int timerMS = 2000; // 2s
      bool blocked = false;
      //leds
      int rojo=11;
      int verde=10;
      int azul=9;

      void enterSystem(){
        pinMode(verde,OUTPUT);
        analogWrite(verde,200);
        delay(1000);
        analogWrite(verde,0);
        lcd.print ("HA ENTRADO");
      };
          
      void error(){
        lcd.print ("ERROR");
        pinMode(rojo,OUTPUT);
        analogWrite(rojo,200);
        delay(1000);
        analogWrite(rojo,0);
        lcd.clear();
        tries--;
        passwordEntered = "";
        index = -1;
        //
        pos = 0;
        
        if(tries == 0) blockSystem();        
      };
            
      void blockSystem(){
        timerMS = 5000; //5s
        blocked = true;
        lcd.print ("POLICIA");
      };
          
      void reset(){
        timerMS = 2000;
        tries = 3;  
        blocked = false;
      };
      
    public:   
    
      //para probar
      int pos = 0;
      
      SECURITY(){};     

      // REEMPLAZAMOS START POR VERIFY DEBIDO A QUE EN ARDUINO SE CICLA SOLO
      void verify(char currentInput){
        lcd.print (currentInput);
        passwordEntered = passwordEntered + currentInput;
        if(currentInput != password[index]){
          error();
        }        
        if(passwordEntered == password) enterSystem();        
        index++;
      };
                  
  };
};



#endif
