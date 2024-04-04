const int ledPins[] = {10, 11, 12, 13}; // Array to hold the LED pin numbers
const int ldrPin = A0; // LDR module connected to analog pin A0
const int irSensorPin = 2; // IR sensor connected to digital pin 2
const int irSensorPin1 = 3;
const int glowDuration = 5000;
void setup() {
  // Set LED pins as output pins
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // Set IR sensor pin as input
  pinMode(irSensorPin, INPUT);
}

void loop() {
  int ldrValue = analogRead(ldrPin); // Read the LDR value
  int check =0;
  // Check if it's nighttime and object is detected by IR sensor
  if (ldrValue > 500 && digitalRead(irSensorPin) == LOW) { // Adjust threshold based on your environment
    // Turn on all LEDs
    check = 1;
     for (int i = 0; i < 2; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    
  }

  if(check==1){
     for (int i = 0; i < 2; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  }

  else if (ldrValue > 500 && digitalRead(irSensorPin1) == LOW) { // Adjust threshold based on your environment
    // Turn on all LEDs
    check =0;
    for (int i = 2; i < 4; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  }

  else {
    // If it's not nighttime or object is not detected, turn off all LEDs
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
  
  delay(500); // Delay to avoid rapid flickering
}


// void checkAndSendLEDStatus() {
//   // Check LED status using LDR sensors
//   for (int i = 0; i < 4; i++) {
//     // Read LDR sensor value
//     int ldrValue = analogRead(ldrPins[i]);
//     // If LDR value indicates darkness (below threshold), send LED status to ESP32
//     if (ldrValue < ldrThreshold) {
//       // Send LED status (1 for on, 0 for off) via serial communication to ESP32
//       Serial.print(i); // Sending LED index
//       Serial.println(digitalRead(ledPins[i])); // Sending LED status
//     }
//   }
// }


