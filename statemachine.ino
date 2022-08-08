
 

/*
* PURPOSE:
* Setup the State Machine
*/
void setup_State_Machine()
{
  // Add transitions
  stateMachine.AddTransition(SECURITY, SECURITY, []() {return currentInput == IncorrectPassword; } );
  stateMachine.AddTransition(SECURITY, CONFIGS, []() { return currentInput == CorrectPassword; });

  stateMachine.AddTransition(CONFIGS,SECURITY , []() { return currentInput == closeSystem; });
  stateMachine.AddTransition(CONFIGS, INFORMATION, []() { return currentInput == ExitConfigs; });

  stateMachine.AddTransition(INFORMATION, CONFIGS, []() {return currentInput == closeInfo; });
  stateMachine.AddTransition(INFORMATION, ALARM, []() { return currentInput == dispatchAlarm; });

  stateMachine.AddTransition( ALARM,CONFIGS, []() { return currentInput == closeAlarm; });

  // Add actions
  /*stateMachine.SetOnEntering(LOW_A, input_LowA);
  stateMachine.SetOnEntering(NORMAL_B, input_NormalB);
  stateMachine.SetOnEntering(HIGH_C, input_HighC);
  stateMachine.SetOnEntering(ALERT_D, input_AlertD);

  stateMachine.SetOnLeaving(LOW_A, output_LowA);
  stateMachine.SetOnLeaving(NORMAL_B, output_NormalB);
  stateMachine.SetOnLeaving(HIGH_C, output_HighC);
  stateMachine.SetOnLeaving(ALERT_D, output_AlertD);*/
}

/*
* PURPOSE:
* Read data from serial port
*/
void read_data(){
  update_Input_State_Machine();
}

/*
* PURPOSE:
* Check conditions for securityState_A
*/
void securityState(){ 
  lcd.begin(0,2); 
  bool flag = true;
  while(flag == true){
    char key = keypad.getKey();  
    lcd.setCursor(0,0);
    lcd.print("Password");
    lcd.setCursor(0,1);
    lcd.print(">");
    if(key){

      lcd.setCursor((securitySystem.pos++) + 1,1);
      lcd.print("*");
     
     if(securitySystem.verify(key)){
      stateMachine.SetState(CONFIGS, false, true);
      currentInput = CorrectPassword;
      break;
     }
    }
    if(securitySystem.pos>15){
      securitySystem.pos=0;
    }    
  }

}

/*
* PURPOSE:
* Check conditions for state_NORMAL_B
*/
void configState(){
  //lcd.begin(0,2); 
  lcd.setCursor(0,0);
  while(true){
    menu.controlMenu();
    if(currentInput != CorrectPassword){
      //update_Input_State_Machine();
      break;
    }
  }

}

/*
* PURPOSE:
* Check conditions for state_HIGH_C
*/
void showInformation(){
  asyncTemperatura.Start();
  asyncLuz.Start();

  //lcd.begin(0,); 
  while(true){
    asyncTemperatura.Update();
    asyncLuz.Update();
    if(currentInput != ExitConfigs){
      delay(1000);
      break;
    }
  }
}

/*
* PURPOSE:
* Check conditions for state_ALERT_D
*/
void alarma(){
  lcd.clear();
  lcd.setCursor(0,0);
  asyncAlarm.Start();
  while(true){
    asyncAlarm.Update();
    EasyBuzzer.singleBeep(160, 1000);
    lcd.setCursor(0,0);
    lcd.print("ERROR TEMP");
    delay(2000);
    EasyBuzzer.stopBeep();
    currentInput = closeAlarm;
    stateMachine.SetState(CONFIGS, false, true);
    if(currentInput != dispatchAlarm){
      break;
    }
  }
}


/*
* PURPOSE:
* update State Machine inputs from temperature sensor
*/
void update_Input_State_Machine()
{  
  int currentState = stateMachine.GetState();
  switch (currentState)
  {
    case SECURITY: 
      lcd.setCursor(0,0);
      lcd.print("Password:");
      securityState(); 
      break;
    
    case CONFIGS: 
      configState(); 
      break;

    case INFORMATION: 
      showInformation(); 
      break;

    case ALARM:  alarma(); break;

    default:  lcd.print("Not:");
      delay(10000); break;
  }
}

/*
* PURPOSE:
* Execute actions when entering state LOW_A
*/
void input_LowA()
{
  /*currentInput = Input::Unknown;*/
  /*lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("State:LOW_A");*/
}

/*
* PURPOSE:
* Execute actions when leaving state LOW_A
*/
void output_LowA()
{
}

/*
* PURPOSE:
* Execute actions when entering state NORMAL_B
*/
void input_NormalB()
{
}

/*
* PURPOSE:
* Execute actions when leaving state NORMAL_B
*/
void output_NormalB()
{
}

/*
* PURPOSE:
* Execute actions when entering state HIGH_C
*/
void input_HighC()
{
}

/*
* PURPOSE:
* Execute actions when leaving state HIGH_C
*/
void output_HighC()
{
}

/*
* PURPOSE:
* Execute actions when entering state ALERT_D
*/
void input_AlertD()
{
}

/*
* PURPOSE:
* Execute actions when leaving state ALERT_D
*/
void output_AlertD()
{
}
