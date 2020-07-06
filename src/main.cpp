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
    void setup() {}
    void loop() {
        // if there is data available on Serial port, pass to morse class
        if (Serial.available()) {
            morse.write(Serial.read());
        }
        // run the morse cycle
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
