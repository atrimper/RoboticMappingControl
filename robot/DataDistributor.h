#ifndef DATA_DISTRIBUTOR_H
#define DATA_DISTRIBUTOR_H

#include "globals.h"

/**
 * Distributes data sent over serial communication. This includes data sent from
 * the mbed on the robot to the PC and includes data sent from the PC to the
 * robot.
 */
class DataDistributor {
    public:
        /**
         * Transmits distances (in inches) to a PC through serial communication.
         * Distances are read from an array where each index corresponds to the
         * angle the distance was read at. Sends a start character to signal
         * start of data stream.
         */
        void transmitObstacles();
        
        /**
         * Receives angle-distance pairs from PC through serial communication.
         * Stores the pairs into an array where even indices correspond to an
         * angle and odd indices correspond to a distance.
         */
        void receiveTrajectory();
};

#endif /* DATA_DISTRIBUTOR_H */