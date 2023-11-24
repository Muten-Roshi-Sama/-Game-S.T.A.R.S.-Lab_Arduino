#include <LiquidCrystal.h>

unsigned long millisTimer;
int IntervalTimer = 1000;

//------PINS-----------
//const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int resetButtonPin = A5;
int buttonState = 0;
char buzzerPin = A4;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//----variables-------
const int initial_min = 10;
const int initial_sec = 0;
int flag = 1;
signed short minutes, secondes;
char timeline[16];









void setup() {
  Serial.begin(9600); //Test, can you use with lcd ??
  millisTimer = millis();
  pinMode(resetButtonPin, INPUT);
  lcd.begin(16, 2);
  lcd.print("Time Left :");
  minutes = initial_min;
  secondes = initial_sec;
  
}



void loop() {
  buttonState = digitalRead(resetButtonPin);

  if ( (millis() - millisTimer) >= IntervalTimer) {
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
}
