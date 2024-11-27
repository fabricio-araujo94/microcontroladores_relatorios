#include <Arduino.h>

String cardCode = "";

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ESP32 is ready. Pass Slide the card over the reader.");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()) {
    char incomingChar = Serial.read();

    if(incomingChar == "0x03") {
      Serial.print("Your card code is: ");
      Serial.println(cardCode);

      cardCode = "";
      break;
    } else {
      cardCode += incomingChar;
    }
  }

  delay(500);
}

// put function definitions here:
