# PushButton
Simple library for a push button

The format for the push button is as follows

## Function Call
PushButton(input,output,eepromaddr,bUseEEPROM,debounceDelay,eepromMaxAddr);  
    input = pin for input  
    output = pin for output  
    eepramaddr = address where state of switch is stored if bUseEeprom is true  
    bUseEeprom = use eeprom or loose values on restart  
    debounceDelay = how long the button has to be held before the light comes on  
    eepromMaxAddr = maximum address of the eeprom  

## Function Start
PushButton.begin(input_type,output_type);  
Input Types:  
        0 = pinMode(pin,INPUT)  
          LOW = 0  
          HIGH = 1  
        1 = pinMode(pin,INPUT)  
          LOW = 1  
          High = 0   
        2 = pinMode(pin,INPUT_PULLUP)  
          LOW=0  
          HIGH=1  
        3 = pinMode(pin,INPUT_PULLUP)  
          LOW = 1  
          High = 0   
Output Types:  
        0 = pinMode(pin,OUTPUT)  
          LOW = 0  
          HIGH = 1  
        1 = pinMode(pin,OUTPUT)  
          LOW = 1  
          High = 0  
        
## Function Running
PushButton.handle();

## Other functions that can be called
PushButton.toggle(); //This function will directly toggle the output
