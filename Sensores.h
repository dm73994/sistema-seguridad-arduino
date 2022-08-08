#ifndef SENSORES_H
#define SENSORES_H

namespace Sensores{
  class FuncSensores{
    public: 

      //int outputValue = 0; 

      AsyncTask getTempAsync(){
        AsyncTask asyncTemperatura(2000, true, readTemp );
        return asyncTemperatura;
      }

      AsyncTask getLuzAsync(){
        AsyncTask asyncLuz(2000, true, luz );
        return asyncLuz;
      }
      
      static void readTemp(){
        long a = 1023 - analogRead(analogPin);
        float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
      
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(tempC);
        lcd.print(" C");
      
        checkTemp(tempC);
      }
      
      static void checkTemp(float temp){
        int ligth = 255;

        const float tempHigh = 0;
        const float tempLow = 0;
        const float umbralLuz = 0;
        EEPROM.get(1, tempHigh);
        EEPROM.get(2, tempLow);
        EEPROM.get(3, umbralLuz);

        if(temp < 25.0f){
          currentInput = dispatchAlarm;
        }
        if(temp > tempHigh){
          //rojo
          analogWrite(RED, ligth);
        }else if(temp < tempLow){
          //azul
          analogWrite(BLUE, ligth);
        }else{
          //verde
          analogWrite(GREEN, ligth);
        }
      
        /*analogWrite(RED, 0);
        analogWrite(BLUE, 0);
        analogWrite(GREEN, 0);*/
      }
      
      static void luz(){
        int outputValue = analogRead(fotoPin);
        lcd.setCursor(0, 1);
        lcd.print("Photocell: ");
        lcd.setCursor(11, 1);
        lcd.print(outputValue);//print the temperature on lcd1602
        lcd.setCursor(11, 1);
        lcd.print(" ");  
      }
      
      static void microfono()
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
      
  }; 
}

#endif
