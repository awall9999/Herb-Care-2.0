void InitEEprom(){

if (EEPROM.read(0)!=99) {EEPROM.write(0,99);EEPROM.write(1,2);EEPROM.write(2,5);}  //first time run setup
                                                                                                                                //when address 0 in EEPROM is not 99, then write 99.
                                                                                                                                //02 on address 1 for the LightCycle 16 and 5 on address 2 for the Light Start Time.
}
 
  
void ReadEEprom(){  
LightCycle=EEPROM.read(1); //Read adress 1 and set LightCycle
LightStartTime=EEPROM.read(2); //Read adress 2 and set Light Start Time.
}

void WriteEEprom(){  
EEPROM.update(1, LightCycle); //If LightCycle has changed, Write new value to adress 1
EEPROM.update(2, LightStartTime); //If Light Start Time has changed, Write new value to adress 2
}
