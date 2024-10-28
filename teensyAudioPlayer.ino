
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
#define SDCARD_MOSI_PIN  11   // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN   13  // Teensy 4 ignores this, uses pin 13

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
  pinMode(0, INPUT);  //trigger for sound 1
  pinMode(1, INPUT); //trigger for sound 2
  pinMode(2, INPUT); //trigger for sound 3
  pinMode(3, INPUT); // stop for sound1
  pinMode(4, INPUT); // stop for sound2
  pinMode(5, INPUT); // stop for sound3
  //pinMode(8, INPUT_PULLUP);
}




void loop() {

  playWav1.play("SOUND1.WAV");

  if (digitalRead(0) == 1) {
    playWav1.play("SOUND1.WAV");
    delay(300);
    Serial.println("playing sound 1");
  }

  if (digitalRead(1) == 1) {
    playWav2.play("SOUND2.WAV");
    delay(300);
    Serial.println("playing sound 2");
  }

  if (digitalRead(2) == 1) {
    playWav3.play("SOUND3.WAV");
    delay(300);
    Serial.println("playing sound 3");
  }

  if (digitalRead(3) == 1) {
    playWav1.stop();
    delay(300);
    Serial.println("stopping sound 1");
  }
  if (digitalRead(4) == 1) {
    playWav2.stop();
    delay(300);
    Serial.println("stopping sound 2");
  }
  if (digitalRead(5) == 1) {
    playWav3.stop();
    delay(300);
    Serial.println("stopping sound 3");
  }

}
