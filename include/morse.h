#include "circular_buffer.h"
#include "morse_state.h"
#include <Arduino.h>

class Morse {
public:
    Morse();
    ~Morse();

    void cycle();
    void transmit();
    void receive();

    void printPtrs();   // TEST ONLY!
    void testCircBuf(); // TEST ONLY!

private:
    // configuration parameters
    static constexpr int BUFSIZE = 2;
    static constexpr int MORSE_UNIT_LENGTH = 1000;
    enum {
        IDLE,

    } MORSE_STATE;

    // variables
    CircularBuffer<char, BUFSIZE> sendBuf;
    CircularBuffer<char, BUFSIZE> recvBuf;
    MorseState sendState;

    // morse dictionary
    static constexpr uint8_t NULL_ = 0; // used as terminator of letters/digits
    static constexpr uint8_t SHORT = 1; // same length as LONG_
    static constexpr uint8_t LONG_ = 3; // same length as SHORT
    static constexpr uint8_t LETTER_BREAK = 3;
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
        {SHORT, LONG_, LONG_, LONG_, LONG_}, // 1
        {SHORT, SHORT, LONG_, LONG_, LONG_}, // 2
        {SHORT, SHORT, SHORT, LONG_, LONG_}, // 3
        {SHORT, SHORT, SHORT, SHORT, LONG_}, // 4
        {SHORT, SHORT, SHORT, SHORT, SHORT}, // 5
        {LONG_, SHORT, SHORT, SHORT, SHORT}, // 6
        {LONG_, LONG_, SHORT, SHORT, SHORT}, // 7
        {LONG_, LONG_, LONG_, SHORT, SHORT}, // 8
        {LONG_, LONG_, LONG_, LONG_, SHORT}, // 9
        {LONG_, LONG_, LONG_, LONG_, LONG_}  // 0
    };
};