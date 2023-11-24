//TO READ : use builtin Servo

//Servo
#include <Servo.h>
Servo servoX;
Servo servoY;
int servopinX = 2;
int servopinY = 3;


//Joystick 
int joystick_x = A2; //joystick connected to A1 and A2 ANALOG pins
int joystick_y = A1;
int Jvalx;
int Jvaly;
int valX = analogRead(0);
int valY = analogRead(0);


void setup() {
  Serial.begin(9600);
  servoX.attach(servopinX);
  servoY.attach(servopinY);

}



void loop() {

  //ServoX
  Jvalx = analogRead(joystick_x);
  valX = map(Jvalx, 0, 1023, 0, 180);
  servoX.write(valX);
  
  //ServoX
  Jvaly = analogRead(joystick_y);
  valY = map(Jvaly, 0, 1023, 0, 180);
  servoY.write(valY);
  
}
