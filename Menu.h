#ifndef MENU_H
#define MENU_H


#include "pitches.h"
#include <EEPROM.h>

//Notas 
using NotesLibrary::Notes;
Notes notas;


namespace Sistema{
      class Menu{
        private:
            const char frame[7][16] = {
              {"UtempHigh      "},
              {"UtempLow       "},
              {"Uluz           "},
              {"Usonido        "},
              {"reset          "},
              {"Continuar...   "},
              {"Salir          "}
            };
            int page = 0;
            int selectedIndex = 0;
            int lastFrame = 6;
            int opt = 0;
            boolean enter = false;

            boolean exitSystem = false;
            boolean nextState = false;
            
            void imprimirMenu(){
              lcd.setCursor(0,0);
              lcd.print( frame[page]);
              lcd.setCursor(0,1);
              lcd.print( frame[page+1]);
              indexCursor();
            }

            void indexCursor(){
              //selectedIndex == 0 ? lcd.setCursor(0,0) : lcd.setCursor(0,1);
              if(selectedIndex == 0){
                lcd.setCursor(15,0);
              }else if(selectedIndex == 1){
                lcd.setCursor(15,1);
              }
              lcd.print("<");
            }           

            void controlIndex(){
              if(selectedIndex == 2){
                selectedIndex = 0;
                page++;              
              }              
              if(selectedIndex < 0){
                page--;  
                selectedIndex = 1;
              }
            }

            void controlPage(){
              if(page == lastFrame ){
                lcd.clear();
                page = 0;
                opt = 0;
              }else if(page < 0){
                lcd.clear();
                page = lastFrame - 1;
                opt = lastFrame; //ultima opcion
              }
            }
            
            float tempHigh =  25.0f ;
            float tempLow = 18.0f;
            float umbralLuz = 300.0f;
            
            void configTempHigh(){
              lcd.setCursor(0,0);
              lcd.print("Temp High");
              
              char key = keypad.getKey();
              if (key == '0' && tempHigh < 40.f ){
                tempHigh = tempHigh + 1.0f;
                EasyBuzzer.stopBeep();
                analogWrite(RED, 0);
              }else if(key == '*' && tempHigh > 24.0f){
                tempHigh = tempHigh - 1.0f;
                EasyBuzzer.stopBeep();
                analogWrite(RED, 0);
              }else if(digitalRead(btn) == 0 && enter == true){
                EEPROM.put(1, tempHigh);
                enter = false;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }    

              if(key == '0' && tempHigh == 40.f || key == '*' && tempHigh == 24.0f){
                analogWrite(RED, 255);
                EasyBuzzer.beep(180, 100, 60, 5, 1000, 2);
              }
              

              lcd.setCursor(0,1);
              lcd.print("Value: ");
              lcd.print(tempHigh,2);
            }
            
            void configTempLow(){
              lcd.setCursor(0,0);
              lcd.print("Temp Low");
              
              char key = keypad.getKey();
              if (key == '0' && tempLow < 19.0f){
                tempLow = tempLow + 1.0f;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }else if(key == '*' && tempLow > 0.0f){
                tempLow = tempLow - 1.0f;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }else if(digitalRead(btn) == 0 && enter == true){
                EEPROM.put(2, tempLow);
                enter = false;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }    

             if(key == '0' && tempLow > 18.0f || key == '*' && tempLow == 0.0f){
                analogWrite(RED, 255);
                EasyBuzzer.beep(180, 100, 60, 5, 1000, 2);
             }

              lcd.setCursor(0,1);
              lcd.print("Value: ");
              lcd.print(tempLow,2);              
            }
            
            void configLuz(){
              lcd.setCursor(0,0);
              lcd.print("Umbral Luz");
              
              char key = keypad.getKey();
              if (key == '0' && umbralLuz < 18.0f){
                umbralLuz = umbralLuz + 1.0f;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }else if(key == '*' && umbralLuz > 0.0f){
                umbralLuz = umbralLuz - 1.0f;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }else if(digitalRead(btn) == 0 && enter == true){
                EEPROM.put(3, umbralLuz);
                enter = false;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }    

             if(key == '0' && tempLow == 18.0f || key == '*' && tempLow == 0.0f){
                analogWrite(RED, 255);
                EasyBuzzer.beep(180, 100, 60, 5, 1000, 2);
             }

              lcd.setCursor(0,1);
              lcd.print("Value: ");
              lcd.print(tempLow,2); 
            }
            
            void configSonido(){
              lcd.setCursor(0,0);
              lcd.print("Julio Jaramillo");
              int melody[] = {
                  notas.NOTE_A4, 
                  notas.NOTE_D4, 
                  notas.NOTE_F4, 
                  notas.NOTE_G4, 
                  notas.NOTE_A4, 
                  notas.NOTE_D4, 
                  notas.NOTE_F4, 
                  notas.NOTE_G4, 
                  notas.NOTE_E4,
                  notas.NOTE_G4, 
                  notas.NOTE_C4, 
                  notas.NOTE_F4, 
                  notas.NOTE_E4, 
                  notas.NOTE_G4, 
                  notas.NOTE_C4, 
                  notas.NOTE_F4, 
                  notas.NOTE_E4, 
                  notas.NOTE_D4          
              };
              
              // duracion notas: 1= negra 2 = blanca...
              
              int DuracionNotas[] = {
                2, 2, 4, 4, 2, 2, 4, 4, 1, 2, 2, 4, 4, 2, 2, 4, 4, 1,
              };

              if(digitalRead(btn) == 0 && enter == true){
                enter = false;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }        

              for (int Nota = 0; Nota < 18; Nota++) {
            
                
                int Duracion = 1000 / DuracionNotas[Nota];
                
                EasyBuzzer.singleBeep(melody[Nota], Duracion);
                //tone(bzz, melody[Nota], Duracion);        
                
                int pausa = Duracion * 1.40;
                   delay(pausa);
                
                EasyBuzzer.stopBeep();
              }            
            }

            void resetConfigs(){
              tempHigh = 25.0f ;
              tempLow = 18.0f;
              umbralLuz = 300.0f;
            }

            void viewInfo(){
              if(digitalRead(btn) == 0 && enter == true){
                currentInput = ExitConfigs;
                enter = false;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }    
            }

            void salir(){
              if(digitalRead(btn) == 0 && enter == true){
                currentInput = closeSystem;
                enter = false;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }    
            }

            void update(){
              EEPROM.update(1, tempHigh);
              EEPROM.update(2, tempLow);
              EEPROM.update(3, umbralLuz);
            }
            
            
            void subMenus(){
              switch (page)
              {
                 case 0:
                    if(selectedIndex == 0){ //UtempHigh
                      configTempHigh();
                    }else{ // UtempLow
                      configTempLow();
                    }
                    break;
                 case 1:
                    if(selectedIndex == 0){ //UtempLow
                      configTempLow();
                    }else{ // Uluz
                      configLuz();
                    }
                    break;
                 case 2:
                    if(selectedIndex == 0){ //Uluz
                      configLuz();
                    }else{ // Usonido
                      configSonido();
                    }
                    break;                    
                 case 3:
                    if(selectedIndex == 0){ //Usonido
                      configSonido();
                    }else{ // reset
                      resetConfigs();
                    }
                    break;

                 case 4:
                    if(selectedIndex == 0){ //reset
                      resetConfigs();
                    }else{ // continuar
                      viewInfo();
                      break;
                    }
                    break;      

                 case 5:
                    if(selectedIndex == 0){ //continuar
                      viewInfo();
                      break;
                    }else{ // salir
                      salir();
                      return;
                    }
                    break;                    
                                                      
                    
                 default: break;
                    //sentencias_default;
              }
            }

     
    
        public: 
            Menu(){};
            
            void controlMenu(){
              update();
              char key = keypad.getKey();

              /*if(exitSystem == true){
                return "salir";
              }
              if(nextState == true){
                return "next";
              }*/

                if (key == '0'){
                  lcd.clear();
                  EasyBuzzer.singleBeep(160, 100);
                  selectedIndex++;
                  opt++;
                }else if(key == '*'){
                  lcd.clear();
                  EasyBuzzer.singleBeep(160, 100);
                  selectedIndex--;
                  opt--;
                }

                //entrada con boton
                if(digitalRead(btn) == 0){
                  enter = true;
                  lcd.clear();
                  while(enter == true){
                    subMenus();
                  }                 
                }
                       
                EasyBuzzer.stopBeep();
                controlIndex();
                controlPage(); 
                
                imprimirMenu();  
                EEPROM.write(1, tempHigh);
                EEPROM.write(2, tempLow);  
                EEPROM.write(3, umbralLuz);  

                return "non";
            }             

            float getTempHigh(){
              return tempHigh;
            }
            float getTempLow(){
              return tempLow;
            }
            float getUmbralLuz(){
              return umbralLuz;
            }

            
        
      };
};


#endif
