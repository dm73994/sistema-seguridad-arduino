#ifndef ALARMA_H
#define ALARMA_H

namespace MiProyecto{
  class Alarma{
    private:
      int timeMs = 5000;
    public:

      AsyncTask getAlarm(){
        AsyncTask asyncAlarm(timeMs, true, stopAlarm );
        return asyncAlarm;
      }
    
      static void stopAlarm(){
        EasyBuzzer.stopBeep();
        currentInput = closeAlarm;
      }
  };
}

#endif
