// this should be a stepper motor
// do not try to build this irl without adjustments for this

int DELAY_LENGTH = 100;

void setup() {
  
  pinMode(A0, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);
  
}
int endTime = millis();
int direction = 0;
// -1 is left, 1 is right
int enabled = LOW;
void loop() {
  
  int masterStart = digitalRead(A0);
  Serial.println(masterStart);
  if (masterStart == HIGH && enabled == LOW) {
    enabled = HIGH;
    endTime = millis() + random(2000, 4000);
    direction = random(0, 2);
  }
  else if (masterStart == HIGH && enabled == HIGH) {
    switch (direction) {
      case 1: {
        digitalWrite(10, LOW);
        digitalWrite(9, HIGH);
        break;
      }
      case 0: {
        digitalWrite(10, HIGH);
        digitalWrite(9, LOW);
        break;
      }
    }
    
    if (millis() >= endTime) {
      // drop a marble
      digitalWrite(11, HIGH);
      delay(200); // todo: figure out time for marble to be released from dropper
      endTime = millis() + random(2000, 4000);
      direction = random(0, 2);
    }
  }
  else if (masterStart == LOW && enabled == HIGH) {
    enabled = LOW; 
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
  }
  
  delay(DELAY_LENGTH);
}