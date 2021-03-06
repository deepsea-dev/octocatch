#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(8, INPUT);
  
  
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Current Score");
  
  Serial.begin(9600);
}

void loop() {

  lcd.setCursor(0, 1);

  int startCount = digitalRead(8);
  Serial.println(startCount);
  if (startCount == HIGH) {
  	lcd.print(millis());  
  }
  
  delay(100);
  
}
 