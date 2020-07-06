template <typename T, int N>
class CircularBuffer {
public:
    CircularBuffer() : putPtr(buffer),
                       getPtr(buffer),
                       pastLastElementPtr(&buffer[N + 1]) {
        static_assert(N > 0, "cant have negative or zero elements!");
    }

    int size() const { return N; }

    // put data in the buffer
    void put(T element) {
        if (putPtr + 1 == pastLastElementPtr) {
            // buffer rols over
            if (getPtr == buffer) {
                return; // buffer is full, element discarded!
            }
        } else {
            // no buffer rollover
            if (putPtr + 1 == getPtr) {
                return; // buffer is full, element discarded!
            }
        }
        // store the element
        *putPtr = element;
        // increment the put pointer
        putPtr++;
        // handle overflow
        if (putPtr == pastLastElementPtr) {
            putPtr = buffer;
        }
    }

    // returns true if data is available in the buffer
    inline bool available() {
        // data is available when the pointers are not equal
        return putPtr != getPtr;
    }

    // get data from the buffer, returns default value when no data available!
    T get() {
        if (available()) {
            // create new element and get the value from the pointer
            T value = *getPtr;
            // increment pointer
            getPtr++;
            // handle overflow
            if (getPtr == pastLastElementPtr) {
                getPtr = buffer;
            }

            return value;
        }
        return T(); // no data available, return default constructor of T!
    }

private:
    // we need 1 additional element to have N usable elements
    T buffer[N + 1];
    T *putPtr;
    T *getPtr;
    // WARNING, this points to 1 position after the buffer!
    T *pastLastElementPtr;
};
