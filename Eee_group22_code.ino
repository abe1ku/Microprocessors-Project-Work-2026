// PIR Motion Security System
// Components: PIR sensor, LED, Piezo buzzer
// Group 22

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int PIR_PIN   =  2;   // PIR sensor output
const int LED_PIN   =  13;  // Status LED
const int BUZZ_PIN  =  8;   // Piezo buzzer

const int ALERT_DURATION =  5000;  // Alert hold time in ms
const int FLASH_DELAY    =  150;   // LED flash interval in ms
const int BUZZ_ON        =  100;   // Buzzer pulse on-time in ms
const int BUZZ_OFF       =  200;   // Buzzer pulse off-time in m

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(PIR_PIN,  INPUT);
  pinMode(LED_PIN,  OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  lcd.init();        // Add this — initialises the I2C backpack
  lcd.backlight();   // Add this — turns the backlight on
  lcd.begin(16, 2); // Set up the number of columns and rows on the LCD.
  // Print a message to the LCD.
  lcd.print("System ready.");
  delay(2000);
  lcd.clear();
  lcd.print("Monitoring...");
  delay(2000);  // Allow PIR sensor to stabilise on power-up
 
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALERT:");
    lcd.setCursor(0, 1);
    lcd.print("Motion detected!");
    triggerAlert(ALERT_DURATION);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alert ended.");
    lcd.setCursor(0, 1);
    lcd.print("Resuming scan...");
    delay(2000); // Wait for 1000 millisecond(s)
    lcd.clear();
  lcd.print("Monitoring...");
  }
}

void triggerAlert(int duration) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    // Flash LED
    digitalWrite(LED_PIN, HIGH);
    delay(FLASH_DELAY);
    digitalWrite(LED_PIN, LOW);
    delay(FLASH_DELAY);

    // Pulse buzzer
    digitalWrite(BUZZ_PIN, HIGH);
    delay(BUZZ_ON);
    digitalWrite(BUZZ_PIN, LOW);
    delay(BUZZ_OFF);
  }
  
  // Reset outputs
  digitalWrite(LED_PIN,  LOW);
  digitalWrite(BUZZ_PIN, LOW);
}