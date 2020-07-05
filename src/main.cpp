#include <Arduino.h>

void setup() {
    // put your setup code here, to run once:
    pinMode(13, OUTPUT);
    pinMode(12, INPUT_PULLUP);
    pinMode(11, OUTPUT);
}

unsigned long lastMillis = millis();

void loop() {
    // put your main code here, to run repeatedly:
    if (millis() > lastMillis + 100) {
        digitalWrite(13, !digitalRead(13));
        lastMillis = millis();
    }
    digitalWrite(11, !digitalRead(12));
}