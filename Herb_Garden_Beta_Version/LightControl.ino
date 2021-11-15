void LightONorOff(){
EndTime= (LightStartTime+LC[LightCycle]);if (EndTime > 23){EndTime=EndTime-24;}


if (EndTime > LightStartTime) {if (EndTime-Hour >0 ) {LightsOn();}
else {LightsOff();}                               } 

                              
if (EndTime < LightStartTime) {if ((24+EndTime)-Hour > 0) {LightsOn();}
else {LightsOff();}                              } 

}



void LightsOn(){

if (LightStatus ==0 ) {for (int i = 0; i <= 255; i++) {
  analogWrite(LightPwmPin,i);
  delay(50);  
  }}
LightStatus = 1;  
  }

void LightsOff(){
if (LightStatus == 1 ) {for (int i = 0; i <= 255; i++) {
  analogWrite(LightPwmPin,255-i);
  delay(50);  
  }}
LightStatus = 0;  
  }


void LightONorOffver2(){
EndTime= (LightStartTime+LC[LightCycle]);if (EndTime > 23){EndTime=EndTime-24;}


if (EndTime > LightStartTime) {if (Hour >= LightStartTime && Hour < EndTime) {LightsOn();}
else {LightsOff();}                               } 

                              
if (EndTime < LightStartTime) {if (Hour >= LightStartTime || Hour < EndTime) {LightsOn();}
else {LightsOff();}                              } 

}
