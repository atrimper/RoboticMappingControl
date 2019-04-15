#ifndef DATA_DISTRIBUTOR_H
#define DATA_DISTRIBUTOR_H

#include "mbed.h"

/**
 * Distributes data sent over serial communication. This includes data sent from
 * the mbed on the robot to the PC and includes data sent from the PC to the
 * robot.
 */
class DataDistributor {
    public:
        /**
         * Sends angle-distance pairs (angle in degrees, distance in inches) to 
         * a PC through serial communication. Sends a start and end character to
         * signal start and end of data stream.
         *
         * @param obstacles angle-distance pairs
         */
        void sendObstacles(float* obstacles);
        // TODO deallocate obstacles
        
        /**
         * Receives angle-distance pairs from PC through serial communication.
         * Returns a pointer array of these pairs that will later be sent to the
         * robot as trajectories for movement.
         *
         * @return angle-distance pairs
         */
        float* receiveTrajectory();
        // TODO allocate new trajectories
};

#endif /* DATA_DISTRIBUTOR_H */