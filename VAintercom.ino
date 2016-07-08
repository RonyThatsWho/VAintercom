/*
 
  AutoMatic DoorBell Answering System
  Powered by Arduino

  Unit will automatically answer intercom requests prompting user for 
  password for entry. If correct activates relays to open door.

  Pitches.h and Original Tone functions part of Public Domain.

  Rony Vargas
  v 1.0
 
 */

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};


int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


//Query Melody
int querymelody[] = {
  NOTE_G3, NOTE_C4, NOTE_C4
};

int queryDurations[] = {
  8, 4, 4
};

//Fail Melody
int failmelody[] = {
  NOTE_G3, NOTE_G3
};

int failDurations[] = {
  8, 8
};

//Success Melody
int grantedmelody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int grantedDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int switchPin = 10;
int ledPin = 13;
int doorPin = 0;
int talkPin = 1;

#define PRESS LOW
#define UNPRESS HIGH 

void playQuery(){
   for (int thisNote = 0; thisNote < 3; thisNote++) 
   {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / queryDurations[thisNote];
    tone(8, querymelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void playDenied(){
   for (int thisNote = 0; thisNote < 2; thisNote++) 
   {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / failDurations[thisNote];
    tone(8, failmelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void playGranted(){
   for (int thisNote = 0; thisNote < 8; thisNote++) 
   {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void playIncorrect(){
   for (int thisNote = 0; thisNote < 8; thisNote++) 
   {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}


void setup() {

   pinMode(switchPin, INPUT);
   pinMode(doorPin, OUTPUT);
   pinMode(talkPin, OUTPUT);
   pinMode(ledPin, OUTPUT);
   pinMode(3, OUTPUT);
 
}

void loop() {
  // Wait and Test for initial Ringer

  //Ringer Detected
  if (digitalRead(switchPin) == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    //Wait 5 seconds for End, Engage Talk and Send Beeps

    delay (5000);
    digitalWrite(talkPin, PRESS);
    delay(500);
    playQuery();
    delay(1000);
    digitalWrite(talkPin, UNPRESS);

    //Listen For 5 seconds
    delay (5000);

    //Test Input (Hold pin for TRUE)
    if (digitalRead(switchPin) == HIGH)
    //Will Be testing for Voice Commands in future revisions
    {
      digitalWrite(talkPin, PRESS);
      delay(500);
      playGranted();
      delay(800);
      digitalWrite(talkPin, UNPRESS);
      delay(100);
      digitalWrite(doorPin, PRESS);
      delay(150);
      digitalWrite(doorPin, UNPRESS);
    }
    else 
    {
      digitalWrite(talkPin, PRESS);
      delay(500);
      playDenied();
      delay(500);
      digitalWrite(talkPin, UNPRESS);
    }
   
  }

  //Reset Conditions
  else
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(talkPin, UNPRESS);
    digitalWrite(doorPin, UNPRESS);
  }

}