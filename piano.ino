#include <redmp3.h>

//Button Setup
#define interruptPin 2

bool prev_state = LOW;

//Speaker Setup
#define ardunioTx 7//connect to RX of the Serial MP3 Player module
#define arduinoRx 8//connect to TX of the Serial MP3 Player modul
const int8_t volume = 0x1e;//0~0x1e (30 adjustable level)

MP3 myMP3(ardunioTx, arduinoRx);

void playWav(){
  randomSeed(analogRead(0));
  int8_t index = random(0, 8);
  if (index == 0){
    index = 2;
  }
  Serial.print("Start index: ");
  Serial.print(index);
  Serial.println();
  myMP3.playWithIndex(index); 
  
}

void stopPlaying(){
  Serial.print("Stop");
  Serial.println();
  myMP3.stopPlay();
}

void setup() {

  //Starting Serial Terminal
  Serial.begin(9600); 

  //Set interruptPin 
  pinMode(interruptPin, INPUT_PULLUP);
  
  //Set Random Seed for WAV files index
  randomSeed(analogRead(0));
  
  //Play Open Sound
  myMP3.setVolume(volume);  

  //attach Interrupt - LOW - When the button is unpressed
  //attachInterrupt(digitalPinToInterrupt(interruptPin), playWav, HIGH);

  //attach Interrupt - HIGH - When the button is pressed
  //attachInterrupt(digitalPinToInterrupt(interruptPin), stopPlaying, LOW);
  
}
/************************************loop Function*********************************/
void loop() {
  bool state = digitalRead(interruptPin);
  
  if (state == HIGH && prev_state == LOW) {
    playWav();
    prev_state = HIGH;
  }
  
  else if (state == LOW && prev_state == HIGH) {
  stopPlaying();
  prev_state = LOW;
  }
  
}
