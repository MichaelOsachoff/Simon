#include "buzzer.h"
#include <Adafruit_CircuitPlayground.h>

//Buttons
const int a4buttonPin = A4;
const int a5buttonPin = A5;
const int a6buttonPin = A6;
const int a7buttonPin = A7;

//Buzzer Notes
const int notes[4] = {E3_NOTE, A3_NOTE, C4s_NOTE, E4_NOTE};
int generatedNotes[MAX_NOTES];
int capturedNotes[MAX_NOTES];

int currentNoteCount = 1;

void intializeButtons(){
  pinMode(a4buttonPin, INPUT_PULLUP);
  pinMode(a5buttonPin, INPUT_PULLUP);
  pinMode(a6buttonPin, INPUT_PULLUP);
  pinMode(a7buttonPin, INPUT_PULLUP);
}

void generateNotes(){
  for(int i = 0; i < MAX_NOTES; i++){
    generatedNotes[i] = notes[random(3)];
  }
}

void playStartTone(){
  for(int i = 0; i < 4; i++)
  {
    CircuitPlayground.playTone(notes[i],200);
    delay(200);
  }
}

void playGeneratedNotes(int numNotes){
  for(int i = 0; i < numNotes; i++){
    delay(200);
    CircuitPlayground.playTone(generatedNotes[i],300);
  }
}

bool retrieveAndVerifyButtonPresses(int numNotes){
  int buttonPresses[numNotes] = {};
  int numButtonPresses = 0;

  //Retrieve button presses
  while(numButtonPresses < numNotes){
    // Read button states
    int a4buttonState = digitalRead(a4buttonPin);
    int a5buttonState = digitalRead(a5buttonPin);
    int a6buttonState = digitalRead(a6buttonPin);
    int a7buttonState = digitalRead(a7buttonPin);
    int buttonReads[4] = {a4buttonState, a5buttonState, a6buttonState, a7buttonState};

    // Once at least one button pressed
    if(a4buttonState == LOW || a5buttonState == LOW || a6buttonState == LOW || a7buttonState == LOW){
      //Ensure no more than one button is pressed at a time
      for(int i = 0; i < 4; i++){
        for(int j = i + 1; j < 4; j++){
          if(buttonReads[i] == LOW && buttonReads[j] == LOW){
            return false;
          }
        }
      }

      // Check which button Pressed
      if(a4buttonState == LOW) {
        buttonPresses[numButtonPresses] = notes[0];
      }
      if(a5buttonState == LOW){
        buttonPresses[numButtonPresses] = notes[1];
      }
      if(a6buttonState == LOW){
        buttonPresses[numButtonPresses] = notes[2];
      }
      if(a7buttonState == LOW){
        buttonPresses[numButtonPresses] = notes[3];
      }
      numButtonPresses++;
      
      delay(500);
    }
  }

  // Check for incorrect button presses
  for(int i = 0; i < numNotes; i++){
    if(buttonPresses[i] != generatedNotes[i])
    {
      return false;
    }
  }

  // All presses must be correct at this point
  return true;
}

void playFailTone(){
  CircuitPlayground.playTone(B2b_NOTE, 100);
  CircuitPlayground.playTone(B2b_NOTE, 100);
  CircuitPlayground.playTone(B2b_NOTE, 100);
}

void playSuccessTone(){
  CircuitPlayground.playTone(E3s_NOTE, 200);
  CircuitPlayground.playTone(A3_NOTE, 50);
  delay(50);
  CircuitPlayground.playTone(C4s_NOTE, 50);
  delay(50);
  CircuitPlayground.playTone(E4s_NOTE, 400);
}

void setup() {
  CircuitPlayground.begin(); //Required for buzzer
  intializeButtons();
}

void loop() {
  //Reset and regenerate notes
  currentNoteCount = 1;
  generateNotes();

  playStartTone();
  delay(1000);

  //Main gameplay loop
  while(true){
    playGeneratedNotes(currentNoteCount);
    bool buttonsPressesCorrect = retrieveAndVerifyButtonPresses(currentNoteCount);

    if(buttonsPressesCorrect == true){
      if(currentNoteCount == MAX_NOTES){
        playSuccessTone();
        delay(5000);
        break;
      }
      else{
        currentNoteCount++;
        delay(200);
      }
    }
    else{
      playFailTone();
      delay(5000);
      break;
    }
  }
}