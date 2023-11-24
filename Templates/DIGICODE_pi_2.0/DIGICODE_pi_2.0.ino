#include <Servo.h>
#include <Keypad.h>
#include <Password.h>

//----------T--------------------------------------
Servo myServoX; // define servo motor for X-axis 
Servo myServoY; // define servo motor for Y-axis 
int ServoXPin = 2; // define  X-axis pin
int ServoYPin = 3; // define  Y-axis pin
int ServoXHomePos =90; // set home position for servos
int ServoYHomePos =90; 
int ServoXPos =103;
int ServoYPos =135; 
int XAxlePin = A2; // define  X-axis pin control for joystick A2
int YAxlePin = A1; // define  Y-axis pin control for joystick A1
int XAxleValue = 0; // set start up value for joystick
int YAxleValue = 0;
int Direction = 0;
int range = 12; // output range of X or Y movement
int center = range/2; // resting position value
int threshold = range/4; // resting threshold

//-------------V--------------------------
String newPasswordString; //hold the new password
char newPassword[6]; //charater string of newPasswordString
const byte ROWS = 4;
const byte COLS = 4;
int GreenPin = A4;
int RedPin = A3;
char buzzerPin = A5;
//you can use password.set(newPassword) to overwrite it
Password password = Password( "1444" );
byte maxPasswordLength = 4;
byte currentPasswordLength = 0;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
}; //R1-8, R2-9, R3-10, R4-11, C1-12, C2-13, C3-None, C4-None
byte rowPins[ROWS] = {6, 7, 8, 9};   //CONNECTIONS: blue-8 red-13, others in order in between
byte colPins[COLS] = {10,11 ,12 ,13 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{
myServoX.attach(ServoXPin); // attaching servo X 
myServoY.attach(ServoYPin); // attaching servo Y
ServoXPos = ServoXHomePos;  // update ServoXPos with home position as startup
ServoYPos = ServoYHomePos;  // update ServoYPos with home position as startup
myServoX.write(ServoXPos);
myServoY.write(ServoYPos);
Serial.begin(9600);
}


void loop()
{
char key = keypad.getKey();
if (key != NO_KEY) {
  delay(60);
  switch (key) {
    default: processNumberKey(key);
  }
}

//-------T------------------------------
XAxleValue = readAxis(XAxlePin);
YAxleValue = readAxis(YAxlePin);
//Serial.print(XAxleValue,DEC);
//Serial.print(" - ");
//Serial.println(YAxleValue,DEC);
// check the values of joystick and move the servos smothly with delay of 100 millisecond
if (XAxleValue>0) { ServoXPos++; myServoX.write(ServoXPos); delay(0.1*(7-XAxleValue)); }
if (XAxleValue<0) { ServoXPos--; myServoX.write(ServoXPos); delay(0.1*(7+XAxleValue)); }
if (YAxleValue<0) { ServoYPos++; myServoY.write(ServoYPos); delay(0.1*(7-YAxleValue)); }
if (YAxleValue>0) { ServoYPos--; myServoY.write(ServoYPos); delay(0.1*(7+YAxleValue)); }
if (ServoXPos>ServoXHomePos+20) { ServoXPos=ServoXHomePos+20; }
if (ServoXPos<ServoXHomePos-20) { ServoXPos= ServoXHomePos-20; }
if (ServoYPos>ServoYHomePos+20) { ServoYPos=ServoYHomePos+20; }
if (ServoYPos<ServoYHomePos-20) { ServoYPos= ServoYHomePos-20; }
delay(10);
}
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


//----------------FUNCTIONS V----------

void processNumberKey(char key) {
  Serial.print(key);
  currentPasswordLength++;
  password.append(key);
  if (currentPasswordLength == maxPasswordLength) {
    checkPassword();
  }
}

void checkPassword() {
  if (password.evaluate()) {
    Serial.println(" OK.");
    buzzer(true);
  } else {
    Serial.println(" Wrong password!");
    buzzer(false);
  }
  resetPassword();
}

void resetPassword() {
  password.reset();
  currentPasswordLength = 0;
}

void buzzer(int x) {
  if (x == true) {
    digitalWrite(GreenPin, HIGH);
    tone(buzzerPin, 800, 1000);
    delay(2000);
    digitalWrite(GreenPin, LOW);
  }
  else {
    digitalWrite(RedPin, HIGH);
    tone(buzzerPin, 1000, 500);
    delay(1000);
    tone(buzzerPin, 1000, 500);
    digitalWrite(RedPin, LOW);
  }
}
