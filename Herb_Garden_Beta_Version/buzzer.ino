void Beep2(int repeat){
  
     
     
     noTone(BuzzerPin);
     
     
     for (int sound = 0; sound <= repeat-1; sound++) {
                                     tone(BuzzerPin, 2000);
                                     delay(100);
                                     noTone(BuzzerPin);
                                     delay(100);
                                     }
  noTone(BuzzerPin);
  
}

void Buzz(int repeat){
 int Timenow;
 //pinMode(BuzzerPin,OUTPUT);
 analogWrite(BuzzerPin,253);

 while ((unsigned long)(millis()  - LoopTimer) <= 100);

 analogWrite(BuzzerPin,0);
 while ((unsigned long)(millis()  - LoopTimer) <= 100);
 LoopTimer = millis();
  
}

void Beep(){
  
     
     
     
     LoopTimer = millis();
     
     
                                     tone(BuzzerPin, 2400);
                                     while ((unsigned long)(millis()  - LoopTimer) <= 200);
                                     noTone(BuzzerPin);
                                     while ((unsigned long)(millis()  - LoopTimer) <= 200);
                                     
  
  LoopTimer = millis();
}
