#include <NewPing.h>

// Pin Definitions
const int t1 = A0;
const int t2 = A2;
const int pin5 = 5;
const int pin6 = 6;
const int pin7 = 8;
const int pin8 = 7;
const int irPin = 4;
const int triggerPin = 13;
const int echoPin = 12;
const int maxDistance = 200;

// Global Variables
int flag = 0;
unsigned long d = 0;
int gantryCounter = 0;
unsigned long startTime = 0;
unsigned long currentTime = 0;
unsigned long elapsedTime = 0;
unsigned long startTimeG = millis();
unsigned long currentTimeG = 0;
unsigned long elapsedTimeG = 0;
unsigned long previousMillisU = millis();
const long intervalU = 500;

NewPing sonar(triggerPin, echoPin, maxDistance);

void setup()
{
    pinMode(pin5, OUTPUT);
    pinMode(pin6, OUTPUT);
    pinMode(pin7, OUTPUT);
    pinMode(pin8, OUTPUT);

    pinMode(irPin, INPUT);
    pinMode(t1, INPUT);
    pinMode(t2, INPUT);
    
    Serial.begin(9600);
}

void loop()
{
    handleSerialInput();
    handleTimers();
    if (flag == 1)
    {
        gantry();
    }
    else if (flag == 3)
    {
        handleGantryParking();
    }
}

void handleSerialInput()
{
    if (flag == 0 && Serial.available() > 0)
    {
        char s = Serial.read();
        if (s == 'B')
        {
            flag = 1;
        }
    }
}

void handleTimers()
{
    unsigned long currentMillisU = millis();
    if (currentMillisU - previousMillisU > intervalU)
    {
        previousMillisU = currentMillisU;
        detectObstacle();
    }
}

void handleGantryParking()
{
    currentTimeG = millis();
    elapsedTimeG = currentTimeG - startTimeG;
    if (elapsedTimeG < 2500)
    {
        leftBlind();
    }
    else if (elapsedTimeG < 6500)
    {
        normalLineFollow();
    }
    else
    {
        stopBuggy();
        Serial.println("Buggy:1 Parked");
        delay(2000);
        flag = -1;
    }
}

void gantry()
{
    int r1 = digitalRead(t1);
    int r2 = digitalRead(t2);

    controlMotors(r1, r2);

    if (digitalRead(irPin) == HIGH)
    {
        startTime = millis();
        d = pulseIn(irPin, HIGH);
        processGantryDetection();
    }
}

void controlMotors(int r1, int r2)
{
    if (r1 == LOW && r2 == LOW)
    {
        setMotorStates(HIGH, LOW, HIGH, LOW);
    }
    else if (r1 == LOW && r2 == HIGH)
    {
        setMotorStates(HIGH, LOW, LOW, LOW);
    }
    else if (r1 == HIGH && r2 == LOW)
    {
        setMotorStates(LOW, LOW, HIGH, LOW);
    }
    else if (r1 == HIGH && r2 == HIGH)
    {
        setMotorStates(HIGH, LOW, HIGH, LOW);
    }
}

void processGantryDetection()
{
    if (d > 3000 && d < 4000)
    {
        Serial.println(d);
        Serial.println("Gantry: 1");
        stopBuggy();
        delay(1000);
    }
    /*else if (d > 1500 && d < 2500)
    {
        Serial.println(d);
        Serial.println("Gantry: 2");        
        Serial.print("The gantry Counter is: ");
        
        stopBuggy();
        delay(1000);
    }
    else if (d > 2500 && d < 3500)
    {
        Serial.println(d);
        Serial.println("Gantry: 3");        
        gantryCounter++;
        Serial.println(gantryCounter);
        delay(1000);
        normalLineFollow() ;
        delay(200);
        
    }
        */
    else
    {
        Serial.println("Gantry: Unknown");
    }

}

void stopBuggy()
{
    setMotorStates(LOW, LOW, LOW, LOW);
}

void normalLineFollow()
{
    int r1 = digitalRead(t1);
    int r2 = digitalRead(t2);

    controlMotors(r1, r2);
}

void leftBlind()
{
    int r2 = digitalRead(t2);

    if (r2 == LOW)
    {
        setMotorStates(LOW, LOW, HIGH, LOW);
    }
    else
    {
        setMotorStates(HIGH, LOW, HIGH, LOW);
    }
}

void detectObstacle()
{
    delay(50);
    unsigned int distanceCm = sonar.ping_cm();
    if (distanceCm < 15 && distanceCm > 0)
    {
        stopBuggy();
        delay(1000);
    }
}

void setMotorStates(int pin5State, int pin6State, int pin7State, int pin8State)
{
    digitalWrite(pin5, pin5State);
    digitalWrite(pin6, pin6State);
    digitalWrite(pin7, pin7State);
    digitalWrite(pin8, pin8State);
}