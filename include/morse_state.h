class MorseState {
public:
    MorseState() : busy(false),
                   currentChar(0),
                   currentPos(0),
                   lastMillis(0){};
    ~MorseState();

public:
    bool busy;
    char currentChar;
    int currentPos;
    unsigned long lastMillis;
};