#ifndef MENU_H
#define MENU_H

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EasyBuzzer.h>
#include "pitches.h"


//led
#define BLUE 7
#define GREEN 8
#define RED 9
//LCD 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//KEYPAD
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
const int btn = 48;

//BUZZER
const int bzz = A7;

//Notas 
using NotesLibrary::Notes;
Notes notas;


namespace Sistema{
      class Menu{
        private:
            const char frame[5][16] = {
              {"UtempHigh      "},
              {"UtempLow       "},
              {"Uluz           "},
              {"Usonido        "},
              {"reset          "}
            };
            int page = 0;
            int selectedIndex = 0;
            int lastFrame = 4;
            int opt = 0;
            boolean enter = false;
            
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
            
            float tempHigh = 25.0f;
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
                tempLow = tempLow + 1.0f;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }else if(key == '*' && tempLow > 0.0f){
                tempLow = tempLow - 1.0f;
                analogWrite(RED, 0);
                EasyBuzzer.stopBeep();
              }else if(digitalRead(btn) == 0 && enter == true){
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
                      configSonido();
                    }
                    break;
                    
                 default: break;
                    //sentencias_default;
              }
            }
    
        public: 
            Menu(){};
            
            void controlMenu(){
              
              char key = keypad.getKey();

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
                }else if(digitalRead(btn) == 0){
                  enter = true;
                }
                       
                //EasyBuzzer.stopBeep();
                controlIndex();
                controlPage();  
                
                while(enter){
                  subMenus();
                }
              
                imprimirMenu(); 
               
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
