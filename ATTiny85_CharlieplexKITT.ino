

/*
  ____ _                _ _            _           ____   ___  _  _____ _____ _____ 
 / ___| |__   __ _ _ __| (_) ___ _ __ | | _____  _|___ \ / _ \| |/ /_ _|_   _|_   _|
| |   | '_ \ / _` | '__| | |/ _ \ '_ \| |/ _ \ \/ / __) | | | | ' / | |  | |   | |  
| |___| | | | (_| | |  | | |  __/ |_) | |  __/>  < / __/| |_| | . \ | |  | |   | |  
 \____|_| |_|\__,_|_|  |_|_|\___| .__/|_|\___/_/\_\_____|\___/|_|\_\___| |_|   |_|  
                                |_|                                                 
 Charlieplexing 20 LEDs using 5 ATTiny85 pins with fading by
 varying the duty cycle of each LED to create a Larson scanner
 (KITT) effect.
 
 Adapted from Charlieplex20snow sketch.
 
 ATTiny85 connections
 Leg  Function
 1    Reset, no connection
 2    D3 GREEN
 3    D4 ORANGE
 4    GND
 5    D0 WHITE
 6    D1 BLUE
 7    D2 YELLOW
 8    +5V
 
 Tested on ATTiny85 running at 8MHz.
 */

// each block of 4 LEDs in the array is groupled by a common anode (+, long leg)
// for simplicity of wiring on breadboard, using a colour code
#define GREEN 0
#define ORANGE 1
#define WHITE 2
#define BLUE 3
#define YELLOW 4

// pin definitions {GREEN, ORANGE, WHITE, BLUE, YELLOW}
const int charliePin[5] = {
  3, 4, 0, 1, 2};

// Charlieplexed LED definitions (current flowing from-to pairs)
const int LED[20][2] = {
  {ORANGE, GREEN},                            // 0 (GREEN GROUP)
  {WHITE, GREEN},                             // 1
  {BLUE, GREEN},                              // 2
  {YELLOW, GREEN},                            // 3
  {GREEN, ORANGE},                            // 4 (ORANGE GROUP)
  {WHITE, ORANGE},                            // 5
  {BLUE, ORANGE},                             // 6
  {YELLOW, ORANGE},                           // 7
  {GREEN, WHITE},                             // 8 (WHITE GROUP)
  {ORANGE, WHITE},                            // 9
  {BLUE, WHITE},                              // 10
  {YELLOW, WHITE},                            // 11
  {GREEN, BLUE},                              // 12 (BLUE GROUP)
  {ORANGE, BLUE},                             // 13
  {WHITE, BLUE},                              // 14
  {YELLOW, BLUE},                             // 15
  {GREEN, YELLOW},                            // 16 (YELLOW GROUP)
  {ORANGE, YELLOW},                           // 17
  {WHITE, YELLOW},                            // 18
  {BLUE, YELLOW}                              // 19
};

// other
int current = 0;                              // LED in array with current focus
int previous = 0;                             // previous LED that was lit
int iterator = 1;                             // direction of travel

void setup() {
}

void loop() {
  unsigned long loopCount = 0;                          // used to determine duty cycle of each LED
  unsigned long timeNow = millis();                     //
  while(millis()- timeNow < 40) {                       // ms each LED is held for in animation
    loopCount++;
    // the focus LED gets full duty cycle.  When it gets to the end, hold it at the end until the tail collapses
    if (current > 19 && iterator == 1) charlieON(19); 
    else if (current < 1 && iterator == -1) charlieON(0);
    else charlieON(current);
    // each member of tail has reduced duty cycle
    if(!(loopCount % 3)) if(current-1 >=0 && current-1 < 19) charlieON(current-1);
    if(!(loopCount % 9)) if(current-2 >=0 && current-2 < 19) charlieON(current-2);
    if(!(loopCount % 12)) if(current-3 >=0 && current-3 < 19) charlieON(current-3);    
    if(!(loopCount % 3)) if(current+1 >=0 && current+1 < 19) charlieON(current+1);
    if(!(loopCount % 9)) if(current+2 >=0 && current+2 < 19) charlieON(current+2);
    if(!(loopCount % 12)) if(current+3 >=0 && current+3 < 19) charlieON(current+3);
  }

  current += iterator;
  if(current==23) {                                          // return
    current = 19;
    iterator = -1;                                           // direction change
    delay(40);
  } else if(current == -4) {
    current = 0;
    iterator = 1;
    delay(40);
  }
}

// --------------------------------------------------------------------------------
// turns on LED #thisLED.  Turns off all LEDs if the value passed is out of range
//
void charlieON(int thisLED) {
  // turn off previous (reduces overhead, only switch 2 pins rather than 5)
  digitalWrite(charliePin[LED[previous][1]], LOW);   // ensure internal pull-ups aren't engaged on INPUT mode
  pinMode(charliePin[LED[previous][0]], INPUT);
  pinMode(charliePin[LED[previous][1]], INPUT);

  // turn on the one that's in focus
  if(thisLED >= 0 && thisLED <= 19) {
    pinMode(charliePin[LED[thisLED][0]], OUTPUT);
    pinMode(charliePin[LED[thisLED][1]], OUTPUT);
    digitalWrite(charliePin[LED[thisLED][0]], LOW);
    digitalWrite(charliePin[LED[thisLED][1]], HIGH);
  }
  previous = thisLED;
}

// --------------------------------------------------------------------------------
// turns off LED #thisLED.  
//
void charlieOFF(int thisLED) {
  digitalWrite(charliePin[LED[thisLED][1]], LOW);   // ensure internal pull-ups aren't engaged on INPUT mode
  pinMode(charliePin[LED[thisLED][0]], INPUT);
  pinMode(charliePin[LED[thisLED][1]], INPUT);
}




