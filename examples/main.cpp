#include <Arduino.h>
#include "datalink/datalink.h"
#include "package/package.h"


Datalink datalink = Datalink(0x7E, 90);
uint16_t send_freq = 3000;
long timer = millis();

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(1000);
}

Package dataParser(Datalink link, Stream &uart) {
    link.read(uart);
    uint8_t size = link.available();
    if (size){
        return Package(link.getPayload(), size);
    } else {
        return Package(0);
    }
}


void loop() {
    Package pack = dataParser(datalink, Serial);

    if (pack.hasValue(0x0A)){
        Package output = Package(3);
        output.addData(0x0B, pack.getValue(0x0A));
        datalink.send(output.dump(), output.getSize(), Serial);
    }

    if (millis() - timer >= send_freq) {
        timer = millis();
        Package output = Package(3);
        output.addData(0x0A, 10);
        datalink.send(output.dump(), output.getSize(), Serial);
    }

}