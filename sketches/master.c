int MASTER_START_PIN = 3;
int TRIGGER_PIN = 13;
int ECHO_PIN = A0;
int PULSE_DELAY = 100;

int missed = 0; // Number of marbles the player has failed to catch
int failCount = 3; // Number of marbles missed before game ends

int inProgress = false; // Game in progress

void setup() {
  pinMode(MASTER_START_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(MASTER_START_PIN, HIGH);
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
  //Serial.println("duration");
  //Serial.print(duration);
  float distance = duration * 0.034 / 2;
  //Serial.println(distance);
  //Serial.println(int(distance));
  return distance;
}

// The distance measured from the senor to the wall
// as a way of figuring out whena marble has passed
//Serial.println("distance to wall");
int lastMarbleDistance = 0;
//Serial.println(lastMarbleDistance);
void loop()
{
  if (lastMarbleDistance == 0) {
    lastMarbleDistance = getDistance();
  }
  
  int currentDistance = getDistance();
  Serial.println(currentDistance);
  if (currentDistance + 2 < lastMarbleDistance) {
   // a marble has passed
    missed++;
    Serial.println("a marble has been missed!");

  }

  if (missed == failCount) {
  	digitalWrite(MASTER_START_PIN, LOW); 
    Serial.println("game over");
  }
  
  delay(200);
  
}