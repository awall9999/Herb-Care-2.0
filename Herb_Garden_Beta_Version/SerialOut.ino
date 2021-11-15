void PrintData(){
 
 
 Serial.print("Time: ");
 if (Hour < 10) {Serial.print("0");Serial.print(Hour);}
 else Serial.print(Hour);
 Serial.print(":");
 if (Minute < 10) {Serial.print("0");Serial.print(Minute);}
 else Serial.print(Minute);
 
 Serial.print("  ");
 Serial.print("Light Cycle: ");Serial.print(LC[LightCycle]);
 Serial.print("  ");
 Serial.print("Light Start Time: ");Serial.print(LightStartTime);
 Serial.print("  ");
 Serial.print("Light End Time in: ");
 
 if (EndTime > LightStartTime) {Serial.print(EndTime-Hour);}
 if (EndTime < LightStartTime) {Serial.print((24+EndTime)-Hour);}  
 Serial.print("h");
 
 
 
 Serial.print("  ");
 if (LightStatus == 1) {Serial.print("Light Status: ");Serial.print("On");}
  else {Serial.print("Light Status: ");Serial.print("Off");}

 Serial.println("  ");

  
}
