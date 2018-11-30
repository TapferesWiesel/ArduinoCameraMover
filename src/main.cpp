// Motorslider Nema 17

#include "arduino.h"



long Distance = 0;  // Record the number of steps we've taken

enum State {SEARCHING_ZERO, INPUT_DISTANCE, INPUT_TIME, WAITING};

State currentState = SEARCHING_ZERO;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);

}

/*
* This Method is called at the beginning of the program to find the start of the rail.
*/
void findZero() {
  //Solange Button nicht gedrückt ist:
  //fahre ein bisschen zurück
  //endLoop
  //fahre ein paar Millimeter vor bis Button nicht mehr gedrückt ist
  //Solange Button nicht gedrückt ist:
  //fahre nur ein kleines bisschen zurück
  //endLoop
}


/*
* Converts millimeters to steps so I don't have to deal with that anymore.
*/
void moveMillimeters(int mm){
for (int i = 0; i < mm; i = i + 128)  { //how many steps are a millimeter?
  /* code */
}
}


void loop() {
  digitalWrite(9, HIGH);
  delayMicroseconds(50);
  digitalWrite(9, LOW);
  delayMicroseconds(50);
  Distance++;   // record this step



  // Check to see if we are at the end of our move
  if (Distance == 1600)
  {

    // We are! Reverse direction (invert DIR signal)
    if (digitalRead(8) == LOW)
    {
      digitalWrite(8, HIGH);
    }
    else
    {
      digitalWrite(8, LOW);
    }
    // Reset our distance back to zero since we're
    // starting a new move
    Distance = 0;
    // Now pause
    delay(500);
  }
}
