# PushButton
Simple library for a push button

The format for the push button is as follows

Function Call
PushButton(input,output,eepromaddr,bUseEEPROM,debounceDelay,eeprom max);

Function Start
PushButton.begin(0,0);

Function Running
PushButton.handle();

Other functions that can be called
PushButton.toggle(); //This function will directly toggle the output
