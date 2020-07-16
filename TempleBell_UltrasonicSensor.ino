/*  Button codes : ON = A90, Volume up = 490, volume down = C90 */
#include <IRremote.h>                                           // infrared library
int RECV_PIN = 2;                                               // connect TSOP data pin to Arduino pin 2
int system_state=0; int led_status=0;                           // flag for system status and LED no
int count=0;    
char a;
int led_pin = 7;
int motorPin = 8;
const int trig = 12;
const int echo = 13;
int flag =2;
int duration = 0;
int distance = 0;
int condition = 0;
int mode = 0;
int PowerFlag = 0;
IRrecv irrecv(RECV_PIN);                                        
decode_results results;                                         

void setup()
{
 
  Serial.begin(9600);                                                                       
  irrecv.enableIRIn(); 
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);

  pinMode(led_pin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  
    
  Serial.begin(9600);                                          
}

void loop() {

  if(PowerFlag ==0)
  {
      digitalWrite(motorPin, 0);
      IR_sensor();
      glow_red();

      if(mode == 9)
      {
          PowerFlag = 1;
          mode = 0;
      }
  }
  
  if(PowerFlag == 1)
  {
      glow_green(); 
      IR_sensor();
      
      if(mode == 9) 
      {
         PowerFlag = 0;
         mode = 0;
      }
      
      if(mode==1)
      {
         
         int x = ultrasonic();
         if(x<20)
         {
            digitalWrite(motorPin, HIGH);
            delay(1000);
            digitalWrite(motorPin, LOW);
            x = ultrasonic();
            while(x<20)
            {
                x = ultrasonic();
                glow_redblink();
            }
            x =0;
            delay(100);
        }
     }


  if(mode==2){
  int x = ultrasonic();
  
  if(x<40)
  {
  digitalWrite(motorPin, HIGH);
  delay(2000);
  digitalWrite(motorPin, LOW);
  
   while(x<40){
        x = ultrasonic();
        glow_redblink();

   }
     x =0;
   delay(100);
  }

  }

  if(mode==3){
  int x = ultrasonic();
  glow_blue();
  for (int i=0; i<600 ;i++)
  {
      digitalWrite(motorPin, HIGH);
      IR_sensor();
      delay(100);
      

      if(mode!=3)
      {
         i=600;
      }
      IR_sensor();
  }
  digitalWrite(motorPin, 0);
  }

 
  if(mode==4){
    glow_blue();

   for (int i=0; i<3000 ;i++)
  {
      digitalWrite(motorPin, HIGH);
      IR_sensor();
      delay(60);
      
      

      if(mode!=3)
      {
         i=3000;
      }
      IR_sensor();
  }
  digitalWrite(motorPin, 0);

  }
  if(mode==5){
    while(mode==5)
    {
      IR_sensor();
      digitalWrite(motorPin, HIGH);
      glow_blue();
      
      delay(100);
      
      }
      digitalWrite(motorPin, 0);

  }

  }
  
  
}

int ultrasonic()
{
  digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);

  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);
  return distance; 
}




int IR_sensor(){
  if (irrecv.decode(&results)) {                                                         
    switch (results.value) {                                    
      
      case 0xA90: 
      Serial.println("P");
      mode = 9;
      blink_green();

      break;
      
      case 0x10:
      Serial.println("1");
      mode = 1;
      blink_green();
      break; 
      case 0x810:
 
      Serial.println("2");
      blink_green();
       mode =2;

      break;
      case 0x410:
      Serial.println("3"); 
      blink_green();
       mode= 3;
      break;
         case 0xC10:
      Serial.println("4"); 
      blink_green();
      mode =4;
      break; 
      case 0x210:
      
      mode =5;
      
      Serial.println("5"); 
      blink_green();
      break;
      case 0xA10:
      mode=6;
     
      Serial.println("6"); 
      blink_green();
      break;
         case 0x610:
      Serial.println("7"); 
      blink_green();
      break; 
      case 0xE10:
      Serial.println("8"); 
      blink_green();
      break;
      case 0x110:
      Serial.println("9"); 
      blink_green();
      break;
      case 0x910:
      Serial.println("0");
      blink_green(); 
      break;
      
      // check whether volume up button pressed                                              
    }
                                                
  irrecv.resume();                                              
  }  
}



int glow_red()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
}

int glow_green()
{
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(7,HIGH);
}

int glow_blue()
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
}

int glow_redblink(){
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  delay(200);
  digitalWrite(7,HIGH);
  digitalWrite(6,HIGH);
  delay(200);
  }  

void blink_green()
{
   digitalWrite(6,HIGH);
   digitalWrite(5,HIGH);
   digitalWrite(7,HIGH);

   for(int i=0; i<4; i++)
   {
       digitalWrite(6,LOW);
       delay(50);
       digitalWrite(6,HIGH);
       delay(50);
   }
}

  

   
