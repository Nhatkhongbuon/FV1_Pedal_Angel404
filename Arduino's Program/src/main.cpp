#include <Arduino.h>
#include <SPI.h>
#include <TFT.h>

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
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
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.rect(25, 80, 90, 40);

    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("1", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Shimmer", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Dwell", 12, 85);
    TFTscreen.text("2: Pitch", 12, 95);
    TFTscreen.text("3: Mix", 12, 105);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 1: // Encoder Position 1
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("2", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Mod Reverb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Dwell", 12, 85);
    TFTscreen.text("2: Depth", 12, 95);
    TFTscreen.text("3: Rate", 12, 105);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 2: // Encoder Position 2
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("3", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Mod Delay", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 12, 85);
    TFTscreen.text("2: Feedback", 12, 95);
    TFTscreen.text("3: Modulation", 12, 105);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 3: // Encoder Position 3
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("4", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Pitch Delay", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 12, 85);
    TFTscreen.text("2: Pitch", 12, 95);
    TFTscreen.text("3: Feedback", 12, 105);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 4: // Encoder Position 4
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("5", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Bit Crusher", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Crush", 12, 85);
    TFTscreen.text("2: Filter", 12, 95);
    TFTscreen.text("3: Detune", 12, 105);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 5: // Encoder Position 5
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("6", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Dual Pitch", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Pitch 1", 12, 85);
    TFTscreen.text("2: Mix", 12, 95);
    TFTscreen.text("3: Pitch 2", 12, 105);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 6: // Encoder Position 6
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("7", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Tremolo", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Rate", 12, 85);
    TFTscreen.text("2: Depth", 12, 95);
    TFTscreen.text("3: Spectrum", 12, 105);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 7: // Encoder Position 7
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("8", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Daydream", 10, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 12, 85);
    TFTscreen.text("2: Feedback", 12, 95);
    TFTscreen.text("3: Filter", 12, 105);

    digitalWrite(14, LOW);  // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 8: // Encoder Position 8
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("9", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Space Delay", 10, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 12, 85);
    TFTscreen.text("2: Filter", 12, 95);
    TFTscreen.text("3: Feedback", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 9: // Encoder Position 9
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("10", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Glitch Delay", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Speed", 12, 85);
    TFTscreen.text("2: Time", 12, 95);
    TFTscreen.text("3: Random", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 10: // Encoder Position 10
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("11", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Starfield", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 12, 85);
    TFTscreen.text("2: Feedback", 12, 95);
    TFTscreen.text("3: Phase", 12, 105);
    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 11: // Encoder Position 11
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("12", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Choirsaw", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Phase", 12, 85);
    TFTscreen.text("2: Width", 12, 95);
    TFTscreen.text("3: Tremolo", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 12: // Encoder Position 12
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("13", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Parallax", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 12, 85);
    TFTscreen.text("2: Feedback", 12, 95);
    TFTscreen.text("3: Tremolo", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 13: // Encoder Position 13
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("14", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("S&H Filter", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Time", 12, 85);
    TFTscreen.text("2: Feedback", 12, 95);
    TFTscreen.text("3: Modulation", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 14: // Encoder Position 14
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("15", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Kaleidoscope", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Up/Down", 12, 85);
    TFTscreen.text("2: Speed", 12, 95);
    TFTscreen.text("3: Feedback", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 15: // Encoder Position 15
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("16", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Digifuzzer", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Sample Rate", 12, 85);
    TFTscreen.text("2: Bit Depth", 12, 95);
    TFTscreen.text("3: Volume", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, LOW);  // eprom2
    digitalWrite(16, HIGH); // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 16: // Encoder Position 16
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("17", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Abbey Verb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Level", 12, 85);
    TFTscreen.text("2: Size", 12, 95);
    TFTscreen.text("3: Damp", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 17: // Encoder Position 17
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("18", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Spring Verb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Level", 12, 85);
    TFTscreen.text("2: Rate", 12, 95);
    TFTscreen.text("3: Depth", 12, 105);
    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 18: // Encoder Position 18
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("19", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Room Reverb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Damp", 12, 85);
    TFTscreen.text("2: Mix", 12, 95);
    TFTscreen.text("3: Decay", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 19: // Encoder Position 19
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("20", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Plate Verb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Level", 12, 85);
    TFTscreen.text("2: Decay", 12, 95);
    TFTscreen.text("3: Resonance", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, LOW);   // s2
    break;

  case 20: // Encoder Position 20
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("21", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Wah Reverb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Level", 12, 85);
    TFTscreen.text("2: Sensitivity", 12, 95);
    TFTscreen.text("3: Wah Level", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 21: // Encoder Position 21
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("22", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Vibrato Verb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Level", 12, 85);
    TFTscreen.text("2: Speed", 12, 95);
    TFTscreen.text("3: Vibrato Level", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, HIGH);  // s0
    digitalWrite(1, LOW);   // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 22: // Encoder Position 22
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("23", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Phaser Verb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Level", 12, 85);
    TFTscreen.text("2: Speed", 12, 95);
    TFTscreen.text("3: Phaser Level", 12, 105);

    digitalWrite(14, HIGH); // eprom1
    digitalWrite(15, HIGH); // eprom2
    digitalWrite(16, LOW);  // eprom3
    digitalWrite(0, LOW);   // s0
    digitalWrite(1, HIGH);  // s1
    digitalWrite(6, HIGH);  // s2
    break;

  case 23: // Encoder Position 23
    TFTscreen.setTextSize(1);
    TFTscreen.fill(0, 0, 0);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(138, 0, 15, 15);
    TFTscreen.rect(25, 80, 90, 40);
    TFTscreen.rect(0, 48, 160, 20);
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.text("24", 140, 5);
    TFTscreen.setTextSize(2);
    TFTscreen.text("Flanger Verb", 12, 50);
    TFTscreen.setTextSize(1);
    TFTscreen.text("1: Reverb Level", 12, 85);
    TFTscreen.text("2: Speed", 12, 95);
    TFTscreen.text("3: Flanger Level", 12, 105);

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
  if(millis() - timeMark > debounceTime)
  {
    counter++;
    if(counter > 23) counter = 0;
    display();
    timeMark = millis();
  }
}

void decrease()
{
  if(millis() - timeMark > debounceTime)
  {
    counter--;
    if(counter < 0) counter = 23;
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
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.setRotation(1);
  TFTscreen.stroke(255, 55, 255);
  TFTscreen.line(10, 70, 150, 70);
  TFTscreen.stroke(255, 255, 55);
  TFTscreen.line(90, 16, 150, 16);
  TFTscreen.setTextSize(1);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text("Program", 94, 5);
  TFTscreen.text("1", 140, 5);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Shimmer", 12, 50);
  TFTscreen.setTextSize(1);
  TFTscreen.text("1: Dwell", 12, 85);
  TFTscreen.text("2: Pitch", 12, 95);
  TFTscreen.text("3: Mix", 12, 105);

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
  if(digitalRead(bypassButton) == LOW) 
  {
    if((millis() - timeMark > bypassdebounceTime) && digitalRead(bypassButton) == LOW)
    {
      digitalWrite(ledPin, !digitalRead(ledPin));
      digitalWrite(relayPin, !digitalRead(relayPin));
      timeMark = millis();
    }
  }
}