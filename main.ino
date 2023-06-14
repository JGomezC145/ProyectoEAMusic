#include <Metro.h>
#include <AltSoftSerial.h>  // Arduino build environment requires this
#include <wavTrigger.h>
#include <Keypad.h>
#include <string.h>
#include <LiquidCrystal.h>

const int rs=51, en=49, d4=47, d5=45, d6=43, d7=41;
const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

byte rowPins[rows] = { 8, 2, 3, 4 };
byte colPins[cols] = { 5, 6, 7 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);


const int boton1 = 38;
const int boton2 = 14;
const int boton3 = 24;
const int boton4 = 26;
const int boton5 = 28;
const int boton6 = 30;
const int boton7 = 32;
const int boton8 = 34;
const int boton9 = 36;

int boton=0;

//AltSoftSerial altSerial(19, 18);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define LED 13

bool updS = false; //actualiza toda la lcd
bool updP = false; // actualiza la pista en lcd

wavTrigger wav;

Metro gLedMetro(500);   // LED blink interval timer
Metro gSeqMetro(6000);  // Sequencer state machine interval timer

byte gLedState = 0;   // LED State
int gSeqState = 0;    // Main program sequencer state
int gRateOffset = 0;  // WAV Trigger sample-rate offset
int gNumTracks;
int currentTrack = 0;
//char[] songs = {"misi", "maso", "miso", "muso"};
String currentDig = "";

char gWTrigVersion[VERSION_STRING_LEN];
String banco = "0";
String lastbanco = "0";


void setup() {
  Serial.begin(9600);
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(boton3, INPUT_PULLUP);
  pinMode(boton4, INPUT_PULLUP);
  pinMode(boton5, INPUT_PULLUP);
  pinMode(boton6, INPUT_PULLUP);
  pinMode(boton8, INPUT_PULLUP);
  pinMode(boton8, INPUT_PULLUP);
  pinMode(boton9, INPUT_PULLUP);


  lcd.begin(16, 2);
  lcd.print("Starting");

  pinMode(LED, OUTPUT);
  digitalWrite(LED, gLedState);

  delay(1000);

  wav.start();
  delay(100);

  wav.stopAllTracks();
  wav.samplerateOffset(0);

  wav.setReporting(true);

  wav.trackPlayPoly(1);
  delay(3000);
  wav.stopAllTracks();

  delay(100);

  if (wav.getVersion(gWTrigVersion, VERSION_STRING_LEN)) {
    gLedState = 1;
    digitalWrite(LED, gLedState);
    Serial.println("version obtenida");
  } else {
    digitalWrite(LED, !gLedState);
    Serial.println("version no obtenida");
  }
  delay(1000);
  Serial.print("Numero de canciones: ");
  Serial.println(wav.getNumTracks());
  // get number of songs
  // print songs in lcd
  lcd.clear();
  lcd.print("Listo");

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
  //char key = keypad.getKey();

  /* if (key) {  // If key is pressed, send it to the Serial Monitor Window
    Serial.print("Key pressed: ");
    Serial.println(key);
    if (key == 0x23) {
      if (currentDig.toInt() <= 24 && currentDig.toInt() >= 1) {
        // play msg in lcd
        wav.trackPlaySolo(currentDig.toInt());
        lclewr("Enviando");
        currentDig = "";
        updS = !updS;

        delay(500);
        return;
      } else if (currentDig == "") {
        wav.stopAllTracks();
        delay(1000);
      } else {
        //print error out of range in lcd
        lclewr("No e");
        currentDig = "";
        updS = !updS;

        delay(500);
        return;
      }
      
    } else if (key == 0x2A) {
    currentDig = "";
    // funcion que borre la espera de digito.
    return;
  } else {
    currentDig += String(key);
    // actualiza display con el nuevo currentDig
    return;
  }
  }
  //Serial.println(currentDig);
  if (currentDig == "") {
    lclewr("Ingrese la pista");
  } else {
    lcinpnum(currentDig);
  }*/



  //Parte 2 *******************************
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 0x23:
        
        break;
      case 0x2A:

        break;
      default:
        banco = String(key);
        lclewr("Banco: " + String(banco));
        delay(10);
        updS = !updS;
    }
    
  }

    if (!digitalRead(boton1)) {boton=1;}
    if (!digitalRead(boton2)) {boton=2;}
    if (!digitalRead(boton3)) {boton=3;}
    if (!digitalRead(boton4)) {boton=4;}
    if (!digitalRead(boton5)) {boton=5;}
    if (!digitalRead(boton6)) {boton=6;}
    if (!digitalRead(boton7)) {boton=7;}
    if (!digitalRead(boton8)) {boton=8;}
    if (!digitalRead(boton9)) {boton=9;}
    //switch para imprimir en consola el boton que se presiono
    if (boton && boton !=9 ) {
      int sonido = banco.toInt() * 8 + boton;
      wav.trackPlaySolo(sonido);
      delay(500);
      lcd.setCursor(0,1);
      lcd.print("            ");
      lcd.setCursor(0,1);
      lcd.print("Reprod: " + String(sonido));
      //return;
    }
    if (boton==9) {
      wav.stopAllTracks();
      lcd.setCursor(0,1);
      lcd.print("            ");
      lcd.setCursor(0,1);
      lcd.print("Detenido");
    }
    /* switch (boton) {
        case 1:
            int sonido = banco * 8 +boton;
            wav.trackPlaySolo(sonido);
            break;
        case 2:
            Serial.println("boton 2");
            break;
        case 3:
            Serial.println("boton 3");
            break;
        case 4:
            Serial.println("boton 4");
            break;
        case 5:
            Serial.println("boton 5");
            break;
        case 6:
            Serial.println("boton 6");
            break;
       case 7:
            Serial.println("boton 7");
            break;
        case 8:
            Serial.println("boton 8");
            break;
        case 9:
            Serial.println("boton 9");
            break;
        default:
            break;
    }*/
    if (boton != NULL) {
        boton = NULL;
    }
    
}

// Limpia y escribe un mensaje en el lcd
void lclewr(String msg) {
  if (!updS) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg);
    updS = !updS;
    updP = !updP;

  }
}

// imprime mensaje (usualmente numero), en la segunda linea
void lcinpnum(String num) {
  updS = false;
  if (!updP) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pista:");
    lcd.setCursor(0,1);
    lcd.print(num);
    updP = !updP;
  } else {
    lcd.setCursor(0,1);
    lcd.print(num);
  }
}



