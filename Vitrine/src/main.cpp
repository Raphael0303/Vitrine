#include <Arduino.h>


#include "pitches.h"
#include <Servo.h> 

Servo monServo;
#include "HX711.h"

#define DOUT       D12
#define CLK        D11

HX711 scale;

float calibrationFactor = 1000;
float weight = 0;

void Ouverture();
void Fermeture();
void ABAB();
/*
// notes in the melody:
int melody[] = {
NOTE_C3, NOTE_F3, NOTE_F3, NOTE_F3, NOTE_A3, NOTE_C3, 0      ,NOTE_C3,
NOTE_F3, NOTE_F3, NOTE_F3, NOTE_A3, NOTE_C4, 0      , NOTE_C4,
239    , 239    , 239    , 239    , NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3,
NOTE_G3, NOTE_G3, NOTE_F3, 0      , NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, 0

};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
float noteDurations[] = {

2, 1.5, 4, 2, 2, 1 ,2, 2,
1.5, 4, 2, 2, 1, 2, 2,
1.5, 4, 2, 2, 2, 2, 2, 2,
1, 1, 1, 1, 3, 3, 3, 0.8, 0.5
};

void sale enculé tu touchera pas à ABAB tssssk.
  ^
  |
  |
  |
(.Y.)
 

void setup() {

  // iterate over the notes of the melody:
  // put your main code here, to run repeatedly:

}
  
 */ 


// notes in the melody:
int melody[] = {

  0      , NOTE_A3, NOTE_B3, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_B3, NOTE_A3, NOTE_G3, 
  0      , NOTE_A3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_A3, 0      , NOTE_G3, NOTE_G4, NOTE_G4, NOTE_D4,
  0      , NOTE_A3, NOTE_A3, NOTE_B3, NOTE_C3, NOTE_A3, NOTE_C3, NOTE_D3, 0      , NOTE_B3, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_D3,
  0      , NOTE_A3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G3, NOTE_G3,
  0      , NOTE_A3, NOTE_B3, NOTE_C4, NOTE_A3, 0      , NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G3, NOTE_A3, NOTE_C4, NOTE_A3,
  NOTE_E4, NOTE_E4, NOTE_D4, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3,
  NOTE_G3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_D4, NOTE_C4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
float noteDurations[] = {

  2    , 4    , 4    , 4, 4, 4, 4, 4, 0.5, 
  4    , 4    , 4    , 4, 4, 4, 4, 4, 2  , 4, 0.75,
  4    , 4    , 4    , 4, 4, 4, 4, 4, 4  , 4, 4   , 8, 8, 1,
  4    , 4    , 4    , 4, 4, 4, 2, 4, 4  , 4, 4   , 1,
  0.75 , 4    , 4    , 4, 4, 4, 4, 4, 4  , 4, 1,
  2    , 4    , 4    , 4, 4, 4, 4, 4, 1.5, 8, 8, 8, 8,
  3.75 , 3.75 , 1.5  , 8, 8, 8, 8  , 3.75, 3.75, 3.75, 8, 4, 
  8, 8, 8, 8,2, 4, 1.5,2,4,2, 2, 1
};

void setup() {

  // iterate over the notes of the melody:
  pinMode(A0, OUTPUT); 
  pinMode(A2,INPUT_PULLDOWN); 
  pinMode(A4,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(A2), ABAB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(A4), Ouverture, CHANGE);
  attachInterrupt(digitalPinToInterrupt(A5), Fermeture, CHANGE);
  monServo.attach(A6);              // relier le servomoteur au port A1
  scale.begin(DOUT, CLK);
  scale.tare();
  bool fin=0;
  
  
  
  monServo.write(90);  
  
  weight = scale.get_value(10);


  while(weight < 2500){
    weight = scale.get_value(10);
  }

  delay(5000);
  
  monServo.write(110);  
  
  


  

  while (fin!=1){
    fin=digitalRead(A2);
  }

  monServo.write(90);
  digitalWrite(A0, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int thisNote = 0; thisNote < 100; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(A3, melody[thisNote], noteDuration);
    
    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);

  }

}

void Ouverture(){
  if (digitalRead(A4)==0)
    monServo.write(110);
  else
    monServo.write(90);
}

void Fermeture(){
  if (digitalRead(A5)==0)
    monServo.write(70);
  else
    monServo.write(90);
}

void ABAB(){
  monServo.write(90);
}