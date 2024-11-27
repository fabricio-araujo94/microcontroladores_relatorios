#include <Arduino.h>

#define LED 25
#define DELAY 3000
#define THRESHOLD 40 // the smaller it is, the more sensitive it is.

RTC_DATA_ATTR int bootCount = 0;
touch_pad_t touchPin;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  bootCount++;
  Serial.println("Boot number: " + String(bootCount));
  delay(1000);

  touchPin = esp_sleep_get_touchpad_wakeup_status(); 

  if(touchPin == 3) { // this was the pin used (15)
    Serial.println("Touch detected in GPIO 15");
    
    digitalWrite(LED, HIGH);
    delay(DELAY);
  } else {
    Serial.println("Wake up not by touch.");
  }

  touchSleepWakeUpEnable(T3, THRESHOLD); // enable pin 15 for wake up

  Serial.println("Prepare for sleep!");

  Serial.flush(); // clean serial port

  esp_deep_sleep_start(); // take a nap
}

void loop() {
  // put your main code here, to run repeatedly:
  // it wasn't necessary this time
}

// put function definitions here:
