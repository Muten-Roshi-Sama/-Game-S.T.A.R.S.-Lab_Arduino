//TO READ : use builtin Servo and Stepper, RGB on PMW ports only, 

//Stepper
//#include <Stepper.h>
int IN1 = 13;
int IN2 = 12;
int IN3 = 8;
int IN4 = 7;
bool dir = false;
int _step = 0;

//Joystick 
int joystick_x = A2; //joystick connected to A1 and A2 ANALOG pins
int joystick_y = A1;
int Jvalx;
int Jvaly;
int val = analogRead(0);



void setup() {
  Serial.begin(9600);

  //Stepper pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}



void loop() {


  //Serial.println(Jvaly);
  

  StepperMotor(_step, false);

  //Servo
  Jvaly = analogRead(joystick_y);


//  //Stepper
//  if (Jvaly <= 500)
//    {
//    _step = StepperMotor(_step, false);
//    delay(10);
//    }
//  else if (Jvaly >= 523)
//  {
//    _step = StepperMotor(_step, true);
//    delay(10);
//  }
//   else 
//   {
//      digitalWrite(IN1, LOW);
//      digitalWrite(IN2, LOW);
//      digitalWrite(IN3, LOW);
//      digitalWrite(IN4, LOW);
//   }
//
//}



//Stepper Function
int StepperMotor(int _step, bool dir)
  {
    switch(_step)
    {
      case 0 :
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;

      case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;

      case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;

      case 3:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    }
    if(dir) _step++;
    else _step--;
    if(_step>3)_step = 0;
    if(_step>0)_step = 3;
    return _step;
  }
