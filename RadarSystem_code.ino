
#include <Servo.h>  


const int trigPin = 11;
const int echoPin = 12;

long duration;
int distance;

const int servoPin = 10;
Servo myServo;  

const int ledPin = 13; 
const int buzzerPin = 9;  

void setup() {
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);   

  pinMode(ledPin, OUTPUT);  
  pinMode(buzzerPin, OUTPUT);  

  Serial.begin(9600);
  myServo.attach(servoPin);  
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);  
    delay(30);  

    distance = calculateDistance();  
    handleAlerts();  

    Serial.print(i);         
    Serial.print(",");       
    Serial.print(distance); 
    Serial.print(".");       
  }

  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);

    distance = calculateDistance(); 
    handleAlerts();  

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);   
  delayMicroseconds(2);         
  digitalWrite(trigPin, HIGH);  
  digitalWrite(trigPin, LOW);  

  
  float distance = pulseIn(echoPin, HIGH) / 58.00;  
  return distance;
}

void handleAlerts() {
   
  if (distance <= 15) {
    digitalWrite(ledPin, HIGH); 
    tone(buzzerPin, 3000);  
  } else {
    digitalWrite(ledPin, LOW);  
    noTone(buzzerPin);  
  }
}