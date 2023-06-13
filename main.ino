#include <Metro.h>
#include <AltSoftSerial.h>  // Arduino build environment requires this
#include <wavTrigger.h>
#include <Keypad.h>
const byte rows = 4; 
const byte cols = 3; 
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows] = {5, 4, 3, 2}; 
byte colPins[cols] = {8, 7, 6}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

AltSoftSerial altSerial(9, 10);

#define LED 13


wavTrigger wav;

Metro gLedMetro(500);   // LED blink interval timer
Metro gSeqMetro(6000);  // Sequencer state machine interval timer

byte gLedState = 0;   // LED State
int gSeqState = 0;    // Main program sequencer state
int gRateOffset = 0;  // WAV Trigger sample-rate offset
int gNumTracks;
int currentTrack = 0;

char gWTrigVersion[VERSION_STRING_LEN];


void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, gLedState);

  delay(1000);

  wav.start();
  delay(10);

  wav.stopAllTracks();
  wav.samplerateOffset(0);

  wav.setReporting(true);

  delay(100);

  if (wav.getVersion(gWTrigVersion, VERSION_STRING_LEN)) {
    gLedState = 1;
    digitalWrite(LED, gLedState);
  }
  else {
    digitalWrite(LED, !gLedState);
  }
}

void loop() {
  /* wav.update();
  wav.trackPlaySolo(2);
  delay(6000);
  wav.trackPlaySolo(1);
  delay(3000);
  wav.trackPause(1);
  delay(2000);
  wav.trackResume(1);
  delay(3000); */
  char key = keypad.getKey();
  
  if (key){   // If key is pressed, send it to the Serial Monitor Window
    switch(key) {
      case 0x31:
        wav.trackPlaySolo(1);
        currentTrack = 1;
        break;
      
      case 0x32:
        wav.trackPlaySolo(2);
        currentTrack = 2;
        break;
      
      case 0x23:
        wav.trackPause(currentTrack);
        break;

      case 0x2A:
        wav.trackResume(currentTrack);
        break;
    }
    if (key == "1"){
      Serial.print(key=="1");
    }
  }

}
