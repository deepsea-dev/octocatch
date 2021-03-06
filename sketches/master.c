#include <Adafruit_NeoPixel.h>

int MASTER_START_PIN = 3;
int TRIGGER_PIN = 13;
int ECHO_PIN = A0;
int START_BUTTON_PIN = A1;
int PEIZO_PIN = 12;
int NEOPIXEL_PIN = 2;

int missed = 0; // Number of marbles the player has failed to catch
int failCount = 3; // Number of marbles missed before game ends

int inProgress = false; // Game in progress

float lastMarbleDistance = 0; // Normal distance to the wall, used for comparison to detect marbles

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
uint32_t red = strip.Color(255, 0, 0);

void setup() {
  pinMode(MASTER_START_PIN, OUTPUT);
  pinMode(START_BUTTON_PIN, INPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(PEIZO_PIN, OUTPUT);
  Serial.begin(9600);
  
  digitalWrite(MASTER_START_PIN, LOW);
}

float getDistance() {
  // Clear the trigger pin
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  // Read the duraton of the sound wave
  int duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void flashColor(uint32_t c, int n) {
  for (int i = 0; i < n; i++) {
    strip.fill(c, 0, 20);
    strip.show();
    delay(100);
    strip.fill(0, 0, 20);
    strip.show(); 
  }

}

void loop()
{
  if (lastMarbleDistance == 0) {
  	lastMarbleDistance = getDistance();  
  }
  
  if (!inProgress && digitalRead(START_BUTTON_PIN) == LOW) {
   inProgress = true; 
   digitalWrite(MASTER_START_PIN, HIGH);
  }
  
  float currentDistance = getDistance();
  if (currentDistance + 2 < lastMarbleDistance && inProgress) {
    missed++;
    digitalWrite(PEIZO_PIN, HIGH);
    flashColor(red, 1);
    delay(100);
    digitalWrite(PEIZO_PIN, LOW);
  }

  if (missed == failCount && inProgress) {
  	digitalWrite(MASTER_START_PIN, LOW);
    inProgress = false;
    digitalWrite(PEIZO_PIN, HIGH);
    delay(100);
    digitalWrite(PEIZO_PIN, LOW);

    flashColor(red, 4);
   
    missed = 0;
  }
  
  delay(200);
  
}