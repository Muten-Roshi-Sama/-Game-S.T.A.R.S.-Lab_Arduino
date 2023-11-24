#include <Keypad.h>
#include <Password.h>
#include <LiquidCrystal.h>

unsigned long millisDigicode;
unsigned long millisTimer;
int IntervalDigicode = 60;
int IntervalTimer = 1000;


//--------Digi---------------
int GreenPin = A4;
int RedPin = A3;
char buzzerPin = 12;
//
String newPasswordString; //hold the new password
char newPassword[6]; //charater string of newPasswordString
const byte ROWS = 4;
const byte COLS = 4;
Password password = Password( "4578" );
byte maxPasswordLength = 4;
byte currentPasswordLength = 0;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
//R2-8 , R3-9 ,C1-10 , C2-11
byte rowPins[ROWS] = {NULL, 8, 9, NULL};
byte colPins[COLS] = {10, 11 , NULL , NULL };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//-------------------------------------


//--------------Timer----------
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int resetButtonPin = A5;
int buttonState = 0;
//char buzzerPin = A4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int initial_min = 10;
const int initial_sec = 0;
int flag = 1;
signed short minutes, secondes;
char timeline[16];

//--------------------------




void setup() {
  millisDigicode = millis();
  millisTimer = millis();

  Serial.begin(9600);
  //  pinMode(GreenPin, OUTPUT);
  //  pinMode(RedPin, OUTPUT);

  //-----Timer--------
  pinMode(resetButtonPin, INPUT);
  lcd.begin(16, 2);
  lcd.print("Time Left :");
  minutes = initial_min;
  secondes = initial_sec;
  //-----------------


}



void loop() {
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
  //------DIGI-------------
  if ( (millis() - millisDigicode) > IntervalDigicode) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
//      delay(60);
      switch (key) {
        default: processNumberKey(key);
      }
    }
    millisDigicode = millis();
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
