#include "SD.h"
#include <TMRpcm.h>
#include <SPI.h>

#define SD_ChipSelectPin 10

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_C5 523
#define NOTE_C2 150  // Very low bass note

class Melody {
private:
  int tempo;
  int buzzer;
  int *notesArray;
  int notesCount;

public:
  Melody(int *melodyArray, int arraySize, int tempo, int buzzerPin) {
    this->notesArray = melodyArray;
    this->notesCount = arraySize / 2;
    this->tempo = tempo;
    this->buzzer = buzzerPin;
  }

  void play() {
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notesCount * 2; thisNote += 2) {
      divider = notesArray[thisNote + 1];
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;
      }
      tone(buzzer, notesArray[thisNote], noteDuration * 0.9);
      delay(noteDuration);
      noTone(buzzer);
    }
  }

  void sush() {
    tone(buzzer, NOTE_C2, 50);  // Play a very low bass note for 50 ms
    delay(500);
    noTone(buzzer);
  }
};

// Define tempo
int tempo = 160;

// Notes of the Happy Birthday melody followed by durations
int happybdy[] = {
  NOTE_C4, 4, NOTE_C4, 8, NOTE_D4, -4, NOTE_C4, -4, NOTE_F4, -4,
  NOTE_E4, -2, NOTE_C4, 4, NOTE_C4, 8, NOTE_D4, -4, NOTE_C4, -4,
  NOTE_G4, -4, NOTE_F4, -2, NOTE_C4, 4, NOTE_C4, 8, NOTE_C5, -4,
  NOTE_A4, -4, NOTE_F4, -4, NOTE_E4, -4, NOTE_D4, -4, NOTE_AS4, 4,
  NOTE_AS4, 8, NOTE_A4, -4, NOTE_F4, -4, NOTE_G4, -4, NOTE_F4, -2
};

// Create an instance of Melody class with Happy Birthday song data
Melody happyBirthdayMelody(happybdy, sizeof(happybdy) / sizeof(int), tempo, 9);

TMRpcm tmrpcm;
int switchAnimation = 0, action = 1;
const int doorSwitch = 2;
bool lastSwitchState = HIGH;  // Assume the switch is initially not pressed

void setup() {
  Serial.begin(9600);
  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(5);
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized successfully.");
  pinMode(doorSwitch, INPUT);
  Serial.println("Can begin now.");
}

void loop() {
  int currentSwitchState = digitalRead(doorSwitch);

  // Check if the switch state has changed
  if (currentSwitchState == LOW && lastSwitchState == HIGH) {
    // Switch has been pressed
    tmrpcm.stopPlayback();  // Ensure previous playback is stopped

    if (action == 1) {
      Serial.println("Action 1");
      delay(534);
      sound1();
      delay(500);
      happyBirthdayMelody.play();
      delay(8040);
      action++;
      Serial.print("After Increment action is: ");
      Serial.println(action);

    } else if (action == 2) {
      Serial.println("Action 2");
      delay(3636);
      Serial.println("Playing 0002.wav");
      tmrpcm.play("0002.wav");
      delay(3000);
      tmrpcm.stopPlayback();
      delay(500);
      // happyBirthdayMelody.sush();
      action++;
      Serial.print("After Increment action is: ");
      Serial.println(action);

    } else if (action == 3) {
      Serial.println("Action 3");
      delay(4542);
      action++;
      Serial.print("After Increment action is: ");
      Serial.println(action);

    } else if (action == 4) {
      Serial.println("Action 4");
      delay(820);
      Serial.println("Playing 0003.wav");
      tmrpcm.play("0003.wav");
      delay(3000);
      tmrpcm.stopPlayback();
      delay(500);
      // happyBirthdayMelody.sush();
      delay(1420);
      delay(2000);
      delay(200);
      delay(400);
      action++;
      Serial.print("After Increment action is: ");
      Serial.println(action);

    } else if (action == 5) {
      Serial.println("Action 5");
      delay(246);
      Serial.println("Playing 0004.wav");
      tmrpcm.play("0004.wav");
      while (tmrpcm.isPlaying()) {}
      tmrpcm.stopPlayback();
      // delay(500);  // use if needed
      Serial.println("Playing abc1.wav");
      tmrpcm.play("abc1.wav");
      delay(21000);
      tmrpcm.stopPlayback();
      delay(500);
      // happyBirthdayMelody.sush();
      action++;
      Serial.print("After Increment action is: ");
      Serial.println(action);
    }
  }

  lastSwitchState = currentSwitchState;
}

void sound1() {
  Serial.println("Playing 0001.wav");
  tmrpcm.play("0001.wav");
  delay(6000);
  tmrpcm.stopPlayback();
}
