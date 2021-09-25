#ifndef DATALINK
#define DATALINK

#include <stdint.h>
#include <Arduino.h>

class Datalink {
    public:
        Datalink(uint8_t header, uint8_t size);
        void read(Stream &uart);
        uint8_t* getPayload();
        void send(uint8_t* payload, uint8_t size, Stream &uart);
        uint8_t available();
    private:
        uint8_t header;
        uint8_t* buffer;
        uint8_t size;
        uint8_t index;
        bool in_waiting;
        bool strict;
};

#endif