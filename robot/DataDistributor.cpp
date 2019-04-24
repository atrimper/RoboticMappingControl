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
                pc.putc(obstacles[i]);
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
    trajectory = new int[trajectoryLength];

    bool readData = false;
    while(!readData) {
        if(pc.readable()) {
            for(int i = 0; i < trajectoryLength; i++) {
                trajectory[i] = pc.getc();
                wait(0.1);
            }
            readData = true;
        }
    }
    led = 0b0000;
}