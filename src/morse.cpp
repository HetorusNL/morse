#include "morse.h"
#include <Arduino.h>

// this is needed in the class for some reason (declaration)
constexpr uint8_t Morse::MORSE_DICT[][5];

Morse::Morse() {
    Serial.println("hello from morse");
}

Morse::~Morse() {}

void Morse::cycle() {
    // run transceive cycle
    transmit();
    receive();
}

void Morse::transmit() {
    if (sendState.busy) {
    }
    if (sendBuf.available()) {
        // not implemented
    }
}

void Morse::receive() {
    // not implemented
}

void Morse::testCircBuf() {
    Serial.print("circular buffer size: ");
    Serial.println(sendBuf.size());
    printPtrs();
    Serial.println("putting 'a'");
    sendBuf.put('a');
    Serial.println("putting 'b'");
    sendBuf.put('b');
    Serial.println("putting 'c'");
    sendBuf.put('c');
    printPtrs();
    Serial.print("getting 'a': ");
    Serial.println(sendBuf.get());
    printPtrs();
    Serial.println("putting 'd'");
    sendBuf.put('d');
    Serial.print("getting 'b': ");
    Serial.println(sendBuf.get());
    Serial.print("getting 'd' (c wasn't put in): ");
    Serial.println(sendBuf.get());
    printPtrs();
    Serial.println("putting 'e'");
    sendBuf.put('e');
    Serial.print("getting 'e': ");
    Serial.println(sendBuf.get());
    printPtrs();
}

void Morse::printPtrs() {
    Serial.println("printing circular buffer pointer values");
    // test the circular buffer pointers
    char *put = NULL;
    char *get = NULL;
    char *pastLast = NULL;
    sendBuf.getPtrs(put, get, pastLast);
    Serial.print("put: ");
    Serial.print((int)put);
    Serial.print(",");
    Serial.print((int)*put);
    Serial.print("; get: ");
    Serial.print((int)get);
    Serial.print(",");
    Serial.print((int)*get);
    Serial.print("; pastLast: ");
    Serial.print((int)pastLast);
    Serial.print(",");
    Serial.println((int)*pastLast);
}