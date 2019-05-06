#include "PushButton.h"

PushButton::PushButton(int input,int output,int eepromaddr,bool bUseEEPROM,long debounceDelay,int maxeeprom )
{
  _input = input;
  _output = output;
  _eepromaddr = eepromaddr;
  _bUseEEPROM = bUseEEPROM;
  _debounceDelay = debounceDelay;
  EEPROM.begin(maxeeprom);
}

void PushButton::begin(int InputType, int OutputType)
{
	if (not _Start)
  {
	  toggle();
  }
  
   if (InputType == 0)
  {
     _LowValIn = LOW;
     _HighValIn = HIGH;
     pinMode(_input,INPUT);
  }
  else if (InputType == 1)
  {
     _LowValIn = HIGH;
     _HighValIn = LOW;
     pinMode(_input,INPUT);
  }
   else if (InputType == 2)
  {
     _LowValIn = LOW;
     _HighValIn = HIGH;
     pinMode(_input,INPUT_PULLUP);
  }
 else if (InputType == 3)
  {
     _LowValIn = HIGH;
     _HighValIn = LOW;
     pinMode(_input,INPUT_PULLUP);
  }

  if (OutputType == 0)
  {
     _LowValOut = LOW;
     _HighValOut = HIGH;
     pinMode(_output,OUTPUT);
  }
  else if (OutputType == 0)
  {
     _LowValOut = HIGH;
     _HighValOut = LOW;
     pinMode(_output,OUTPUT);
  }
  
    //Set the start bit to true. This function is only ran once at startup
      _Start = true;
}


void PushButton::read(unsigned long now){

//State Machine Control
  _CurrentReading = digitalRead(_input);
  _PreviousState = _CurrentState;
  //State Machine Section
  switch (_CurrentState) {
    case 0: //Home
      //Home State for the State MAchine
      _CurrentState = 1;
    break;

    case 1: //Wait for switch
      //Wait for the switch to go low
      if (_CurrentReading == _LowValIn) {_CurrentState = 2;}
    break;

    case 2: //Switch Pushed
      //Record the time and proceed to ARMED
      _lastDebounceTime = _now;
      _CurrentState = 3;
    break;

    case 3: //Switch high
      //Check to see if the proper delay has passed.  If a bounce occures then RESET
      if (_now - _lastDebounceTime > _debounceDelay) {_CurrentState = 4;}
      if (_CurrentReading == _HighValIn) {_CurrentState = 0;}
    break;

    case 4: //Switch is triggered now wait for off
      //If switch goes high, then TRIGGER.
      if (_CurrentReading == _HighValIn) {_CurrentState = 5;}
    break;

    case 5: //Switch is off, Go to home state
      //reset the State Machine
      _CurrentState = 0;
    break;

  }
}


bool PushButton::check()
{

  //Run function to toggle if needed
  if(_PreviousState != _CurrentState) //if the state has changed and the current step is 4 then toggle lights
      if (_CurrentState == 4){               //this prevents multiple toggles as the state is 4 for as long as the switch is held
           toggle();
		   return true;
       }
	   return false;
}



//Toggle function
void PushButton::toggle()
 {
  //Check if this is the first run
  if (_Start == true){
  //If it is not first run then toggle value
      _Val ^= 1; // xor current value with 1 (causes value to toggle)
      digitalWrite(_output, _Val);
    //store the value to EEPROM address 0 and commit changes to EEPROM

    if (_bUseEEPROM) {
      EEPROM.write(_eepromaddr,_Val);
      EEPROM.commit();
    }
  }
  //If this is the first run then set all values accordingly
  else {
  //Set relay variable from the EEPROM
      if (_bUseEEPROM) {
      _Val = EEPROM.read(_eepromaddr);
		digitalWrite(_output,_Val);
      }
      else
      {
        digitalWrite(_output,_LowValOut);
      }
 
  }
 
 }

bool PushButton::write (int value)
{
	if (value = 0)
	{
		
			digitalWrite(_output,_LowValOut);
			return true;
	}
	else if (value = 1)
	{
		
			digitalWrite(_output,_HighValOut);
			return true;
	}
	return false;
}


void PushButton::handle()
{
  _now = millis(); 
  read(_now);
  check();

}
  
