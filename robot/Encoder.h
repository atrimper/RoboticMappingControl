#ifndef ENCODER_H
#define ENCODER_H

#include "globals.h"

/**
 * Hall Effect Encoder (ROB-12629) bare-metal I/O driver class.
 * For more details, visit https://www.sparkfun.com/products/12629
 * Fork of https://os.mbed.com/users/electromotivated/code/HALLFX_ENCODER/
 */
class Encoder{
    public:
        /**
         * Encoder constructor. Connect to 3.3 V.
         * @param trig mbed pin receiving encoder trigger
         */
        Encoder(PinName trig);

        /**
         * Encoder destructor.
         */
        ~Encoder();

        /**
         * Read encoder count.
         * @return encoder count
         */
        int read();

        /**
         * Reset encoder count.
         */
        void reset();

    private:
        int count;
        InterruptIn _trig;
        void increment();
};

#endif /* ENCODER_H */