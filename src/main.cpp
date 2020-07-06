#include "morse.h"
#include <Arduino.h>

class MainClass {
private:
    Morse morse;
    unsigned long lastMillis;

public:
    MainClass() : lastMillis(millis()){};
    ~MainClass();

    // implement arduino functionality
    void setup() {
        pinMode(13, OUTPUT);
        pinMode(12, INPUT_PULLUP);
        pinMode(11, OUTPUT);
    }
    void loop() {
        unsigned long _millis = millis();
        if (_millis > lastMillis + 100) {
            digitalWrite(13, !digitalRead(13));
            lastMillis = _millis;
        }
        digitalWrite(11, !digitalRead(12));
        morse.cycle();
    }
};

// use this so we can store members in the class
MainClass *mainClass;

void setup() {
    // create the MainClass instance here
    Serial.begin(115200);
    mainClass = new MainClass();
    mainClass->setup();
}

void loop() {
    // run the loop of the MainClass instance here
    mainClass->loop();
}
