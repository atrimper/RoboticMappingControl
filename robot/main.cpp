#include "globals.h"
#include "DataDistributor.h"
#include "RobotController.h"

Serial pc(USBTX, USBRX);
BusOut led(LED1, LED2, LED3, LED4);
DigitalIn pb(p23);

float* obstacles = new float[360];
int trajectoryLength = 0;
float* trajectory = new float[0];

int main() {
    delete []trajectory;
    DataDistributor dataDistributor;
    RobotController robotController(p21, p15, p16, p22, p18, p19, p13, p14);

    while(1) {
        robotController.detectObstacles();
        dataDistributor.transmitObstacles();
        dataDistributor.receiveTrajectory();
        robotController.followTrajectory();
    }
}