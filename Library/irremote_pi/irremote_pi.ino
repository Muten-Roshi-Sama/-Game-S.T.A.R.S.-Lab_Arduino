#include <IRremote.h>
#include <Password.h>

const char DIN_RECEPTEUR_INFRAROUGE = 2;
int flag = 0;
int GAME_COMPLETE = false;

IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE);
decode_results messageRecu;
Password password = Password( "1234" );


void setup()
{
 Serial.begin(9600);
 monRecepteurInfraRouge.enableIRIn();
 monRecepteurInfraRouge.blink13(true);
}

void loop()
{
   //-----------------------------assign variables to input-----------------
   if (flag<4)
   {
    if (monRecepteurInfraRouge.decode(&messageRecu))
    {
      if (messageRecu.value == 0xFF30CF)
      {Serial.print("1");
      password.append('1');
      }
      if (messageRecu.value == 0xFF18E7)
      {Serial.print("2");
      password.append('2');
      }
      if (messageRecu.value == 0xFF7A85)
      {Serial.print("3");
      password.append('3');
      }
      if (messageRecu.value == 0xFF10EF)
      {Serial.print("4");
      password.append('4');
      }
      if (messageRecu.value == 0xFF38C7)
      {Serial.print("5");
      password.append('5');
      }
      if (messageRecu.value == 0xFF5AA5)
      {Serial.print("6");
      password.append('6');
      }
      if (messageRecu.value == 0xFF42BD)
      {Serial.print("7");
      password.append('7');
      }
      if (messageRecu.value == 0xFF4AB5)
      {Serial.print("8");
      password.append('8');
      }
      if (messageRecu.value == 0xFF52AD)
      {Serial.print("9");
      password.append('9');
      }
      if (messageRecu.value == 0xFF6897)
      {Serial.print("0");
      password.append('0');
      }
      delay(500);
      monRecepteurInfraRouge.resume();
    }
    flag += 1;
    Serial.print(GAME_COMPLETE);
   }
  if (flag>=4)
  {
//    Serial.println( password.evaluate()?"true":"false" );
    if (password.evaluate() == true)
      {GAME_COMPLETE == true;
      } 
    password.reset();
  }
  
  
  delay(1);
}










//
