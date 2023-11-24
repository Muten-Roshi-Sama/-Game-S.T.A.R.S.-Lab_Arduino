#include <Stepper.h>
#include <Keypad.h>  // https://downloads.arduino.cc/libraries/github.com/Chris--A/Keypad-3.1.1.zip
#include <Password.h> // https://playground.arduino.cc/uploads/Code/Password/index.zip

//------Millis--------
unsigned long millisDigicode;
unsigned long millisStepper;
unsigned long millisEncoder;
int IntervalDigicode = 60;
int IntervalStepper = 1000;
int IntervalEncoder = 100;
bool Jeu1TrousNoir = true;
bool Jeu2Labyrinthe = true;
bool Jeu3Python = true;
bool Jeu4Engrenages = true;

//------Encodeur--------
#define CLK 6
#define DT 7
#define Succes 8
const int ledpinEncodeur = A0;
int counter = 0;
int aState;
int aLastState;
bool flagEncodeur = true;
//-----------Stepper--------------
const int det1Pin  = A1; //Trous noir
const int det2Pin  = A2; //
const int butplusPin = A3;
const int butresetPin = A4;
int det1Val = 0;
int det2Val = 0;
int butplusState = 0;
int butresetState = 0;
const int stepsPerRevolution = 1024;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 9, 10, 11);

//-----Digicode-----
int GreenPin = 13;
int RedPin = 12;
char buzzerPin = 7;
String newPasswordString; //hold the new password
char newPassword[6]; //charater string of newPasswordString
const byte ROWS = 4;
const byte COLS = 4;
Password password = Password( "4444" );
Password password2 = Password( "5555" );
Password password3 = Password( "7777" );
Password password4 = Password( "8888" ); //if not needed, input NULL
Password password5 = Password( "8888" );
byte maxPasswordLength = 4;
byte currentPasswordLength = 0;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
//R2-8 , R3-9 ,C1-10 , C2-11
byte rowPins[ROWS] = {NULL, 5, 4, NULL};
byte colPins[COLS] = {3, 2 , NULL , NULL };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup() {
  Serial.begin(9600);
  millisDigicode = millis();
  millisStepper = millis();
  millisEncoder = millis();
  
  //-----Ecodeur-----
  pinMode (CLK, INPUT);
  pinMode (DT, INPUT);
  pinMode (Succes, OUTPUT);
  pinMode (ledpinEncodeur, OUTPUT);
  aLastState = digitalRead(CLK);
  
  //--------Digicode-------
  pinMode(GreenPin, OUTPUT);
  pinMode(RedPin, OUTPUT);

  //-----------Stepper-------
  // Set the speed to 5 rpm:
  myStepper.setSpeed(15);
  //  Serial.println(F("Initialize System"));
  pinMode(det1Pin, INPUT);
  pinMode(det2Pin, INPUT);
  pinMode(butplusPin, INPUT);
  pinMode(butresetPin, INPUT);

  delay(100); //pause for setup to initialise
}


void loop() {
  //------Encodeur-------
  if ( (millis() - millisEncoder) >= IntervalEncoder && Jeu4Engrenages) {
    if (counter != -125) {
      aState = digitalRead(CLK);
      if (aState != aLastState) {
        if (digitalRead(DT) != aState) {
          counter ++;
        } else {
          counter --;
        }
        Serial.print("Position: ");
        Serial.println(counter);
      }
      aLastState = aState;
    }
    else if (counter == -125) {
      run1step(1);
      Jeu4Engrenages = false;
      buzzer("levelUP");
      digitalWrite(ledpinEncodeur, HIGH);
    }
   millisEncoder = millis();
  }
  
  //--------Digicode-------
  if ( (millis() - millisDigicode) >= IntervalDigicode && Jeu3Python) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      //      delay(60);
      switch (key) {
        default: processNumberKey(key);
      }
    }
    millisDigicode = millis();

  }

  //-----------Stepper--------------
  if ( (millis() - millisStepper) >= IntervalStepper) {
    butplusState = digitalRead(butplusPin);
    butresetState = digitalRead(butresetPin);
    testDET();
    millisStepper = millis();
  }
}


//-----------FUNCTIONS--------------

//--------Digicode------------

void processNumberKey(char key) {
  Serial.print(key);
  currentPasswordLength++;
  password.append(key);
  password2.append(key);
  password3.append(key);
  password4.append(key);
  password5.append(key);
  if (currentPasswordLength == maxPasswordLength) {
    if (password.evaluate() && Jeu1TrousNoir) {
      Serial.println(" OK.");
      buzzer("passwordOK");
      delay(1000);
      buzzer("levelUP");
      run1step(1);
      Jeu1TrousNoir = false;
    }
    else if (password2.evaluate() && Jeu2Labyrinthe) {
      Serial.println(" OK.");
      buzzer("passwordOK");
      delay(1000);
      buzzer("levelUP");
      run1step(1);
      Jeu2Labyrinthe = false;
    }
    else if (password3.evaluate() && Jeu3Python) {
      Serial.println(" OK.");
      buzzer("passwordOK");
      delay(2000);
      buzzer("levelUP");
      run1step(1);
      Jeu3Python = false;
    }
    else if (password4.evaluate() && Jeu4Engrenages) {
      Serial.println(" OK.");
      buzzer("passwordOK");
      delay(1000);
      buzzer("levelUP");
      run1step(1);
      Jeu4Engrenages = false;
    }
    else if (password5.evaluate()) {
      Serial.println(" OK.");
      buzzer("passwordOK");
      delay(2000);
      buzzer("reset");
      run1step(1);
    }
    else {
      Serial.println(" Wrong password!");
      buzzer("passwordWrong");
    }
    resetPassword();
  }
}

void resetPassword() {
  password.reset();
  password2.reset();
  password3.reset();
  currentPasswordLength = 0;
}

void buzzer(int x) {
  if (x == "passwordOK") {
    digitalWrite(GreenPin, HIGH);
    tone(buzzerPin, 800, 1000);
    delay(2000);
    digitalWrite(GreenPin, LOW);
  } 
  else if (x == "passwordWrong") {
    digitalWrite(RedPin, HIGH);
    tone(buzzerPin, 1000, 500);
    delay(1000);
    tone(buzzerPin, 1000, 500);
    digitalWrite(RedPin, LOW);
  }
  else if (x =="levelUP") {
    digitalWrite(GreenPin, HIGH);
    tone(buzzerPin, 800, 1000);
    delay(200);
    tone(buzzerPin, 1000, 1000);
    delay(200);
    tone(buzzerPin, 1200, 200);
    delay(200);
    tone(buzzerPin, 800, 1000);
    delay(200);
    tone(buzzerPin, 1000, 1000);
    delay(200);
    tone(buzzerPin, 1200, 200);
    delay(200);
    tone(buzzerPin, 1600, 500);

    digitalWrite(GreenPin, LOW);
  }
  else if (x == "reset") {
    digitalWrite(GreenPin, HIGH);
    tone(buzzerPin, 600, 2000);
    digitalWrite(GreenPin, LOW);
  }
}






//-----------Stepper--------------
void testDET( ) { /* Read distance sensor */
  det1Val = analogRead(det1Pin);
  det2Val = analogRead(det2Pin);

  if (butresetState == HIGH) {
    //    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution);
    myStepper.step(-stepsPerRevolution);
  }

  if (det1Val < 200 && Jeu1TrousNoir) {
    run1step(1);
    Jeu1TrousNoir = false;
  }
  if (det2Val < 200 && Jeu2Labyrinthe) {
    run1step(1);
    Jeu2Labyrinthe = false;
  }

}

void run1step(int x) {
  myStepper.step(x * stepsPerRevolution);
  myStepper.step(x * stepsPerRevolution);
}


int distRawToPhys(int raw) { /* function distRawToPhys */
  ////IR Distance sensor conversion rule
  float Vout = float(raw) * 0.0048828125; // Conversion analog to voltage
  int phys = 13 * pow(Vout, -1); // Conversion volt to distance

  return phys;
}
