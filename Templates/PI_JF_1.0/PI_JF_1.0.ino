const int det1Pin  = A1;
const int det2Pin  = A2;
int det1Val  = 0;
int det2Val  = 0;

//Tom + lcd
//ajouter digicode et code corentin

#include <Stepper.h>

// Define number of steps per rotation:
const int stepsPerRevolution = 1024;
// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver
// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Set the speed to 5 rpm:
  myStepper.setSpeed(15);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
  Serial.println(F("Initialize System"));

  pinMode(det1Pin, INPUT);
  pinMode(det2Pin, INPUT);
}


void loop() {
  testDET();
}

void testDET( ) { /* function testDET1 */
  ////Read distance sensor
  det1Val = analogRead(det1Pin);
  Serial.print(det1Val); Serial.print(F(" - ")); Serial.println(distRawToPhys(det1Val));
  det2Val = analogRead(det2Pin);
  Serial.print(det2Val); Serial.print(F(" - ")); Serial.println(distRawToPhys(det2Val));
  
  if (det1Val < 200 or det2Val < 200) {
   
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);

  delay(3000);
  
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);


  delay(3000);
   
   }
}

int distRawToPhys(int raw) { /* function distRawToPhys */
  ////IR Distance sensor conversion rule
  float Vout = float(raw) * 0.0048828125; // Conversion analog to voltage
  int phys = 13 * pow(Vout, -1); // Conversion volt to distance

  return phys;   

}
 
