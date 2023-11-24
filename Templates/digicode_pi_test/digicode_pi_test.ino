#include <Keypad.h>
#include <Password.h>

String newPasswordString; //hold the new password
char newPassword[6]; //charater string of newPasswordString
const byte ROWS = 4;
const byte COLS = 4;
int GreenPin = A4;
int RedPin = A3;
char buzzerPin = 12;

//you can use password.set(newPassword) to overwrite it
Password password = Password( "4444" );

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
  pinMode(GreenPin, OUTPUT);
  pinMode(RedPin, OUTPUT);
}



void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    delay(60);
    switch (key) {
      default: processNumberKey(key);
    }
  }
}



//-------Functions----------\\


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
