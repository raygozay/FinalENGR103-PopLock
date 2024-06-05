#include <Adafruit_CircuitPlayground.h>

volatile int point = 0;
volatile bool AB = false;
volatile bool BB = false;
volatile bool switchFlag = false;
bool game = false;
bool gameOver = false;
bool gameW = false;
bool slideswitch;
int endgame;
int store;
int randLED;
int mode = 0;
int stopwatch = 300;
int reduce = 3;
int time; 

void setup() {

  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt(4, A, FALLING);
  attachInterrupt(5, B, FALLING);
  attachInterrupt(7, S, CHANGE);
  randomSeed(analogRead(0));

}

void loop() {

  switch(mode) {
    case 0:
    chooseDifficulty();
    break;

    case 1:
    chooseDifficulty();
    endgame = 50;
    break;

    case 2:
    chooseDifficulty();
    endgame = 75;
    break;

    case 3:
    chooseDifficulty();
    endgame = 100;
    break;
      }

  while(game) {
    spin();
  }
  while(gameOver) {
    gameEnd();
  }
  while(gameW) {
    gameWon();
  }
}

void chooseDifficulty() {
  if (AB == true) {
    delay(5);
    mode++;
    if (mode >= 4) {
      mode = 1;
    }
    Serial.print("Difficulty: ");
    Serial.println(mode);
      CircuitPlayground.clearPixels();
      for (int i = 0; i < mode; i++) {
      CircuitPlayground.setPixelColor(i, 255, 255, 255);
        }
    AB = false;
  }
  if (BB == true) {
    delay(5);
    game = true;
    BB = false;
  }
}

void LED() {
    randLED = random(0, 10);
    CircuitPlayground.setPixelColor(randLED, 0, 255, 0);
    store = randLED; 
}

void readLED(int store) {
 CircuitPlayground.setPixelColor(store, 0, 255, 0);
}

void ping() {
  CircuitPlayground.playTone(700, 100);
}

void spin() {
  for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
    delay(stopwatch);
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
    delay(1);
    if((i == store) && (BB == true)) {
      LED();
      ping();
      point++;
      stopwatch = stopwatch - reduce;
      Serial.print("Score: ");
      Serial.println(point);
      BB = false;
    } else {
        readLED(store);
    }
      if((i != store) && (BB == true)) {
      game = false;
      gameOver = true;
      BB = false;
      }
      if(point == endgame) {
      game = false;
      gameW = true;
      }
  }
}

void gameEnd() {
    for(int p=0; p<10; ++p) {
    CircuitPlayground.setPixelColor(p, 255, 0, 0);
    delay(20);
    CircuitPlayground.clearPixels();
  }
}  

void gameWon() {
    for(int o=0; o<10; ++o) {
    CircuitPlayground.setPixelColor(o, 0, 255, 0);
    delay(20);
    CircuitPlayground.clearPixels();
  }
} 

void A() {
  AB = true;
}

void B() {
  BB = true;
}

void S() {
  switchFlag = true;
}
