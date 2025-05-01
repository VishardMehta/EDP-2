#include<NewPing.h>                 
bool start = false;                
const int trigPin = 13;             
const int echoPin = 12;             
const int maxDistance  = 20;      
NewPing sonar(trigPin,echoPin,maxDistance); 
int distanceCm;                    
int counter = 0;                    
int prevGantry = 0;                
unsigned long prevTime = millis(); 
unsigned long currentTime;

void setup() {
  pinMode(5,OUTPUT);              
  pinMode(6,OUTPUT);            
  pinMode(7,OUTPUT);          
  pinMode(8,OUTPUT);             
  pinMode(A0,INPUT);           
  pinMode(A1,INPUT);              
  pinMode(A2,INPUT);              
  pinMode(trigPin,OUTPUT);        
  pinMode(echoPin,INPUT);
  Serial.begin(9600);           
}

void Forward()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}
void Backward()
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
}
void Left()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
void Right()
{
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}
void Anti()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
}
void Clock()
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}
void Stop()
{
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}

void loop() {
  if(Serial.available())
  {
    char a = Serial.read();               
    if(a=='W')                          
    {
      start =true;
    }
  }
    if(start)                             
    { 
      int d0 = digitalRead(A0);           
      int d1 = digitalRead(A1);           
      int g = pulseIn(A2,HIGH,5000);     
      if(g>=3000 && g<4000 && prevGantry!=1)
      {
        Serial.println("gantry 1 crossed");
        Stop();
        delay(1000);
        prevGantry = 1;
      }
     /* else if(g>=1000 && g<2000 && prevGantry!=2)
      {
        Serial.println("gantry 222");
        Stop();
        delay(1000);
        prevGantry = 2;
      }
      else if(g>=2000 && g<3000 && prevGantry!=3)
      {
        Serial.println("gantry 333");
        Stop();
        delay(1000);
        prevGantry = 3;
      }*/
      if(d0 == 0 && d1 == 0)                        
      { 
        currentTime = millis();
        if(currentTime-prevTime>500 && counter == 0)
        {
          //Parking Line
          prevTime = millis();
          counter=counter+1; //counter 1
          Forward();
          delay(25);
        }
        else if(currentTime-prevTime>750 && counter == 1)
        {
          prevTime = millis();
          counter=counter+1; //counter 2
          Left();
          delay(20);
        }
        else if(currentTime-prevTime>1000 && counter == 2)
        {
          //out
          prevTime = millis();
          counter=counter+1; //counter 3
          Forward();
          delay(20);
        }
        else if(currentTime-prevTime>1000 && counter == 3)
        {
          //in
          prevTime = millis();
          counter=counter+1; // counter 4
          Forward();
          delay(20);
        }
        else if(currentTime-prevTime>500 && counter == 4)
        {
          //parking 1
          prevTime = millis();
          counter=counter+1;
          Forward();
          delay(10);
        }
        else if(currentTime-prevTime>500 && counter == 5)
        {
          //parking 1
          prevTime = millis();
          counter=counter+1;
          Left(); 
          delay(600);
        }
        else if(currentTime-prevTime>500 && counter == 6)
        {
          //parking 1
          prevTime = millis();
          counter=counter+1;
          Forward();
          delay(10);
        }

        else if (currentTime-prevTime>500 && counter >=6)
        {
          Serial.println("Buggy Parked");
          Stop();
          start = false;
        }
        Serial.print("Forward: ");
        Serial.println(counter);
      }
      else if(d0 == 0)
      {
        Left();
      }
      else if(d1 == 0)
      {
        Right();
      }
      else
      {
        Forward();
      }
    }
    distanceCm = sonar.ping_cm();            
    if(distanceCm>0 && distanceCm<15)      
    {
      Stop();
      delay(500);
    }
}