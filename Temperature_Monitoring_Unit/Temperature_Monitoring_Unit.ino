// Include the LiquidCrystal library code:
#include <LiquidCrystal.h>

// Define the pins for the LCD:
const int rs = 4, en = 3, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Constants for sensor and actuators:
const int sensorPin = A0;    // Pin that the sensor is attached to
const int led_red = 9;       // Pin for red LED
const int led_green = 10;    // Pin for green LED
const int buzzer = 11;       // Pin for buzzer

// Temperature thresholds:
int maxvalue = 40;           // Maximum temperature threshold
int minvalue = 10;           // Minimum temperature threshold

void setup() {
  // Initialize pins:
  pinMode(sensorPin, INPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a static message to the LCD:
  lcd.print("Temperature ");
  lcd.print((char)223);  // Print degree symbol
  lcd.print("C");
  digitalWrite(buzzer, HIGH); // Activate the buzzer initially
}

void loop() {
  // Initialize serial communication:
  Serial.begin(9600);

  // Read temperature from the sensor:
  double thermo = 0.568155 * (analogRead(sensorPin) - 20);
  delay(100); // Wait for 100 milliseconds

  // Print the temperature to the serial monitor:
  Serial.print(thermo);
  Serial.print("\n");

  delay(500); // Wait for 500 milliseconds

  // Set the cursor to column 0, line 1 on the LCD:
  lcd.setCursor(0, 1);
  // Print the live temperature:
  lcd.print(thermo);

  // Check temperature thresholds and control LEDs and buzzer accordingly:
  if (thermo < minvalue) {
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, HIGH);
    digitalWrite(buzzer, HIGH);
  } else if (thermo > maxvalue) {
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, HIGH);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(led_green, HIGH);
    digitalWrite(led_red, LOW);
    digitalWrite(buzzer, LOW);
  }

  // Delay a bit before the next loop iteration:
  delay(100);
}

