#include "morse.h"
#include <Arduino.h>

// this is needed in the class for some reason (declaration)
constexpr uint8_t Morse::MORSE_DICT[][5];

Morse::Morse(uint8_t sendPin, uint8_t receivePin, uint8_t recvFBPin)
    : sendPin(sendPin),
      receivePin(receivePin),
      recvFBPin(recvFBPin) {
    Serial.println("hello from morse");
    static_assert(sizeof(MORSE_DICT) > 0, "MORSE_DICT can't be empty!");
    static_assert(sizeof(MORSE_DICT[0]) > 0, "MORSE_DICT can't be empty!");
}

Morse::~Morse() {}

void Morse::cycle() {
    // run transceive cycle
    transmit();
    receive();
}

void Morse::transmit() {
    // we're not busy sending
    if (!sendState.busy) {
        // there is data available in the send buffer
        if (sendBuf.available()) {
            initTransmitterForSymbol();
            transmitSymbol();
        }
    }
    if (sendState.busy) {
        // check if the symbol/space is already send, if so check for the next
        if (millis() >= sendState.targetMillis) {
            // if we're sending a symbol
            if (sendState.state == MorseState::SENDING_SYMBOL) {
                // common code after sending symbols
                digitalWrite(sendPin, LOW);
                sendState.state = MorseState::SENDING_SPACE;

                // check if there are NO more symbols in this morseIndex
                if (isLastSymbolIndex()) {
                    // last symbol, send LETTER_BREAK
                    sendState.targetMillis += LETTER_BREAK * MORSE_UNIT_LENGTH;
                } else {
                    // there are more symbols, send symbol break (SHORT)
                    sendState.targetMillis += SHORT * MORSE_UNIT_LENGTH;
                }
            } else { // we're sending a space
                if (isLastSymbolIndex()) {
                    // last space, send new character or stop sending
                    // if no characters to send
                    if (sendBuf.available()) {
                        // send new character
                        reInitTransmitterForSymbol();
                        transmitSymbol();
                    } else {
                        sendState.busy = false;
                    }
                } else {
                    // more symbols available
                    // increment index and start sending next symbol
                    sendState.symbolIndex++;
                    transmitSymbol();
                }
            }
        }
    }
}

void Morse::receive() {
    // not implemented
}

const uint8_t *Morse::getMorseEntry(char c) {
    if (c >= 'a' && c <= 'z') {
        return MORSE_DICT[c - 'a']; // [a-z] with index [0-25]
    } else if (c >= 'A' && c <= 'Z') {
        return MORSE_DICT[c - 'A']; // [A-Z] with index [0-25]
    } else if (c >= '0' && c <= '9') {
        return MORSE_DICT[c - '0' + 26]; // [0-9] with index [26-35]
    } else {
        return MORSE_DICT[36]; // index [36] invalid number containing no morse
    }
}

void Morse::initTransmitterForSymbol() {
    sendState.busy = true;
    sendState.targetMillis = millis();
    reInitTransmitterForSymbol();
}

void Morse::reInitTransmitterForSymbol() {
    // get the morse pattern for this character
    sendState.morseIndex = getMorseEntry(sendBuf.get());
    sendState.symbolIndex = 0;
}

void Morse::transmitSymbol() {
    // start sending the symbol
    uint8_t currentSymbol = sendState.morseIndex[sendState.symbolIndex];
    switch (currentSymbol) {
    case SHORT:
        sendState.targetMillis += currentSymbol * MORSE_UNIT_LENGTH;
        digitalWrite(sendPin, HIGH);
        sendState.state = MorseState::SENDING_SYMBOL;
        break;
    case LONG_:
        sendState.targetMillis += currentSymbol * MORSE_UNIT_LENGTH;
        digitalWrite(sendPin, HIGH);
        sendState.state = MorseState::SENDING_SYMBOL;
        break;
    case WORD_BREAK:
        sendState.targetMillis += currentSymbol * MORSE_UNIT_LENGTH;
        digitalWrite(sendPin, LOW); // should already be low
        sendState.state = MorseState::SENDING_SPACE;
        break;
    default:
        // any non-valid symbol results in a WORD_BREAK to sync receiver
        sendState.targetMillis += WORD_BREAK * MORSE_UNIT_LENGTH;
        sendState.symbolIndex = 4;  // forse symbolIndex to 4 to send next character after this
        digitalWrite(sendPin, LOW); // should already be low
        sendState.state = MorseState::SENDING_SPACE;
    }
}

inline bool Morse::isLastSymbolIndex() {
    const int entrySize = sizeof(MORSE_DICT[0]) / sizeof(MORSE_DICT[0][0]);
    return (sendState.symbolIndex >= entrySize - 1 ||
            sendState.morseIndex[sendState.symbolIndex + 1] == NULL_);
}
