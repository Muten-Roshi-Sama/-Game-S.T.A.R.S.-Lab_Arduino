/* table de verite 
 *  sel = but1
 *  I0 = but2
 *  I1 = but3
 *  
 *  si sel, renvoie but2
 *  sinon but3
 *  
 *  breadboard : 3 but + 3 * 10kOhm
 *  led et ohm
 *  
 *  
 */


int led = 7;
int button1 = 8;
int button2 = 9;
int button3 = 12;
int buttonstate1 = 0;
int buttonstate2 = 0;
int buttonstate3 = 0;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  buttonstate1 = digitalRead(button1);
  buttonstate2 = digitalRead(button2);
  buttonstate3 = digitalRead(button3);

  if(buttonstate1)
  {
    if(buttonstate2)
        {digitalWrite(led, HIGH);
        }
        
    else
        {digitalWrite(led, LOW);

        }
  }
  else
    {
      if(buttonstate3)
      {digitalWrite(led, HIGH);
      }

      else
      {digitalWrite(led, LOW);
      }
    }











  



}
