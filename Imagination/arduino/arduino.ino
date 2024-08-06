#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

int angle_x = 120;  // initial angle for x-axis servo
int angle_y = 120;  // initial angle for y-axis servo
int step = 5;       // angle step size for each command

// String inString="";

void setup() {
  Serial.begin(9600);

  myservo1.attach(5);  // (y axes) attaches the servo on pin 5 to the servo object
  myservo2.attach(6);  // (x axes) attaches the servo on pin 6 to the servo object
  
  // Set initial positions
  myservo2.write(120); 
  myservo1.write(120);  
}

void loop() {
  if (Serial.available() > 0) {
    int x = Serial.parseInt();
    int y = Serial.parseInt();
    
    // Assuming x and y are angles for the servos
    myservo1.write(x);
    myservo2.write(y);

    // Optional: Add a way to ensure the full reading cycle
    while(Serial.available() > 0) {
      Serial.read(); // Clean up any leftover in the buffer
    }
  }
}
