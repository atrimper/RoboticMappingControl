#include "DataDistributor.h"

void DataDistributor::transmitObstacles() {
    led = 0b0010;
    while(!pb);
    wait(1);
    
    bool sentData = false;
    while(!sentData) {
        if(pc.writeable()) {
            pc.putc('s');
            for(int i = 0; i < 360; i++) {
                if(obstacles[i] >= 120) {
                    pc.putc(120);
                } else {
                    pc.putc(obstacles[i]);
                }
                wait(0.1);
            }
            sentData = true;
        }
    }
    led = 0b0000;
}

void DataDistributor::receiveTrajectory() {
    led = 0b0100;
    while(pc.getc() != 's');
    wait(0.1);
    trajectoryLength = pc.getc();
    wait(0.1);
    trajectory = new int[trajectoryLength * 2];
    
    bool readData = false;
    while(!readData) {
        if(pc.readable()) {
            for(int i = 0; i < trajectoryLength * 2; i += 2) {
                uint8_t aLow = pc.getc();
                wait(0.1);
                uint8_t aHigh = pc.getc();
                wait(0.1);
                uint8_t dLow = pc.getc();
                wait(0.1);
                uint8_t dHigh = pc.getc();
                uint16_t angle = ((uint16_t)aHigh << 8) | aLow;
                uint16_t dist = ((uint16_t)dHigh << 8) | dLow;
                trajectory[i] = (int)angle;
                trajectory[i + 1] = (int)dist;
            }
            readData = true;
        }
    }
    led = 0b0000;
}