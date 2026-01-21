#include <SoftwareSerial.h>
#include <Servo.h>

// Function declarations
void forward();
void backward();
void left();
void right();
void stopMotors();

bool isMovingForward = false;
SoftwareSerial BT(10, 11); // RX, TX
Servo myservo; // create servo object to control a servo

int pos = 0; // variable to store the servo position

// Motor A pins
int in1 = 4;
int in2 = 5;
int ena = 8;

// Motor B pins
int in3 = 6;
int in4 = 7;
int enb = 9;

// Ultrasonic pins
const int trigPin = 12;
const int echoPin = 13;

char command;
long duration;
int distance;

void setup() {
    myservo.attach(3); 
    // Set motor pins as outputs
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(ena, OUTPUT);
    pinMode(enb, OUTPUT);
    
    digitalWrite(ena, HIGH);
    digitalWrite(enb, HIGH);
    
    // Start Bluetooth
    BT.begin(9600);
    Serial.begin(9600);
    
    // Set initial servo position
    myservo.write(90);
}

void loop() {
    // Measure distance using ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
    
    // Bluetooth command handling
    if (BT.available()) {
        command = BT.read();
        
        switch (command) {
            case 'F': // Forward
                isMovingForward = true;
                forward(); // Immediately start moving
                myservo.write(90); // Point sensor forward
                Serial.print("forward");
                break;
            case 'B': // Backward
                isMovingForward = false; // Backward movement doesn't need obstacle avoidance
                backward();
                myservo.write(90);// Point sensor forward
                Serial.print("backward");
                break;
            case 'L': // Left turn
                isMovingForward = false; // Stop while turning
                stopMotors();
                myservo.write(180); // Point sensor left
                delay(500); // Give time for servo to move
                left(); // Turn wheels left
                Serial.print("left");
                break;
            case 'R': // Right turn
                isMovingForward = false; // Stop while turning
                stopMotors();
                myservo.write(0); // Point sensor right
                delay(500); // Give time for servo to move
                right(); // Turn wheels right
                Serial.print("right");
                break;
            case 'S': // Stop
                isMovingForward = false;
                stopMotors();
                myservo.write(90); // Center the sensor
                Serial.print("stop");
                break;
        }
    }
    
    // Obstacle detection 
    if (isMovingForward) {
        if (distance <= 15) { 
            stopMotors();
            isMovingForward = false; // Stop and change state
        }
    }
    delay(50); 
}

// Motor control functions (moved to outside of loop)
void forward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
}

void backward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void left() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void right() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void stopMotors() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
