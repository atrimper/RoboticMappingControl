#include "Encoder.h"

Encoder::Encoder(PinName trig): _trig(trig) {
    _trig.mode(PullUp);
    _trig.rise(this, &Encoder::increment);
    count = 0;
}

Encoder::~Encoder() {
    delete &_trig;
}

int Encoder::read() {
    return count;
}

void Encoder::reset() {
    count = 0;
}

void Encoder::increment() {
    count = count + 1;   
}