/*

1 normal mode
2 youtube mode
3 discord mode
4 notification mode
0 disable

# turn off led
* mute alarm


*/



// Membránová klávesnice 4x4

// připojení knihovny
#include <Keypad.h>

#define pinR 9
#define pinG 10
#define pinB 11


bool led = true;
bool sound = true;
bool disabled = false;

int color[3] = {0, 0, 255};

// vytvoření proměnných údávajících
// počet řádků a sloupců klávesnice
const byte radky = 4;
const byte sloupce = 4;
// vytvoření pole s rozmístěním kláves
char keys[radky][sloupce] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// nastavení čísel pinů pro spojení s klávesnicí
byte pinyRadku[radky] = {12, 8, 7, 6};
byte pinySloupcu[sloupce] = {5, 4, 3, 2};

// vytvoření instance klavesnice z knihovny Keypad
Keypad klavesnice = Keypad( makeKeymap(keys), pinyRadku, pinySloupcu, radky, sloupce); 

void setup() {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);

  setColor(); // blue
}
  
void loop() {
  // načtení hodnoty stisknuté klávesy do proměnné
  char klavesa = klavesnice.getKey();
  // kontrola obsahu proměnné se stisknutou klávesou
  // pokud bylo cokoli stisknuto, vytiskneme klávesu
  // po Sériové lince
  if (klavesa){
    //Serial.print("Stisknuta klavesa: ");
    Serial.println(klavesa);

    if (klavesa == '1') {
      Serial.println(1);
      color[0] = 0;
      color[1] = 0;
      color[2] = 255;

      setColor(); //blue

      disabled = false;
    }

    else if (klavesa == '2') {
      color[0] = 0;
      color[1] = 255;
      color[2] = 0;

      setColor(); //green

      disabled = false;
    }

    else if (klavesa == '3') {
      color[0] = 255;
      color[1] = 0;
      color[2] = 247;

      setColor(); //magenta

      disabled = false;
    }

    else if (klavesa == '4') {
      color[0] = 255;
      color[1] = 150;
      color[2] = 0;

      setColor(); //yellow

      disabled = false;
    }

    else if (klavesa == '0') {
      color[0] = 255;
      color[1] = 0;
      color[2] = 0;

      setColor(); //red

      disabled = true;
    }

    else if (klavesa == '#') {
      led = !led;
      
      setColor(); //last color
    }

    else if (klavesa == '*') {
      sound = !sound;

      if (sound) {
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
        delay(100);
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
      }
    }
  }


  //Serial.println(analogRead(A0));

  

  if (analogRead(A0) < 240) {  // closed
    //Serial.println('');  
  }

  
  else {  // opened
    if (sound && led && !disabled) {  // blink and beep
      Serial.println('o');
      
      digitalWrite(13, HIGH);
      analogWrite(pinR, 255);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
  
      delay(500);
  
  
      digitalWrite(13, LOW);
      analogWrite(pinR, 0);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
  
      delay(500);
  
      digitalWrite(13, HIGH);
      analogWrite(pinR, 255);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
  
      delay(500);
  
      digitalWrite(13, LOW);
      analogWrite(pinR, 0);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
    }


    else if (sound && !disabled) {  // beep
      Serial.println('o');
      
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
    }

    else if (led && !disabled) { // blink
      Serial.println('o');
      
      analogWrite(pinR, 255);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
  
      delay(500);
  
  
      analogWrite(pinR, 0);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
  
      delay(500);
  
      analogWrite(pinR, 255);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
  
      delay(500);
  
      analogWrite(pinR, 0);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
    }
  }
  setColor(); // set previous color
  
}

void setColor(){
  if (led == true) {
    analogWrite(pinR, color[0]);
    analogWrite(pinG, color[1]);
    analogWrite(pinB, color[2]);
  }

  else {
    analogWrite(pinR, 0);
    analogWrite(pinG, 0);
    analogWrite(pinB, 0);
  }
}
