#include "datalink.h"


Datalink::Datalink(uint8_t header, uint8_t size) {
    this->header = header;
    this->size = size;
    this->buffer = new uint8_t[this->size];
    this->strict = strict;
    this->index = 0;
}

void Datalink::read(Stream &uart) {
    if(uart.available()){
        uint8_t rec_header = uint8_t(uart.read());
        if (rec_header == this->header) {
            uint8_t* length_buffer = new uint8_t[1];
            uart.readBytes(length_buffer, 1);
            uint8_t length = length_buffer[0] + 1;
            uint8_t* buffer = new uint8_t[length];
            uart.readBytes(buffer, length);
            int local_checksum = 0;
            for(int i=0; i <(length - 1); i++){
                local_checksum += buffer[i];
            }
            // Serial.println()
            if(byte(0xFF - local_checksum) == buffer[length - 1]){
                for(int i = 0; i < (length - 1) ; i++) {
                    this->buffer[this->index+i] = buffer[i];
                }
                this->index += length - 1;
                this->in_waiting = true;
                //uart.println(this->index);
            }
        } 
    }
}

uint8_t* Datalink::getPayload(){
    uint8_t* payload = new uint8_t[this->index];
    for(int i=0; i<this->index; i++){
        payload[i] = this->buffer[i];
    }
    this->index=0;
    this->in_waiting = false;
    return payload;
}

void Datalink::send(uint8_t* payload, uint8_t size, Stream &uart) {
    uart.write(this->header);
    uart.write(size);
    uint8_t checksum = 0;
    for(int i=0; i<size; i++) {
        uart.write(payload[i]);
        checksum += payload[i];
    }
    uart.write(byte(0xFF - checksum));
}

uint8_t Datalink::available(){
    return this->index;
}
