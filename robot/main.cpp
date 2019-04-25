#include "globals.h"
#include "DataDistributor.h"
#include "RobotController.h"
#include "XNucleo53L0A1.h"

Serial pc(USBTX, USBRX);
BusOut led(LED1, LED2, LED3, LED4);
DigitalIn pb(p23);
Thread lidarThread;

int* obstacles = new int[360];
int trajectoryLength = 0;
int* trajectory = new int[0];
uint32_t lidarDistance = 0;
bool useImu = false;

void getLidarDistance() {
    DevI2C* lidarDevice = new DevI2C(p28, p27);
    XNucleo53L0A1* lidarBoard = XNucleo53L0A1::instance(lidarDevice, A2, D8, D2);
    DigitalOut _lidarShdn(p26);
    _lidarShdn = 0;
    Thread::wait(100);
    _lidarShdn = 1;
    Thread::wait(100);
    int status = lidarBoard->init_board();
    while (status) {
        status = lidarBoard->init_board();
    }
    while(1) {
        if (!useImu) {
            lidarBoard->sensor_centre->get_distance(&lidarDistance);
        }
    }
}

int main() {
    delete []trajectory;
    DataDistributor dataDistributor;
    RobotController robotController(p21, p15, p16, p22, p18, p19, p13, p14, p28, p27);
    lidarThread.start(getLidarDistance);

    while(1) {
        robotController.detectObstacles();
        dataDistributor.transmitObstacles();
        dataDistributor.receiveTrajectory();
        robotController.followTrajectory();
    }
}