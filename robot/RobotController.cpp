#include "RobotController.h"

RobotController::RobotController(PinName leftWheelPwm, PinName leftWheelFwd,
    PinName leftWheelRev, PinName rightWheelPwm, PinName rightWheelFwd,
    PinName rightWheelRev, PinName leftEncoder, PinName rightEncoder,
    PinName imuSda, PinName imuScl) :
    leftWheel(leftWheelPwm, leftWheelFwd, leftWheelRev),
    rightWheel(rightWheelPwm, rightWheelFwd, rightWheelRev),
    leftEncoder(leftEncoder), rightEncoder(rightEncoder),
    imu(imuSda, imuScl, 0xD6, 0x3C) {
        imu.begin();
        imu.calibrate();
        w1 = 0.0;
        w2 = 0.0;
        t1 = 0.0;
        t2 = 0.0;
}

RobotController::~RobotController() {
    delete &leftWheel;
    delete &rightWheel;
    delete &leftEncoder;
    delete &rightEncoder;
    delete &imu;
    delete &t;
}

void RobotController::detectObstacles() {
    led = 0b0001;
    for (int i = 0; i < 360; i++) {
        leftEncoder.reset();
        rightEncoder.reset();
        t.start();
        leftWheel.speed(0.2);
        rightWheel.speed(-0.2);
//        while((leftEncoder.read() < COUNTPERDEG) && (rightEncoder.read() < COUNTPERDEG));
        while((((w2+w1)/2.0)*(t2-t1)) < 1.0) {
            while(!imu.gyroAvailable());
            imu.readGyro();
            w1 = w2;
            w2 = imu.calcGyro(imu.gz);
            t1 = t2;
            t2 = t.read();
        }
        t.stop();
        leftWheel.speed(0);
        rightWheel.speed(0);
        obstacles[i] = 0; // TODO ping lidar
    }
    led = 0;
}

void RobotController::followTrajectory() {
    led = 0b1000;
    while(!pb);
    for (int i = 0; i < trajectoryLength; i = i + 2) {
        leftEncoder.reset();
        rightEncoder.reset();
        leftWheel.speed(0.2);
        rightWheel.speed(-0.2);
        int angleCount = (int)(trajectory[i]*COUNTPERDEG);
        while((leftEncoder.read() < angleCount) && (rightEncoder.read() < angleCount));
        leftWheel.speed(0);
        rightWheel.speed(0);
        leftEncoder.reset();
        rightEncoder.reset();
        int distanceCount = (int)(trajectory[i + 1]*COUNTPERIN);
        leftWheel.speed(0.2);
        rightWheel.speed(0.2);
        pc.putc(distanceCount);
        while((leftEncoder.read() < distanceCount) && (rightEncoder.read() < distanceCount));
        leftWheel.speed(0);
        rightWheel.speed(0);
    }
    delete []trajectory;
    led = 0;
}