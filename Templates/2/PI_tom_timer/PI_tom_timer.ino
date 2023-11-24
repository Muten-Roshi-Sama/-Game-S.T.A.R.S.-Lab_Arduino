#include <Servo.h>
#include <LiquidCrystal.h>

unsigned long millisTimer;
unsigned long millisMaze;
int IntervalTimer = 1000;
int IntervalMaze = 10;


//---------TOM--------------------
Servo myServoX; // define servo motor for X-axis
Servo myServoY; // define servo motor for Y-axis
int ServoXPin = 8; // define  X-axis pin
int ServoYPin = 9; // define  Y-axis pin
int ServoXHomePos = 60; // set home position for servos
int ServoYHomePos = 105;
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

//--------------Timer----------
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int resetButtonPin = A5;
int buttonState = 0;
char buzzerPin = A4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int initial_min = 0;
const int initial_sec = 2;
int flag = 1;
signed short minutes, secondes;
char timeline[16];


void setup()
{
  Serial.begin(9600);
  millisTimer = millis();
  millisMaze = millis();
  //--------------Timer---------------------
  pinMode(resetButtonPin, INPUT);
  lcd.begin(16, 2);
  lcd.print("Time Left :");
  minutes = initial_min;
  secondes = initial_sec;


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

  if ( (millis() - millisTimer) >= IntervalTimer) {
    buttonState = digitalRead(resetButtonPin);
    if (buttonState == HIGH) {
      minutes = initial_min;
      secondes = initial_sec;
      flag = 1;
    }

    lcd.setCursor(0, 1);
    sprintf(timeline, "%0.2d mins %0.2d secs", minutes, secondes);
    lcd.print(timeline);
    //      delay(1000);

    if (secondes == 0 && minutes != 0)
    {
      secondes = 60;
      minutes --;
    }
    if (minutes != 0 or secondes != 0) {
      secondes--;
    }
    if (secondes == 0 && minutes == 0) {
      if ( flag == 1) {
        for (int i = 0; i < 4; i++) {
          tone(buzzerPin, 600, 500);
          delay(1000);
          tone(buzzerPin, 600, 500);
          delay(1000);
          tone(buzzerPin, 600, 500);
          delay(1000);
        }
      }
      flag = 0;
    }
    millisTimer = millis();
  }


  if ( (millis() - millisMaze) >= IntervalMaze) {
    //---------TOM------------------
    XAxleValue = readAxis(XAxlePin);
    YAxleValue = readAxis(YAxlePin);
//    Serial.print(XAxleValue, DEC);
//    Serial.print(" - ");
//    Serial.println(YAxleValue, DEC);
    // check the values of joystick and move the servos smothly with delay of 100 millisecond
    if (XAxleValue < 0) {
      ServoXPos++;
      myServoX.write(ServoXPos);
      delay(0.1 * (7 - XAxleValue));
    }
    if (XAxleValue > 0) {
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
    if (ServoXPos > ServoXHomePos + 15) {
      ServoXPos = ServoXHomePos + 15;
    }
    if (ServoXPos < ServoXHomePos - 15) {
      ServoXPos = ServoXHomePos - 15;
    }
    if (ServoYPos > ServoYHomePos + 15) {
      ServoYPos = ServoYHomePos + 15;
    }
    if (ServoYPos < ServoYHomePos - 15) {
      ServoYPos = ServoYHomePos - 15;
    }
    //  delay(10);
    millisMaze = millis();
  }
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
//Orange = 9

//Servo 1 (petite boite)
//Brun = GND
//Rouge = 5V
//Orange = 8
