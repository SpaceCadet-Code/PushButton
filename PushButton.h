#ifndef PushButton_h
#define PushButton_h

#include <EEPROM.h>
#include "Arduino.h"

class PushButton
{
  
public:
  PushButton(int input,int output,int eepromaddr=0,bool bUseEeprom=false,long debounceDelay=100,int maxeeprom=512);
  void begin(int=0,int=0);
  void read(unsigned long);
  void toggle();
  bool check();
  void handle();
  bool write (int);
private:
  int _input;
  int _output;
  //Define Outputs, inputs, and if started bit. 
  boolean _Start = false;
  int _Val  = 0;  //Define Val as 0
  //State Machine Variables
  int _CurrentState = 0;
  int _PreviousState= 0;
  int _CurrentReading = 0;           // the current reading from the input pin
  unsigned long _lastDebounceTime = 0;  // the last time the output pin was toggled
  
  bool  _bUseEEPROM;
  
  bool _LowValIn;
  bool _HighValIn;
  bool _LowValOut;
  bool _HighValOut;

  
  long _debounceDelay;
  unsigned long _now =0 ;
  int _eepromaddr;
  long _printline;
};


#endif