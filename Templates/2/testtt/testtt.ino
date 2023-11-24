int GreenPin = 13;
int RedPin = 12;
char buzzerPin = 7;

void setup() {
  pinMode(GreenPin, OUTPUT);
  pinMode(RedPin, OUTPUT); 
}

void loop() {

//  buzzer("passwordOK");
//  delay(3000);
//  buzzer("passwordWrong");
//  delay(3000);
  buzzer("levelUP");
  delay(3000);
 
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
}
