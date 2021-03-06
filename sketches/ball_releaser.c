int DELAY_LENGTH = 100;

void setup() {
  Serial.begin(9600);
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop() {

  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);

  delay(DELAY_LENGTH);
  
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  
  delay(DELAY_LENGTH);
}