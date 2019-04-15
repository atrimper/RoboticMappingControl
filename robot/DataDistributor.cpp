#include "DataDistributor.h"
#include "globals.h"

int numTurns = 10;

void DataDistributor::sendObstacles(float* obstacles) {
    bool sentData = false;
    // deallocate obstacles with delete
    while(!sentData) {
        if(!pb) {
            for(int i = 0; i < numTurns; i++) {
                pc.putc(obstacles[i]);
            }
            sentData = true;
        }
    }
    delete[] obstacles;
}

float* DataDistributor::receiveTrajectory() {
    // allocate obstacles with new
    bool readData = false;
    char temp;
    float* pair = new float[2];
    while(!readData) {
        if(pc.readable()) {
            temp = pc.getc();
            if (temp != 0xAA) {
                wait(0.1);
                pair[0] = pc.getc();
                pair[1] = pc.getc();
                readData = true;
            }
        }
    }
    return pair;
}