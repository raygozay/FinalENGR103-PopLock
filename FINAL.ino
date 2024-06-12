#include <Adafruit_CircuitPlayground.h>

volatile int point = 0;
volatile bool AB = false;
volatile bool BB = false;
volatile bool switchFlag = false;
bool slideswitch;
bool game = false;
bool gameOver = false;
bool gameW = false;
int endgame;
int store;
int randLED;
int mode = 0;
int stopwatch = 300;
int reduce = 3;
float midi[127];
int A_four = 440;

int song[25][2] = { // Game over song
    {70, 44},  
    {75, 44},  
    {70, 44},  
    {69, 44},  
    {74, 44},  
    {69, 44},  
    {68, 44},  
    {73, 44},  
    {68, 44},  
    {67, 44},
    {72, 44},  
    {67, 44},  
    {49, 44},
    {48, 44},  
    {47, 44},  
    {46, 44},  
    {45, 44},  
    {44, 44},  
    {43, 44},  
    {42, 44},  
    {41, 44},  
    {40, 44},  
    {39, 44},
    {38, 44},  
    {37, 380},  
  };

int song1[9][2] = { // Game won song
    {57, 64},  
    {55, 64},  
    {53, 64},  
    {55, 128},  
    {56, 128},  
    {58, 128},  
    {60, 64},  
    {58, 64},  
    {53, 200},  
};

void setup() {

  CircuitPlayground.begin();
  Serial.begin(9600);
  generateMIDI();
  attachInterrupt(4, A, FALLING);
  attachInterrupt(5, B, FALLING);
  attachInterrupt(7, S, CHANGE);
  randomSeed(analogRead(0));

}

void loop() {

  switch(mode) { // Here is where you choose difficulty and where you can decide up to how many points you can try to get
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

  while(game) { //Here is where the game starts once game is true
    spin();
    reset();
  }

  if (gameOver) { // Here is where the game ends once gameOver is true
    gameEndSong();
  while(gameOver) {
    gameEnd();
    reset();
    }
  }

  if (gameW) { // Here is where te game also ends but with victory when gameW is true.
    gameWonSong();
  while(gameW) {
    gameWon();
    reset();
    }
  }
}

void chooseDifficulty() { //This is where the game starts. Here you can choose your difficulty level and start the game.
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

void LED() { //Turns on a random LED 
  randLED = random(0, 10);
  CircuitPlayground.setPixelColor(randLED, 0, 255, 0);
  store = randLED; 
}

void readLED(int store) { // Reads and stores what value the random led is at.
 CircuitPlayground.setPixelColor(store, 0, 255, 0);
}

void ping() { // Sound that plays when you correctly time the button press
  CircuitPlayground.playTone(700, 100);
}

void spin() { // This is where most of the game is stored, plays the spinning LED, chooses the random LED decides what to turn true or false depending on conditions, prints score and difficulty level, reduces time.
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
      break;
      }
      if(point == endgame) {
      game = false;
      gameW = true;
      break;
      }
  }
}

void gameEndSong() { // This is the song that will play immediately when you lose the game along with a little animation.
    for(int p=0; p<25; ++p) {
    CircuitPlayground.playTone(midi[song[p][0]], song[p][1]);
    CircuitPlayground.setPixelColor(p %10, 255, 0, 0);
    delay(20);
    CircuitPlayground.clearPixels();
  }
}  

void gameEnd() { // This is the animation loop that will play after it plays the game over song.
 for(int p=0; p<10; ++p) {
    CircuitPlayground.setPixelColor(p, 255, 0, 0);
    delay(20);
    CircuitPlayground.clearPixels();
    Serial.println("Damn thats tough");
  }
}

void gameWonSong() { //This is a song that will play immediately when you reach the points difficulty along with a little animation
  for(int o=0; o<10; ++o) {
      if (o<9) {
        CircuitPlayground.playTone(midi[song1[o][0]], song1[o][1]);   
      }
  CircuitPlayground.setPixelColor(o, 0, 255, 0);
  delay(10);
  CircuitPlayground.clearPixels();
  }
} 

void gameWon() { //This is the animation loop that will play after the gameWonSong
    for(int o=0; o<10; ++o) {
    CircuitPlayground.setPixelColor(o, 0, 255, 0);
    delay(20);
    CircuitPlayground.clearPixels();
    Serial.println("Congrats now try the next hardest difficulty :)");
  }
} 

void reset() { //This is the switch function that allows you to reset the game to choosing the difficulty any time
    if (switchFlag == true && (game == true || gameOver == true || gameW == true)) {
    game = false;
    gameOver = false;
    gameW = false;
    point = 0;
    mode = 0;
    stopwatch = 300;
    CircuitPlayground.clearPixels();
    chooseDifficulty();
    switchFlag = false;
  }
}

void generateMIDI() //Generates the midi necessary for the songs
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
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
