#include <Arduino.h>
#include "datalink/datalink.h"
#include "package/package.h"
#include "Dispatcher/dispatcher.h"

Datalink datalink = Datalink(0x7E, 90);
uint16_t send_freq = 3000;
long timer = millis();
int led = 3;
long pot;
uint16_t valor;
Dispatcher dispatcher = Dispatcher(led);

void setup()
{
    Serial.begin(115200);
    Serial.setTimeout(1000);
    pinMode(led, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(led, LOW);
}

Package dataParser(Datalink link, Stream &uart)
{
    link.read(uart);
    uint8_t size = link.available();
    if (size)
    {
        return Package(link.getPayload(), size);
    }
    else
    {
        return Package(0);
    }
}

void loop()
{
    pot = analogRead(A0);
    valor = map(pot, 0, 1023, 0, 254);
    Package pack = dataParser(datalink, Serial);
    dispatcher.dispatch(pack);
    if (pack.getSize() != 0)
    {
        if (pack.getBuffer()[0] == 0x01)
        {
            Package output = Package(3);
            output.addData(0x01, valor);
            datalink.send(output.dump(), output.getSize(), Serial);
        }
    }

    // if (millis() - timer >= send_freq) {
    //     timer = millis();
    //     Package output = Package(3);
    //     output.addData(0x0A, 10);
    //     datalink.send(output.dump(), output.getSize(), Serial);
    // }
}