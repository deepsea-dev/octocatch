#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(8, INPUT);
  
  
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  showStart();
  
  Serial.begin(9600);
}

void showStart() {
  lcd.setCursor(0, 0);
  lcd.print("OctoCatch       ");
  lcd.setCursor(0, 1);
  lcd.print("Start game?     ");
}

int startTime = 0;
int counting = LOW;
void loop() {


  int startCount = digitalRead(8);
  Serial.println(startCount);
  if (startCount == HIGH && counting == LOW) {
	counting = HIGH;
    
    startTime = millis();
    
    lcd.setCursor(0, 0);
    lcd.print("Current Score   ");

    lcd.setCursor(0, 1);
    
    lcd.print("                ");
  }
  else if (startCount == HIGH && counting == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(millis() - startTime);  
  }
  else if (startCount == LOW && counting == HIGH) {
  	// Player has failed, gameover
    lcd.setCursor(0, 0);
    lcd.print("Gameover - Score");
    counting = LOW;
    
    startTime = millis();
  } else if (millis() - startTime > 3000) {
   	showStart(); 
  }
  
  
  delay(100);
  
}
 