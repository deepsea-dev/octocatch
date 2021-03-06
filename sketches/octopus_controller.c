int sensorValue = 0;
int DEAD_ZONE = 4;
int MIDPOINT = 512;
int DELAY_LENGTH = 100;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  // Sensor measures from 0 to 1023
  sensorValue = analogRead(A0);
  
  if (sensorValue > MIDPOINT + DEAD_ZONE) {
  	digitalWrite(10, LOW);
    analogWrite(9, (sensorValue - MIDPOINT) / 180);
  }
  else if (sensorValue < MIDPOINT - DEAD_ZONE) {
    analogWrite(10, (MIDPOINT - sensorValue) / 180);
    digitalWrite(9, LOW);
  }
  else {
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
  }
  Serial.println(sensorValue);
  delay(DELAY_LENGTH);
}