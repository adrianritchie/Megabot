#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial btSerial(A5, A4); // RX, TX

#define FORWARD 1
#define BACKWARD 0

char data = 0;

void setup()
{
    // enable serial connection
    Serial.begin(9600);
    btSerial.begin(9600);

    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
}

void rightMotor(bool dir) {
    digitalWrite(13, HIGH);
    digitalWrite(11, dir);
    digitalWrite(12, !dir);
}

void leftMotor(bool dir) {
    digitalWrite(8, HIGH);
    digitalWrite(9, !dir);
    digitalWrite(10, dir);
}

void forward() {
    rightMotor(FORWARD);
    leftMotor(FORWARD);
}

void backward() { 
    rightMotor(BACKWARD);
    leftMotor(BACKWARD);
}

void left() {
    rightMotor(FORWARD);
    leftMotor(BACKWARD);
}
 void right() {
    rightMotor(BACKWARD);
    leftMotor(FORWARD);
 }

 void stop() {
     for (int i = 8; i <=13; i++) {
         digitalWrite(i, LOW);
     }
 }

void loop()
{
    // put your main code here, to run repeatedly:

    if (btSerial.available() > 0) // Send data only when you receive data:
    {
        data = btSerial.read();       //Read the incoming data and store it into variable data
        Serial.println(data);         //Print Value inside data in Serial monitor
       
       switch(data) {
            case 'f':
                forward();
                break;
            case 'b':
                backward();
                break;
            case 'l':
                left();
                break;
            case 'r':
                right();
                break;
            case 's':
                stop();
                break;
       }
    }
}