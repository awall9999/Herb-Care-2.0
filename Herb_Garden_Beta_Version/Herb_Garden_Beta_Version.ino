// Kräider Créche 2.0 / Herb Care 2.0
Beta Version
// www.alainsprojects.com
// (c) Alain MAUER

#include <Wire.h>
#include <EEPROM.h>
#define RTC_ADDRESS 0x68

byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

byte Second, Minute, Hour, OldMinute;

long int Blinktime;
int OnOff = 0;   //ON OFF Variable for the colon and the Display itself, where 1 is On and 0 is Off


// Display Configuration
int Clock = 7; // Clock Pin Display
int Data = 8; // Data Pin Display
const byte Seg[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00}; // Define Segment Numbers 0-9, and Blanc 
const byte CubeUp = 0x63, CubeDown = 0x5c, LetterC=0x39, LetterCs=0x58, LetterL=0x38, LetterN=0x54; // Define Special Segment Caracters
// End Display Configuration

const byte LC[] = {12,14,16,18}; //Light Cycle 12hours,14hours,16hours and 18hours ON

const int BuzzerPin = 9; // Buzzer Pin
const int LightPwmPin = 5; // PWM Pin
const int ButtonPin = 2; // Select Button Pin

int LightCycle;
int LightStartTime ;
int EndTime;
int LightStatus=1;
byte LedOn[24];

long int LoopTimer;
long int ButtonPushTimer;
int DisplayMenu = 0;
int SetupMenu = 0;
bool BlockPush = false;
bool BlockSetup = false;
bool SetupPusch = false;
byte Brightness=0x8e;
bool DisplayOn = true;
int Seg1 , Seg2 , Seg3, Seg4;

// Blinktimer is used to make the colon or the Display blink in a defined time
void BlinkTimer(int Time){
  if ((unsigned long)(millis() - Blinktime) > Time) {OnOff = !OnOff; Blinktime = millis();}  
}

void setup() {
 Serial.begin(9600);
 pinMode(Clock,OUTPUT);
 pinMode(Data,OUTPUT);
 pinMode(ButtonPin,INPUT);
 InitEEprom(); //Init the internal EEprom for first time use
 ReadEEprom(); // Read the internal EEprom
 
 Beep2(3); //Beep twice when Setup is done
 Serial.println("Kräider Créche 1.0 / Herb Care 1.0");
 Serial.println("www.alainsprojects.com");
 Serial.println("(c) Alain MAUER");

}

void loop() {
   LoopTimer = millis();
   
   do{
   
   
    if (digitalRead(ButtonPin) == 1 && BlockPush == false) {LoopTimer = millis();ButtonPushTimer = millis(); BlockPush = true;SetupPusch = false;Beep2(1);} 
    if (digitalRead(ButtonPin) == 1 && BlockPush == true && BlockSetup == false) {
                                                                                 if ((unsigned long)(millis() - ButtonPushTimer) > 1500){SetupPusch = true;BlockSetup = true;DisplayMenu = 9;SetupMenu++;if (SetupMenu > 5){SetupMenu = 0;}}}
                                                          
    
    if (digitalRead(ButtonPin) == 0 && BlockPush == true && DisplayMenu < 3) {BlockPush = false;DisplayMenu++;if (DisplayMenu > 2){DisplayMenu = 0;}}
   
    if (digitalRead(ButtonPin) == 0 && BlockPush == true && DisplayMenu == 9) {BlockPush = false;BlockSetup = false;
                                                                              if (SetupPusch == false && SetupMenu == 1) {Hour++;if(Hour>23){Hour=0;}} 
                                                                              if (SetupPusch == false && SetupMenu == 2) {Minute++;if(Minute>59){Minute=0;}}
                                                                              if (SetupPusch == false && SetupMenu == 3) {LightCycle++;if(LightCycle>3){LightCycle=0;}}
                                                                              if (SetupPusch == false && SetupMenu == 4) {LightStartTime++;if(LightStartTime>23){LightStartTime=0;}} 
                                                                              
                                                                              }

   
    if (DisplayMenu == 0){ReadRTC();
                           BlinkTimer(1000);
                           DisplayRawData(Hour,Minute);
                           DispOut(Seg[Seg1],Seg[Seg2],Seg[Seg3],Seg[Seg4],OnOff,1);}
                           
    if (DisplayMenu == 1){DisplayRawData(99,LC[LightCycle]);DispOut(LetterL,LetterCs,Seg[Seg3],Seg[Seg4],0,1);}
    if (DisplayMenu == 2){DisplayRawData(99,LightStartTime);DispOut(CubeDown,LetterN,Seg[Seg3],Seg[Seg4],0,1);}

    if (SetupMenu == 1){BlinkTimer(200); DisplayRawData(Hour,99);DispOut(Seg[Seg1],Seg[Seg2],Seg[Seg3],Seg[Seg4],1,OnOff);}
    if (SetupMenu == 2){BlinkTimer(200); DisplayRawData(99,Minute);DispOut(Seg[Seg1],Seg[Seg2],Seg[Seg3],Seg[Seg4],1,OnOff);}
    if (SetupMenu == 3){BlinkTimer(200); DisplayRawData(99,LC[LightCycle]);DispOut(LetterL,LetterCs,Seg[Seg3],Seg[Seg4],0,OnOff);}
    if (SetupMenu == 4){BlinkTimer(200); DisplayRawData(99,LightStartTime);DispOut(CubeDown,LetterN,Seg[Seg3],Seg[Seg4],0,OnOff);}
    if (SetupMenu == 5){SetRTC();WriteEEprom();Beep2(3);while (digitalRead(ButtonPin) == 1);PrintData();LightONorOff();break;}
    
    if(OldMinute != Minute && DisplayMenu < 9) {PrintData();LightONorOff(); OldMinute=Minute;}
    } while ((unsigned long)(millis() - LoopTimer) < 10000); 
   
   
 LoopTimer = millis();  
 BlockPush = false;
 DisplayMenu = 0;
 SetupMenu = 0;
 BlockSetup = false;
 ReadEEprom(); 
  
}
