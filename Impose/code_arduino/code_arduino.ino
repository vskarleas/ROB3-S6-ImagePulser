#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

String inString="";
void setup() {
  Serial.begin(9600);

  myservo1.attach(5);  // (y axes) attaches the servo on pin 5 to the servo object
  myservo2.attach(6);  // (x axes) attaches the servo on pin 6 to the servo object
  myservo2.write(120); 
  myservo1.write(120);  
}

float x;
float y;
float error_x;
float error_y;
float a = 0.01;
float roi = 225;
int angle_x = 40;
int angle_y = 40;

void loop() {

    if (Serial.available() > 0) {
     
    


     int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
     }
    // if you get a newline, print the string, then the string's value:
    if (inChar == ' ') {
      Serial.print("Value Y:");
      int pos1 =inString.toInt();
      Serial.println(pos1);
      error_y = float(pos1) - roi;
      Serial.print("y final: ");
      angle_y = angle_y + error_y * a;
      Serial.println(angle_y);
      // clear the string for new input:
      myservo1.write(angle_y);              // tell servo to go to position in variable 'pos'

      inString = "";
      }
          // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.print("Value X:");
      int pos2 =inString.toInt();
      Serial.println(pos2);
      error_x = float(pos2)- roi;
      angle_x = angle_x - error_x * a;
      Serial.print("x final: ");
      Serial.println(angle_x);
      // clear the string for new input:
      myservo2.write(angle_x);              // tell servo to go to position in variable 'pos'
      Serial.print("\n");
      inString = "";
      }
      delay(15);   // waits 15ms for the servo to reach the position
    }
    

}

