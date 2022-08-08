// LED.h
#ifndef SECURITY_h
#define SECURITY_h

#include <string.h>
#include <Arduino.h>

namespace MiProyecto{
  class SECURITY {
    
    private:
      String password = "12";//3456";
      String passwordEntered = "";
      int index = 0;
      int tries = 2;
      int timerMS = 2000; // 2s
      bool blocked;
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
        for(int i = 0; i < 3; i++){
          EasyBuzzer.singleBeep(160, 1000);
          delay(100);
          EasyBuzzer.stopBeep();
        }
        
        lcd.setCursor(1,1);
        lcd.print("INCORRECTO");
        delay(1000);
        lcd.clear();
        tries--;
        passwordEntered = "";
        index = -1;
        pos = 0;
        lcd.setCursor(0,15);
        lcd.print(tries);
        if(tries == 3) blockSystem();        
      };

      void blockSystem(){
          EasyBuzzer.singleBeep(160, 1000);
          //timerMS = 5000; //5s
          //SECURITY::blocked = true;
          lcd.setCursor(0,0);
          lcd.print("LLAMAR POLICIA");
      };
          
      void resetSys(){
        lcd.clear();
        EasyBuzzer.stopBeep();
        timerMS = 2000;
        tries = 2;  
        blocked = false;
      };
      
    public:   
    
      //para probar
      int pos = 0;
      
      SECURITY(){};     

      // REEMPLAZAMOS START POR VERIFY DEBIDO A QUE EN ARDUINO SE CICLA SOLO
      bool verify(char currentInput){
        passwordEntered = passwordEntered + currentInput;
        if(currentInput != password[index]){
          if(tries == 0){
            lcd.clear();
            blockSystem();
            delay(3000);
            resetSys();
          }else{
            error();
          }
        }        
        if(passwordEntered == password)
        {
          lcd.setCursor(0,1);
          lcd.print("HA INGRESADO.");
          enterSystem();    
          return true;   
        }
        index++;
        return false;
      };
                  
  };
};



#endif
