#ifndef DISPACHER
#define DISPACHER

#include <stdint.h>
#include <Arduino.h>
#include "package/package.h"

class Dispatcher {
    public:
        Dispatcher(int led);
        void rojo(int led, Package pack);
        void rgb(Package pack);
        void multiplicar();
        void division();
        void dispatch(Package pack);
        int led;
};

#endif