#include "mbed.h"
#include "globals.h"
#include "DataDistributor.h"
#include "RobotController.h"

Serial pc(USBTX, USBRX);
DigitalIn pb(p26);

int main() {
    pb.mode(PullUp);
    DataDistributor dataDistributor;
    RobotController robotController(p21, p15, p16, p22, p18, p19, p17, p20);

    while(1) {
        float* obstacles = robotController.obstacleDetection();
        dataDistributor.sendObstacles(obstacles);
        float* trajectory = dataDistributor.receiveTrajectory();
        robotController.followTrajectory(trajectory);
        robotController.toOrigin(trajectory);
    }
}