#include "globals.h"
#include "DataDistributor.h"
#include "RobotController.h"

Serial pc(USBTX, USBRX);
BusOut led(LED1, LED2, LED3, LED4);
DigitalIn pb(p23);

int* obstacles = new int[360];
int trajectoryLength = 0;
int* trajectory = new int[0];

int main() {
    delete []trajectory;
    DataDistributor dataDistributor;
    RobotController robotController(p21, p15, p16, p22, p18, p19, p13, p14, p9, p10);

    while(1) {
        robotController.detectObstacles();
        dataDistributor.transmitObstacles();
        dataDistributor.receiveTrajectory();
        robotController.followTrajectory();
    }
}