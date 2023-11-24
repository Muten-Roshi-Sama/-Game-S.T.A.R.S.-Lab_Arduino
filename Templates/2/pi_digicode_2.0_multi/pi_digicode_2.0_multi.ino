#include <Keypad.h>
#include <Password.h>


int GreenPin = A4;
int RedPin = A3;
char buzzerPin = 12;
Password password = Password( "1234" );
Password password1 = Password( "4567" );
const byte ROWS = 4;
const byte COLS = 4;
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

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
