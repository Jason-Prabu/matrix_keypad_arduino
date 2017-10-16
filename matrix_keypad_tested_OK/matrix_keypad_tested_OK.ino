#include <Keypad.h>

const int buzzer = 9;               // +VE TERMINAL OF BUZZER CONNECTED TO D9 THROUGHN RESISTOR



unsigned long bus_number[3];
unsigned long send_bus_no;
int k = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

}


void loop() {

  if (kpd.getKeys())   //IF KEY AVAILABLE
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
    {
      if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
      {
        switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
          case RELEASED:
            tone(buzzer, 100);                 // SOUND BUZZER ....TURN OFF WHEN KeY RELEASED // SOUND BUZZER
            delay(100);
            noTone(buzzer);   // SOUND OFF BUZZER
            if (k < 3)
            {
              bus_number[k++] =  kpd.key[i].kchar;
            }
            break;

        }

        if (k == 3)
        {
          k = 0;
          send_bus_no = 100 * (bus_number[0] - '0') + 10 * (bus_number[1] - '0') + 1 * (bus_number[2] - '0');
          Serial.println(send_bus_no);
        }
      }
    }
  }



}




