#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "globals.h"
#include "Motor.h"
#include "HALLFX_ENCODER.h"
#include "XNucleo53L0A1.h"

#define COUNTPERIN 75.029 ///< Encoder counts 192 every 65 mm of wheel rotation
#define COUNTPERDEG 1.21 ///< Encoder counts 2.42 every 1 deg of body rotation

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
         * @param leftEncoder mbed pin receiving rotation count from left encoder
         * @param rightEncoder mbed pin receiving rotation count from right encoder
         */
        RobotController(PinName leftWheelPwm, PinName leftWheelFwd,
            PinName leftWheelRev, PinName rightWheelPwm, PinName rightWheelFwd,
            PinName rightWheelRev, PinName leftEncoder, PinName rightEncoder);
    
        /**
         * Detect obstacles in 360-degree field of view around the robot.
         */
        void detectObstacles();

        /**
         * Follow trajectory set by user in C# GUI.
         */
        void followTrajectory();

    private:
        Motor leftWheel;
        Motor rightWheel;
        HALLFX_ENCODER leftEncoder;
        HALLFX_ENCODER rightEncoder;
};

#endif /* ROBOT_CONTROLLER_H */