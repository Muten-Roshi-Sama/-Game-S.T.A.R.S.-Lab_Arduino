#define CLK 6
#define DT 7
#define Succes 8

unsigned long millisEncoder;
int IntervalEncoder = 100;

int counter = 0;
int aState;
int aLastState;

void setup() {
  Serial.begin (9600);
  millisEncoder = millis();
  pinMode (CLK, INPUT);
  pinMode (DT, INPUT);
  pinMode (Succes, OUTPUT);
  digitalWrite(8, LOW);
  aLastState = digitalRead(CLK);
}

void loop() {
  if ( (millis() - millisEncoder) >= IntervalEncoder) {
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
      digitalWrite(8, HIGH);
    }
   millisEncoder = millis();
  }
}
