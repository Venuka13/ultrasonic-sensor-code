#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
Servo radarServo;

// WARNING COMPONENT PINS
const int greenLED = 5;
const int yellowLED = 4;
const int redLED = 3;
const int buzzerPin = 2; // Active Buzzer linked to Pin 2

int angleOffset = 0; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT); // Set up buzzer as an output
  
  Serial.begin(9600);
  radarServo.attach(9); 
}

void loop() {
  // Sweep from 30 to 150 degrees
  for(int i=30; i<=150; i++){  
    int calibratedAngle = i + angleOffset;
    calibratedAngle = constrain(calibratedAngle, 0, 180); 
    
    radarServo.write(calibratedAngle);
    delay(35); 
    distance = calculateDistance();
    
    updateWarningSystem(distance);
    
    Serial.print(calibratedAngle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print("."); 
  }
  
  // Sweep back from 150 to 30 degrees
  for(int i=150; i>30; i--){  
    int calibratedAngle = i + angleOffset;
    calibratedAngle = constrain(calibratedAngle, 0, 180);
    
    radarServo.write(calibratedAngle);
    delay(35);
    distance = calculateDistance();
    
    updateWarningSystem(distance);
    
    Serial.print(calibratedAngle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print("."); 
  }
}

int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void updateWarningSystem(int dist) {
  if (dist > 0 && dist <= 15) {
    // ZONE 1: DANGER CLOSE - Red LED + Alarm Sound
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzerPin, HIGH); // Alarm ON
  } 
  else if (dist > 15 && dist <= 35) {
    // ZONE 2: WARNING - Yellow only
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzerPin, LOW);  // Alarm OFF
  } 
  else if (dist > 35 && dist <= 100) {
    // ZONE 3: ALL CLEAR - Green only
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzerPin, LOW);  // Alarm OFF
  } 
  else {
    // Out of bounds - All systems quiet
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzerPin, LOW);  // Alarm OFF
  }
}
