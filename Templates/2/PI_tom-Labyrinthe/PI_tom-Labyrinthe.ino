#include <Servo.h>

//--------------Timer----------



//---------TOM--------------------
Servo myServoX; // define servo motor for X-axis
Servo myServoY; // define servo motor for Y-axis
int ServoXPin = 2; // define  X-axis pin
int ServoYPin = 3; // define  Y-axis pin
int ServoXHomePos = 90; // set home position for servos
int ServoYHomePos = 90;
int ServoXPos = 103;
int ServoYPos = 135;
int XAxlePin = A2; // define  X-axis pin control for joystick A2
int YAxlePin = A1; // define  Y-axis pin control for joystick A1
int XAxleValue = 0; // set start up value for joystick
int YAxleValue = 0;
int Direction = 0;
int range = 12; // output range of X or Y movement
int center = range / 2; // resting position value
int threshold = range / 4; // resting threshold



void setup()
{
  Serial.begin(9600);
  //--------------Timer---------------------
  


  //------------TOM---------------
  myServoX.attach(ServoXPin); // attaching servo X
  myServoY.attach(ServoYPin); // attaching servo Y
  ServoXPos = ServoXHomePos;  // update ServoXPos with home position as startup
  ServoYPos = ServoYHomePos;  // update ServoYPos with home position as startup
  myServoX.write(ServoXPos);
  myServoY.write(ServoYPos);
  
}
void loop()
{
  //--------------Timer---------------------




  //---------TOM------------------
  XAxleValue = readAxis(XAxlePin);
  YAxleValue = readAxis(YAxlePin);
  Serial.print(XAxleValue, DEC);
  Serial.print(" - ");
  Serial.println(YAxleValue, DEC);
  // check the values of joystick and move the servos smothly with delay of 100 millisecond
  if (XAxleValue > 0) {
    ServoXPos++;
    myServoX.write(ServoXPos);
    delay(0.1 * (7 - XAxleValue));
  }
  if (XAxleValue < 0) {
    ServoXPos--;
    myServoX.write(ServoXPos);
    delay(0.1 * (7 + XAxleValue));
  }
  if (YAxleValue < 0) {
    ServoYPos++;
    myServoY.write(ServoYPos);
    delay(0.1 * (7 - YAxleValue));
  }
  if (YAxleValue > 0) {
    ServoYPos--;
    myServoY.write(ServoYPos);
    delay(0.1 * (7 + YAxleValue));
  }
  if (ServoXPos > ServoXHomePos + 20) {
    ServoXPos = ServoXHomePos + 20;
  }
  if (ServoXPos < ServoXHomePos - 20) {
    ServoXPos = ServoXHomePos - 20;
  }
  if (ServoYPos > ServoYHomePos + 20) {
    ServoYPos = ServoYHomePos + 20;
  }
  if (ServoYPos < ServoYHomePos - 20) {
    ServoYPos = ServoYHomePos - 20;
  }
  delay(10);
}





//---------------Functions------------------
int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);
  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);
  // if the output reading is outside from the
  // rest position threshold, use it:
  int distance = reading - center;
  if (abs(distance) < threshold) {
    distance = 0;
  }
  // return the distance for this axis:
  return distance;
}

//Cablage :
//Joystick :
//GND = sur GND
//5V = 5V
//VRX = A1
//VRY = A2

//Servo 1 (grosse boite)
//Brun = GND
//Rouge = 5V
//Orange = 3

//Servo 1 (petite boite)
//Brun = GND
//Rouge = 5V
//Orange = 2
