#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "mbed.h"
#include "Motor.h"
#include "HALLFX_ENCODER.h"
#include "LSM9DS1.h"

/**
 * Robot Controller class.
 */
class RobotController {
    public:
        /**
         * Robot Controller Constructor.
         * @param leftWheelPwm mbed pin transmitting speed to left motor driver
         * @param leftWheelFwd mbed pin transmitting forward direction to left motor driver
         * @param leftWheelRev mbed pin transmitting reverse direction to left motor driver
         * @param rightWheelPwm mbed pin transmitting speed to right motor driver
         * @param rightWheelFwd mbed pin transmitting forward direction to right motor driver
         * @param rightWheelRev mbed pin transmitting reverse direction to right motor driver
         * @param leftEncoderIn mbed pin receiving rotation count from left encoder
         * @param rightEncoderIn mbed pin receiving rotation count from right encoder
         */
        RobotController(PinName leftWheelPwm, PinName leftWheelFwd,
            PinName leftWheelRev, PinName rightWheelPwm, PinName rightWheelFwd,
            PinName rightWheelRev, PinName leftEncoderIn, PinName rightEncoderIn);
    
        /**
         * Detect obstacles in 360-degree field of view around the robot.
         * @return angle-distance pairs of obstacles
         */
        float* obstacleDetection();

        /**
         * Follow trajectory set by user in C# GUI.
         * @param trajectory angle-distance vectors
         */
        void followTrajectory(float* trajectory);

        /**
         * Return to position before following trajectory.
         * @param trajectory angle-distance vectors
         */
        void toOrigin(float* trajectory);
        // TODO delete trajectory

    private:
        Motor leftWheel;
        Motor rightWheel;
        HALLFX_ENCODER leftEncoder;
        HALLFX_ENCODER rightEncoder;
};

#endif /* ROBOT_CONTROLLER_H */