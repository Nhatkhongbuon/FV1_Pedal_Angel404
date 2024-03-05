#include <Arduino.h>
#include <SPI.h>
#include <TFT.h>

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9
#define relayPin 7
#define ledPin 5
TFT TFTscreen = TFT(TFT_CS, TFT_DC, TFT_RST);

static int upButton = 2;
static int downButton = 3;
static int bypassButton = 4;
int counter = 0; // count variable
double timeMark = 0;
double debounceTime = 100;
double bypassdebounceTime = 300;

void display()
{
  switch (counter)
  {
  case 0: // Encoder Position 0
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("001", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Hall", 10, 55);
    TFTscreen.text("Shimmer", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Damping", 10, 110);
    TFTscreen.text("2: Feedback", 10, 125);
    TFTscreen.text("3: Decay", 10, 140);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 1: // Encoder Position 1
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("002", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Shimmer", 10, 55);
    TFTscreen.text("Reverb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Shimmer", 10, 110);
    TFTscreen.text("2: Reverb Level", 10, 125);
    TFTscreen.text("3: Reverb Time", 10, 140);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 2: // Encoder Position 2
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("003", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Dattorro", 10, 55);
    TFTscreen.text("Shimmer", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Shimmer Level", 10, 110);
    TFTscreen.text("2: Reverb Time", 10, 125);
    TFTscreen.text("3: Damping", 10, 140);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 3: // Encoder Position 3
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("004", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Rev", 10, 55);
    TFTscreen.text("Shimmer", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Time", 10, 110);
    TFTscreen.text("2: Treb", 10, 125);
    TFTscreen.text("3: Shimmer Level", 10, 140);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 4: // Encoder Position 4
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("005", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Up/Down", 10, 55);
    TFTscreen.text("Octave", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Mix", 10, 110);
    TFTscreen.text("2: Octave Up", 10, 125);
    TFTscreen.text("3: Octave Down", 10, 140);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 5: // Encoder Position 5
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("006", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Ionian", 10, 55);
    TFTscreen.text("404", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Volume", 10, 110);
    TFTscreen.text("2: Speed", 10, 125);
    TFTscreen.text("3: Number Of Notes", 10, 140);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 6: // Encoder Position 6
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("007", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Faux", 10, 55);
    TFTscreen.text("Phaser", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: LFO Speed/Width", 10, 110);
    TFTscreen.text("2: Delay Time", 10, 125);
    TFTscreen.text("3: Delay Level", 10, 140);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 7: // Encoder Position 7
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("008", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Faux", 10, 55);
    TFTscreen.text("Phaser 2", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: LFO Speed/Width", 10, 110);
    TFTscreen.text("2: Delay Time", 10, 125);
    TFTscreen.text("3: Delay Level", 10, 140);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 8: // Encoder Position 8
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("009", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Space", 10, 55);
    TFTscreen.text("Delay", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 10, 110);
    TFTscreen.text("2: Filter", 10, 125);
    TFTscreen.text("3: Feedback", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 9: // Encoder Position 9
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("010", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Glitch", 10, 55);
    TFTscreen.text("Delay", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Speed", 10, 110);
    TFTscreen.text("2: Time", 10, 125);
    TFTscreen.text("3: Random", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 10: // Encoder Position 10
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("011", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Star", 10, 55);
    TFTscreen.text("Filed", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 10, 110);
    TFTscreen.text("2: Feedback", 10, 125);
    TFTscreen.text("3: Phase", 10, 140);
    
    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 11: // Encoder Position 11
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("012", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Choir", 10, 55);
    TFTscreen.text("See", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Phase", 10, 110);
    TFTscreen.text("2: Width", 10, 125);
    TFTscreen.text("3: Tremolo", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 12: // Encoder Position 12
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("013", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Parallel", 10, 55);
    TFTscreen.text("404", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 10, 110);
    TFTscreen.text("2: Feedback", 10, 125);
    TFTscreen.text("3: Tremolo", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 13: // Encoder Position 13
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("014", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("S&H", 10, 55);
    TFTscreen.text("Filter", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 10, 110);
    TFTscreen.text("2: Feedback", 10, 125);
    TFTscreen.text("3: Modulation", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 14: // Encoder Position 14
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("015", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Kaleido", 10, 55);
    TFTscreen.text("Scope", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Up/Down", 10, 110);
    TFTscreen.text("2: Speed", 10, 125);
    TFTscreen.text("3: Feedback", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 15: // Encoder Position 15
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("016", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Digi", 10, 55);
    TFTscreen.text("Fuzz", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Sample Rate", 10, 110);
    TFTscreen.text("2: Bit Deepth", 10, 125);
    TFTscreen.text("3: Volume", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 16: // Encoder Position 16
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("017", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Abbey", 10, 55);
    TFTscreen.text("Verb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Level", 10, 110);
    TFTscreen.text("2: Size", 10, 125);
    TFTscreen.text("3: Damp", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 17: // Encoder Position 17
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("018", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Spring", 10, 55);
    TFTscreen.text("Verb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Level", 10, 110);
    TFTscreen.text("2: Rate", 10, 125);
    TFTscreen.text("3: Deepth", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 18: // Encoder Position 18
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("019", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Room", 10, 55);
    TFTscreen.text("Reverb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Damp", 10, 110);
    TFTscreen.text("2: Mix", 10, 125);
    TFTscreen.text("3: Decay", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 19: // Encoder Position 19
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("020", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Plate", 10, 55);
    TFTscreen.text("Reverb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Level", 10, 110);
    TFTscreen.text("2: Decay", 10, 125);
    TFTscreen.text("3: Resonance", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 20: // Encoder Position 20
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("021", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Wah", 10, 55);
    TFTscreen.text("Reverb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Level", 10, 110);
    TFTscreen.text("2: Sensitivity", 10, 125);
    TFTscreen.text("3: Wah Level", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 21: // Encoder Position 21
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("022", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Vibrato", 10, 55);
    TFTscreen.text("Reverb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Level", 10, 110);
    TFTscreen.text("2: Speed", 10, 125);
    TFTscreen.text("3: Vibrato Level", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 22: // Encoder Position 22
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("023", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Phaser", 10, 55);
    TFTscreen.text("Reverb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Level", 10, 110);
    TFTscreen.text("2: Speed", 10, 125);
    TFTscreen.text("3: Phaser Level", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 23: // Encoder Position 23
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(0, 0, 120, 95);
    TFTscreen.rect(0, 110, 120, 50);
    TFTscreen.setTextSize(5);
    TFTscreen.stroke(255, 255, 55);
    TFTscreen.text("024", 10, 10);
    TFTscreen.line(10, 100, 120, 100);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Flanger", 10, 55);
    TFTscreen.text("Reverb", 10, 75);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Level", 10, 110);
    TFTscreen.text("2: Speed", 10, 125);
    TFTscreen.text("3: Flanger Level", 10, 140);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;
  }
}

void increase()
{
  if (millis() - timeMark > debounceTime)
  {
    counter++;
    if (counter > 23)
      counter = 0;
    display();
    timeMark = millis();
  }
}

void decrease()
{
  if (millis() - timeMark > debounceTime)
  {
    counter--;
    if (counter < 0)
      counter = 23;
    display();
    timeMark = millis();
  }
}

void setup()
{
  // for button system
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(bypassButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  // for EEPROM system
  pinMode(0, OUTPUT);  // RX s0
  pinMode(1, OUTPUT);  // TX s1
  pinMode(6, OUTPUT);  // pin6 s2
  pinMode(14, OUTPUT); // pin14 eeprom1
  pinMode(15, OUTPUT); // pin16 eeprom2
  pinMode(16, OUTPUT); // pin16 eeprom3

  attachInterrupt(digitalPinToInterrupt(upButton), increase, FALLING);
  attachInterrupt(digitalPinToInterrupt(downButton), decrease, FALLING);

  // display information
  // display information
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.setRotation(2);

  TFTscreen.setTextSize(5);
  TFTscreen.stroke(255, 255, 55);
  TFTscreen.text("001", 10, 10);
  TFTscreen.line(10, 100, 120, 100);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Hall", 10, 55);
  TFTscreen.text("Shimmer", 10, 75);
  TFTscreen.setTextSize(1);
  TFTscreen.text("1: Damping", 10, 110);
  TFTscreen.text("2: Feedback", 10, 125);
  TFTscreen.text("3: Decay", 10, 140);

  // select eeprom 1
  digitalWrite(14, LOW);  // eeprom 1
  digitalWrite(15, HIGH); // eeprom 2
  digitalWrite(16, HIGH); // eeprom 3
  digitalWrite(0, LOW);   // s0
  digitalWrite(0, LOW);   // s1
  digitalWrite(0, LOW);   // s2
}

void loop()
{
  if (digitalRead(bypassButton) == LOW)
  {
    if ((millis() - timeMark > bypassdebounceTime) && digitalRead(bypassButton) == LOW)
    {
      digitalWrite(ledPin, !digitalRead(ledPin));
      digitalWrite(relayPin, !digitalRead(relayPin));
      timeMark = millis();
    }
  }
}