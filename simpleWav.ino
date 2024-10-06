// teensy 3.2 w/audio shield
// all audio must be 16 bit PCM, 44100 Hz WAV
// start files 1-3 by grounding pins 0,1,2 
// stop files 1-3 by grounding pins 3,4,5
// sd card files must be labeled "sound1.wav" , "sound2.wav", and "sound3.wav". Naming is case-sensitive. Don't include the quotes!


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


AudioPlaySdWav           playWav1;     //xy=275,381
AudioPlaySdWav           playWav2;     //xy=278,342
AudioPlaySdWav           playWav3;     //xy=279,299
AudioPlaySdWav           playWav4;     //xy=284,443
AudioMixer4              mixer1;         //xy=477,487

AudioOutputI2S           audioOutput;

AudioConnection          patchCord1(playWav1, 0, mixer1, 2);
AudioConnection          patchCord2(playWav2, 0, mixer1, 1);
AudioConnection          patchCord3(playWav3, 0, mixer1, 0);
AudioConnection          patchCord4(playWav4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, audioOutput, 0);
AudioConnection          patchCord6(mixer1, 1, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=797,489

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7   // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN   14  // Teensy 4 ignores this, uses pin 13

void setup() {
  Serial.begin(9600);

  AudioMemory(8);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  pinMode(0, INPUT_PULLUP);  //trigger for sound 1
  pinMode(1, INPUT_PULLUP); //trigger for sound 2
  pinMode(2, INPUT_PULLUP); //trigger for sound 3
  pinMode(3, INPUT_PULLUP); // stop for sound1
  pinMode(4, INPUT_PULLUP); // stop for sound2
  pinMode(5, INPUT_PULLUP); // stop for sound3
  pinMode(8, INPUT_PULLUP);
}




void loop() {

  if(digitalRead(0) == 0){
    playWav1.play("SDTEST1.WAV");
  }
  
  if(digitalRead(1) == 0){
    playWav2.play("SDTEST2.WAV");
  }
  
  if(digitalRead(2) == 0){
    playWav3.play("SDTEST3.WAV");
  }
  
  if(digitalRead(3) == 0){
    playWav1.stop();
  }
  if(digitalRead(4) == 0){
    playWav2.stop();
  }
  if(digitalRead(5) == 0){
    playWav3.stop();
  }

}
