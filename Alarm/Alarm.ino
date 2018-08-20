 #include <DS3231.h>
 #include <LiquidCrystal.h>
 #include <Servo.h> 
 
 const int trigpin=5;
 const int echopin=4;
 const int buzzer=7;

 Servo motor;

 DS3231  rtc(SDA, SCL);  
   LiquidCrystal lcd(8, 9, 10, 11, 12, 13); 
 
void setup() 
  {
     rtc.begin();
     analogWrite(6,20); //Contrast=20
     lcd.begin(16,2);
     Serial.begin(9600);
     pinMode(trigpin,OUTPUT);
     pinMode(echopin,INPUT);
     pinMode(buzzer,OUTPUT);
     pinMode(buzzer,OUTPUT);
     motor.attach (3);
  }

void loop() 
  {
    long duration,cm;
     digitalWrite(trigpin,LOW);
     delayMicroseconds(2);
     digitalWrite(trigpin,HIGH);
     delayMicroseconds(10);
     digitalWrite(trigpin,LOW);

     duration=pulseIn(echopin,HIGH);
     cm= microsecTocentimeter(duration);

  

     if(cm<10)
      {
        
        digitalWrite(buzzer,HIGH);
        delay(10);
         lcd.setCursor(0,0);
         lcd.print("Distance: ");
         lcd.print(cm);
         lcd.print("cm   ");
         lcd.setCursor(0,1);
         lcd.print(" Door Opened  ");
         delay(10);
         
                              
             motor.write(180);                
             delay(15);

     }
  

     else if(cm>10 && cm<50)
      {
         digitalWrite(buzzer,LOW);
         lcd.setCursor(0,0);
         lcd.print("Someone's coming");
         lcd.setCursor(0,1);
         lcd.print("  Please Alert  ");

      }
   
     else
      {
         digitalWrite(buzzer,LOW);
         delay(10);

           // ------ Time---------
         lcd.setCursor(0,0);
         lcd.print("Time:   ");
         lcd.print(rtc.getTimeStr());
     
         lcd.setCursor(0,1);
         lcd.print("Date: ");
         lcd.print(rtc.getDateStr());
         delay(10);

               
                                    
             motor.write(45);              //command to rotate the servo to the specified angle
             delay(15);                       
      
      }


      

                            
   
  }


     long microsecTocentimeter(long ms)
      {
         return ms/29/2;
      }
   
