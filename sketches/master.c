void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  
  delay(2000);
  	
}

void loop()
{
  digitalWrite(3, HIGH);
  Serial.println(3);
  
  delay(2000);
  
  digitalWrite(3, LOW);
  
  delay(4000);
}