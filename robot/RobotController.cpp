#include "RobotController.h"

RobotController::RobotController(PinName leftWheelPwm, PinName leftWheelFwd,
    PinName leftWheelRev, PinName rightWheelPwm, PinName rightWheelFwd,
    PinName rightWheelRev, PinName leftEncoderIn, PinName rightEncoderIn) :
    leftWheel(leftWheelPwm, leftWheelFwd, leftWheelRev),
    rightWheel(rightWheelPwm, rightWheelFwd, rightWheelRev),
    leftEncoder(leftEncoderIn), rightEncoder(rightEncoderIn) {
}

float* RobotController::obstacleDetection() {
    
}

void RobotController::followTrajectory(float* trajectory) {
    
}

void RobotController::toOrigin(float* trajectory) {
    
}