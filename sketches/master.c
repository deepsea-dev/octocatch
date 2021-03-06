int MASTER_START_PIN = 3;
int TRIGGER_PIN = 13;
int ECHO_PIN = A0;

int missed = 0; // Number of marbles the player has failed to catch
int failCount = 3; // Number of marbles missed before game ends

int inProgress = false; // Game in progress

float lastMarbleDistance = 0; // Normal distance to the wall, used for comparison to detect marbles

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
  float distance = duration * 0.034 / 2;
  return distance;
}

void loop()
{
  if (lastMarbleDistance == 0) {
  	lastMarbleDistance = getDistance();  
  }
  
  float currentDistance = getDistance();
  if (currentDistance + 2 < lastMarbleDistance) {
    missed++;
  }

  if (missed == failCount) {
  	digitalWrite(MASTER_START_PIN, LOW); 
  }
  
  delay(200);
  
}