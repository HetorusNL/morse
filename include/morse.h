#include "circular_buffer.h"
#include "morse_state.h"
#include <Arduino.h>

class Morse {
public:
    Morse();
    Morse(uint8_t sendPin, uint8_t receivePin, uint8_t recvFBPin);
    ~Morse();

    // function to be called cyclically that performs the morse transceiving
    void cycle();

    // function to write data (single character)
    inline void write(char character) {
        sendBuf.put(character);
    };

    // function to write data (pointer to NULL terminated character array)
    inline void write(const char *characters) {
        const char *c = characters;
        while (*c != '\0') {
            write(*c);
            c++;
        }
    };

    // function to read data (single character)
    char read();

private:
    // configuration parameters
    static constexpr int BUFSIZE = 32;
    static constexpr int MORSE_UNIT_LENGTH = 150; // in milliseconds

    // variables
    CircularBuffer<char, BUFSIZE> sendBuf;
    CircularBuffer<char, BUFSIZE> recvBuf;
    MorseState sendState;
    uint8_t sendPin;    // defaults to LED pin (13)
    uint8_t receivePin; // defaults to pin 12
    uint8_t recvFBPin;  // defaults to pin 11

    // morse dictionary
    static constexpr uint8_t NULL_ = 0;        // used as terminator of letters/digits
    static constexpr uint8_t SHORT = 1;        // same length as LONG_
    static constexpr uint8_t LONG_ = 3;        // same length as SHORT
    static constexpr uint8_t LETTER_BREAK = 3; // not in morse dictionary!
    static constexpr uint8_t WORD_BREAK = 7;
    static constexpr uint8_t MORSE_DICT[][5] = {
        // letters
        {SHORT, LONG_},               // A
        {LONG_, SHORT, SHORT, SHORT}, // B
        {LONG_, SHORT, LONG_, SHORT}, // C
        {LONG_, SHORT, SHORT},        // D
        {SHORT},                      // E
        {SHORT, SHORT, LONG_, SHORT}, // F
        {LONG_, LONG_, SHORT},        // G
        {SHORT, SHORT, SHORT, SHORT}, // H
        {SHORT, SHORT},               // I
        {SHORT, LONG_, LONG_, LONG_}, // J
        {LONG_, SHORT, LONG_},        // K
        {SHORT, LONG_, SHORT, SHORT}, // L
        {LONG_, LONG_},               // M
        {LONG_, SHORT},               // N
        {LONG_, LONG_, LONG_},        // O
        {SHORT, LONG_, LONG_, SHORT}, // P
        {LONG_, LONG_, SHORT, LONG_}, // Q
        {SHORT, LONG_, SHORT},        // R
        {SHORT, SHORT, SHORT},        // S
        {LONG_},                      // T
        {SHORT, SHORT, LONG_},        // U
        {SHORT, SHORT, SHORT, LONG_}, // V
        {SHORT, LONG_, LONG_},        // W
        {LONG_, SHORT, SHORT, LONG_}, // X
        {LONG_, SHORT, LONG_, LONG_}, // Y
        {LONG_, LONG_, SHORT, SHORT}, // Z
        // numbers
        {LONG_, LONG_, LONG_, LONG_, LONG_}, // 0
        {SHORT, LONG_, LONG_, LONG_, LONG_}, // 1
        {SHORT, SHORT, LONG_, LONG_, LONG_}, // 2
        {SHORT, SHORT, SHORT, LONG_, LONG_}, // 3
        {SHORT, SHORT, SHORT, SHORT, LONG_}, // 4
        {SHORT, SHORT, SHORT, SHORT, SHORT}, // 5
        {LONG_, SHORT, SHORT, SHORT, SHORT}, // 6
        {LONG_, LONG_, SHORT, SHORT, SHORT}, // 7
        {LONG_, LONG_, LONG_, SHORT, SHORT}, // 8
        {LONG_, LONG_, LONG_, LONG_, SHORT}, // 9
        // word seperator (space)
        {WORD_BREAK},
        // invalid (empty) entry
        {},
    };

    // functions

    // init function called by the constructors
    void init();
    // the transmit function that sends pending data via morse code
    void transmit();
    // the receive function that receives data via morse code
    void receive();
    // get the MORSE_DICT entry for the provided character
    const uint8_t *getMorseEntry(char c);
    // function is called when sending first character
    void initTransmitterForSymbol();
    // function is called when sending subsequent characters
    void reInitTransmitterForSymbol();
    // function is called when starting to transmit a symbol
    void transmitSymbol();
    // function to determine if the symbolIndex points to the last symbol
    inline bool isLastSymbolIndex();
};
