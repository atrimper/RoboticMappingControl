#include "DataDistributor.h"

//int numTurns = 10;

void DataDistributor::transmitObstacles() {
    led = 0b0010;
    while(!pb);
    // transmit s, d_0, ..., d_259, e

//    bool sentData = false;
//    while(!sentData) {
//        if(pc.writeable()) {
//            for(int i = 0; i < numTurns; i++) {
//                pc.putc(obstacles[i]);
//            }
//            sentData = true;
//        }
//    }

    led = 0;
}

void DataDistributor::receiveTrajectory() {
    led = 0b0100;
    while(pc.getc() != 115);
    trajectoryLength = pc.getc();
    trajectory = new float[trajectoryLength];
    // receive s, n, a_0, d_0, ..., a_n, d_n, e

//    bool readData = false;
//    char temp;
//    float* pair = new float[2];
//    while(!readData) {
//        if(pc.readable()) {
//            temp = pc.getc();
//            if (temp != 0xAA) {
//                wait(0.1);
//                pair[0] = pc.getc();
//                pair[1] = pc.getc();
//                readData = true;
//            }
//        }
//    }
//    return pair;

    led = 0;
}