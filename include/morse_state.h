#include <Arduino.h>

class MorseState {
public:
    MorseState() : busy(false),
                   morseIndex(0),
                   symbolIndex(0),
                   targetMillis(0),
                   state(IDLE){};
    ~MorseState();

public:
    enum STATE {
        IDLE,
        SENDING_SYMBOL,
        SENDING_SPACE
    };

    bool busy;
    const uint8_t *morseIndex;
    int symbolIndex;
    unsigned long targetMillis;
    STATE state;
};
