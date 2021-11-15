
void start()
{
  digitalWrite(Clock,HIGH);//send start signal to TM1637
  digitalWrite(Data,HIGH);
  microsecond();

  digitalWrite(Data,LOW);
  digitalWrite(Clock,LOW);
  microsecond();
}
void stop()
{
  digitalWrite(Clock,LOW);
  digitalWrite(Data,LOW);
  microsecond();

  digitalWrite(Clock,HIGH);
  digitalWrite(Data,HIGH);
  microsecond();
}

void microsecond() // 45 microsecond delay 
{
long int slowdown = micros();
  do {
    
  } while ((unsigned long)(micros() - slowdown) < 45); 
}


void shiftOut(byte val)
{
      

      for (int i = 0; i < 8; i++)  
            {
            
            digitalWrite(Data, !!(val & (1 << i)));
                              
            microsecond();
            digitalWrite(Clock, HIGH);
            microsecond();
            digitalWrite(Clock, LOW);
            microsecond();            
           }
      
            digitalWrite(Clock, HIGH);
            microsecond();
            digitalWrite(Clock, LOW);
      
}
void DispOut(byte val0,byte val1,byte val2,byte val3,byte dp,byte br) // Segment 1-4, colon, Brightness
{
 

 start();
 shiftOut(0x40);
 stop();
 
 start();
 shiftOut(0xC0);
 
 shiftOut(val0);
 
 if (dp==1) shiftOut(val1=val1+0x80);
 else shiftOut(val1);
 
 shiftOut(val2);
 shiftOut(val3);
 
 start();
 if (br==1) shiftOut(Brightness);
 else shiftOut(0x80);
 stop();
 
}



void DisplayRawData(int Val1,int Val2){


Seg1 = (Val1/10);
Seg2 = (Val1 - (Seg1*10));
Seg3 = (Val2/10);
Seg4 = (Val2 - (Seg3*10));
if (Val1==99) {Seg1=10;Seg2=10;}
if (Val2==99) {Seg3=10;Seg4=10;}

  
  
}
