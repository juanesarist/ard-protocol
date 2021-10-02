#include <Arduino.h>
#include "package/package.h"
#include "dispatcher.h"

Dispatcher::Dispatcher(int led)
{
    this->led = led;
}

void Dispatcher::rojo(int led, Package pack)
{
    uint8_t data = pack.getBuffer()[1];
    if (data == 0x00)
    {
        analogWrite(led, LOW);
    }
    if (data == 0x01)
    {
        digitalWrite(led, HIGH);
    }
}

void Dispatcher::rgb(Package pack)
{
    uint8_t* data = pack.getBuffer();
    analogWrite(9, data[1]);
    analogWrite(10, data[2]);
    analogWrite(11, data[3]);
}


void Dispatcher::dispatch(Package pack)
{
    if (pack.getSize() != 0)
    {
        uint8_t key = pack.getBuffer()[0];
        //Serial.println(key);

        if (key == 0x0A)
        {
            this->rojo(this->led, pack);
        }
        else if (key == 0x00)
        {
            this->rgb(pack);
        }
    }
}