/*
 * for wiring, see memory_game-wiring.txt
 *
 * LED and corresponding frequency
 *  red    -> 880  Hz
 *  green  -> 1108 HZ
 *  yellow -> 1318 Hz
*/

#define spkrPin     9
#define redLED      11
#define greenLED    12
#define yellowLED   13
#define PB1         1
#define PB2         2
#define PB3         3
#define unconnectedPin 5    // analog pin necessary for generating a random seed

#define seq_len     4       // length of a sequence
int sequence[seq_len];      // global array storing generated sequences
int user_sequence[seq_len]; // global array storing user's seqences

void setup() {
  pinMode(spkrPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(PB1, INPUT_PULLUP);   // pressed    -> pin LOW
  pinMode(PB2, INPUT_PULLUP);   // unpressed  -> pin HIGH
  pinMode(PB3, INPUT_PULLUP);
}

void loop() {
  // play a random sequence
  generateSequence();

  bool winner = false;
  while(!winner) {
    // play the generated sequence
    playSequence();
    
    // take in user input
    user_input();
  
    // compare sequence[] with user_sequence[]
    if(areArraysDiff(sequence, user_sequence, seq_len) == true) {
      // if arrays are different, play loser sound
      delay(250);
      int i = 0;
      while(i < 2) {
        playTone(880, redLED, 250);
        delay(250);
        i++;
      }
      winner = false;
      delay(1000);
    }
    else {
      // if arrays are the same, play winner sound
      delay(250);
      int i = 0;
      while(i < 2) {
        playTone(1318, yellowLED, 250);
        noTone(spkrPin);
        delay(250);
        i++;
      }
      winner = true;
      delay(2000);
    }
  }
}

void generateSequence() {
  // initialize sequence[] to -1
  int i = 0;
  while(i < seq_len) {
    sequence[i] = -1;
    i++;
  }

  randomSeed(analogRead(unconnectedPin));
  i = 0;
  while(i < seq_len) {
    // pick a random number between 1 and 3
    sequence[i] = random(1, 4);
    i++;
  }
}

void user_input() {
  // initialize user_sequence[] to -1
  int i = 0;
  while(i < seq_len) {
    user_sequence[i] = -1;
    i++;
  }
  
  int freq = 0;
  int LED = 0;

  i = 0;
  while(i < seq_len) {
    if(digitalRead(PB1) == LOW) {
      freq = 880;
      LED = redLED;
      user_sequence[i] = 1;
    }
    if(digitalRead(PB2) == LOW) {
      freq = 1108;
      LED = greenLED;
      user_sequence[i] = 2;
    }
    if(digitalRead(PB3) == LOW) {
      freq = 1318;
      LED = yellowLED;
      user_sequence[i] = 3;
    }
  
    if(freq != 0) {
      playTone(freq, LED, 500);
      freq = 0;
      LED = 0;
      i++;
    }
  }
}

void playSequence() {
  int i = 0;
  while(i < seq_len) {
    //play the tone
    if(sequence[i] == 1) { playTone(880,     redLED, 500); }
    if(sequence[i] == 2) { playTone(1108,  greenLED, 500); }
    if(sequence[i] == 3) { playTone(1318, yellowLED, 500); }
    i++;
  }
}

void playTone(const unsigned int freq, const unsigned int LED, const unsigned int duration) {
  tone(spkrPin, freq);
  digitalWrite(LED, HIGH);
  delay(duration);
  noTone(spkrPin);
  digitalWrite(LED, LOW);
}

// returns false if a[] and b[] are exactly the same
// returns true otherwise
bool areArraysDiff(int a[], int b[], int size) {
  int i = 0;
  while(i < size) {
    if(a[i] != b[i]) {
      return true;
    }
    i++;
  }
  return false;
}

